import sys, os, lib, functools, json



def do():

	txt = functools.partial(print, end = ' ')

	alg, data = json.load(sys.stdin)

	def abbr(key):
		a = ''
		for word in os.path.basename(key).split('_'):
			if not word or word.isnumeric(): continue
			elif len(word) > 3 or word == 'vnd' : a += word[0]
			else : a += word

		return a.upper()


	print('\\newpage\\cleardoublepage\\phantomsection')
	print('\\thispagestyle{empty}')
	print('\\begin{landscape}')

	print('\\begin{table}')
	print('\\tiny')
	print('\\tabcolsep=0.11cm')


	print('\\begin{longtable}{|%s}' % ('l|' * len(alg)))
	print('\\hline')
	txt('&')

	for j in range(1, len(alg) - 1):
		txt('\\textbf{%s} &' % abbr(alg[j]))

	print('\\textbf{%s}\\\\' % abbr(alg[-1]))
	print('\\hline')


	for i in range(len(alg) - 1):
		txt('\\textbf{%s} &' % abbr(alg[i]))
		for j in range(i):
			txt('&')
		for j in range(i+1, len(alg)):
			txt('\\begin{tabular}{@{}l@{}}')
			txt('{:.3e}'.format(data[i][j][0]))
			txt('\\\\')
			txt('{:.3e}'.format(data[i][j][1]))
			txt('\\end{tabular}')
			if j < len(alg) - 1 : txt('&')

		print('\\\\')
		print('\\hline')


	print('\\end{longtable}')
	print('\\end{table}')
	print('\\end{landscape}')


if __name__ == '__main__':

	do()

