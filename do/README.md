



split.py
==


usage:

	python3 do/split.py <list> <out>


example:
	
	python3 do/split.py data/old/best data/best




gen.py
==


usage :

	python3 do/gen.py <runnable> <**kwargs> <in> <out>


example:

	python3 do/gen.py ./run/pfsp-ii --neighborhood transpose --init random --pivoting best data/in data/out




tim.py
==


usage :

	python3 do/gen.py <runnable> <**kwargs> <in>


example:

	ls data/in/50x20_* | python3 do/tim.py ./run/pfsp-ii --neighborhood exchange --init random --pivoting best --




bench.py
==


usage :

	python3 do/bench.py <script> <runnable> <in> <out>


example:

	python3 do/bench.py tim ./run/pfsp-ii data/in data/out




diff.py
==


usage :

	python3 do/diff.py <hi> <lo>


example:

	python3 do/diff.py data/out/tim/03281520/ data/out/tim/03291518/




report.py
==


usage :

	python3 do/report.py <out> <best> [<floatp>,]


example :

	python3 do/report.py data/out/03302218/ data/best/ 4




dev.py
==


usage :

	python3 do/dev.py <in> <best> <out>


example :

	python3 do/dev.py data/out/03302218/ data/best/ data/dev




stat.py
==


usage :

	python3 do/stat.py <in> <out> <script>


example :

	python3 do/stat.py data/dev/ -- Rscript do/stat.r