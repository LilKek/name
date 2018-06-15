#include "automat.h"

int main(int argc, char *argv[]){

	if (!argv[1] || !argv[2] || !argv[3]) {
        printf("Insufficient number of arguments\n");
        return 0;
    }
	
	char *substring = argv[2];
	
	int substr_size = strlen(substring);
	int al_size = 30;
	
	if(strcmp(argv[1], "fsmatcher") == 0 ){ 
		dir(argv[3],substr_size, al_size, substring);
   		
	}else{
		if(strcmp(argv[1], "fsmatcher-r") == 0){
		//	list_dir(argv[3],substr_size, al_size, substring);
		}else
			printf("Wrong argument");
			return 0;
	}

	return 0;
}
