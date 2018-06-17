#include "automat.h"

int main(int argc, char *argv[]){

	if (!argv[0] || !argv[1] || !argv[2]) {
        printf("Insufficient number of arguments\n");
        return 0;
    }
	
	char *substring = argv[1];
	
	int substr_size = strlen(substring);
	int al_size = 30;
	
	if(strcmp(argv[0], "./fsmatcher") == 0 ){ 
		dir(argv[2],substr_size, al_size, substring);
   		
	}else{
		printf("Wrong argument");
		return 0;
	}

	return 0;
}
