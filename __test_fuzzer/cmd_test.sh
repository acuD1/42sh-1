#!/bin/zsh

make fclean -C ../
make debug CC=gcc -C ../;
mkdir dump;
cd dump;
for f in ../test_file/*;
#for f in ../leaks_and_segv/leaks/*;
	do echo "-----\n\033[32m$f\033[0m\n-----\n";
		file=`cat $f`;
		echo $file | ../../21shdb;
	done
cd ..;
rm dump/*;
rmdir dump;

