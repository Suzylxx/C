#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int main(int argc, char *argv[])
{
	if(argc!=2){
		printf("ERROR: Wrong number of arguments. One required.\n");
		return 0;
	}
	
	int i, j, k;
	int h = atoi(argv[1]);
	int m = h%2;
	if((m==0)||h<=0||isdigit(argv[1]==0)){
		printf("ERROR: Bad argument. Height must be positive odd integer.\n");
		return 0;
	}
	if(h>0&&m!=0){
		for(i=1;i<=h/2+1;i++){//above part including middle line
			for(j=h/2;j>=i;j--){
				printf(" ");
			}
			for(k=1;k<=2*i-1;k++){
				printf("*");
			}
			printf("\n");
		}
		for(i=h/2;i>=1;i--){
			for(j=i;j<=h/2;j++){
				printf(" ");
			}
			for(k=1;k<=2*i-1;k++){
				printf("*");
			}
			printf("\n");
		}
	}
	

	return 0;
}
