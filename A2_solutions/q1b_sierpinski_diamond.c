#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <ctype.h>

int height = 0;
int shape(int theH, int level, int col, int row, char array[height][height]) {
	//print the basic triangle, upper and bottom
	if(level == 1) {
		int first = col + theH;
		int last = first;
		for(int i = row; i <= (row + theH); i++) {
			for(int j = col; j <= (col + (theH * 2)); j++) {
				if(j >= first && j <= last) {
					array[i][j] = '*';
					array[height-i-1][j]='*';
				}
			}
			first--;
			last++;
		}
	} else {
		//top one
		shape(theH/2, level - 1, col + theH/2 + 1, row, array);
		//right part
		shape(theH/2, level - 1, col + theH + 1, row + theH/2 + 1, array);
		//left part
		shape(theH/2, level - 1, col, row + theH/2 + 1, array);

	}
	return 0;
}

bool checkh(int n)
{
   return (ceil(log2(n)) == floor(log2(n)));
}

int main(int argc, char *argv[]){
	//check if the diamond can be created
	if(argc!=3){
		printf("ERROR: Wrong number of arguments. One required.\n");
		return 0;
	}
	//get height and level of the diamond
	int h = atoi(argv[1]);
	int l = atoi(argv[2]);
	height = h;
	//get modulo of h divide 2
	int m = h%2;
	int theCol=0;
	int theRow=0;
	double p = pow(2,l-1);
	//get half height
    int half = h/2;
    if(half<(h/2.0)){
        half++;
    }
	char arr[h][h];
	//check if the diamond can be created
	if((m==0)||h<=0){
		printf("ERROR: Bad argument. Height must be positive odd integer.\n");
		return 0;
	}else if(h<(int)p||!checkh(half)){
		printf("ERROR: Height does not allow evenly dividing requested number of levels.\n");
		return 0;
	}else{
		//first create the whole box, store in array
		for(int i = 0; i < h; i++) {
			for(int j = 0; j < h; j++) {
				arr[i][j] = ' ';
		    }
		}
    }
	//make the diamond
	shape(h/2, l, theCol, theRow, arr);
	//print the diamond
	for(int i = 0; i < h; i++) {
		    for(int j = 0; j < h; j++) {
		        printf("%c", arr[i][j]);
		    }
		    printf("\n");
		}
}

