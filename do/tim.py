import sys, os, lib



def do(data, out, filt):



	tim = {}

	def callback(f):
		ins = os.path.basename(f.name)
		if filt not in ins : return
		dim, n = ins.split('_')
		n = int(n)
		alg = f.name[:-len(ins)]

		tim.setdefault(alg, {})
		tim[alg].setdefault(dim, {})

		f.readline() # skip
		sol = float(f.readline().split()[0])

		tim[alg][dim][n] = sol

	lib.file.walk(data, callback)

	if not os.path.exists(out) : os.makedirs(out)

	for alg in sorted(tim.keys()):
		with open(os.path.join(out, alg[len(data):].replace('/', '_')), 'w') as f:
			print(f.name)
			for dim in sorted(tim[alg].keys()):
				for n in sorted(map(int, tim[alg][dim].keys())):
					f.write(str(tim[alg][dim][n]))
					f.write('\n')


if __name__ == '__main__':
	name = sys.argv[3]

	data = sys.argv[1] + name
	filt = '' if len(sys.argv) < 5 else sys.argv[4]
	out = sys.argv[2] + name + (filt + '/' if filt else '')

	do(data, out, filt)

