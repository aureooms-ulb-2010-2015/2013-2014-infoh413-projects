import sys, os, lib, parserun



def do(data, best, filt, outdir):

	c = {}

	def parse_best(f):
		 c[f.name[len(best):]] = float(f.readline())

	lib.file.walk(best, parse_best)



	algos = set()
	out = {}

	def callback(f):
		ins = os.path.basename(f.name)
		if ins != filt : return
		alg = f.name[len(data):].split('/')[0]

		out.setdefault(ins, {})
		out[ins].setdefault(alg, [{0:0}, 0])

		for event in parserun.parse(f):
			if event[1] <= c[ins]:
				out[ins][alg][0].setdefault(event[0], 0)
				out[ins][alg][0][event[0]] += 1
				break

		out[ins][alg][1] += 1

		algos.add(alg);

	lib.file.walk(data, callback)

	algos = sorted(list(algos))


	for ins in sorted(out):
		for alg in sorted(out[ins]):
			a = list(sorted(out[ins][alg][0]))
			for t in range(len(a) - 1):
				out[ins][alg][0][a[t+1]] += out[ins][alg][0][a[t]]


	for ins in sorted(out):
		for alg1 in sorted(out[ins]):
			for alg2 in sorted(out[ins]):
				if alg1 == alg2 : continue
				a = list(sorted(out[ins][alg1][0]))
				b = list(sorted(out[ins][alg2][0]))

				i, j = 1, 1


				while j < len(b):
					while i < len(a) and a[i] < b[j]:
						out[ins][alg2][0].setdefault(a[i], out[ins][alg2][0][b[j-1]])
						i += 1

					j += 1

				while i < len(a):
					out[ins][alg2][0].setdefault(a[i], out[ins][alg2][0][b[-1]])
					i += 1


	for ins in sorted(out):
		for alg in sorted(out[ins]):
			for t in out[ins][alg][0]:
				out[ins][alg][0][t] /= out[ins][alg][1]

		with open(outdir, 'w') as f:
			for i in sorted(out[ins][algos[0]][0]):
				f.write('%d %f %f\n' % (i / 1000, out[ins][algos[0]][0][i], out[ins][algos[1]][0][i]))




if __name__ == '__main__':
	data = sys.argv[1]
	best = sys.argv[2]
	filt = sys.argv[3]
	out = sys.argv[4]

	do(data, best, filt, out)