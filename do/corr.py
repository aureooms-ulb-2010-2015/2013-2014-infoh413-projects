

import sys, os, lib, functools


tmpfile = '.DAZIUGZD2038ZA_S'

def rscript(f, a, b, out):
	f.write('cost.a <- read.table("%s")$V1\n' % a)
	f.write('cost.b <- read.table("%s")$V1\n' % b)
	f.write('pdf(file="%s", height=6, width=10)\n' % out)
	f.write('plot(cost.a, cost.b, asp=1, pch=19, cex=0.05, main="Relative percentage deviation correlation between the two algorithms.", xlab="%s", ylab="%s")\n' % (a, b))
	f.write('dev.off()\n')

	
def do(inp, out):

	alg = []

	lib.dir.walk(data, f = lambda x : alg.append(x))

	alg = sorted(alg)

	data = []

	with open(tmpfile, 'w') as f:
		rscript(f, alg[0], alg[1], out)
	
	r, _ = lib.sys.run(['Rscript', tmpfile])
	os.remove(tmpfile)

if __name__ == '__main__':
	inp = sys.argv[1]
	out = sys.argv[2]

	do(inp, out)
