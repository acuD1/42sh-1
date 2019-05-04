#!/bin/zsh

make fclean;
make debug CC=gcc;
mkdir dump;
cd dump;
for f in ../leaks_and_segv/*;
	do echo "-----\n\033[32m$f\033[0m\n-----\n";
		file=`cat $f`;
		echo "$file" | ../21shdb;
	done
cd ..;
rm dump/*;
rmdir dump;


## segv 1 et 6 segv sur la hashmap uniquement en compilant avec gcc
#
#ASAN:DEADLYSIGNAL
#=================================================================
#==11409==ERROR: AddressSanitizer: SEGV on unknown address 0x000000000000 (pc 0x55cfbc1eeab4 bp 0x7ffcb31cb9e0 sp 0x7ffcb31cb9c0 T0)
#==11409==The signal is caused by a READ memory access.
#==11409==Hint: address points to the zero page.
#ls: cannot access ''$'\254': No such file or directory
    #0 0x55cfbc1eeab3 in ft_hash_str srcs/hashmap/ft_hash_str.c:31
    #1 0x55cfbc1ed3c9 in ft_hmap_getdata srcs/hashmap/ft_hmap_getdata.c:22
    #2 0x55cfbc1cc2f7 in launch_process srcs/resolution/launch_process.c:113
    #3 0x55cfbc1cb042 in launch_job srcs/resolution/launch_job.c:61
    #4 0x55cfbc1bad3f in execution_pipeline srcs/./routines.c:90
    #5 0x55cfbc1b73a2 in stdin_build_cmd srcs/./main.c:31
    #6 0x55cfbc1b775d in launch_shell srcs/./main.c:57
    #7 0x55cfbc1b792f in main srcs/./main.c:78
    #8 0x7ffabd07eb96 in __libc_start_main (/lib/x86_64-linux-gnu/libc.so.6+0x21b96)
    #9 0x55cfbc1b7249 in _start (/home/gladys/Desktop/42sh/21shdb+0x3e249)

#AddressSanitizer can not provide additional info.
#SUMMARY: AddressSanitizer: SEGV srcs/hashmap/ft_hash_str.c:31 in ft_hash_str



#######
# for i in {1000..3000}; do for f in example.*; do zzuf -r 0.2 -s $i < "$f" > "$i-$f"; done; done                               
#######
