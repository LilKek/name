#include "automat.h"

// ’еш-функци€ дл€ строк [KP]
unsigned int hash(char s)
{
	unsigned int h = 0;

	h = h * HASH_MUL + (unsigned int)s;
	return h % HASH_SIZE;
}


void dir (char * dir_name, int substr_size, int al_size, char *substring){
	DIR * d;
	d = opendir (dir_name);
	if (! d) {
        printf("Can't open directory %s", dir_name);
        return;
    }
    while (1) {
        struct dirent * entry;
        const char * d_name;
        entry = readdir (d);
        if (! entry) {
            break;
        }
        d_name = entry->d_name;
       
        	int ln = strlen(d_name);
        	if(d_name[ln - 1] == 't' && d_name[ln - 2] == 'x' && d_name[ln - 3] == 't'){
        			printf ("\n%s\\%s", dir_name, d_name);
                	char dir[100];
                	strcpy(dir, dir_name);
                	int l = strlen(dir);
                	dir[l] = '/';
                	dir[l +1] = '\0';
					
					strncat (dir, d_name,100);
                	open_file(dir, substr_size, al_size,substring);
                	
			}
	}
	if (closedir (d)) {
        printf ("Could not close \n");
    }
}


void list_dir (char * dir_name, int substr_size, int al_size, char *substring){
    DIR * d;


    d = opendir (dir_name);

    if (! d) {
        printf("Can't open directory");
        return;
    }
    while (1) {
        struct dirent * entry;
        const char * d_name;

        entry = readdir (d);
        if (! entry) {
            
            break;
        }
        d_name = entry->d_name;
        if (strncmp(d_name, ".", strlen("."))) 
            printf ("\n%s\\%s", dir_name, d_name);
        	int ln = strlen(d_name);
        	if(d_name[ln - 1] == 't' & d_name[ln - 2] == 'x' & d_name[ln - 3] == 't'){
                	char dir[100];
                	strcpy(dir, dir_name);
                	int l = strlen(dir);
                	dir[l] = '\\';
                	dir[l +1] = '\0';
					
					strncat (dir, d_name,100);
                	open_file(dir, substr_size, al_size,substring);
            }


        if (entry->d_type & DT_DIR) {
            
            if (strcmp (d_name, "..") != 0 &&
                strcmp (d_name, ".") != 0) {
                int path_length;
                char path[PATH_MAX];
 
                path_length = snprintf (path, PATH_MAX,
                                        "%s/%s", dir_name, d_name);
                printf ("/"); 
                if (path_length >= PATH_MAX) {
                    printf("error with path length");
                    return;
                }
                list_dir (path, substr_size, al_size, substring);
            }
        }
    }
    if (closedir (d)) {
        printf ("Could not close \n");
                 
        
    }
}


void open_file(char *file, int substr_size, int al_size, char *substring) {
	//FILE *ifp;
    FILE *ifp = fopen(file, "r");
    //if( (ifp = fopen(file, "r")) == NULL) {
    if(ifp == NULL) {
        perror("fopen");
        return;
    }
    int N = 10, d=10, i = 0;   
    char* buf = (char*) malloc (sizeof(char)*N);    
    while ((buf [i] = fgetc(ifp)) != EOF  )  {                
        if (++i >= N) {
            N += d;
            buf = (char*) realloc (buf, sizeof(char)*N);        
        }   
    } 
    buf[i] = '\0';
    if (fclose(ifp)) {
        printf ("Could not close file\n");
    } 
   	search(buf, substr_size, al_size, substring);
 	
    return;

}



void search(char *string, int substr_size, int al_size, char *substring)
{
 	int len = strlen(string);
 	int delta[substr_size][al_size];
	
     // таблица автомата. размер длина подстроки*размер алфавита
	int i, j, it, temp, star;
	char tmp;
 	//создание автомата
 	star = hash('*');
	for(i = 0; i < substr_size; i++){
		for(j = 0; j < al_size; j++){
			delta[i][j] = 0;
		}
	}
 	
 	for (j=0; j < substr_size; j++) {
 		tmp = substring[j];
 		if(tmp == '?'){
 			for(it=0; it < al_size; it++){
   				delta[j][it] = j+1;
			}
			delta[j][star] = 0;
 		}else{
 			temp = hash(tmp);
    		i=delta[j][temp];
   			delta[j][temp]=j+1;
   			if(j == 0){
			      	for(it=j; it < substr_size; it++){
   						delta[it][temp] = delta[j][temp];
   					}
			}	
		}
	}
	
	for(j = 0; j < substr_size;j++){
		if(delta[j][star] != 0){ 
			if(j+1 < substr_size){//если * не последн€€
				for(it = 0; it < al_size; it++){
					delta[j][it] = j;
				}
				for(i = 0; i < al_size; i++){
					if(delta[j+1][i] == j+2){
						delta[j][i]= j+2;
					}
				}
			}else{// если последн€€
				for(it = 0; it < al_size; it++){
					delta[j][it] = j+1;
				}
			}
		}
	}
	j = 0;
	it = 0;
	int k = 0;
 	for (i=0; i < len; i++){
 		tmp = string[i];
 		temp = hash(tmp);
   		j=delta[j][temp];
   		if((j == 1) && (k == 0)){
   			it = i;
   			k = 1;
		   }
		if((j == 1) && (delta[j][star] != 1)) {
   			it = i;
		   }   
   		if (j == substr_size){
   			j = 0;
		   printf("\nMatches starting with %d characters\n", it+1);
		   int out = it;
		   while(out <= i){
		   		printf("%c", string[out]);
		   		out += 1;
		   }
		   printf("\n");
		}
   	}
}

