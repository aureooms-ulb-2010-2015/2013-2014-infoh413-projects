import sys, os, lib, functools



def do(inp, out, script):

	txt = functools.partial(print, end = ' ')

	def abbr(key):
		a = ''
		for word in key[len(inp):].split('_'):
			if not word or word.isnumeric(): continue
			elif len(word) > 3 or word == 'VND' : a += word[0]
			else : a += word

		return a.upper()

	alg = []

	lib.dir.walk(inp, f = lambda x : alg.append(x))

	alg = sorted(alg)


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
			r, _ = lib.sys.run(script + [alg[i], alg[j]])
			r = r.decode().split('\n')
			txt('\\begin{tabular}{@{}l@{}}')
			txt('{:.3e}'.format(float(r[0].split(' ')[1])))
			txt('\\\\')
			txt('{:.3e}'.format(float(r[1].split(' ')[1])))
			txt('\\end{tabular}')
			if j < len(alg) - 1 : txt('&')

		print('\\\\')
		print('\\hline')


	print('\\end{longtable}')
	print('\\end{table}')
	print('\\end{landscape}')


if __name__ == '__main__':
	inp = sys.argv[1]
	out = sys.argv[2]
	script = sys.argv[3:]

	do(inp, out, script)

