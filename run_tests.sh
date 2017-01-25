#!/bin/bash

make 1>/dev/null;
cd tests;
for t in *.in; do
	echo -n -e "Running test $t...\t";
	../ex5.exe < $t > `echo $t | sed "s/in/ir/"` && ../bvm.pl `echo $t | sed "s/in/ir/"` > `echo $t | sed "s/in/myout/"`;
	diff `echo $t | sed "s/in/myout/"` `echo $t | sed "s/in/out/"` &>/dev/null;
	if [[ $? -eq 0 ]]; then 
		echo "PASS";
	else
		echo "FAIL";
	fi
done
