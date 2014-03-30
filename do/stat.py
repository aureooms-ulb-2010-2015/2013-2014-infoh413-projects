import sys, os, lib



def do(inp, out, script):

	alg = []

	lib.dir.walk(inp, f = lambda x : alg.append(x))

	for i in range(len(alg) - 1):
		for j in range(i+1, len(alg)):
			r, _ = lib.sys.run(script + [alg[i], alg[j]])
			print(r.decode())


if __name__ == '__main__':
	inp = sys.argv[1]
	out = sys.argv[2]
	script = sys.argv[3:]

	do(inp, out, script)

