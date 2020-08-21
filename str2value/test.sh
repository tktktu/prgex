#!/bin/bash

INT_MAX=2147483647
INT_MIN=-2147483648

seq $INT_MIN $INT_MAX | while read INPUT
do
	echo "$INPUT"
	echo "$INPUT" | ./prg3
done
