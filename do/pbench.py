import os, sys, lib, gen, uuid


def do(ben, run, opt, inp, out, tmpdir, name, tmpl, p):

	jobname = name + '-' + uuid.uuid4().hex

	runs = [([], [])]

	for o in opt:
		tmp = []
		for v in o[1]:
			for r in runs:
				tmp.append((r[0] + [o[0], v], r[1] + [v]))

		runs = tmp

	cmdfile = os.path.join(tmpdir, name, 'cmd')
	cmdpath = os.path.split(cmdfile)[0]
	if not os.path.isdir(cmdpath):
		if os.path.exists(cmdpath) : raise cmdpath + ' is an existing thingy'
		else : os.makedirs(cmdpath)

	out = os.path.join(out, name, os.path.split(run)[1].split('-')[-1])

	with open(cmdfile, 'w') as f:

		nruns = [0]

		def callback(inpfile):
			for r in runs:
				nruns[0] += 1
				o = os.path.join(out, *r[1])
				if not os.path.isdir(o):
					if os.path.exists(o) : raise o + ' is an existing thingy'
					else : os.makedirs(o)

				f.write(' '.join(['ls', inpfile, '|', 'python3', 'do/bench.py', ben, run, '--', out, '"' + ' '.join(r[0]) + '"']))
				f.write(os.linesep)

		lib.dir.walk(inp, f = callback)


	jobfile = os.path.join(tmpdir, name, 'job')
	jobpath = os.path.split(jobfile)[0]
	if not os.path.isdir(jobpath):
		if os.path.exists(jobpath) : raise jobpath + ' is an existing thingy'
		else : os.makedirs(jobpath)


	with open(jobfile, 'w') as f:
		f.write(tmpl.format(nruns[0], p['time'], p['np'], p['ppn'], p['mem'], jobname, cmdfile))



if __name__ == '__main__':
	ben = sys.argv[1]
	run = sys.argv[2]
	inp = sys.argv[3]
	out = sys.argv[4]
	tmp = sys.argv[5]
	name = sys.argv[6]

	with open(sys.argv[8]) as f:
		tmpl = f.read()


	with lib.json.proxy(sys.argv[7]) as data:
		opt = data

	with lib.json.proxy(sys.argv[9]) as data:
		p = data

	seedv = ['0'] if len(sys.argv) < 11 else sys.argv[10:]
	opt[run].append(['--seed', seedv])


	do(ben, run, opt[run], inp, out, tmp, name, tmpl, p)

	