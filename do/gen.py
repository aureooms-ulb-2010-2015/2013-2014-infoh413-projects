import sys, os, lib

def do(run, options, inp, out):

	def callback(f):
		o = os.path.join(out, os.path.basename(f))
		print(o)
		r,_ = lib.sys.run([run] + options + ['--', f])
		with open(o, 'wb') as g : g.write(r)


	if not os.path.exists(out) : os.mkdir(out)

	if os.path.isfile(inp) : callback(inp)
	elif inp != '--' : lib.dir.walk(inp, f = callback)
	else : lib.stdin.read(f = callback)

if __name__ == '__main__':

	run = sys.argv[1]
	options = sys.argv[2:-2]
	inp = sys.argv[-2]
	out = sys.argv[-1]

	do(run, options, inp, out)