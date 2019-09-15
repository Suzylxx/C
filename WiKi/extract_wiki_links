#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[])
{
	if(argc!=2){
		printf("ERROR: Bad file.\n");
		return 0;
	}

	//read the file
	char* fname = argv[1];
	FILE* f1=fopen(fname,"r");
	size_t sz;
	fseek(f1,0L,SEEK_END);
	//get size of the file
	sz = ftell(f1);
	rewind(f1);
	//output the text file to array
	char f1_array[sz+1];
	fread(f1_array, 1, sz+1, f1);
	//set f1_array as pointer
	char* f1_ptr = f1_array;

	//get the match part
	char head[1000] = "<a href=\"/wiki/";
	char middle[1000] = "title=\"";
	char tail[1000] = "</a>";

	while(f1_ptr!=NULL){
		//match head
		char* findh = strstr(f1_ptr,head);
		if(findh==NULL){
			break;
		}
		f1_ptr = findh;

		//match middle part
		char* findm = strstr(f1_ptr,middle);
		char* findht = strchr(f1_ptr,'>');
		if(findm==NULL){
			break;
		}
		if(findm<findht){
			findm = &findm[7];
			while(*findm!='"'){
				printf("%c",*(findm));
				findm++;
			}
			printf("\n");
		}
		f1_ptr = findht;

		//get pagename


		//if the next check part is not tail(</a>)
	}

	fclose(f1);
}




