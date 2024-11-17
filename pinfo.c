#define _GNU_SOURCE
/*
NAME: JAN KOWAL
ASSIGNMENT: LAB 9 SYSTEM CALLS
SECTION: 111
DATE: 2024-11-16
*/


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <sched.h>
#include <errno.h>

void print_scheduler(int policy);

int main(int argc, char* argv[]) {
    pid_t pid;
    if (argc > 1) {
        pid = atoi(argv[1]);
    } else {
        pid = getpid();
    }

    int priority = getpriority(PRIO_PROCESS, pid);
    if (priority == -1 && errno != 0) {
        perror("Error getting priority");
        return 1;
    }

    int policy = sched_getscheduler(pid);
    if (policy == -1) {
        perror("Error getting scheduling method");
        return 1;
    }

    printf("Process ID: %d\n", pid);
    printf("Process priority: %d\n", priority);
    print_scheduler(policy);

    return 0;
}

void print_scheduler(int policy) {
    switch (policy) {
        case SCHED_OTHER:
            printf("Scheduling method: SCHED_OTHER\n");
            break;
        case SCHED_FIFO:
            printf("Scheduling method: SCHED_FIFO\n");
            break;
        case SCHED_RR:
            printf("Scheduling method: SCHED_RR\n");
            break;
        case SCHED_BATCH:
            printf("Scheduling method: SCHED_BATCH\n");
            break;
        case SCHED_IDLE:
            printf("Scheduling method: SCHED_IDLE\n");
            break;
        default:
            printf("Unknown scheduling method\n");
    }
}
