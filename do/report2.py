import sys, os, lib



def do(data, best, filt, floatp, rgobble):

	c = {}

	def parse_best(f):
		 c[f.name[len(best):]] = float(f.readline())

	lib.file.walk(best, parse_best)


	algos = set()
	out = {}

	def callback(f):
		ins = os.path.basename(f.name)
		if filt not in ins : return
		alg = f.name[:-len(ins)][:-rgobble]

		out.setdefault(ins, {})
		out[ins].setdefault(alg, [0, 0, 0])

		sol = float(f.readline().split()[0])

		out[ins][alg][0] += 100 * (sol - c[ins]) / c[ins]
		out[ins][alg][2] += 1

		algos.add(alg);

	lib.file.walk(data, callback)

	algos = sorted(list(algos))

	def will_it_float(s):
		try:
			float(s)
			return True
		except ValueError:
			return False

	def abbr(key):
		a = ''
		for word in key[len(data):].split('/'):
			if not word or word.isnumeric() or will_it_float(word): continue
			elif len(word) > 3  or word == 'vnd' : a += word[0]
			else : a += word

		return a.upper()

	format = '%%s & %%.%df & %%.%df\\\\' % floatp

	print('\\begin{table}[H]')
	print('\\begin{center}')
	print('\\caption{avg rel \\%% dev for %s instances}' % filt if filt else 'all')
	print('\\label{app:report/table/%s}' % filt if filt else 'all')
		 
	print('\\begin{tabular}{|l|d{%d}|d{%d}|}' % floatp)
	print('\\hline')
	print('\\textbf{instance} & \\textbf{%s} & \\textbf{%s}\\\\' % (abbr(algos[0]), abbr(algos[1])))
	print('\\hline')

	for ins in sorted(out):
		out[ins][algos[0]][0] /= out[ins][algos[0]][2]
		out[ins][algos[1]][0] /= out[ins][algos[1]][2]
		print(format % (ins, out[ins][algos[0]][0], out[ins][algos[1]][0]))
		print('\\hline')

	print('\\end{tabular}')
	print('\\end{center}')
	print('\\end{table}')

if __name__ == '__main__':
	data = sys.argv[1]
	best = sys.argv[2]
	filt = sys.argv[3]
	floatp = int(sys.argv[4])
	rgobble = int(sys.argv[5])

	do(data, best, filt, floatp, rgobble)

