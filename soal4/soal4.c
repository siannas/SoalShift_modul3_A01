#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

int zipnow = 0;

const char *loc []= {
    "/home/vagrant/Documents/FolderProses1/SimpanProses1.txt",
    "/home/vagrant/Documents/FolderProses2/SimpanProses2.txt"
};
const char *dir[] = {
    "/home/vagrant/Documents/FolderProses1/",
    "/home/vagrant/Documents/FolderProses2/"
}; 

const char *file[] = {
    "SimpanProses1.txt",
    "SimpanProses2.txt"
};

const char *zipped[] = {
    "KompresProses1.zip",
    "KompresProses2.zip"
}; 

void* createFile(void *arg){
    int num = (int) arg;

    char syn [100] = "ps -aux | head -10 > ";
    strcat(syn, loc[num]);
    system(syn);

    zipnow=1;
}

void* zipper(void *arg){
    while(zipnow != 1){}

    char syn [100];
    int num = (int) arg;
    
    sprintf(syn,"zip -m %s %s", zipped[num], file[num]);
    chdir(dir[num]);
    system(syn);

}

void* unzipper(void *arg){
    while(zipnow != 1){}

    char syn [100];
    int num = (int) arg;
  
    sprintf(syn,"unzip %s %s", zipped[num], file[num]);
    chdir(dir[num]);
    system(syn);
}


int main(){
	int err, i;
    pthread_t tid[100];

    // membuat file dari ps -aux
    for(i=0;i<2;i++){
		err = pthread_create( &(tid[i]), NULL, createFile, (void*) i );
		if(err){
            fprintf(stderr,"Error - pthread_create() return code: %d\n",err);
            exit(EXIT_FAILURE);
        }
	}

    // memanggil threat zipper
	for(i=0;i<2;i++){
		err = pthread_create( &(tid[i]), NULL, zipper, (void*) i );
		if(err){
            fprintf(stderr,"Error - pthread_create() return code: %d\n",err);
            exit(EXIT_FAILURE);
        }
	}

	sleep(15);
	printf("Menunggu 15 detik untuk mengekstrak kembali\n");

    //memanggil threat unzipper
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
