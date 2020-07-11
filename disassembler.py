#!/usr/bin/python
import os
import sys
import struct
from termcolor import colored, cprint

yellow =  lambda x: cprint(x, 'yellow', end="")

green = lambda x: cprint(x, "green", attrs=["bold"], end="")
red = lambda x: cprint(x, "red", attrs=["bold"], end="")
blue = lambda x: cprint(x, "blue", attrs=["bold"], end="")
cyan = lambda x: cprint(x, "cyan", attrs=["bold"], end="")


IND_SIZE = 2
REG_SIZE = 2
DIR_SIZE = REG_SIZE
IND_CODE = 3

REG_NUMBER = 16

T_REG = 1
T_DIR = 2
T_IND = 4
T_LAB = 8

SYMBOLS = [
	"live",
	"ld",
	"st",
	"add",
	"sub",
	"and",
	"or",
	"xor",
	"zjmp",
	"ldi",
	"sti",
	"fork",
	"lld",
	"lldi",
	"lfork",
	"aff"
]

if len(sys.argv) != 2:
	red("python dissambler.py <filename>\n")
	exit(1)


try:
	file = open(sys.argv[1], "r")
	buffer = file.read()
	file.close()

except IOError:
	print("The assembler file does not exist")
	sys.exit(1)

if len(buffer) < 0x890:
	print("The header of the assembly file is not complete")
	sys.exit(1)

if struct.unpack("<I", buffer[:4])[0] != 0xf383ea00:
	print("File format does not match Core War assembler")
	sys.exit(1)

def get_param_type(value, begin, end):
	return

print("Nom du champion: {}".format(buffer[4:132]).replace('\x00', ''))
comment = buffer[140:2180].replace('\x00', '')
print("Commentaire: \"{}\"\n".format(comment))

get_param = lambda params, offset: (params >> offset & 3)

ocp_required = lambda opcode: not any(map(lambda each: each == opcode, [0x01, 0x09, 0x0c, 0xf]))

get_dir_size = lambda opcode: 2 if opcode in [0x9, 0xa, 0xb, 0xc, 0xe, 0xf] else 4

code = buffer[0x890:]
offset = 0

while offset < len(code):
	parameters = []
	opcode = ord(code[offset])
	dir_size = get_dir_size(opcode)

	sys.stdout.write("{:#x}:\t".format(offset))
	offset += 1
	yellow("{} ".format(SYMBOLS[opcode - 1]))
	if ocp_required(opcode):
		ocp = ord(code[offset])
		parameters.append(get_param(ocp, 6))
		parameters.append(get_param(ocp, 4))
		parameters.append(get_param(ocp, 2))
		offset += 1
	elif not ocp_required(opcode): parameters.append(T_DIR)

	for index in range(0, 3):
		comments = []
		if index >= len(parameters): break ;
		if not parameters[index]: break ;
		if index > 0: sys.stdout.write(',')
		if parameters[index] == T_REG:
			register_number = str(ord(code[offset]))
			red(" r{}".format(register_number))
			offset += 1
		if parameters[index] == T_IND - 1:
			shift = offset
			short = struct.unpack(">h", code[shift:(shift + IND_SIZE)])[0]
			blue(" %{:#x}".format(short))
			offset += IND_SIZE
		if parameters[index] == T_DIR:
			shift = offset
			schema = ">i" if dir_size == 4 else ">h"
			integer = struct.unpack(schema, code[shift:(shift + dir_size)])[0]
			if not ocp_required(opcode):
				if opcode == 0x9:
					comments.append("Jump to {} bytes from here".format(integer))
				cyan(" *{:#x}".format(integer))
			else:
				green(" %{:#x}".format(integer))
			offset += dir_size
		if len(comments) > 0:
			green("\t\t\t# ")
			for i in range(0, len(comments)):
				if i > 0: sys.stdout.write(',')
				green(comments[i])
	sys.stdout.write('\n')
