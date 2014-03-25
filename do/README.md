

split.py
==


usage:

	python3 do/split.py <list> <out>


example:
	
	python3 do/split.py data/best/list data/best


gen.py
==


usage :

	python3 do/gen.py <runnable> <**kwargs> <in> <out>


example:

	python3 do/gen.py ./run/ils --neighborhood transpose --init random --pivoting best data/in data/out


bench.py
==


usage :

	python3 do/bench.py <runnable> <in> <out>


example:

	python3 do/bench.py ./run/ils data/in data/out


diff.py
==


usage :

	python3 do/diff.py <out> <best> <instance>


example:

	python3 do/diff.py data/out data/best 100x20_9


