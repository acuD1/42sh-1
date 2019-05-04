#!/bin/zsh

rm -f test_file/* 2>/dev/null
rmdir test_file 2>/dev/null
mkdir test_file 2>/dev/null
cd test_file
echo $1 > example.test
for i in {1000..3000};
	do for f in example.*;
       		do zzuf -r 0.02 -s $i < "$f" > "$i-$f";
	       	done;
       	done

