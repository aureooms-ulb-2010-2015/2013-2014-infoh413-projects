

def read(f = print):
	while True:
		try:
			s = input()
		except EOFError:
			break
		if not s : break
		f(s)