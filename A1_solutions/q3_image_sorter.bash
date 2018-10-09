#!/bin/bash

ls -lR --time-style=full $1 | grep .jpg | sort -u -k6 -k7>sortpic.txt

#list all the documents(include the specific time) in the second command line argument
#get all .jpg files
#sort .jpg files by their date and time in increase order
#save the sorted name of files in a .txt

for i in $(cat sortpic.txt)
	do find $1 -name "$i">>fname.txt
done

#find the sorted .jpg file in their directory and save them in a new .txt

name=$(echo $1 | tr '/' '_')
new=$(echo "$name.jpg")

#create the name for the new image, substitute slash with underscore

convert  $(cat fname.txt) -append "$new"

#convert the image name arguments and append them into a new image with new name

