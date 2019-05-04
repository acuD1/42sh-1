#!/bin/zsh

mkdir test_file 2>/dev/null
cd test_file
echo $1 > example.test
for i in {1000..3000};
	do for f in example.*;
       		do zzuf -r 0.2 -s $i < "$f" > "$i-$f";
	       	done;
       	done

