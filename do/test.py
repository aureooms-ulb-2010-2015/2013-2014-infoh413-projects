import sys, os, lib, functools



def do(inp, out, script):

	alg = []

	lib.dir.walk(inp, f = lambda x : alg.append(x))

	alg = sorted(alg)



	data = [[None for _ in range(len(alg))]] * (len(alg) - 1)

	n = 1

	for i in range(len(alg) - 1):
		for j in range(i+1, len(alg)):
			print('%3d/%3d' % (n, (len(alg)**2 - len(alg))//2), alg[i], alg[j])
			r, _ = lib.sys.run(script + [alg[i], alg[j]])
			r = r.decode().split('\n')
			data[i][j] = float(r[0].split(' ')[1]), float(r[1].split(' ')[1])
			n += 1



	lib.json.pretty({'alg':alg,'data':data}, sys.stdout)


if __name__ == '__main__':
	inp = sys.argv[1]
	out = sys.argv[2]
	script = sys.argv[3:]

	do(inp, out, script)

