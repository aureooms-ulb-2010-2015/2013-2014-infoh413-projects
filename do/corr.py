

import sys, os, lib, functools

from util import abbr

tmpfile = '.DAZIUGZD2038ZA_S'
tmpdata1 = '.DAZIUGZD2038ZA_S72YETGVDY'
tmpdata2 = '.DAZIUGZD2038ZA_SDH28DC'

def rscript(f, a, b, out, nbJob, nbMac, x, y):
	f.write('cost.a <- read.table("%s")$V1\n' % a)
	f.write('cost.b <- read.table("%s")$V1\n' % b)
	f.write('svg(file="%s", height=6, width=10)\n' % out)
	f.write('plot(cost.a,')
	f.write('cost.b,')
	f.write('main="Relative percentage deviation correlation between the two algorithms (%s x %s) .",' % (nbJob, nbMac))
	f.write('xlab="%s",' % abbr(x.split('/')[-1].replace('_', '/')))
	f.write('ylab="%s"' % abbr(y.split('/')[-1].replace('_', '/')))
	f.write(')\n')
	f.write('dev.off()\n')

def patch(alg, tmp, n, d):
	a = [0] * d
	with open(alg) as f:
		for i in range(n):
			a[i%d] += float(f.readline())

	with open(tmp, 'w') as f:
		for i in range(d):
			f.write(str(a[i] / (n / d)))
			f.write(os.linesep)

	
def do(inp, out):

	alg = []

	lib.dir.walk(inp, f = lambda x : alg.append(x))

	alg = sorted(alg)

	nbJob, nbMac = inp.split('/')[-2].split('x')

	patch(alg[0], tmpdata1, 50, 10)
	patch(alg[1], tmpdata2, 50, 10)


	with open(tmpfile, 'w') as f:
		rscript(f, tmpdata1, tmpdata2, out, nbJob, nbMac, alg[0], alg[1])
	
	r, e = lib.sys.run(['Rscript', tmpfile])

	os.remove(tmpfile)
	os.remove(tmpdata1)
	os.remove(tmpdata2)


	print(r.decode())
	print(e.decode())

if __name__ == '__main__':
	inp = sys.argv[1]
	out = sys.argv[2]

	do(inp, out)
