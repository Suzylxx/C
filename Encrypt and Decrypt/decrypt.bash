#!/bin/bash

cat $2 | tr [`cat $1 | tail -1`] [A-Z] | tr [`cat $1 | head -1`] [a-z] 

# decrypt is a reverse of encrypt
# "cat $2" read the third command line argument and save the content in a pipe
# first translate the lower-cases into decrypted letter and save the content in a pipe
# then translate the upper-cases into decrypted letter
