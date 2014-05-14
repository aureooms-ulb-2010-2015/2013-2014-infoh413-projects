import sys, os, lib, functools, fileinput

def parse(f):

	f.readline()
	f.readline()
	f.readline()

	yield (0, int(f.readline().split()[1]))

	line = f.readline()
	while line[:4] == 'best':
		line = line.split()

		yield (int(line[5]), int(line[1]))

		line = f.readline()
