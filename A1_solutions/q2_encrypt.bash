#!/bin/bash

cat $2 | tr [A-Z] [`cat $1 | tail -1`] | tr [a-z] [`cat $1 | head -1`]

# "cat $2" read the third command line argument and save the content in a pipe
# first translate the lower-cases into encrypted letter and save the content in a pipe
# then translate the upper-cases into encrypted letter
