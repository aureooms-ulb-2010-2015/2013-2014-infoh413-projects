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
		if filt not in ins : return
		alg = f.name[:-len(ins)].split('/')[0]

		out.setdefault(ins, {})
		out[ins].setdefault(alg, [{}, 0])

		for event in parserun.parse(f):
			out[ins][alg][0][event[0]] += event[1] < c[ins]

		out[ins][alg][1] += 1

		algos.add(alg);

	lib.file.walk(data, callback)

	algos = sorted(list(algos))


	for ins in out:
		for alg in out[ins]:
			a = list(sorted(out[ins][alg][0]))
			for t in range(len(a) - 1):
				out[ins][alg][0][a[t+1]] += out[ins][alg][0][a[t]]


	for ins in out:
		for alg1 in out[ins]:
			for alg2 in out[ins]:
				if alg1 == alg2 : continue
					a = list(sorted(out[ins][alg1][0]))
					b = list(sorted(out[ins][alg2][0]))

					i, j = 1, 1

					while j < len(b):
						while i < len(a) and a[i] < a[j]:
							out[ins][alg2].setdefault(a[i], out[ins][alg2][a[j-1]])
							i += 1

						j += 1

					while i < len(a):
						out[ins][alg2].setdefault(a[i], out[ins][alg2][a[-1]])
						i += 1




	for ins in sorted(out):
		for alg in sorted(out[ins]):
			for t in out[ins][alg][0]:
				out[ins][alg][0][t] /= out[ins][alg][1]

		with open(outdir, 'w') as f:
			for i in sorted(out[ins][algos[0]][0]):
				f.write('%f %f %f\n' % (i, out[ins][algos[0]][0][i], out[ins][algos[1]][0][i]))




if __name__ == '__main__':
	data = sys.argv[1]
	best = sys.argv[2]
	filt = sys.argv[3]
	out = sys.argv[4]

	do(data, best, filt, out)