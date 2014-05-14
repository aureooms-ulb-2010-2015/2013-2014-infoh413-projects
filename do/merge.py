import sys, os, lib



def do(data, out, filt, rgobble):

	merged = {}

	for d in data:
		def callback(f):
			path, alg = os.path.split(f.name)
			alg = alg[:-rgobble]
			dim = path[len(d):]
			if filt not in dim and filt not in alg : return

			merged.setdefault(alg, {})
			merged[alg].setdefault(dim, [])

			for line in f:
				merged[alg][dim].append(float(line.split()[0]))

		lib.file.walk(d, callback)

	if not os.path.exists(out) : os.makedirs(out)

	for alg in sorted(merged.keys()):
		with open(os.path.join(out, alg), 'w') as f:
			print(f.name)
			for dim in sorted(merged[alg].keys()):
				for e in merged[alg][dim]:
					f.write(str(e))
					f.write('\n')


if __name__ == '__main__':
	root = sys.argv[1]
	data = [root + x for x in sys.argv[3:-2]]

	filt = sys.argv[-2]
	out = root + sys.argv[2] + (filt + '/' if filt else '')
	rgobble = int(sys.argv[-1])

	do(data, out, filt, rgobble)

