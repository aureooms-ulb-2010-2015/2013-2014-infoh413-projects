# /!\ WARNING

	* compiles with g++ 4.8.1

		$ g++ -v
		Using built-in specs.
		COLLECT_GCC=g++
		COLLECT_LTO_WRAPPER=/usr/lib/gcc/x86_64-linux-gnu/4.8/lto-wrapper
		Target: x86_64-linux-gnu
		Configured with: ../src/configure -v --with-pkgversion='Ubuntu/Linaro 4.8.1-10ubuntu9' --with-bugurl=file:///usr/share/doc/gcc-4.8/README.Bugs --enable-languages=c,c++,java,go,d,fortran,objc,obj-c++ --prefix=/usr --program-suffix=-4.8 --enable-shared --enable-linker-build-id --libexecdir=/usr/lib --without-included-gettext --enable-threads=posix --with-gxx-include-dir=/usr/include/c++/4.8 --libdir=/usr/lib --enable-nls --with-sysroot=/ --enable-clocale=gnu --enable-libstdcxx-debug --enable-libstdcxx-time=yes --enable-gnu-unique-object --enable-plugin --with-system-zlib --disable-browser-plugin --enable-java-awt=gtk --enable-gtk-cairo --with-java-home=/usr/lib/jvm/java-1.5.0-gcj-4.8-amd64/jre --enable-java-home --with-jvm-root-dir=/usr/lib/jvm/java-1.5.0-gcj-4.8-amd64 --with-jvm-jar-dir=/usr/lib/jvm-exports/java-1.5.0-gcj-4.8-amd64 --with-arch-directory=amd64 --with-ecj-jar=/usr/share/java/eclipse-ecj.jar --enable-objc-gc --enable-multiarch --disable-werror --with-arch-32=i686 --with-abi=m64 --with-multilib-list=m32,m64,mx32 --with-tune=generic --enable-checking=release --build=x86_64-linux-gnu --host=x86_64-linux-gnu --target=x86_64-linux-gnu
		Thread model: posix
		gcc version 4.8.1 (Ubuntu/Linaro 4.8.1-10ubuntu9)


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