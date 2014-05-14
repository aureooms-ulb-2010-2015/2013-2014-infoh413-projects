
def will_it_float(s):
	try:
		float(s)
		return True
	except ValueError:
		return False

def abbr(key):
	a = ''
	for word in key.split('/'):
		if not word or word.isnumeric() or will_it_float(word): continue
		elif len(word) > 3  or word == 'vnd' : a += word[0]
		else : a += word

	return a.upper()