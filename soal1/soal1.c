#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void* factorial(void *arg);

int main(int argc, char *argv[]){
	int err, i;
    pthread_t tid[100];

    //sort
    for (i = 1; i <= argc; i++){
    	if(array[i]>array[i+1])
	{
    		temp = array[i];
    		array[i] = array[i+1];
    		array[i+1] = temp;
	}
    }//sort done;

	for(i=0;i<argc;i++){
		err = pthread_create( &(tid[i]), NULL, prime, (void*) (argv[i]));
		if(err){
            fprintf(stderr,"Error - pthread_create() return code: %d\n",err);
            exit(EXIT_FAILURE);
        }
	}

	for(i=0;i<argc;i++){
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