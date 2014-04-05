import sys, os, lib



def do(data, best, out, filt):

	c = {}

	def parse_best(f):
		 c[f.name[len(best):]] = float(f.readline())

	lib.file.walk(best, parse_best)



	dev = {}

	def callback(f):
		ins = os.path.basename(f.name)
		if filt not in ins : return
		dim, n = ins.split('_')
		n = int(n)
		alg = f.name[:-len(ins)]

		dev.setdefault(alg, {})
		dev[alg].setdefault(dim, {})

		sol = float(f.readline().split()[0])

		dev[alg][dim][n] = 100 * (sol - c[ins]) / c[ins]

	lib.file.walk(data, callback)

	if not os.path.exists(out) : os.makedirs(out)

	for alg in sorted(dev.keys()):
		with open(os.path.join(out, alg[len(data):].replace('/', '_')), 'w') as f:
			print(f.name)
			for dim in sorted(dev[alg].keys()):
				for n in sorted(map(int, dev[alg][dim].keys())):
					f.write(str(dev[alg][dim][n]))
					f.write('\n')


if __name__ == '__main__':
	name = sys.argv[4]

	data = sys.argv[1] + name
	best = sys.argv[2]
	filt = '' if len(sys.argv) < 6 else sys.argv[5]
	out = sys.argv[3] + name + (filt + '/' if filt else '')

	do(data, best, out, filt)

