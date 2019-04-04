#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

char loc1 []= "/home/vagrant/Documents/FolderProses1/SimpanProses1.txt";
char loc2  []= "/home/vagrant/Documents/FolderProses2/SimpanProses2.txt";
const char *dir[2], *file[2]; *zipped[2];
dir[0] = "/home/vagrant/Documents/FolderProses1/";
dir[1] = "/home/vagrant/Documents/FolderProses2/";

file[0] = "SimpanProses1.txt";
file[1] = "SimpanProses2.txt";

zipped[0] = "KompresProses1.zip";
zipped[1] = "KompresProses2.zip";

void* createFile(void *arg){
    char syn [50] = "ps -aux | head -10 > ";
    strcat(syn, loc1);
    system(syn);

    execlp("cp","cp",loc1,loc2,NULL);

    return NULL
}

void* zipper(void *arg){
    int num = (int) arg;

    chdir(dir[num]);
    execl("/usr/bin/zip","zip","-m", zipped[num], file[num], NULL);

    return NULL;
}

void* unzipper(void *arg){
    int num = (int) arg;

    chdir(dir[num]);
    execl("/usr/bin/unzip","unzip", zipped[num], file[num], NULL);

    return NULL;
}

int main(){
	int err, i;
    pthread_t tid[100];

    // membuat file dari ps -aux
    err = pthread_create( &(tid[i]), NULL, createFile, NULL );
    if(err){
        fprintf(stderr,"Error - pthread_create() return code: %d\n",err);
        exit(EXIT_FAILURE);
    }

    // memanggil threat zipper
	for(i=0;i<2;i++){
		err = pthread_create( &(tid[i]), NULL, zipper, (void*) i );
		if(err){
            fprintf(stderr,"Error - pthread_create() return code: %d\n",err);
            exit(EXIT_FAILURE);
        }
	}

	for(i=0;i<2;i++){
		pthread_join(tid[i], NULL);
	}

    sleep(15);

    // memanggil threat unzipper
	for(i=0;i<2;i++){
		err = pthread_create( &(tid[i]), NULL, unzipper, (void*) i );
		if(err){
            fprintf(stderr,"Error - pthread_create() return code: %d\n",err);
            exit(EXIT_FAILURE);
        }
	}

	for(i=0;i<2;i++){
		pthread_join(tid[i], NULL);
	}

	return 0;
}