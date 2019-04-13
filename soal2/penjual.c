#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <arpa/inet.h>
#define PORT 8080
  
int *barang;

void* showBarang(void* arg){
    while (1)
    {
        sleep(5);
        printf("stok barang : %d\n", *barang);
    }
    
}

int main(int argc, char const *argv[]) {
    struct sockaddr_in address;
    int sock = 0, valread;
    struct sockaddr_in serv_addr;
    char buffer[1024] = {0};
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("\n Socket creation error \n");
        return -1;
    }
  
    memset(&serv_addr, '0', sizeof(serv_addr));
  
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
      
    if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0) {
        printf("\nInvalid address/ Address not supported \n");
        return -1;
    }
  
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        printf("\nConnection Failed \n");
        return -1;
    }

    //shared mem
    key_t key = 1234;
    int err;
    int shmid = shmget(key, sizeof(int), IPC_CREAT | 0666);
    barang = shmat(shmid, NULL, 0);
    //end of shared mem

    //create thread
    pthread_t tid;
    err = pthread_create( &tid, NULL, showBarang, NULL );
    if(err){
        fprintf(stderr,"Error - pthread_create() return code: %d\n",err);
        exit(EXIT_FAILURE);
    }
    //end create thread

    char say[30];
    while(1){
        fgets(say, sizeof(say), stdin);
        send(sock , say , strlen(say) , 0 );
     //   printf("barang : %d\n", *barang);
    }
    
    pthread_join(tid, NULL);

    shmdt(barang);
    shmctl(shmid, IPC_RMID, NULL);
    return 0;
}