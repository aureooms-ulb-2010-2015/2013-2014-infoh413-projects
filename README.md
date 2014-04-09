


# files

	* data: instance files and output files
	* do  : python3/shell scripts for benching, latex tables, etc.

	* h   : header files
		* lib : library header files for useful things (array shuffling, io)
		* pfsp: library header files for PFSP

		* pfsp_commons : header file for data types used for PFSP
		* pfsp_ii : configuration and global variables for pfsp-ii
		* pfsp_vnd : configuration and global variables for pfsp-vnd

	* pdf : implementation sheets
	* src : the main program source code for pfsp-ii and pfsp-vnd

	* report.pdf : pdf report with tables, explanation and notes
	* Makefile : makefile for the implementation in C++
	* README.md : this file




# compile it

	make clean all




# run it

	./run/ii <filename> --init {random, slack} --neighborhood {transpose, exchange, insert} --pivoting {first, best} [--seed <seed>]

	./run/vnd <filename> --init {random, slack} --ordering {tie, tei} [--pivoting {first, best}, --seed <seed>]


# flags

	-v, --verbose
	-h, --help




# output non-verbose format

	twt
	running time [ms]
	seed