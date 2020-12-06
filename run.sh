#!/bin/sh
if [ $# -ne 2 ]
  then
    echo "Usage: $0 [SCRIPT_FILE] [INPUT_FILE]"
    exit
fi

filename=$(basename -- "$1")
extension="${filename##*.}"

case $extension in
    "cpp")
        g++ -std=c++17 -O2 $1 -o tmp && cat $2 | ./tmp && rm tmp
        ;;
    "swift")
        cat helpers.swift $1 > tmp.swift
        cat $2 | swift tmp.swift
        rm tmp.swift
        ;;
esac

