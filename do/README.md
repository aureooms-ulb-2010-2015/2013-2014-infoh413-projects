



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

	ls data/in/50x20_* | python3 do/gen.py ./run/pfsp-ii --neighborhood transpose --init random --pivoting best -- data/out


bench.py
==


usage :

	python3 do/bench.py <script> <runnable> <in> <out>


example:

	python3 do/bench.py tim ./run/pfsp-ii data/in data/out




diff.py
==


usage :

	python3 do/diff.py <hi> <lo> <var>


example:

	python3 do/diff.py data/out/tim/03281520/ data/out/tim/03291518/ 0




report.py
==


usage :

	python3 do/report.py <out> <best> [<filt>, <floatp>,]


example :

	python3 do/report.py data/out/03302218/ data/best/ 100x20 4


reportall
==

usage :

	do/reportall <name>

example :

	do/reportall 04041753+all\:insert2/



dev.py
==


usage :

	python3 do/dev.py <in> <best> <out> <name> <filt>


example :

	python3 do/dev.py data/out/ data/best/ data/dev/ 04041753+all\:insert2/ 100x20



devall
==

usage :

	do/devall <name>

example :

	do/devall 04041753+all\:insert2/


tim.py
==


usage :

	python3 do/tim.py <in> <best> <out> <name> <filt>


example :

	python3 do/tim.py data/out/ data/best/ data/tim/ 04041753+all\:insert2/ 100x20



timall
==

usage :

	do/timall <name>

example :

	do/timall 04041753+all\:insert2/




stat.py
==


usage :

	<in> | python3 do/stat.py <name> <title> <tl> > <out>


example :

	cat data/test/dev/04041753+all\:insert2/100x20 | python3 do/stat.py 100x20 "Relative percentage deviation" dev > data/stat/dev/04041753+all\:insert2/100x20



test.py
==


usage :

	python3 do/test.py <in> <out> <script>


example :

	python3 do/test.py data/dev/ -- Rscript do/test.r