#!/usr/bin/env python

import argparse

def binary(num, length=8):
    return format(num, '#0{}b'.format(length + 2))

def ip2bin(ip_str, is_hex):
    ip_bin = ""
    for byte in ip_str.split('.'):
        if is_hex:
            ip_bin += f"{binary(int(byte, 16))} " 
        else:
            ip_bin += f"{binary(int(byte))} " 
    print(ip_bin.replace("0b", ""))

parser = argparse.ArgumentParser()
parser.add_argument('--ip', dest='dec_ip', required=False, type=str, help='IP address (binary)')
parser.add_argument('--hex', dest='hex_ip', required=False, type=str, help='IP address (hex)')
args = parser.parse_args()

if (args.dec_ip):
    ip2bin(args.dec_ip, False)
    exit(0)

if (args.hex_ip):
    ip2bin(args.hex_ip, True)
    exit(0)

print("No IP given.")
