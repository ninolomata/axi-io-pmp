// Copyright 2022 ETH Zurich and University of Bologna.
// Copyright and related rights are licensed under the Solderpad Hardware
// License, Version 0.51 (the "License"); you may not use this file except in
// compliance with the License.  You may obtain a copy of the License at
// http://solderpad.org/licenses/SHL-0.51. Unless required by applicable law
// or agreed to in writing, software, hardware and materials distributed under
// this License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
// CONDITIONS OF ANY KIND, either express or implied. See the License for the
// specific language governing permissions and limitations under the License.
//
// Author:      Andreas Kuster, <kustera@ethz.ch>
// Author:      Francisco Marques
// Author:      Bruno Sá
// Description: Traditional style AXI IO-PMP module

module axi_io_pmp import io_pmp_reg_pkg::*; #(
    // width of data bus in bits
    parameter int unsigned DATA_WIDTH     = 64,
    // width of address bus in bits
    parameter int unsigned ADDR_WIDTH     = 64,
    // width of strobe (width of data bus in words)
    parameter int unsigned STRB_WIDTH     = (DATA_WIDTH / 8),
    // width of id signal
    parameter int unsigned ID_WIDTH       = 8,
    // propagate awuser signal
    parameter int unsigned USER_WIDTH     = 0,
    // AXI channel structs
    parameter type         axi_aw_chan_t  = logic,
    parameter type         axi_w_chan_t   = logic,
    parameter type         axi_b_chan_t   = logic,
    parameter type         axi_ar_chan_t  = logic,
    parameter type         axi_r_chan_t   = logic,
    // AXI request/response
    parameter type         axi_req_t      = logic,
    parameter type         axi_rsp_t      = logic,
    // register interface request/response
    parameter type         reg_req_t      = logic,
    parameter type         reg_rsp_t      = logic,
    parameter int          XLEN           = 64,
    // PMP parameters TODO: better naming (i.e for the person that instantiates them)
    parameter int unsigned PLEN           = (XLEN == 64) ? 56 : 34, // rv64: 56, rv32: 34
    parameter int unsigned PMP_LEN        = (XLEN == 64) ? 54 : 32, // rv64: 54, rv32: 32
    parameter int unsigned PMPGranularity = 10,                // 2**(G+2) = 4K
    // Implementation specific parameters
    parameter int unsigned NR_MD = ${mem_domains},
    parameter int unsigned NR_ENTRIES_PER_MD = ${nr_entries},
    parameter int unsigned NR_MASTERS = ${nr_masters},
    // AXI parameters
    // maximum number of AXI bursts outstanding at the same time
    parameter int unsigned MaxTxns        = 32'd2
) (
    // rising-edge clock 
    input  logic     clk_i,
    // asynchronous reset, active low
    input  logic     rst_ni,
    // slave port
    input  axi_req_t slv_req_i,
    output axi_rsp_t slv_rsp_o,
    // master port
    output axi_req_t mst_req_o,
    input  axi_rsp_t mst_rsp_i,
    // configuration port
    input  reg_req_t cfg_req_i,
    output reg_rsp_t cfg_rsp_o,
    // enable test/dev modes of the different modules
    input  logic     devmode_i
);
  // Allow to select the:
  //
  // Device configuration and status registers
  //
  io_pmp_reg_pkg::io_pmp_reg2hw_t io_pmp_reg2hw;
  io_pmp_reg_pkg::io_pmp_hw2reg_t io_pmp_hw2reg;
  reg_req_t cfg_req_mod;
  reg_rsp_t cfg_rsp_mod;
  // IOPMP Logic signals
  logic                                 clear_illcgt_d, clear_illcgt_q;
  logic [(NR_ENTRIES_PER_MD*NR_MD)-1:0] match;
  logic                                 allow_transaction;
  axi_req_t                             slv_req_tmp;

  io_pmp_reg_top #(
      .reg_req_t(reg_req_t),
      .reg_rsp_t(reg_rsp_t)
  ) i_io_pmp_reg_top (
      .clk_i,
      .rst_ni,
      .devmode_i,  // if 1, explicit error return for unmapped register access
      // register interface
      .reg_req_i(cfg_req_mod),
      .reg_rsp_o(cfg_rsp_mod),
      // from registers to hardware 
      .hw2reg   (io_pmp_hw2reg),
      .reg2hw   (io_pmp_reg2hw)
  );


  //
  // Read channel PMP
  //
  logic [PLEN-1:0] pmp_addr_r;
  logic allow_r;

  // check boundaries and assemble allow signal
  // TODO: for now, we expect granularity of 4K i.e. we can do the PMP check in one cycle for the whole burst and only have to check if the AXI 4k boundary constraint has been followed. Later, we can multi-cycle check and allow smaller granularity levels (or us the burst splitter)
  always_comb begin

    // reject by default
    allow_r = 1'b0;
    pmp_addr_r = slv_req_i.ar.addr[PLEN-1:0]; // extract relevant address to check, default (for BURST_WRAP, we have to compute the base address first!)

    case (slv_req_i.ar.burst)
      axi_pkg::BURST_FIXED: begin
        // reading from same location: simply check that base_addr + burst_size does not cross the 4K boundary
        if ((slv_req_i.ar.addr & 12'hfff) + (1'b1 << slv_req_i.ar.size) < (1'b1 << 12)) begin
          allow_r = allow_transaction;
        end else begin  // boundary violation
          allow_r = 1'b0;
        end

      end
      axi_pkg::BURST_WRAP: begin
        // wrap_boundary = (start_address/(number_bytes*burst_length)) * (number_bytes*burst_length)
        // address_n = wrap_boundary + (number_bytes * burst_length)
        logic [11:0] wrap_boundary, address_n;

        // by spec, burst lenth must be e {2, 4, 8, 16}
        logic [2:0] log2_len;
        case (slv_req_i.ar.len)
          8'd2: log2_len = 3'b001;
          8'd4: log2_len = 3'b010;
          8'd8: log2_len = 3'b011;
          8'd16: log2_len = 3'b100;
          default: log2_len = 3'b111;  // invalid
        endcase

        wrap_boundary = (slv_req_i.ar.addr >> (log2_len + slv_req_i.ar.size)) << (log2_len + slv_req_i.ar.size);
        // address_n = wrap_boundary + (slv_req_i.ar.len << slv_req_i.ar.size);

        pmp_addr_r = wrap_boundary; // BURST_WRAP has to check from the wrap_boundary aka lower bound address

        if(log2_len != 3'b111 && (wrap_boundary & 12'hfff) + (slv_req_i.ar.len << slv_req_i.ar.size) < (1'b1 << 12) ) begin
          allow_r = allow_transaction;
        end else begin
          allow_r = 1'b0;
        end

      end
      axi_pkg::BURST_INCR: begin
        // check if burst is within 4K range
        if((slv_req_i.ar.addr & 12'hfff) + (slv_req_i.ar.len << slv_req_i.ar.size) < (1'b1 << 12)) begin
          allow_r = allow_transaction;
        end else begin  // boundary violation
          allow_r = 1'b0;
        end
      end
    endcase
  end


  //
  // Write channel PMP
  //
  logic [PLEN-1:0] pmp_addr_w;
  logic allow_w;

  // check boundaries and assemble allow signal
  // TODO: for now, we expect granularity of 4K i.e. we can do the PMP check in one cycle for the whole burst and only have to check if the AXI 4k boundary constraint has been followed. Later, we can multi-cycle check and allow smaller granularity levels (or us the burst splitter)
  always_comb begin

    // reject by default
    allow_w = 1'b0;
    pmp_addr_w = slv_req_i.aw.addr[PLEN-1:0]; // extract relevant address to check, default (for BURST_WRAP, we have to compute the base address first!)
    slv_req_tmp = slv_req_i;
    if( slv_req_i.ar_valid)
      slv_req_tmp.aw_valid = 1'b0;
    case (slv_req_i.aw.burst)
      axi_pkg::BURST_FIXED: begin
        // writing to same location: simply check that base_addr + burst_size does not cross the 4K boundary
        if ((slv_req_i.aw.addr & 12'hfff) + (1'b1 << slv_req_i.aw.size) < (1'b1 << 12)) begin
          allow_w = allow_transaction;
        end else begin  // boundary violation
          allow_w = 1'b0;
        end

      end
      axi_pkg::BURST_WRAP: begin

        // wrap_boundary = (start_address/(number_bytes*burst_length)) * (number_bytes*burst_length) // lower address
        // address_n = wrap_boundary + (number_bytes * burst_length) // upper address
        logic [11:0] wrap_boundary, address_n;

        // by spec, burst lenth must be e {2, 4, 8, 16}
        logic [2:0] log2_len;
        case (slv_req_i.aw.len)
          8'd2: log2_len = 3'b001;
          8'd4: log2_len = 3'b010;
          8'd8: log2_len = 3'b011;
          8'd16: log2_len = 3'b100;
          default: log2_len = 3'b111;  // invalid
        endcase

        wrap_boundary = (slv_req_i.aw.addr >> (log2_len + slv_req_i.aw.size)) << (log2_len + slv_req_i.aw.size);
        // address_n = wrap_boundary + (slv_req_i.aw.len << slv_req_i.aw.size);

        pmp_addr_w = wrap_boundary; // BURST_WRAP has to check from the wrap_boundary aka lower bound address

        if(log2_len != 3'b111 && (wrap_boundary & 12'hfff) + (slv_req_i.aw.len << slv_req_i.aw.size) < (1'b1 << 12) ) begin
          allow_w = allow_transaction;
        end else begin
          allow_w = 1'b0;
        end
      end
      axi_pkg::BURST_INCR: begin
        // check if burst is within 4K range
        if((slv_req_i.aw.addr & 12'hfff) + (slv_req_i.aw.len << slv_req_i.aw.size) < (1'b1 << 12)) begin
          allow_w = allow_transaction;
        end else begin  // boundary violation
          allow_w = 1'b0;
        end
      end
    endcase
  end

  //
  // Demultiplex between authorized and unauthorized transactions
  //
  axi_req_t error_req;
  axi_rsp_t error_rsp;
  axi_demux #(
      .AxiIdWidth (ID_WIDTH),
      .aw_chan_t  (axi_aw_chan_t),
      .w_chan_t   (axi_w_chan_t),
      .b_chan_t   (axi_b_chan_t),
      .ar_chan_t  (axi_ar_chan_t),
      .r_chan_t   (axi_r_chan_t),
      .req_t      (axi_req_t),
      .resp_t     (axi_rsp_t),
      .NoMstPorts (2),
      .MaxTrans   (MaxTxns),
      .AxiLookBits(ID_WIDTH),       // TODO: not sure what this is?
      .FallThrough(1'b0),           // TODO: check what the right value is for them
      .SpillAw    (1'b0),
      .SpillW     (1'b0),
      .SpillB     (1'b0),
      .SpillAr    (1'b0),
      .SpillR     (1'b0)
  ) i_axi_demux (
      .clk_i,
      .rst_ni,
      .test_i         (devmode_i),
      .slv_aw_select_i(allow_w),
      .slv_ar_select_i(allow_r),
      .slv_req_i      (slv_req_tmp),
      .slv_resp_o     (slv_rsp_o),
      .mst_reqs_o     ({mst_req_o, error_req}),  // { 1: mst, 0: error }
      .mst_resps_i    ({mst_rsp_i, error_rsp})   // { 1: mst, 0: error }
  );


  //
  // Respond to unauthorized transactions with slave errors
  //
  axi_err_slv #(
      .AxiIdWidth(ID_WIDTH),
      .req_t(axi_req_t),
      .resp_t(axi_rsp_t),
      .Resp(axi_pkg::RESP_SLVERR),  // error generated by this slave.
      .RespWidth(DATA_WIDTH),  // data response width, gets zero extended or truncated to r.data.
      .RespData(64'hCA11AB1EBADCAB1E),  // hexvalue for data return value
      .ATOPs(1'b1),
      .MaxTrans(1)
  ) i_axi_err_slv (
      .clk_i,
      .rst_ni,
      .test_i    (devmode_i),
      .slv_req_i (error_req),
      .slv_resp_o(error_rsp)
  );

    // -----------------------------
    // Configuration Registers Update Logic
    // -----------------------------

    always_comb begin
      // write: default pass through
      cfg_req_mod.addr  = cfg_req_i.addr;
      cfg_req_mod.write = cfg_req_i.write;
      cfg_req_mod.wdata = cfg_req_i.wdata;
      cfg_req_mod.wstrb = cfg_req_i.wstrb;
      cfg_req_mod.valid = cfg_req_i.valid;
      // enable always writes to the IOPMP CFG Registers
      for(int i = 0; i < 8; i++) begin
        io_pmp_hw2reg.pmp_cfg_0[i].de = 1'b1;
        io_pmp_hw2reg.pmp_cfg_1[i].de = 1'b1;
      end
      // enable always writes to the IOPMP SRC MD Registers
      for(int i = 0; i < NR_MASTERS; i++) begin
          io_pmp_hw2reg.pmp_srcmd[i].de = 1'b1;
      end

      // written from APB bus - gets priority
      if (cfg_req_i.write) begin
        case (cfg_req_i.addr) inside
          io_pmp_reg_pkg::IO_PMP_IOPMP_CTL_OFFSET: begin
            // block writes when IOPMPCTL is locked
            if(~io_pmp_reg2hw.iopmp_ctl.l) begin
                cfg_req_mod.write = 1'b0;
            end
          end
          io_pmp_reg_pkg::IO_PMP_IOPMP_RCD_OFFSET: begin
            // Write 1 to clear (W1C)
            if(cfg_req_i.wdata[0] == 1) begin
                clear_illcgt_d = 1'b1;
            end
          end
          % if xlen == 32:
          io_pmp_reg_pkg::IO_PMP_IOPMP_MDMSK_LO_OFFSET,
          io_pmp_reg_pkg::IO_PMP_IOPMP_MDMSK_HI_OFFSET: begin
            if(~io_pmp_reg2hw.iopmp_mdmsk_hi.l) begin
              cfg_req_mod.write = 1'b0;
            end
          end
          % else:
          io_pmp_reg_pkg::IO_PMP_IOPMP_MDMSK_OFFSET: begin
            if(~io_pmp_reg2hw.iopmp_mdmsk.l) begin
              cfg_req_mod.write = 1'b0;
            end
          end
          % endif
          % for i in range(mem_domains):
          [io_pmp_reg_pkg::IO_PMP_IOPMP_ADDR_0_OFFSET+${i*nr_entries*(xlen//8)}:io_pmp_reg_pkg::IO_PMP_IOPMP_ADDR_0_OFFSET+${(i + 1)*((nr_entries * (xlen//8))-1)}]: begin
            automatic int index_addr = (cfg_req_i.addr - IO_PMP_IOPMP_ADDR_${i*nr_entries}_OFFSET);
            automatic int index_cfg = index_addr >> ${(xlen//16)};
            if(index_addr < ${nr_entries}) begin
              if (!(!io_pmp_reg2hw.pmp_cfg_${1}[index_cfg][7] && !(io_pmp_reg2hw.pmp_cfg_${1}[index_cfg + 1][7] && io_pmp_reg2hw.pmp_cfg_${1}[index_cfg + 1][4:3] == riscv::TOR))) cfg_req_mod.write = 1'b0;
            end else if (index_addr == ${nr_entries}) begin
              if (io_pmp_reg2hw.pmp_cfg_${1}[${nr_entries}][7])  cfg_req_mod.write = 1'b0;
            end
          end
          % endfor
          % for i in range(mem_domains):
          io_pmp_reg_pkg::IO_PMP_PMP_CFG_${i}_OFFSET: begin
            automatic int index_cfg = (cfg_req_i.addr - io_pmp_reg_pkg::IO_PMP_PMP_CFG_${i}_OFFSET) & ~(${(xlen//8) - 1});
            for (int i = 0; i < XLEN/8; i++) if (!io_pmp_reg2hw.pmp_cfg_${i}[index_cfg][7]) io_pmp_hw2reg.pmp_cfg_${i}[index_cfg].d  = cfg_req_mod.wdata[i*8+:8];
          end
          % endfor
          % for i in range(nr_masters-1):
          io_pmp_reg_pkg::IO_PMP_PMP_SRCMD_${i+1}_OFFSET,
          % endfor
          io_pmp_reg_pkg::IO_PMP_PMP_SRCMD_0_OFFSET: begin
              automatic int index_src_addr = (cfg_req_i.addr - io_pmp_reg_pkg::IO_PMP_PMP_SRCMD_0_OFFSET);
              io_pmp_hw2reg.pmp_srcmd[index_src_addr].d = (cfg_req_mod.wdata & (~io_pmp_reg2hw.iopmp_mdmsk.md)) | io_pmp_reg2hw.pmp_srcmd[index_src_addr].q;
          end
          default:;
        endcase
      end
    end

    // -----------------------------
    // Configuration Registers Read Logic
    // -----------------------------

    //
    // RISC-V Privilege Specs:
    //  - "When G ≥ 2 and pmpcfgi.A[1] is set, i.e. the mode is NAPOT, then bits pmpaddri[G-2:0] read as all ones."
    //  - "When G ≥ 1 and pmpcfgi.A[1] is clear, i.e. the mode is OFF or TOR, then bits pmpaddri[G-1:0] read as all zeros."
    //

    always_comb begin
      // read: default pass through
      cfg_rsp_o.rdata   = cfg_rsp_mod.rdata;
      cfg_rsp_o.error   = cfg_rsp_mod.error;
      cfg_rsp_o.ready   = cfg_rsp_mod.ready;
      if (!cfg_req_i.write) begin
        // modify response with granularity > 0
        % for i in range(mem_domains) :
        if(PMPGranularity > 0 && cfg_req_i.addr >= io_pmp_reg_pkg::IO_PMP_IOPMP_ADDR_${nr_entries*i}_OFFSET && cfg_req_i.addr < io_pmp_reg_pkg::IO_PMP_IOPMP_ADDR_${(nr_entries*(i+1))-1}_OFFSET + ${xlen//8}) begin
          automatic int index = '0;
          if (!cfg_req_i.write) begin  // read access
            index = (cfg_req_i.addr - io_pmp_reg_pkg::IO_PMP_IOPMP_ADDR_${nr_entries*i}_OFFSET) >> 3;

            if(!io_pmp_reg2hw.pmp_cfg_${i}[index][4] &&  PMPGranularity >= 1) begin  // riscv::OFF or riscv::TOR -> force 0 for bits [G-1:0] where G is the granularity
              cfg_rsp_o.rdata[PMPGranularity-1:0] = {PMPGranularity{1'b0}};
            end

            if(io_pmp_reg2hw.pmp_cfg_${i}[index][4] &&  PMPGranularity >= 2) begin // riscv::NAPOT -> force 1 for bits [G-2:0] where G is the granularity
              cfg_rsp_o.rdata[PMPGranularity-2:0] = {(PMPGranularity - 1) {1'b1}};
            end

          end  
        end
        % endfor
      end
    end

    // -----------------------------
    // IOPMP Logic
    // -----------------------------
    // Rule Checker
    logic [PLEN-1:0] pmp_addr;
    assign pmp_addr = slv_req_i.ar_valid ? pmp_addr_r : pmp_addr_w;
    % for i in range(mem_domains):
    for(genvar i = 0; i < NR_ENTRIES_PER_MD; i = i + 1) begin
        automatic logic [PMP_LEN-1:0] conf_addr_prev;

        assign conf_addr_prev = (i == 0) ? '0 : io_pmp_reg2hw.iopmp_addr[${i*nr_entries}+i-1];

          pmp_entry #(
              .PLEN    ( PLEN    ),
              .PMP_LEN ( PMP_LEN )
          ) i_pmp_entry(
              .addr_i           ( pmp_addr                                          ),
              .conf_addr_i      ( io_pmp_reg2hw.iopmp_addr[${i*nr_entries}+i]                       ),
              .conf_addr_prev_i ( conf_addr_prev                                      ),
              .conf_addr_mode_i ( io_pmp_reg2hw.pmp_cfg_${i}[${i*nr_entries}+i][4:3]                    ),
              .match_o          ( match[${i*nr_entries}+i]                                          )
          );
    end
    % endfor

    // MD discovery, Rule checker evaluation, Execute response.
    riscv::pmp_access_t access_type;
    logic[ID_WIDTH-1:0] sid;

    assign access_type = slv_req_i.ar_valid ? riscv::ACCESS_READ : riscv::ACCESS_WRITE;
    assign sid         = slv_req_i.ar_valid ? slv_req_i.ar.id : slv_req_i.aw.id;

    always_comb begin
        automatic logic [((NR_ENTRIES_PER_MD*NR_MD) - 1):0][7:0] iopmp_cfg;
        % for i in range(mem_domains):
        for(integer i = 0; i < NR_ENTRIES_PER_MD; i++) begin
          iopmp_cfg[i+${i*nr_entries}] = io_pmp_hw2reg.pmp_cfg_${i}[i];
        end
        % endfor
        io_pmp_hw2reg.iopmp_rcd.sid.d      = io_pmp_reg2hw.iopmp_rcd.sid.q & {!clear_illcgt_q, {31{1'h1}}};
        io_pmp_hw2reg.iopmp_rcd.read.d     = io_pmp_reg2hw.iopmp_rcd.read.q;
        io_pmp_hw2reg.iopmp_rcd.length.d   = io_pmp_reg2hw.iopmp_rcd.length.q;
        io_pmp_hw2reg.iopmp_rcd.extra.d    = io_pmp_reg2hw.iopmp_rcd.extra.q;
        io_pmp_hw2reg.iopmp_rcd.illcgt.d   = io_pmp_reg2hw.iopmp_rcd.illcgt.q;
        // enable write by default
        io_pmp_hw2reg.iopmp_rcd.sid.de     = 1'b1;
        io_pmp_hw2reg.iopmp_rcd.read.de    = 1'b1;
        io_pmp_hw2reg.iopmp_rcd.length.de  = 1'b1;
        io_pmp_hw2reg.iopmp_rcd.extra.de   = 1'b1;
        io_pmp_hw2reg.iopmp_rcd.illcgt.de  = 1'b1;

        % if xlen == 32 :
        io_pmp_hw2reg.iopmp_rcd_lo.d       = io_pmp_reg2hw.iopmp_rcd_lo.q;
        io_pmp_hw2reg.iopmp_rcd_hi.d       = io_pmp_reg2hw.iopmp_rcd_hi.q;
        // enable write by default
        io_pmp_hw2reg.iopmp_rcd_lo.de      = 1'b1;
        io_pmp_hw2reg.iopmp_rcd_hi.de      = 1'b1;
        % else :
        io_pmp_hw2reg.iopmp_rcd_addr.d       = io_pmp_reg2hw.iopmp_rcd_addr.q;
        io_pmp_hw2reg.iopmp_rcd_addr.de      = 1'b1;
        % endif

        allow_transaction                  = 1'b0;
        // Evaluate if IOPMP device is enbaled. Otherwise block every transaction.
        if(io_pmp_reg2hw.iopmp_ctl.enable) begin   
            if(NR_ENTRIES_PER_MD*NR_MD > 0) begin
                for(integer i = 0; i < NR_MD; i++) begin
                    automatic int handler = (io_pmp_reg2hw.iopmp_mdcfg[i].t - NR_ENTRIES_PER_MD);
                    for(integer j = 0; j < NR_ENTRIES_PER_MD; j++) begin
                        //Evalute if there is any match
                        if(match[handler])begin
                            // Evaluate if MD is enabled for the current SID. And the access type
                            if (((access_type & iopmp_cfg[handler][2:0]) != access_type) | !io_pmp_hw2reg.pmp_srcmd[sid][i]) begin
                                allow_transaction = 1'b0;
                                // Store the illegal transaction if this field is enabled
                                if(iopmp_cfg[handler][3]) begin
                                    if (io_pmp_reg2hw.iopmp_ctl.rcall | (!io_pmp_reg2hw.iopmp_ctl.rcall & !io_pmp_reg2hw.iopmp_rcd.illcgt)) begin
                                        io_pmp_hw2reg.iopmp_rcd.illcgt.d  = 1'b1;
                                        io_pmp_hw2reg.iopmp_rcd.extra.d    = '0;
                                        io_pmp_hw2reg.iopmp_rcd.length.d   = '0;
                                        io_pmp_hw2reg.iopmp_rcd.read.d    = (access_type == riscv::ACCESS_READ)? 1'b1: 1'b0;
                                        io_pmp_hw2reg.iopmp_rcd.sid.d     = {{12{1'b0}}, sid};
                                        % if xlen == 32 :
                                        io_pmp_hw2reg.iopmp_rcd_lo.d[31:0]  = cfg_req_i.addr[31:0];
                                        io_pmp_hw2reg.iopmp_rcd_lo.d[63:32]  = cfg_req_i.addr[63:32] ;
                                        % else :
                                        io_pmp_hw2reg.iopmp_rcd_addr.d = cfg_req_i.addr;
                                        % endif
                                    end 
                                end                                
                            end else begin
                                allow_transaction = 1'b1;
                            end
                            break;
                        end
                        handler += 1;
                    end
                end
            end else begin
                allow_transaction = 1'b1;
            end
        end else begin
            allow_transaction = 1'b0;
        end
    end
    // Sequential circuit
    always @(posedge clk_i or negedge rst_ni) begin
        if (!rst_ni) begin
            clear_illcgt_q <= 0;
        end else begin
            clear_illcgt_q <= clear_illcgt_d;
        end
    end

  //
  // Assumptions and assertions
  //
`ifndef VERILATOR
`ifndef SYNTHESIS
  // pragma translate_off
  if (PMPGranularity < 10)  // check IO-PMP granularity restrictions
    $fatal(1, "AXI IO-PMP only supports granularity >= 4K");
  // pragma translate_on
`endif
`endif

endmodule
