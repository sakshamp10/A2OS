#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>
#include<unistd.h>
#include <time.h>
#include <sched.h>

int main() {
    FILE *datafile = fopen("/home/saksham/histogram/data.txt", "w");
    pid_t proc_a = fork();
    if (proc_a == 0) {
        struct timespec ta1, ta2;
        int Ta1 = clock_gettime(CLOCK_REALTIME, &ta1);
        pid_t proc_1 = fork();
        struct sched_param sp1;
        sp1.sched_priority = 0;
        sched_setscheduler(proc_1, SCHED_OTHER, &sp1);
        if (proc_1 == 0) {
            execlp("/bin/sh", "sh", "b1.sh", NULL);
        }
        else if (proc_1 > 0) {
            int w1 = waitpid(proc_1, 0, 0);
            int Tb2 = clock_gettime(CLOCK_REALTIME, &ta2);
            double time = (ta2.tv_sec - ta1.tv_sec + (ta2.tv_nsec - ta1.tv_nsec) / (double) 1e9);

            printf("----------RunTime for first thread: %lfs----------\n", (time));
            fprintf(datafile, "%lf\n", time);
        }

        pid_t proc_b = fork();
        if(proc_b==0){
            struct timespec tb1, tb2;
            int Tb1 = clock_gettime(CLOCK_REALTIME, &tb1);
            pid_t proc_2 = fork();
            struct sched_param sp2;
            sp2.sched_priority = 0;
            sched_setscheduler(proc_2, SCHED_RR, &sp2);
            if (proc_2 == 0) {
                execlp("/bin/sh", "sh", "b2.sh", NULL);
            } else if (proc_2 > 0) {
                int w2 = waitpid(proc_2, 0, 0);
                int Tb2 = clock_gettime(CLOCK_REALTIME, &tb2);
                double time = (tb2.tv_sec - tb1.tv_sec + (tb2.tv_nsec - tb1.tv_nsec) / (double) 1e9);

                printf("----------RunTime for first thread: %lfs----------\n", (time));
                fprintf(datafile, "%lf\n", time);
            }

            pid_t proc_c = fork();
            if(proc_c==0){
                struct timespec tc1, tc2;
                int Tc1 = clock_gettime(CLOCK_REALTIME, &tc1);
                pid_t proc_3 = fork();
                struct sched_param sp3;
                sp2.sched_priority = 0;
                sched_setscheduler(proc_3, SCHED_FIFO, &sp3);
                if (proc_3 == 0) {
                    execlp("/bin/sh", "sh", "b2.sh", NULL);
                } else if (proc_3 > 0) {
                    int w3 = waitpid(proc_3, 0, 0);
                    int Tc2 = clock_gettime(CLOCK_REALTIME, &tc2);
                    double time = (tc2.tv_sec - tc1.tv_sec + (tc2.tv_nsec - tc1.tv_nsec) / (double) 1e9);

                    printf("----------RunTime for first thread: %lfs----------\n", (time));
                    fprintf(datafile, "%lf\n", time);
                }
            }
            else{
                wait(NULL);
            }
        }
        else{
            wait(NULL);
        }
    }
    else {
        wait(NULL);
    }
        //     else {
//        pid_t proc_b = fork();
//        if (proc_b == 0) {
////            struct timespec tb1, tb2;
////            int Tb1 = clock_gettime(CLOCK_REALTIME, &tb1);
////            pid_t proc_2 = fork();
////            struct sched_param sp2;
////            sp2.sched_priority = 0;
////            sched_setscheduler(proc_2, SCHED_OTHER, &sp2);
////            if (proc_2 == 0) {
////                execlp("/bin/sh", "sh", "b2.sh", NULL);
////            } else if (proc_2 > 0) {
////                int w2 = waitpid(proc_2, 0, 0);
////                int Tb2 = clock_gettime(CLOCK_REALTIME, &tb2);
////                double time = (tb2.tv_sec - tb1.tv_sec + (tb2.tv_nsec - tb1.tv_nsec) / (double) 1e9);
////
////                printf("----------RunTime for first thread: %lfs----------\n", (time));
////                fprintf(datafile, "%lf\n", time);
////            }
//        } else {
//            pid_t proc_c = fork();
//            if (proc_c == 0) {
//                struct timespec tc1, tc2;
//                int Tc1 = clock_gettime(CLOCK_REALTIME, &tc1);
//                pid_t proc_3 = fork();
//                struct sched_param sp2;
//                sp2.sched_priority = 0;
//                sched_setscheduler(proc_3, SCHED_OTHER, &sp2);
//                if (proc_3 == 0) {
//                    execlp("/bin/sh", "sh", "b2.sh", NULL);
//                } else if (proc_3 > 0) {
//                    int w3 = waitpid(proc_3, 0, 0);
//                    int Tc2 = clock_gettime(CLOCK_REALTIME, &tc2);
//                    double time = (tc2.tv_sec - tc1.tv_sec + (tc2.tv_nsec - tc1.tv_nsec) / (double) 1e9);
//
//                    printf("----------RunTime for first thread: %lfs----------\n", (time));
//                    fprintf(datafile, "%lf\n", time);
//                }
//                wait(NULL);
//            }
//            wait(NULL);
//        }
//        wait(NULL);
        fclose(datafile);
        return 0;
}
