import sys, os, gen

run = sys.argv[1]
inp = sys.argv[2]
out = sys.argv[3]

for init in ['random', 'slack']:
	for pivoting in ['first', 'best']:
		for neighborhood in ['transpose', 'exchange', 'insert']:
			o = os.path.join(out, init, pivoting, neighborhood)
			if not os.path.isdir(o):
				if os.path.exists(o) : raise o + ' is an existing thingy'
				else : os.makedirs(o)
			

			gen.do(run,
				['--init', init, '--pivoting', pivoting, '--neighborhood', neighborhood],
				inp, o)