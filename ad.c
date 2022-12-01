#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <pthread.h>
#include <sched.h>
#include <math.h>
#include <unistd.h>


void count_A(){
    
    long long i=1;
    long long y = 1;
    long long x=(y<<32);
    while(i<=x) {
        //printf("%lld",i);
        i++;
    }
}

void* call_A(){
    nice(0);
    struct sched_param* p1 = (struct sched_param*)malloc(sizeof(struct sched_param));
    if(p1 != NULL) p1 -> sched_priority = 0;

    pthread_setschedparam(pthread_self(), SCHED_OTHER, p1);

    struct timespec s,e;
    int st = clock_gettime(CLOCK_REALTIME,&s);
    count_A();
    int et = clock_gettime(CLOCK_REALTIME,&e);
    struct timespec ans;
    ans.tv_sec=(e.tv_sec-s.tv_sec);
    ans.tv_nsec=(e.tv_nsec-s.tv_nsec);
    double rt = ans.tv_sec + ans.tv_nsec/ 1e9L;

    printf("countA's Run Time is %lfs\n",rt);

    free(p1);
    return NULL;
}

void count_B(){
    long long i=1;
    long long y = 1;
    long long x=(y<<32);
    while(i<=x) i++;
}

void* call_B(){
    struct sched_param* p2 = (struct sched_param*)malloc(sizeof(struct sched_param));
    if(p2 != NULL) p2 -> sched_priority = 1;

    pthread_setschedparam(pthread_self(), SCHED_RR, p2);
    /*int policy;
    struct sched_param p;

    pthread_getschedparam(pthread_self(),&policy,&p);
    printf("p->%d p.s->%d",policy,p.sched_priority);*/
    struct timespec s,e;
    int st = clock_gettime(CLOCK_REALTIME,&s);
    count_B();

    int et = clock_gettime(CLOCK_REALTIME,&e);
    struct timespec ans;
    ans.tv_sec=(e.tv_sec-s.tv_sec);
    ans.tv_nsec=(e.tv_nsec-s.tv_nsec);
    double rt = ans.tv_sec + ans.tv_nsec/ 1e9L;

    printf("countB's Run Time is %lfs\n",rt);
    
    free(p2);
    return NULL;
}

void count_C(){
    long long i=1;
    long long y = 1;
    long long x=(y<<32);
    while(i<=x) i++;
}

void* call_C(){
    struct sched_param* p3 = (struct sched_param*)malloc(sizeof(struct sched_param));
    if(p3 != NULL) p3 -> sched_priority =1;

    pthread_setschedparam(pthread_self(), SCHED_FIFO, p3);

    struct timespec s,e;
    int st = clock_gettime(CLOCK_REALTIME,&s);
    count_C();
    int et = clock_gettime(CLOCK_REALTIME,&e);
    struct timespec ans;
    ans.tv_sec=(e.tv_sec-s.tv_sec);
    ans.tv_nsec=(e.tv_nsec-s.tv_nsec);
    double rt = ans.tv_sec + ans.tv_nsec/ 1e9L;
    printf("countC's Run Time is %lfs\n",rt);
    
    free(p3);
    return NULL;
}

int main(){
    
    pthread_t thr_A;
    pthread_t thr_B;
    pthread_t thr_C;
    pthread_create(&thr_A, NULL, call_A, NULL);

    pthread_create(&thr_B, NULL, call_B, NULL);

    pthread_create(&thr_C, NULL, call_C, NULL);
    pthread_join(thr_A, NULL);
    pthread_join(thr_B, NULL);
    pthread_join(thr_C, NULL);
    
    return 0;
    
}
