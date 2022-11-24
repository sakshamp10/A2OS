#include <unistd.h>
#include <pthread.h>
#include <sched.h>
#include <stdlib.h>
#include <time.h>


int p1=0,p2=1,p3=1;

void* countA(){
    struct  timespec t1,t2;
    struct sched_param *sp;
    sp=(struct sched_param*)malloc(sizeof(struct sched_param));
    sp->sched_priority=p1;
    pthread_setschedparam(pthread_self(),SCHED_OTHER,sp);
    clock_gettime(CLOCK_REALTIME,&t1);
    for(long long i=0;i<4294967296;i++){

    }
    clock_gettime(CLOCK_REALTIME,&t2);
    return NULL;
}

void* countB(){
    struct  timespec t1,t2;
    struct sched_param *sp;
    sp=(struct sched_param*)malloc(sizeof(struct sched_param));
    sp->sched_priority=p2;
    pthread_setschedparam(pthread_self(),SCHED_RR,sp);
    clock_gettime(CLOCK_REALTIME,&t1);
    for(long long i=0;i<4294967296;i++){

    }
    clock_gettime(CLOCK_REALTIME,&t2);
    return NULL;
}

void* countC(){
    struct  timespec t1,t2;
    struct sched_param *sp;
    sp=(struct sched_param*)malloc(sizeof(struct sched_param));
    sp->sched_priority=p3;
    pthread_setschedparam(pthread_self(),SCHED_FIFO,sp);
    clock_gettime(CLOCK_REALTIME,&t1);
    for(long long i=0;i<4294967296;i++){

    }
    clock_gettime(CLOCK_REALTIME,&t2);
    return NULL;
}


int main(){
    pthread_t ThA,ThB,ThC;
    int i=6;
    while(i--){
        pthread_create(&ThA,NULL,&countA,NULL);
        pthread_create(&ThB,NULL,&countB,NULL);
        pthread_create(&ThC,NULL,&countC,NULL);
        pthread_join(ThA,NULL);
        pthread_join(ThB,NULL);
        pthread_join(ThC,NULL);
        p1++;
        p2++;
        p3++;
    }


    return 0;
}