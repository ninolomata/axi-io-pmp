// Generated register defines for io_pmp

#ifndef _IO_PMP_REG_DEFS_
#define _IO_PMP_REG_DEFS_

#ifdef __cplusplus
extern "C" {
#endif
// Register width
#define IO_PMP_PARAM_REG_WIDTH 32

// Indicates the IP version and other vendor details.
#define IO_PMP_VERSION_REG_OFFSET 0x0
#define IO_PMP_VERSION_VENDOR_MASK 0xffffff
#define IO_PMP_VERSION_VENDOR_OFFSET 0
#define IO_PMP_VERSION_VENDOR_FIELD \
  ((bitfield_field32_t) { .mask = IO_PMP_VERSION_VENDOR_MASK, .index = IO_PMP_VERSION_VENDOR_OFFSET })
#define IO_PMP_VERSION_SPECVER_MASK 0xff
#define IO_PMP_VERSION_SPECVER_OFFSET 24
#define IO_PMP_VERSION_SPECVER_FIELD \
  ((bitfield_field32_t) { .mask = IO_PMP_VERSION_SPECVER_MASK, .index = IO_PMP_VERSION_SPECVER_OFFSET })

// the implementation ID
#define IO_PMP_IMP_REG_OFFSET 0x4

// Indicates the configurations of current IOPMP instance
#define IO_PMP_HWCFG0_REG_OFFSET 0x8
#define IO_PMP_HWCFG0_MD_NUM_MASK 0x7f
#define IO_PMP_HWCFG0_MD_NUM_OFFSET 0
#define IO_PMP_HWCFG0_MD_NUM_FIELD \
  ((bitfield_field32_t) { .mask = IO_PMP_HWCFG0_MD_NUM_MASK, .index = IO_PMP_HWCFG0_MD_NUM_OFFSET })
#define IO_PMP_HWCFG0_SID_NUM_MASK 0x1ff
#define IO_PMP_HWCFG0_SID_NUM_OFFSET 7
#define IO_PMP_HWCFG0_SID_NUM_FIELD \
  ((bitfield_field32_t) { .mask = IO_PMP_HWCFG0_SID_NUM_MASK, .index = IO_PMP_HWCFG0_SID_NUM_OFFSET })
#define IO_PMP_HWCFG0_ENTRY_NUM_MASK 0x7fff
#define IO_PMP_HWCFG0_ENTRY_NUM_OFFSET 16
#define IO_PMP_HWCFG0_ENTRY_NUM_FIELD \
  ((bitfield_field32_t) { .mask = IO_PMP_HWCFG0_ENTRY_NUM_MASK, .index = IO_PMP_HWCFG0_ENTRY_NUM_OFFSET })
#define IO_PMP_HWCFG0_ENABLE_BIT 31

// Indicates the configurations of current IOPMP instance
#define IO_PMP_HWCFG1_REG_OFFSET 0xc
#define IO_PMP_HWCFG1_TOR_EN_BIT 0
#define IO_PMP_HWCFG1_SPS_EN_BIT 1
#define IO_PMP_HWCFG1_USER_CFG_EN_BIT 2
#define IO_PMP_HWCFG1_PROG_PRIENT_BIT 3
#define IO_PMP_HWCFG1_MODEL_MASK 0xf
#define IO_PMP_HWCFG1_MODEL_OFFSET 4
#define IO_PMP_HWCFG1_MODEL_FIELD \
  ((bitfield_field32_t) { .mask = IO_PMP_HWCFG1_MODEL_MASK, .index = IO_PMP_HWCFG1_MODEL_OFFSET })
#define IO_PMP_HWCFG1_MODEL_VALUE_FULL 0x0
#define IO_PMP_HWCFG1_MODEL_VALUE_RAPID_K 0x1
#define IO_PMP_HWCFG1_MODEL_VALUE_DYNAMIC_K 0x2
#define IO_PMP_HWCFG1_MODEL_VALUE_ISOLATION 0x3
#define IO_PMP_HWCFG1_MODEL_VALUE_COMPACT_K 0x4
#define IO_PMP_HWCFG1_PRIO_ENTRY_MASK 0xffff
#define IO_PMP_HWCFG1_PRIO_ENTRY_OFFSET 16
#define IO_PMP_HWCFG1_PRIO_ENTRY_FIELD \
  ((bitfield_field32_t) { .mask = IO_PMP_HWCFG1_PRIO_ENTRY_MASK, .index = IO_PMP_HWCFG1_PRIO_ENTRY_OFFSET })

// Indicates the internal address offsets of each table.
#define IO_PMP_ENTRY_OFFSET_REG_OFFSET 0x10

// Indicates errors events in the IOPMP IP.
#define IO_PMP_ERRREACT_REG_OFFSET 0x14
#define IO_PMP_ERRREACT_L_BIT 0
#define IO_PMP_ERRREACT_IE_BIT 1
#define IO_PMP_ERRREACT_IP_BIT 2
#define IO_PMP_ERRREACT_IRE_BIT 4
#define IO_PMP_ERRREACT_RRE_MASK 0x7
#define IO_PMP_ERRREACT_RRE_OFFSET 5
#define IO_PMP_ERRREACT_RRE_FIELD \
  ((bitfield_field32_t) { .mask = IO_PMP_ERRREACT_RRE_MASK, .index = IO_PMP_ERRREACT_RRE_OFFSET })
#define IO_PMP_ERRREACT_IWE_BIT 8
#define IO_PMP_ERRREACT_RWE_MASK 0x7
#define IO_PMP_ERRREACT_RWE_OFFSET 9
#define IO_PMP_ERRREACT_RWE_FIELD \
  ((bitfield_field32_t) { .mask = IO_PMP_ERRREACT_RWE_MASK, .index = IO_PMP_ERRREACT_RWE_OFFSET })
#define IO_PMP_ERRREACT_RSV_MASK 0xf
#define IO_PMP_ERRREACT_RSV_OFFSET 12
#define IO_PMP_ERRREACT_RSV_FIELD \
  ((bitfield_field32_t) { .mask = IO_PMP_ERRREACT_RSV_MASK, .index = IO_PMP_ERRREACT_RSV_OFFSET })
#define IO_PMP_ERRREACT_PEE_BIT 28
#define IO_PMP_ERRREACT_RPE_MASK 0x7
#define IO_PMP_ERRREACT_RPE_OFFSET 29
#define IO_PMP_ERRREACT_RPE_FIELD \
  ((bitfield_field32_t) { .mask = IO_PMP_ERRREACT_RPE_MASK, .index = IO_PMP_ERRREACT_RPE_OFFSET })

// The MDSTALL(H) is implemented to support atomicity issue while programming
// the IOPMP,
#define IO_PMP_MDSTALL_REG_OFFSET 0x18
#define IO_PMP_MDSTALL_MD_MASK 0x7fffffff
#define IO_PMP_MDSTALL_MD_OFFSET 0
#define IO_PMP_MDSTALL_MD_FIELD \
  ((bitfield_field32_t) { .mask = IO_PMP_MDSTALL_MD_MASK, .index = IO_PMP_MDSTALL_MD_OFFSET })

// The MDSTALL(H) is implemented to support atomicity issue while programming
// the IOPMP,
#define IO_PMP_MDSTALLH_REG_OFFSET 0x1c
#define IO_PMP_MDSTALLH_MD_MASK 0x7fffffff
#define IO_PMP_MDSTALLH_MD_OFFSET 0
#define IO_PMP_MDSTALLH_MD_FIELD \
  ((bitfield_field32_t) { .mask = IO_PMP_MDSTALLH_MD_MASK, .index = IO_PMP_MDSTALLH_MD_OFFSET })

// The SIDSCP is implemented to support atomicity issue while programming the
// IOPMP,
#define IO_PMP_SIDSCP_REG_OFFSET 0x20
#define IO_PMP_SIDSCP_SID_MASK 0xffff
#define IO_PMP_SIDSCP_SID_OFFSET 0
#define IO_PMP_SIDSCP_SID_FIELD \
  ((bitfield_field32_t) { .mask = IO_PMP_SIDSCP_SID_MASK, .index = IO_PMP_SIDSCP_SID_OFFSET })
#define IO_PMP_SIDSCP_OP_STAT_MASK 0x3
#define IO_PMP_SIDSCP_OP_STAT_OFFSET 30
#define IO_PMP_SIDSCP_OP_STAT_FIELD \
  ((bitfield_field32_t) { .mask = IO_PMP_SIDSCP_OP_STAT_MASK, .index = IO_PMP_SIDSCP_OP_STAT_OFFSET })

// Bitmap field register low bits to indicate which MDs are locked.
#define IO_PMP_MDLCK_REG_OFFSET 0x24
#define IO_PMP_MDLCK_L_BIT 0
#define IO_PMP_MDLCK_MD_MASK 0x7fffffff
#define IO_PMP_MDLCK_MD_OFFSET 1
#define IO_PMP_MDLCK_MD_FIELD \
  ((bitfield_field32_t) { .mask = IO_PMP_MDLCK_MD_MASK, .index = IO_PMP_MDLCK_MD_OFFSET })

// Bitmap field register high bits to indicate which MDs are locked.
#define IO_PMP_MDLCKH_REG_OFFSET 0x28

// Lock Register for MDCFG table.
#define IO_PMP_MDCFGLCK_REG_OFFSET 0x2c
#define IO_PMP_MDCFGLCK_L_BIT 0
#define IO_PMP_MDCFGLCK_F_MASK 0x7f
#define IO_PMP_MDCFGLCK_F_OFFSET 1
#define IO_PMP_MDCFGLCK_F_FIELD \
  ((bitfield_field32_t) { .mask = IO_PMP_MDCFGLCK_F_MASK, .index = IO_PMP_MDCFGLCK_F_OFFSET })

// Lock register for entry array.
#define IO_PMP_ENTRYLCK_REG_OFFSET 0x30
#define IO_PMP_ENTRYLCK_L_BIT 0
#define IO_PMP_ENTRYLCK_F_MASK 0x7fff
#define IO_PMP_ENTRYLCK_F_OFFSET 1
#define IO_PMP_ENTRYLCK_F_FIELD \
  ((bitfield_field32_t) { .mask = IO_PMP_ENTRYLCK_F_MASK, .index = IO_PMP_ENTRYLCK_F_OFFSET })

// Indicate the errored request address low bits.
#define IO_PMP_ERR_REQADDR_REG_OFFSET 0x60

// Indicate the errored request address high bits.
#define IO_PMP_ERR_REQADDRH_REG_OFFSET 0x64

// Indicate the errored SID.
#define IO_PMP_ERR_REQSID_REG_OFFSET 0x68
#define IO_PMP_ERR_REQSID_SID_MASK 0xffff
#define IO_PMP_ERR_REQSID_SID_OFFSET 0
#define IO_PMP_ERR_REQSID_SID_FIELD \
  ((bitfield_field32_t) { .mask = IO_PMP_ERR_REQSID_SID_MASK, .index = IO_PMP_ERR_REQSID_SID_OFFSET })

// Captures more detailed error infomation.
#define IO_PMP_ERR_REQINFO_REG_OFFSET 0x6c
#define IO_PMP_ERR_REQINFO_NO_HIT_BIT 0
#define IO_PMP_ERR_REQINFO_PAR_HIT_BIT 1
#define IO_PMP_ERR_REQINFO_EID_MASK 0x3ffffff
#define IO_PMP_ERR_REQINFO_EID_OFFSET 6
#define IO_PMP_ERR_REQINFO_EID_FIELD \
  ((bitfield_field32_t) { .mask = IO_PMP_ERR_REQINFO_EID_MASK, .index = IO_PMP_ERR_REQINFO_EID_OFFSET })
#define IO_PMP_ERR_REQINFO_TYPE_ERR_MASK 0x7
#define IO_PMP_ERR_REQINFO_TYPE_ERR_OFFSET 8
#define IO_PMP_ERR_REQINFO_TYPE_ERR_FIELD \
  ((bitfield_field32_t) { .mask = IO_PMP_ERR_REQINFO_TYPE_ERR_MASK, .index = IO_PMP_ERR_REQINFO_TYPE_ERR_OFFSET })

// MDCFG table is a lookup to specify the number of IOPMP entries that is
// associated with each MD. (common parameters)
#define IO_PMP_MDCFG_T_FIELD_WIDTH 16
#define IO_PMP_MDCFG_T_FIELDS_PER_REG 2
#define IO_PMP_MDCFG_MULTIREG_COUNT 1

// MDCFG table is a lookup to specify the number of IOPMP entries that is
// associated with each MD.
#define IO_PMP_MDCFG_REG_OFFSET 0x800
#define IO_PMP_MDCFG_T_0_MASK 0xffff
#define IO_PMP_MDCFG_T_0_OFFSET 0
#define IO_PMP_MDCFG_T_0_FIELD \
  ((bitfield_field32_t) { .mask = IO_PMP_MDCFG_T_0_MASK, .index = IO_PMP_MDCFG_T_0_OFFSET })
#define IO_PMP_MDCFG_T_1_MASK 0xffff
#define IO_PMP_MDCFG_T_1_OFFSET 16
#define IO_PMP_MDCFG_T_1_FIELD \
  ((bitfield_field32_t) { .mask = IO_PMP_MDCFG_T_1_MASK, .index = IO_PMP_MDCFG_T_1_OFFSET })

// Bitmapped MD enable register low bits for source 0.
#define IO_PMP_SRCMD_EN0_REG_OFFSET 0x1000
#define IO_PMP_SRCMD_EN0_L_BIT 0
#define IO_PMP_SRCMD_EN0_MD_MASK 0x7fffffff
#define IO_PMP_SRCMD_EN0_MD_OFFSET 1
#define IO_PMP_SRCMD_EN0_MD_FIELD \
  ((bitfield_field32_t) { .mask = IO_PMP_SRCMD_EN0_MD_MASK, .index = IO_PMP_SRCMD_EN0_MD_OFFSET })

// Bitmapped MD enable register high bits for source 0.
#define IO_PMP_SRCMD_ENH0_REG_OFFSET 0x1004

// (Optional) Bitmapped MD read enable register low bits for source 0,
#define IO_PMP_SRCMD_R0_REG_OFFSET 0x1008
#define IO_PMP_SRCMD_R0_MD_MASK 0x7fffffff
#define IO_PMP_SRCMD_R0_MD_OFFSET 1
#define IO_PMP_SRCMD_R0_MD_FIELD \
  ((bitfield_field32_t) { .mask = IO_PMP_SRCMD_R0_MD_MASK, .index = IO_PMP_SRCMD_R0_MD_OFFSET })

// (Optional)Bitmapped MD read enable register high bits for source 0,
#define IO_PMP_SRCMD_RH0_REG_OFFSET 0x100c

// (Optional)Bitmapped MD write enable register low bits for source 0,
#define IO_PMP_SRCMD_W0_REG_OFFSET 0x1010
#define IO_PMP_SRCMD_W0_MD_MASK 0x7fffffff
#define IO_PMP_SRCMD_W0_MD_OFFSET 1
#define IO_PMP_SRCMD_W0_MD_FIELD \
  ((bitfield_field32_t) { .mask = IO_PMP_SRCMD_W0_MD_MASK, .index = IO_PMP_SRCMD_W0_MD_OFFSET })

// (Optional)Bitmapped MD write eanble register high bits for source 0,
#define IO_PMP_SRCMD_WH0_REG_OFFSET 0x1014

// Bitmapped MD enable register low bits for source 1.
#define IO_PMP_SRCMD_EN1_REG_OFFSET 0x1018
#define IO_PMP_SRCMD_EN1_L_BIT 0
#define IO_PMP_SRCMD_EN1_MD_MASK 0x7fffffff
#define IO_PMP_SRCMD_EN1_MD_OFFSET 1
#define IO_PMP_SRCMD_EN1_MD_FIELD \
  ((bitfield_field32_t) { .mask = IO_PMP_SRCMD_EN1_MD_MASK, .index = IO_PMP_SRCMD_EN1_MD_OFFSET })

// Bitmapped MD enable register high bits for source 1.
#define IO_PMP_SRCMD_ENH1_REG_OFFSET 0x101c

// (Optional) Bitmapped MD read enable register low bits for source 1,
#define IO_PMP_SRCMD_R1_REG_OFFSET 0x1020
#define IO_PMP_SRCMD_R1_MD_MASK 0x7fffffff
#define IO_PMP_SRCMD_R1_MD_OFFSET 1
#define IO_PMP_SRCMD_R1_MD_FIELD \
  ((bitfield_field32_t) { .mask = IO_PMP_SRCMD_R1_MD_MASK, .index = IO_PMP_SRCMD_R1_MD_OFFSET })

// (Optional)Bitmapped MD read enable register high bits for source 1,
#define IO_PMP_SRCMD_RH1_REG_OFFSET 0x1024

// (Optional)Bitmapped MD write enable register low bits for source 1,
#define IO_PMP_SRCMD_W1_REG_OFFSET 0x1028
#define IO_PMP_SRCMD_W1_MD_MASK 0x7fffffff
#define IO_PMP_SRCMD_W1_MD_OFFSET 1
#define IO_PMP_SRCMD_W1_MD_FIELD \
  ((bitfield_field32_t) { .mask = IO_PMP_SRCMD_W1_MD_MASK, .index = IO_PMP_SRCMD_W1_MD_OFFSET })

// (Optional)Bitmapped MD write eanble register high bits for source 1,
#define IO_PMP_SRCMD_WH1_REG_OFFSET 0x102c

// Bitmapped MD enable register low bits for source 2.
#define IO_PMP_SRCMD_EN2_REG_OFFSET 0x1030
#define IO_PMP_SRCMD_EN2_L_BIT 0
#define IO_PMP_SRCMD_EN2_MD_MASK 0x7fffffff
#define IO_PMP_SRCMD_EN2_MD_OFFSET 1
#define IO_PMP_SRCMD_EN2_MD_FIELD \
  ((bitfield_field32_t) { .mask = IO_PMP_SRCMD_EN2_MD_MASK, .index = IO_PMP_SRCMD_EN2_MD_OFFSET })

// Bitmapped MD enable register high bits for source 2.
#define IO_PMP_SRCMD_ENH2_REG_OFFSET 0x1034

// (Optional) Bitmapped MD read enable register low bits for source 2,
#define IO_PMP_SRCMD_R2_REG_OFFSET 0x1038
#define IO_PMP_SRCMD_R2_MD_MASK 0x7fffffff
#define IO_PMP_SRCMD_R2_MD_OFFSET 1
#define IO_PMP_SRCMD_R2_MD_FIELD \
  ((bitfield_field32_t) { .mask = IO_PMP_SRCMD_R2_MD_MASK, .index = IO_PMP_SRCMD_R2_MD_OFFSET })

// (Optional)Bitmapped MD read enable register high bits for source 2,
#define IO_PMP_SRCMD_RH2_REG_OFFSET 0x103c

// (Optional)Bitmapped MD write enable register low bits for source 2,
#define IO_PMP_SRCMD_W2_REG_OFFSET 0x1040
#define IO_PMP_SRCMD_W2_MD_MASK 0x7fffffff
#define IO_PMP_SRCMD_W2_MD_OFFSET 1
#define IO_PMP_SRCMD_W2_MD_FIELD \
  ((bitfield_field32_t) { .mask = IO_PMP_SRCMD_W2_MD_MASK, .index = IO_PMP_SRCMD_W2_MD_OFFSET })

// (Optional)Bitmapped MD write eanble register high bits for source 2,
#define IO_PMP_SRCMD_WH2_REG_OFFSET 0x1044

// Bitmapped MD enable register low bits for source 3.
#define IO_PMP_SRCMD_EN3_REG_OFFSET 0x1048
#define IO_PMP_SRCMD_EN3_L_BIT 0
#define IO_PMP_SRCMD_EN3_MD_MASK 0x7fffffff
#define IO_PMP_SRCMD_EN3_MD_OFFSET 1
#define IO_PMP_SRCMD_EN3_MD_FIELD \
  ((bitfield_field32_t) { .mask = IO_PMP_SRCMD_EN3_MD_MASK, .index = IO_PMP_SRCMD_EN3_MD_OFFSET })

// Bitmapped MD enable register high bits for source 3.
#define IO_PMP_SRCMD_ENH3_REG_OFFSET 0x104c

// (Optional) Bitmapped MD read enable register low bits for source 3,
#define IO_PMP_SRCMD_R3_REG_OFFSET 0x1050
#define IO_PMP_SRCMD_R3_MD_MASK 0x7fffffff
#define IO_PMP_SRCMD_R3_MD_OFFSET 1
#define IO_PMP_SRCMD_R3_MD_FIELD \
  ((bitfield_field32_t) { .mask = IO_PMP_SRCMD_R3_MD_MASK, .index = IO_PMP_SRCMD_R3_MD_OFFSET })

// (Optional)Bitmapped MD read enable register high bits for source 3,
#define IO_PMP_SRCMD_RH3_REG_OFFSET 0x1054

// (Optional)Bitmapped MD write enable register low bits for source 3,
#define IO_PMP_SRCMD_W3_REG_OFFSET 0x1058
#define IO_PMP_SRCMD_W3_MD_MASK 0x7fffffff
#define IO_PMP_SRCMD_W3_MD_OFFSET 1
#define IO_PMP_SRCMD_W3_MD_FIELD \
  ((bitfield_field32_t) { .mask = IO_PMP_SRCMD_W3_MD_MASK, .index = IO_PMP_SRCMD_W3_MD_OFFSET })

// (Optional)Bitmapped MD write eanble register high bits for source 3,
#define IO_PMP_SRCMD_WH3_REG_OFFSET 0x105c

// IOPMP entrie number 0 low bits of physical address of protected memory
// region
#define IO_PMP_ENTRY_ADDR0_REG_OFFSET 0x2000

// IOPMP entrie number 0 high bits of physical address of protected memory
// region
#define IO_PMP_ENTRY_ADDRH0_REG_OFFSET 0x2004

// IOPMP entrie number 0 configuration register.
#define IO_PMP_ENTRY_CFG0_REG_OFFSET 0x2008
#define IO_PMP_ENTRY_CFG0_R_BIT 0
#define IO_PMP_ENTRY_CFG0_X_BIT 0
#define IO_PMP_ENTRY_CFG0_W_BIT 1
#define IO_PMP_ENTRY_CFG0_A_MASK 0x3
#define IO_PMP_ENTRY_CFG0_A_OFFSET 3
#define IO_PMP_ENTRY_CFG0_A_FIELD \
  ((bitfield_field32_t) { .mask = IO_PMP_ENTRY_CFG0_A_MASK, .index = IO_PMP_ENTRY_CFG0_A_OFFSET })

// Users defined additional IOPMP check rules entriy 0
#define IO_PMP_ENTRY_USER_CFG0_REG_OFFSET 0x200c

// IOPMP entrie number 1 low bits of physical address of protected memory
// region
#define IO_PMP_ENTRY_ADDR1_REG_OFFSET 0x2010

// IOPMP entrie number 1 high bits of physical address of protected memory
// region
#define IO_PMP_ENTRY_ADDRH1_REG_OFFSET 0x2014

// IOPMP entrie number 1 configuration register.
#define IO_PMP_ENTRY_CFG1_REG_OFFSET 0x2018
#define IO_PMP_ENTRY_CFG1_R_BIT 0
#define IO_PMP_ENTRY_CFG1_X_BIT 0
#define IO_PMP_ENTRY_CFG1_W_BIT 1
#define IO_PMP_ENTRY_CFG1_A_MASK 0x3
#define IO_PMP_ENTRY_CFG1_A_OFFSET 3
#define IO_PMP_ENTRY_CFG1_A_FIELD \
  ((bitfield_field32_t) { .mask = IO_PMP_ENTRY_CFG1_A_MASK, .index = IO_PMP_ENTRY_CFG1_A_OFFSET })

// Users defined additional IOPMP check rules entriy 1
#define IO_PMP_ENTRY_USER_CFG1_REG_OFFSET 0x201c

// IOPMP entrie number 2 low bits of physical address of protected memory
// region
#define IO_PMP_ENTRY_ADDR2_REG_OFFSET 0x2020

// IOPMP entrie number 2 high bits of physical address of protected memory
// region
#define IO_PMP_ENTRY_ADDRH2_REG_OFFSET 0x2024

// IOPMP entrie number 2 configuration register.
#define IO_PMP_ENTRY_CFG2_REG_OFFSET 0x2028
#define IO_PMP_ENTRY_CFG2_R_BIT 0
#define IO_PMP_ENTRY_CFG2_X_BIT 0
#define IO_PMP_ENTRY_CFG2_W_BIT 1
#define IO_PMP_ENTRY_CFG2_A_MASK 0x3
#define IO_PMP_ENTRY_CFG2_A_OFFSET 3
#define IO_PMP_ENTRY_CFG2_A_FIELD \
  ((bitfield_field32_t) { .mask = IO_PMP_ENTRY_CFG2_A_MASK, .index = IO_PMP_ENTRY_CFG2_A_OFFSET })

// Users defined additional IOPMP check rules entriy 2
#define IO_PMP_ENTRY_USER_CFG2_REG_OFFSET 0x202c

// IOPMP entrie number 3 low bits of physical address of protected memory
// region
#define IO_PMP_ENTRY_ADDR3_REG_OFFSET 0x2030

// IOPMP entrie number 3 high bits of physical address of protected memory
// region
#define IO_PMP_ENTRY_ADDRH3_REG_OFFSET 0x2034

// IOPMP entrie number 3 configuration register.
#define IO_PMP_ENTRY_CFG3_REG_OFFSET 0x2038
#define IO_PMP_ENTRY_CFG3_R_BIT 0
#define IO_PMP_ENTRY_CFG3_X_BIT 0
#define IO_PMP_ENTRY_CFG3_W_BIT 1
#define IO_PMP_ENTRY_CFG3_A_MASK 0x3
#define IO_PMP_ENTRY_CFG3_A_OFFSET 3
#define IO_PMP_ENTRY_CFG3_A_FIELD \
  ((bitfield_field32_t) { .mask = IO_PMP_ENTRY_CFG3_A_MASK, .index = IO_PMP_ENTRY_CFG3_A_OFFSET })

// Users defined additional IOPMP check rules entriy 3
#define IO_PMP_ENTRY_USER_CFG3_REG_OFFSET 0x203c

// IOPMP entrie number 4 low bits of physical address of protected memory
// region
#define IO_PMP_ENTRY_ADDR4_REG_OFFSET 0x2040

// IOPMP entrie number 4 high bits of physical address of protected memory
// region
#define IO_PMP_ENTRY_ADDRH4_REG_OFFSET 0x2044

// IOPMP entrie number 4 configuration register.
#define IO_PMP_ENTRY_CFG4_REG_OFFSET 0x2048
#define IO_PMP_ENTRY_CFG4_R_BIT 0
#define IO_PMP_ENTRY_CFG4_X_BIT 0
#define IO_PMP_ENTRY_CFG4_W_BIT 1
#define IO_PMP_ENTRY_CFG4_A_MASK 0x3
#define IO_PMP_ENTRY_CFG4_A_OFFSET 3
#define IO_PMP_ENTRY_CFG4_A_FIELD \
  ((bitfield_field32_t) { .mask = IO_PMP_ENTRY_CFG4_A_MASK, .index = IO_PMP_ENTRY_CFG4_A_OFFSET })

// Users defined additional IOPMP check rules entriy 4
#define IO_PMP_ENTRY_USER_CFG4_REG_OFFSET 0x204c

// IOPMP entrie number 5 low bits of physical address of protected memory
// region
#define IO_PMP_ENTRY_ADDR5_REG_OFFSET 0x2050

// IOPMP entrie number 5 high bits of physical address of protected memory
// region
#define IO_PMP_ENTRY_ADDRH5_REG_OFFSET 0x2054

// IOPMP entrie number 5 configuration register.
#define IO_PMP_ENTRY_CFG5_REG_OFFSET 0x2058
#define IO_PMP_ENTRY_CFG5_R_BIT 0
#define IO_PMP_ENTRY_CFG5_X_BIT 0
#define IO_PMP_ENTRY_CFG5_W_BIT 1
#define IO_PMP_ENTRY_CFG5_A_MASK 0x3
#define IO_PMP_ENTRY_CFG5_A_OFFSET 3
#define IO_PMP_ENTRY_CFG5_A_FIELD \
  ((bitfield_field32_t) { .mask = IO_PMP_ENTRY_CFG5_A_MASK, .index = IO_PMP_ENTRY_CFG5_A_OFFSET })

// Users defined additional IOPMP check rules entriy 5
#define IO_PMP_ENTRY_USER_CFG5_REG_OFFSET 0x205c

// IOPMP entrie number 6 low bits of physical address of protected memory
// region
#define IO_PMP_ENTRY_ADDR6_REG_OFFSET 0x2060

// IOPMP entrie number 6 high bits of physical address of protected memory
// region
#define IO_PMP_ENTRY_ADDRH6_REG_OFFSET 0x2064

// IOPMP entrie number 6 configuration register.
#define IO_PMP_ENTRY_CFG6_REG_OFFSET 0x2068
#define IO_PMP_ENTRY_CFG6_R_BIT 0
#define IO_PMP_ENTRY_CFG6_X_BIT 0
#define IO_PMP_ENTRY_CFG6_W_BIT 1
#define IO_PMP_ENTRY_CFG6_A_MASK 0x3
#define IO_PMP_ENTRY_CFG6_A_OFFSET 3
#define IO_PMP_ENTRY_CFG6_A_FIELD \
  ((bitfield_field32_t) { .mask = IO_PMP_ENTRY_CFG6_A_MASK, .index = IO_PMP_ENTRY_CFG6_A_OFFSET })

// Users defined additional IOPMP check rules entriy 6
#define IO_PMP_ENTRY_USER_CFG6_REG_OFFSET 0x206c

// IOPMP entrie number 7 low bits of physical address of protected memory
// region
#define IO_PMP_ENTRY_ADDR7_REG_OFFSET 0x2070

// IOPMP entrie number 7 high bits of physical address of protected memory
// region
#define IO_PMP_ENTRY_ADDRH7_REG_OFFSET 0x2074

// IOPMP entrie number 7 configuration register.
#define IO_PMP_ENTRY_CFG7_REG_OFFSET 0x2078
#define IO_PMP_ENTRY_CFG7_R_BIT 0
#define IO_PMP_ENTRY_CFG7_X_BIT 0
#define IO_PMP_ENTRY_CFG7_W_BIT 1
#define IO_PMP_ENTRY_CFG7_A_MASK 0x3
#define IO_PMP_ENTRY_CFG7_A_OFFSET 3
#define IO_PMP_ENTRY_CFG7_A_FIELD \
  ((bitfield_field32_t) { .mask = IO_PMP_ENTRY_CFG7_A_MASK, .index = IO_PMP_ENTRY_CFG7_A_OFFSET })

// Users defined additional IOPMP check rules entriy 7
#define IO_PMP_ENTRY_USER_CFG7_REG_OFFSET 0x207c

#ifdef __cplusplus
}  // extern "C"
#endif
#endif  // _IO_PMP_REG_DEFS_
// End generated register defines for io_pmp