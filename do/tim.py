import sys, os, lib, time


def do(run, options, inp, out):

	def callback(f):
		o = os.path.join(out, os.path.basename(f))
		print(o, end=' ')
		start = time.time()
		_ = lib.sys.run([run] + options + ['--', f])
		end = time.time()
		s = '%f s' % (end - start)
		print(s)
		with open(o, 'w') as g : g.write(s)

	if not os.path.exists(out) : os.mkdir(out)

	if inp != '--' : lib.dir.walk(inp, f = callback)
	else : lib.stdin.read(f = callback)

if __name__ == '__main__':

	run = sys.argv[1]
	options = sys.argv[2:-2]
	inp = sys.argv[-2]
	out = sys.argv[-1]

	do(run, options, inp, out)


