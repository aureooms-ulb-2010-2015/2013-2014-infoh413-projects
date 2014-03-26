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

	td = 0

	for key in a[hi]:
		if key in a[lo]:
			d = a[lo][key] - a[hi][key];
			td += d
			print('%s : %f <> %f --> %f' % (key, a[hi][key], a[lo][key], d))
		else:
			print('%s : NO lo data' % (key))

	for key in a[lo]:
		if not key in a[hi]:
			print('%s : NO hi data' % (key))


	print('td = %f' % td)


if __name__ == '__main__':
	hi = sys.argv[1]
	lo = sys.argv[2]

	do(hi,lo)

