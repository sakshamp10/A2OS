#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<sched.h>

void* countA(){
    for(int i=1;i<4294967296;i++){

    }
    return NULL;
}

void* countB(){
    for(int i=1;i<4294967296;i++){

    }
    return NULL;
}

void* countC(){
    for(int i=1;i<4294967296;i++){

    }
    return NULL;
}

int main(){
    pthread_t ThrA,ThrB,ThrC;
    pthread_create(ThrA,NULL,countA(),NULL);


    return 0;
}
