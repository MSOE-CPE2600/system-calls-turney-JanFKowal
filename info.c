/*
NAME: JAN KOWAL
ASSIGNMENT: LAB 9 SYSTEM CALLS
SECTION: 111
DATE: 2024-11-16
*/

#include <stdio.h>
#include <time.h>
#include <sys/utsname.h>
#include <unistd.h>
#include <sys/sysinfo.h>
#include <netdb.h>
#include <string.h>

int main() {
    // Get the current time
    struct timespec ts;
    clock_gettime(CLOCK_REALTIME, &ts);

    // Get the current time in seconds since the epoch
    time_t now = time(NULL);
    struct tm *local = localtime(&now);

    // Calculate the number of seconds since midnight
    long seconds_since_midnight = local->tm_hour * 3600 + local->tm_min * 60 + local->tm_sec;

    // Calculate the total nanoseconds since midnight
    long nanoseconds_since_midnight = seconds_since_midnight * 1000000000L + ts.tv_nsec;

    printf("Current time of day in nanoseconds since 12 AM: %ld\n", nanoseconds_since_midnight);

    // System's network name (Fully Qualified Domain Name)
    char hostname[1024];
    gethostname(hostname, sizeof(hostname));

    struct addrinfo hints, *info;
    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC;
    hints.ai_flags = AI_CANONNAME;

    if (getaddrinfo(hostname, NULL, &hints, &info) == 0) {
        printf("Network name (FQDN): %s\n", info->ai_canonname);
        freeaddrinfo(info);
    } else {
        printf("Hostname: %s\n", hostname);
    }

    // Operating system information
    struct utsname uts;
    uname(&uts);
    printf("OS Name: %s\n", uts.sysname);
    printf("OS Release: %s\n", uts.release);
    printf("OS Version: %s\n", uts.version);
    printf("Hardware Type: %s\n", uts.machine);

    // Number of CPUs
    long nprocs = sysconf(_SC_NPROCESSORS_ONLN);
    printf("Number of CPUs: %ld\n", nprocs);

    // Physical memory information
    struct sysinfo si;
    sysinfo(&si);
    unsigned long total_ram = si.totalram * si.mem_unit;
    unsigned long free_ram = si.freeram * si.mem_unit;
    printf("Total Physical Memory: %lu bytes\n", total_ram);
    printf("Free Physical Memory: %lu bytes\n", free_ram);

    return 0;
}