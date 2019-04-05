#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void* factorial(void *arg);

int main(){
	int err;
    pthread_t tid[100];

    //scan arg

	while(1){
		err = pthread_create( &(tid[i]), NULL, prime, (void*) (arr[i]));
		if(err){
            fprintf(stderr,"Error - pthread_create() return code: %d\n",err);
            exit(EXIT_FAILURE);
        }
	}

	for(i=0;i<T;i++){
		pthread_join(tid[i], NULL);
	}

	return 0;
}

void* factorial(void *arg){
    int num = (int) arg;
    int result;
    
    result = (num<0) ? 0 : 1;

    printf("%d! = ",num);
    while(num > 1){
        result *= num;
        num--;
    }
    printf("%d",result);
}