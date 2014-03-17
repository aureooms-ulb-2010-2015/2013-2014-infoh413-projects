import sys, os


inp = sys.argv[1]
out = sys.argv[2]


with open(inp, 'r') as f:
	for line in f:
		size, n, best = line.split()
		with open(os.path.join(out, '%s_%s' % (size, n)), 'w') as o : o.write(str(best))



