import sys, os, lib



def do(data, best, filt, floatp):

	c = {}

	def parse_best(f):
		 c[f.name[len(best):]] = float(f.readline())

	lib.file.walk(best, parse_best)



	out = {}

	def callback(f):
		ins = os.path.basename(f.name)
		if filt not in ins : return
		alg = f.name[:-len(ins)]

		out.setdefault(alg, [0, 0, 0])

		sol = float(f.readline().split()[0])
		tim = int(f.readline().split()[0])

		out[alg][0] += 100 * (sol - c[ins]) / c[ins]
		out[alg][1] += tim
		out[alg][2] += 1

	lib.file.walk(data, callback)

	def abbr(key):
		a = ''
		for word in key[len(data):].split('/'):
			if not word or word.isnumeric(): continue
			elif len(word) > 3  or word == 'vnd' : a += word[0]
			else : a += word

		return a.upper()

	bydev = []
	bytime = []

	format = '%%s & %%.%df & %%d ms\\\\' % floatp
		 
	print('\\begin{longtable}{|l|d{%d}|r|}' % floatp)
	print('\\caption{std dev and running time for %s instances}' % filt if filt else 'all')
	print('\\label{app:report/table/%s}\\\\' % filt if filt else 'all')
	print('\\hline')
	print('\\textbf{alg} & \\textbf{std dev} & \\textbf{avg time}\\\\')
	print('\\hline')

	for key in sorted(out):
		out[key][0] /= out[key][2]
		bydev.append((out[key][0], out[key][1], key))
		bytime.append((out[key][1], out[key][0], key))
		print(format % (abbr(key), out[key][0], out[key][1]))
		print('\\hline')

	print('\\end{longtable}')


	print('\\begin{longtable}{|l|d{%d}|r|}' % floatp)
	print('\\caption{std dev and running time for %s instances (sorted by dev)}\\\\' % filt if filt else 'all')
	print('\\hline')
	print('\\textbf{alg} & \\textbf{std dev} & \\textbf{avg time}\\\\')
	print('\\hline')

	for dev, t, key in sorted(bydev):
		print(format % (abbr(key), dev, t))
		print('\\hline')

	print('\\end{longtable}')

	print('\\begin{longtable}{|l|d{%d}|r|}' % floatp)
	print('\\caption{std dev and running time for %s instances (sorted by time)}\\\\' % filt if filt else 'all')
	print('\\hline')
	print('\\textbf{alg} & \\textbf{std dev} & \\textbf{avg time}\\\\')
	print('\\hline')

	for t, dev, key in sorted(bytime):
		print(format % (abbr(key), dev, t))
		print('\\hline')

	print('\\end{longtable}')


if __name__ == '__main__':
	data = sys.argv[1]
	best = sys.argv[2]
	filt = '' if len(sys.argv) < 4 else sys.argv[3]
	floatp = -1 if len(sys.argv) < 5 else int(sys.argv[4])

	do(data, best, filt, floatp)

