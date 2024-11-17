/*
NAME: JAN KOWAL
ASSIGNMENT: LAB 9 SYSTEM CALLS
SECTION: 111
DATE: 2024-11-16
*/

#include <stdio.h>
#include <unistd.h>
#include <time.h>

int main(int argc, char* argv[])
{
    // Reduce the priority by 10
    int priority = nice(10);
    if (priority == -1) {
        perror("nice");
        return 1;
    }

    // Sleep for 1,837,272,638 nanoseconds
    struct timespec req;
    req.tv_sec = 1; // 1 second
    req.tv_nsec = 837272638; // 837,272,638 nanoseconds

    if (nanosleep(&req, NULL) == -1) {
        perror("nanosleep");
        return 1;
    }

    // Print goodbye message
    printf("Goodbye!\n");

    return 0;
}