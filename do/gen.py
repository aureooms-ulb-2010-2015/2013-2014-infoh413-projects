import sys, os , lib

run = sys.argv[1]
inp = sys.argv[2]
out = sys.argv[3]

def callback(f):
	print(f)
	r,_ = lib.sys.run([run, f])
	with open(os.path.join(out, os.path.basename(f)), 'wb') as g : g.write(r)


if not os.path.exists(out) : os.mkdir(out)

lib.dir.walk(inp, f = callback)