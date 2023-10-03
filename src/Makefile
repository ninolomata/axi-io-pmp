# Copyright 2022 University of Minho.
# Copyright and related rights are licensed under the Solderpad Hardware
# License, Version 0.51 (the "License"); you may not use this file except in
# compliance with the License.  You may obtain a copy of the License at
# http://solderpad.org/licenses/SHL-0.51. Unless required by applicable law
# or agreed to in writing, software, hardware and materials distributed under
# this License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
# CONDITIONS OF ANY KIND, either express or implied. See the License for the
# specific language governing permissions and limitations under the License.
#
# Author:      Bruno Sa, <bruno.vilaca.sa@gmail.com>
# Description: Generate registers and top level for iopmp

DIR_NAME ?= $(dir $(realpath $(lastword $(MAKEFILE_LIST))))
PYTHON ?= python3
# Default values for script
XLEN ?= 64
MEM_DOMAINS ?= 2
NR_ENTRIES ?= 8
NR_MASTERS ?= 2

.PHONY: clean

all: iopmp_top iopmp_regs

iopmp_top: iopmp_regs
	$(PYTHON) $(DIR_NAME)/io_pmp.py -d $(MEM_DOMAINS) -e $(NR_ENTRIES)  -m $(NR_MASTERS) -x $(XLEN) $(DIR_NAME)/axi_io_pmp.sv.tpl > axi_io_pmp.sv

iopmp_regs:
	$(PYTHON) $(DIR_NAME)register/reg_axi_io_pmp.py -d $(MEM_DOMAINS) -e $(NR_ENTRIES)  -m $(NR_MASTERS) -x $(XLEN) $(DIR_NAME)register/io_pmp.tpl.hjson > $(DIR_NAME)register/io_pmp.hjson
	@ $(MAKE) -C $(DIR_NAME)register all


clean:
	@cd $(DIR_NAME)../register; rm -rf *.sv *.html *.h; cd -
