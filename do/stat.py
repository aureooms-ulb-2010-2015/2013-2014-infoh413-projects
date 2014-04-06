import sys, os, lib, functools, json, math

log = lambda x : math.log(x, 10)


def do(name):

	txt = functools.partial(print, end = ' ')

	alg, data = json.load(sys.stdin)

	# m, M = float("inf"), float("-inf")

	# for x in data:
	# 	for y in x:
	# 		if y is not None : m, M = min(m, y[1]), max(M, y[1])

	# m, M = log(m), log(M)
	# w = m - M

	def abbr(key):
		a = ''
		for word in os.path.basename(key).split('_'):
			if not word or word.isnumeric(): continue
			elif len(word) > 3 or word == 'vnd' : a += word[0]
			else : a += word

		return a.upper()


	# print('\\newpage\\cleardoublepage\\phantomsection')
	# print('\\thispagestyle{empty}')
	# print('\\begin{landscape}')

	print('\\begin{table}[H]')
	print('\\begin{center}')
	print('\\caption{Student t-test and Wilcoxon test results for %s instances}' % name)
	print('\\label{app:stat/table/%s}' % name)
	print('\\tiny')
	print('\\tabcolsep=0.11cm')


	print('\\begin{tabular}{|%s}' % ('l|' * len(alg)))
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
			cellcolor = int(data[i][j][1] * 100)
			textcolor = (cellcolor + 50) % 100
			txt('\\cellcolor{black!%d}' % cellcolor)
			txt('\\begin{tabular}{@{}l@{}}')
			txt('\\textcolor{black!%d}{' % textcolor)
			txt('{:.3e}'.format(data[i][j][0]))
			txt('}')
			txt('\\\\')
			txt('\\textcolor{black!%d}{' % textcolor)
			txt('{:.3e}'.format(data[i][j][1]))
			txt('}')
			txt('\\end{tabular}')
			if j < len(alg) - 1 : txt('&')

		print('\\\\')
		print('\\hline')


	print('\\end{tabular}')
	print('\\end{center}')
	print('\\end{table}')
	# print('\\end{landscape}')


if __name__ == '__main__':
	name = sys.argv[1]
	do(name)

