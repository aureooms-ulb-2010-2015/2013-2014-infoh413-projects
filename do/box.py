import sys, os, lib, functools

from util import abbr


tmpfile = '.DAZIUGZD2038ZA_S'

def rscript(f, a, b, out, nbJob, nbMac):
	f.write('cost.a <- read.table("%s")$V1\n' % a)
	f.write('cost.b <- read.table("%s")$V1\n' % b)
	f.write('svg(file="%s", height=6, width=10)\n' % out)
	f.write('boxplot(cost.a, cost.b,')
	f.write('main="Relative percentage deviation boxplot for both algorithms (%s x %s) .",' % (nbJob, nbMac))
	f.write('ylab="Relative percentage deviation",')
	f.write('names=c("%s","%s"),' % (abbr(a.split('/')[-1].replace('_', '/')), abbr(b.split('/')[-1].replace('_', '/'))))
	f.write('notch=FALSE, col=c("red","blue"),')
	f.write('xlab="Algorithm"')
	f.write(')\n')
	f.write('dev.off()\n')

def do(inp, out):

	alg = []

	lib.dir.walk(inp, f = lambda x : alg.append(x))

	alg = sorted(alg)

	nbJob, nbMac = inp.split('/')[-2].split('x')

	with open(tmpfile, 'w') as f:
		rscript(f, alg[0], alg[1], out, nbJob, nbMac)
	
	r, e = lib.sys.run(['Rscript', tmpfile])

	os.remove(tmpfile)

	print(r.decode())
	print(e.decode())

if __name__ == '__main__':
	inp = sys.argv[1]
	out = sys.argv[2]

	do(inp, out)


