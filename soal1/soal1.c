#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void* factorial(void *arg);

int main(int argc, char *argv[]){
    int err, i, j, temp, arr[100];
    int length = argc-1;
    pthread_t tid[100];

    // masukin argv ke array semua
    for (i = 0; i < length; i++){
        arr[i] = atoi(argv[i+1]);
    }

   //sort gan
   for(j=0;j<length-1;j++){
   for (i = 0; i < length-1; i++){
    	if(arr[i]<arr[i+1]){
            temp = arr[i];
            arr[i] = arr[i+1];
            arr[i+1] = temp;
        }
    }}//sort done;
   
   for(i=0;i<length;i++){
		err = pthread_create( &(tid[i]), NULL, factorial, (void*) (arr[i]));
		if(err){
            fprintf(stderr,"Error - pthread_create() return code: %d\n",err);
            exit(EXIT_FAILURE);
        }
        pthread_join(tid[i], NULL);
	}
	return 0;
}

void* factorial(void *arg){
    int num = (int) arg;
    unsigned int result;
    
    result = (num<0) ? 0 : 1;

    printf("%d! = ",num);
    while(num > 1){
        result *= num;
        num--;
    }
    printf("%u\n",result);
}
