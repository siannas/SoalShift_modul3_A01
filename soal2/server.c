#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/socket.h>
#include <netinet/in.h>

int *barang;

struct serverInfo{
    int port;
    char *role;
};

void *createServer(void *arg){
    struct serverInfo *pt = (struct serverInfo*) arg;

    int server_fd, new_socket, valread;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    char *hello = "transaksi berhasil  ";
      
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }
      
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons( pt->port );
      
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address))<0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 3) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen))<0) {
        perror("accept");
        exit(EXIT_FAILURE);
    }

    // *barang = 0;
    while(1){
        char buffer[1024] = {0};
        valread = read( new_socket , buffer, 1024);
        
        if(strcmp(pt->role, "penjual") == 0){
            if(strcmp(buffer, "tambah\n") == 0){
                *barang += 1;
            }
        }
        else if(strcmp(pt->role, "pembeli") == 0){
            if(strcmp(buffer, "beli\n") == 0){
                if(*barang<1){
                    send(new_socket , (char*)"transaksi gagal" , strlen(hello) , 0 );
                }else{
                    *barang -= 1;
                    send(new_socket , (char*)"transaksi berhasil" , strlen(hello) , 0 );
                }
            }
        }
        printf("%ssisa : %d\n",buffer, *barang);
    }
    
    return 0;
}

int main(int argc, char const *argv[]) {
    int err;
    key_t key = 1234;
    pthread_t tid1, tid2;

    int shmid = shmget(key, sizeof(int), IPC_CREAT | 0666);
    barang = shmat(shmid, NULL, 0);

    *barang = 0;
    
    struct serverInfo *pt = malloc(sizeof(struct serverInfo));
    pt->port = 8080;
    pt->role = "penjual";

    err = pthread_create( &tid1, NULL, createServer, (void*)pt );
    if(err){
        fprintf(stderr,"Error - pthread_create() return code: %d\n",err);
        exit(EXIT_FAILURE);
    }

    pt = malloc(sizeof(struct serverInfo));
    pt->port = 8081;
    pt->role = "pembeli";

    err = pthread_create( &tid2, NULL, createServer, (void*)pt );
    if(err){
        fprintf(stderr,"Error - pthread_create() return code: %d\n",err);
        exit(EXIT_FAILURE);
    }

    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);

    shmdt(barang);
    shmctl(shmid, IPC_RMID, NULL);
}
