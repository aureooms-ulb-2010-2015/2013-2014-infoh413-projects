import sys, os, lib



def do(hi, lo):

	a = {
		hi : {},
		lo : {}
	}

	def callback(w, f):
		a[w][f.name[len(w):]] = float(f.readline().split()[0])

	lib.file.walk(hi, f = lambda x : callback(hi, x))
	lib.file.walk(lo, f = lambda x : callback(lo, x))

	hit = 0
	lot = 0

	def c(hi, d):
		if -d > 0.05 * hi:
			return lib.io.ansy.OKGREEN + lib.io.ansy.UNDERLINE + lib.io.ansy.BOLD
		if d < 0 : return lib.io.ansy.OKGREEN
		if d < 0.05 * hi : return lib.io.ansy.WARNING
		return lib.io.ansy.FAIL

	e = lib.io.ansy.ENDC

	for key in a[hi]:
		if key in a[lo]:
			f, s = a[hi][key], a[lo][key]
			d = s - f;
			hit += f
			lot += s
			print('%s%s : %f <> %f --> %f%s' % (c(f, d), key, f, s, d, e))
		else:
			print('%s : NO lo data' % (key))

	for key in a[lo]:
		if not key in a[hi]:
			print('%s : NO hi data' % (key))


	print('%s%s : %f <> %f --> %f%s' % (c(hit, lot - hit), 'total', hit, lot, lot - hit, e))


if __name__ == '__main__':
	hi = sys.argv[1]
	lo = sys.argv[2]

	do(hi,lo)

