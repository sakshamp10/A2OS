#include <unistd.h>
#include <pthread.h>
#include <sched.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>


int p1=0,p2=1,p3=1;

void* countA(){
    struct  timespec ta2;
    struct sched_param *sp;
    sp=(struct sched_param*)malloc(sizeof(struct sched_param));
    sp->sched_priority=p1;
    pthread_setschedparam(pthread_self(),SCHED_OTHER,sp);
    clock_gettime(CLOCK_REALTIME,&ta2);
    nice(0);
    for(long long i=0;i<4294967296;i++){
        if(p1){
            continue;
        }
    }
    struct timespec ta1;
    clock_gettime(CLOCK_REALTIME,&ta1);
    printf("countA =%f\n",(ta1.tv_sec-ta2.tv_sec)+(ta1.tv_nsec-ta2.tv_nsec)/1e9);
    return NULL;
}

void* countB(){
    struct  timespec tb1,tb2;
    struct sched_param *sp;
    sp=(struct sched_param*)malloc(sizeof(struct sched_param));
    sp->sched_priority=p2;
    pthread_setschedparam(pthread_self(),SCHED_RR,sp);
    clock_gettime(CLOCK_REALTIME,&tb2);
    for(long long i=0;i<4294967296;i++){
        if(p2){
            continue;
        }
    }
    clock_gettime(CLOCK_REALTIME,&tb1);
    printf("countB =%f\n",tb1.tv_sec-tb2.tv_sec+(tb1.tv_nsec-tb2.tv_nsec)/1e9);
    return NULL;
}

void* countC(){
    struct  timespec tc1,tc2;
    struct sched_param *sp;
    sp=(struct sched_param*)malloc(sizeof(struct sched_param));
    sp->sched_priority=p3;
    pthread_setschedparam(pthread_self(),SCHED_FIFO,sp);
    clock_gettime(CLOCK_REALTIME,&tc2);
    for(long long i=0;i<4294967296;i++){
        if(p3){
            continue;
        }
    }
    clock_gettime(CLOCK_REALTIME,&tc1);
    printf("countC =%f\n",tc1.tv_sec-tc2.tv_sec+(tc1.tv_nsec-tc2.tv_nsec)/1e9);
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
