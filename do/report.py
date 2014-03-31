import sys, os, lib



def do(data, best):

	c = {}

	def parse_best(f):
		 c[f.name[len(best):]] = float(f.readline())

	lib.file.walk(best, parse_best)



	out = {}

	def callback(f):
		ins = os.path.basename(f.name)
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
			elif len(word) > 3 : a += word[0]
			else : a += word

		return a.upper()
		 
	print('\\begin{longtable}{|l|l|l|}')
	print('\\hline')
	print('\\textbf{alg} & \\textbf{std dev} & \\textbf{avg time}\\\\')
	print('\\hline')

	for key in sorted(out):
		out[key][0] /= out[key][2]
		print(abbr(key), '&', out[key][0], '&', out[key][1], 'ms\\\\')
		print('\\hline')

	print('\\end{longtable}')


if __name__ == '__main__':
	data = sys.argv[1]
	best = sys.argv[2]

	do(data, best)

