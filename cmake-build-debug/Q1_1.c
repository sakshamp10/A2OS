#include <unistd.h>
#include <pthread.h>
#include <sched.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>


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
    printf("countA =%f\n",((t2.tv_sec-t1.tv_sec)+(t2.tv_nsec-t1.tv_nsec))/1e9);
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
    printf("countB =%f\n",(t2.tv_sec-t1.tv_sec+t2.tv_nsec-t1.tv_nsec)/1e9);
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
    printf("countC =%f\n",(t2.tv_sec-t1.tv_sec+t2.tv_nsec-t1.tv_nsec)/1e9);
    return NULL;
}


int main(){
    pthread_t ThA,ThB,ThC;
        pthread_create(&ThA,NULL,&countA,NULL);
        pthread_create(&ThB,NULL,&countB,NULL);
        pthread_create(&ThC,NULL,&countC,NULL);
        pthread_join(ThA,NULL);
        pthread_join(ThB,NULL);
        pthread_join(ThC,NULL);


    return 0;
}