#!/bin/zsh

for f in test/*; do echo "-----\n\033[32m$f\033[0m\n-----\n";file=`cat $f`;echo $file >/dev/null | ./21shdb; sleep 0.02; done
