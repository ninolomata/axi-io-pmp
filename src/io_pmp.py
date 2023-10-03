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
    parser.add_argument('--domains', '-d', type=int,
                        default="2",
                        help='Number of Memory Domains')
    parser.add_argument('--entries', '-e', type=int,
                        default=8,
                        help='Number of Entries per Domain')
    parser.add_argument('--masters', '-m', type=int,
                        default=4,
                        help='Number of masters')
    parser.add_argument('--xlen', '-x', type=int,
                        default=64,
                        help='xlen')

    args = parser.parse_args()

    # Determine output: if stdin then stdout if not then ??
    out = StringIO()

    reg_tpl = Template(args.input.read())
    out.write(reg_tpl.render(mem_domains=args.domains,
                             nr_entries=args.entries,
                             nr_masters=args.masters,
                             xlen=args.xlen))

    print(out.getvalue())

    out.close()

if __name__ == "__main__":
    main()

