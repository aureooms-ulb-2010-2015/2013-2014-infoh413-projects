import sys, os, lib, functools


tmpfile = '.DAZIUGZD2038ZA_S'

def rscript(f, a, b):
	f.write('a.cost <- read.table("%s")$V1\n' % a)
	f.write('b.cost <- read.table("%s")$V1\n' % b)
	f.write('t <- t.test (a.cost, b.cost, paired=T)$p.value\n')
	f.write('w <- wilcox.test (a.cost, b.cost, paired=T)$p.value\n')
	f.write('print(t)\n')
	f.write('print(w)\n')


def do(inp):

	alg = []

	lib.dir.walk(inp, f = lambda x : alg.append(x))

	alg = sorted(alg)

	data = []

	for i in range(len(alg)-1) : data.append([None for _ in range(len(alg))])

	with open(tmpfile, 'w') as f:
		for i in range(len(alg) - 1):
			for j in range(i+1, len(alg)):
				rscript(f, alg[i], alg[j])

	r, _ = lib.sys.run(['Rscript', tmpfile])
	os.remove(tmpfile)
	r = r.decode().split('\n')

	k = 0

	for i in range(len(alg) - 1):
		for j in range(i+1, len(alg)):
			data[i][j] = float(r[k].split(' ')[1]), float(r[k+1].split(' ')[1])
			k += 2

	lib.json.pretty([alg, data], sys.stdout)


if __name__ == '__main__':
	inp = sys.argv[1]

	do(inp)

