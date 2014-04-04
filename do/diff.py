import sys, lib



def do(hi, lo, x, filt):

	a = {
		hi : {},
		lo : {}
	}

	def callback(w, f):
		for i in range(x) : f.readline()
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

	out = []

	for key in a[hi]:
		if key in a[lo]:
			f, s = a[hi][key], a[lo][key]
			d = s - f;
			txt = '%s%s : %f <> %f --> %f%s' % (c(f, d), key, f, s, d, e)
			if filt in txt:
				out.append((d, txt))
				hit += f
				lot += s
		else:
			txt = '%s : NO lo data' % (key)
			if filt in txt : out.append((float('-inf'), txt))

	for key in a[lo]:
		if not key in a[hi]:
			txt = '%s : NO hi data' % (key)
			if filt in txt : out.append((float('-inf'), txt))

	out.sort()

	for _, txt in out : print(txt)
	print('%stotal : %f <> %f --> %f%s' % (c(hit, lot - hit), hit, lot, lot - hit, e))


if __name__ == '__main__':
	hi = sys.argv[1]
	lo = sys.argv[2]
	x = int(sys.argv[3])
	filt = '' if len(sys.argv) < 5 else sys.argv[4]

	do(hi, lo, x, filt)

