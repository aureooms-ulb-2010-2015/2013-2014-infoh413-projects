import sys, os, lib



def do(data, best, out):

	c = {}

	def parse_best(f):
		 c[f.name[len(best):]] = float(f.readline())

	lib.file.walk(best, parse_best)



	dev = {}

	def callback(f):
		ins = os.path.basename(f.name)
		dim, n = ins.split('_')
		n = int(n)
		alg = f.name[:-len(ins)]

		dev.setdefault(alg, {})
		dev[alg].setdefault(dim, {})

		sol = float(f.readline().split()[0])

		dev[alg][dim][n] = 100 * (sol - c[ins]) / c[ins]

	lib.file.walk(data, callback)

	for alg in sorted(dev.keys()):
		with open(os.path.join(out, alg.replace('/', '_')), 'w') as f:
			for dim in sorted(dev[alg].keys()):
				for n in sorted(map(int, dev[alg][dim].keys())):
					# f.write(dim)
					# f.write(' ')
					# f.write(str(n))
					# f.write(' ')
					f.write(str(dev[alg][dim][n]))
					f.write('\n')


if __name__ == '__main__':
	data = sys.argv[1]
	best = sys.argv[2]
	out = sys.argv[3]

	do(data, best, out)

