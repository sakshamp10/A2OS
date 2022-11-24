#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>
#include<unistd.h>
#include <time.h>
#include <sched.h>

int main() {
    FILE *datafile = fopen("/home/saksham/histogram/data.txt", "a");
    pid_t proc_a = fork();
    if (proc_a == 0) {
        struct timespec ta1;
        int Ta1 = clock_gettime(CLOCK_REALTIME, &ta1);
        pid_t proc_1 = fork();
        struct sched_param sp1;
        sp1.sched_priority = 0;
        sched_setscheduler(proc_1, SCHED_OTHER, &sp1);
        if (proc_1 == 0) {
            execlp("/bin/sh", "sh", "b1.sh", NULL);
        }
        else if (proc_1 > 0) {
            struct timespec ta2;
            int w1,Tb2;
            Tb2 = clock_gettime(CLOCK_REALTIME, &ta2);
            w1 =waitpid(proc_1, 0, 0);
            fprintf(datafile, "first process: %lf\n", (double)((ta2.tv_sec - ta1.tv_sec + (ta2.tv_nsec - ta1.tv_nsec) / (double) 1e9)));
        }

        pid_t proc_b = fork();
        if(proc_b==0){
            struct timespec tb1;
            int Tb1 = clock_gettime(CLOCK_REALTIME, &tb1);
            pid_t proc_2 = fork();
            struct sched_param sp2;
            sp2.sched_priority = 1;
            sched_setscheduler(proc_2, SCHED_RR, &sp2);
            if (proc_2 == 0) {
                execlp("/bin/sh", "sh", "b2.sh", NULL);
            } else if (proc_2 > 0) {
                int w2,Tb2;
                struct timespec tb2;
                w2=waitpid(proc_2, 0, 0);
                Tb2 = clock_gettime(CLOCK_REALTIME, &tb2);
                fprintf(datafile, "second process: %lf\n", (double)( (tb2.tv_sec - tb1.tv_sec + (tb2.tv_nsec - tb1.tv_nsec) / (double) 1e9)));
            }

            pid_t proc_c = fork();
            if(proc_c==0){
                struct timespec tc1;
                int Tc1 = clock_gettime(CLOCK_REALTIME, &tc1);
                pid_t proc_3 = fork();
                struct sched_param sp3;
                sp2.sched_priority = 1;
                sched_setscheduler(proc_3, SCHED_FIFO, &sp3);
                if (proc_3 == 0) {
                    execlp("/bin/sh", "sh", "b2.sh", NULL);
                } else if (proc_3 > 0) {
                    struct timespec tc2;
                    int w3,Tc2;
                    w3=waitpid(proc_3, 0, 0);
                    Tc2 = clock_gettime(CLOCK_REALTIME, &tc2);
                    fprintf(datafile, "third process: %lf\n", (double)(tc2.tv_sec - tc1.tv_sec + (tc2.tv_nsec - tc1.tv_nsec) / (double) 1e9));
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
        fclose(datafile);
        return 0;
}
