import sys, os, lib, gen



def do(ben, run, opt, inp, out):

	runs = [([], [])]

	for o in opt:
		tmp = []
		for v in o[1]:
			for r in runs:
				tmp.append((r[0] + [o[0], v], r[1] + [v]))

		runs = tmp

	for r in runs:
		o = os.path.join(out, *r[1])
		if not os.path.isdir(o):
			if os.path.exists(o) : raise o + ' is an existing thingy'
			else : os.makedirs(o)

		ben.do(run, r[0], inp, o)


if __name__ == '__main__':
	scr = {
		'gen' : gen
	}

	seed = '0' if len(sys.argv) < 6 else sys.argv[5]

	opt = {
		'./run/pfsp-ii' : [
			('--init', ['random', 'slack']),
			('--pivoting', ['first', 'best']),
			('--neighborhood', ['transpose', 'exchange', 'insert']),
			('--seed', [seed])
		],
		'./run/pfsp-vnd' : [
			('--init', ['random', 'slack']),
			('--pivoting', ['first', 'best']),
			('--ordering', ['tie', 'tei']),
			('--seed', [seed])
		]
	}
	
	ben = scr[sys.argv[1]]
	run = sys.argv[2]
	inp = sys.argv[3]
	out = sys.argv[4]

	if inp != '--' : do(ben, run, opt[run], inp, out)
	else : lib.stdin.read(f = lambda s : do(ben, run, opt[run], s, out))