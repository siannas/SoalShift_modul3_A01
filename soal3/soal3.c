#include<stdio.h>
#include<string.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>

int status;
int WakeUp_Status = 0;
int Spirit_Status = 100;
int Acount = 0;
int Icount = 0;

void* Agmal(void *arg)
{
    while(status){
        if(WakeUp_Status >= 100){
            printf("Agmal Terbangun,mereka bangun pagi dan berolahraga\n");
            status = 0;
            return NULL;
        }

        if(Icount == 3){
            printf("Fitur Iraj Ayo Tidur disabled 10 s\n");
            sleep(10);
            Icount = 0;
        }
    }

    return NULL;
}

void* Iraj(void *arg)
{
    while(status){

        if(Spirit_Status <= 0){
            printf("Iraj ikut tidur, dan bangun kesiangan bersama Agmal\n");
            status = 0;
            return NULL;
        }

        if(Acount == 3){
            printf("Agmal Ayo Bangun disabled 10 s\n");
            sleep(10);
            Acount = 0;
        }
    }

    return NULL;
}

int main(void)
{
    pthread_t tid1, tid2;
    char say[100];
    status = 1;

    pthread_create(&(tid1), NULL, Agmal, NULL);
    pthread_create(&(tid2), NULL, Iraj, NULL);

    while(status){
        fgets(say, sizeof(say), stdin);
	printf("-----------\n");

        if(strcmp(say, "Agmal Ayo Bangun\n") == 0 && Acount<3){
            Icount++;
            WakeUp_Status += 15;
        }
        else if(strcmp(say, "Iraj Ayo Tidur\n") == 0 && Icount<3){
            Acount++;
            Spirit_Status -= 20;
        }
        else if(strcmp(say, "All Status\n") == 0){
            printf("Agmal WakeUp_Status = %d\nIraj Spirit_Status = %d\n", WakeUp_Status, Spirit_Status);
        }
    }

    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);
    return 0;
}
