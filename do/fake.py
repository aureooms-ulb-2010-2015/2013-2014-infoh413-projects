import sys, os, lib, gen, random


def fake(f, verbose):

	if verbose:

		steps = random.randint(40, 10000)

		v = random.randint(1, 528037 * 2)
		s = 0
		t = 0

		f.write('fake\n')
		f.write('fake\n')
		f.write('fake\n')
		f.write('best %d\n' % v)
		v -= random.randint(1, 1000)
		s += random.randint(1, 100)
		t += s * random.randint(400, 1000)
		while s < steps and v > 0:
			f.write('best %d step %d time %d ms\n' % (v, s, t))
			v -= random.randint(1, 10000)
			s += random.randint(1, 100)
			t += s * random.randint(4, 10)
		f.write('fake\n')
		f.write('fake\n')
		f.write('fake\n')
		f.write('fake\n')

	else:

		f.write('%d\n' % random.randint(0, 528037))
		f.write('%d\n' % random.randint(17, 78236))
		f.write('fake\n')




def do(opt, inp, out, verbose):

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

		def callback(f):
			out = os.path.join(o, os.path.basename(f))
			print(out)
			with open(out, 'w') as g : fake(g, verbose)

		if os.path.isfile(inp) : callback(inp)
		elif inp != '--' : lib.dir.walk(inp, f = callback)
		else : lib.stdin.read(f = callback)


if __name__ == '__main__':

	verbose = sys.argv[1] == '-v'
	run = sys.argv[2]
	inp = sys.argv[3]
	out = sys.argv[4]

	if(sys.argv[5][:2] == '--'):
		opt = []
		cmd = sys.argv[5].split(' ')
		for k, v in zip(cmd[::2], cmd[1::2]):
			opt.append([k, [v]])

	else:

		with lib.json.proxy(sys.argv[5]) as data:
			opt = data
	
		seed = ['0'] if len(sys.argv) < 7 else sys.argv[6:]
		opt[run].append(['--seed', seed])
		opt = opt[run]

	if inp != '--' : do(opt, inp, out, verbose)
	else : lib.stdin.read(f = lambda s : do(opt, s, out, verbose))