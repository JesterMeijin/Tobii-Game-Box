#!/bin/bash

# Absolute path to this script.
SCRIPT=$(readlink -f $0)
# Absolute path this script 
SCRIPTPATH=`dirname $SCRIPT`

cd "$SCRIPTPATH"

find . -maxdepth 1 -mindepth 1 -type d | sort | while read TESTDIR; do
    echo -e "\e[93m"
    echo -n "Running test $TESTDIR : "
    cd "$SCRIPTPATH/$TESTDIR"
    ln -sf ../../polytech
    rm -f test-latexmk.log
    find . -iname "*.bbl" -delete
    # generate latexmkrc
    echo "\documentclass[earlystop]{polytech/polytech}\begin{document}x\end{document}" | pdflatex > /dev/null
    mv latexmkrc.REMOVE_MY_EXTENSION latexmkrc
    latexmk -gg -pdf -interaction=nonstopmode test.tex >> test-latexmk.log 2>> test-latexmk.log
    result=$?
    
    if [ -n "$(echo $TESTDIR | grep -i mustfail)" ]; then
	if [ $result = 0 ]; then
	    result=1
	else
	    result=0
	fi
    fi

    if [ $result = 0 ]; then
	echo -e "\e[92mOK\e[39m"
	latexmk -C > /dev/null 2>/dev/null
    else
	echo -e "\e[91mERROR\e[39m"
	cat test-latexmk.log
	exit 1
    fi
done