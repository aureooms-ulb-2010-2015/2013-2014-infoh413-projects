



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




tim.py
==


usage :

	python3 do/gen.py <runnable> <**kwargs> <in>


example:

	ls data/in/50x20_* | python3 do/tim.py ./run/ils --neighborhood exchange --init random --pivoting best --




bench.py
==


usage :

	python3 do/bench.py <script> <runnable> <in> <out>


example:

	python3 do/bench.py tim ./run/ils data/in data/out




diff.py
==


usage :

	python3 do/diff.py <hi> <lo>


example:

	python3 do/diff.py data/time/before-opt/ data/time/before-opt2/


