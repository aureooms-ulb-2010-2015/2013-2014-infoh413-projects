import sys, os, lib, gen, tim



def do(ben, run, inp, out):

	for init in ['random', 'slack']:
		for pivoting in ['first', 'best']:
			for neighborhood in ['transpose', 'exchange', 'insert']:
				o = os.path.join(out, init, pivoting, neighborhood)
				if not os.path.isdir(o):
					if os.path.exists(o) : raise o + ' is an existing thingy'
					else : os.makedirs(o)

				ben.do(run,
					['--init', init, '--pivoting', pivoting, '--neighborhood', neighborhood],
					inp, o)


if __name__ == '__main__':
	scr = {
		'tim' : tim,
		'gen' : gen
	}
	
	ben = scr[sys.argv[1]]
	run = sys.argv[2]
	inp = sys.argv[3]
	out = sys.argv[4]

	if inp != '--' : do(ben, run, inp, out)
	else : lib.stdin.read(f = lambda s : do(ben, run, s, out))