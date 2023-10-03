#!/usr/bin/env python3
# Copyright lowRISC contributors.
# Licensed under the Apache License, Version 2.0, see LICENSE for details.
# SPDX-License-Identifier: Apache-2.0

r"""Mako template to hjson register description
"""
import sys
import argparse
from io import StringIO

from mako.template import Template

def main():
    parser = argparse.ArgumentParser(prog="reg_axi_io_pmp")
    parser.add_argument('input', nargs='?', metavar='file',
                        type=argparse.FileType('r'),
                        default=sys.stdin,
                        help='input template file')
    parser.add_argument('--version', '-v', type=int,
                        default="0",
                        help='Version number')
    parser.add_argument('--enable_tor', '-t', type=int,
                        default="1",
                        help='Enable TOR support')
    parser.add_argument('--enable_sps', '-s', type=int,
                        default="1",
                        help='Enable Secondary permission settings support')
    parser.add_argument('--enable_usr_cfg', '-u', type=int,
                        default="1",
                        help='Enable user customized attributes support')
    parser.add_argument('--model', '-l', type=int,
                        default="0",
                        help='''
                            Indicate the model:
                             - 0x0: Full model: the number of MDCFG registers is equal to HWCFG.md_num,
                                    all MDCFG registers are readable and writable.
                             - 0x1: Rapid-k model: a single MDCFG register to indicate the k value,
                                    read only.
                             - 0x2: Dynamic-k model: a single MDCFG register to indicate the k value,
                                    readable and writable.
                             - 0x3: Isolation model: the number of MDCFG registers is equal to
                                    HWCFG.md_num, all MDCFG registers are readable and writable.
                             - 0x4 Compact-k model: a single MDCFG register to indicate the k value,
                                   read only.''')
    parser.add_argument('--entry_offset', '-o', type=int,
                        default="8192",
                        help='Offset address of the IOPMP array')
    parser.add_argument('--domains', '-d', type=int,
                        default="2",
                        help='Number of Memory Domains')
    parser.add_argument('--entries', '-e', type=int,
                        default=8,
                        help='Number of Entries')
    parser.add_argument('--masters', '-m', type=int,
                        default=4,
                        help='Number of masters')

    args = parser.parse_args()

    # Determine output: if stdin then stdout if not then ??
    out = StringIO()

    reg_tpl = Template(args.input.read())
    out.write(reg_tpl.render(
                             version=args.version,
                             enable_tor=args.enable_tor,
                             enable_sps=args.enable_sps,
                             enable_usr_cfg=args.enable_usr_cfg,
                             model=args.model,
                             mem_domains=args.domains,
                             entry_offset=args.entry_offset,
                             nr_entries=args.entries,
                             nr_masters=args.masters))

    print(out.getvalue())

    out.close()

if __name__ == "__main__":
    main()

