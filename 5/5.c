/*
============================================================================
Name : 5.c
Author : Uttkarsh Ranjan
Description : Write a program to print the system limitation of
            a. maximum length of the arguments to the exec family of functions.
            b. maximum number of simultaneous process per user id.
            c. number of clock ticks (jiffy) per second.
            d. maximum number of open files
            e. size of a page
            f. total number of pages in the physical memory
            g. number of currently available pages in the physical memory.
Date: 19th September 2025
============================================================================
*/

#include <stdio.h>
#include <unistd.h>

void show_limit(const char *label, int name) {
    long res = sysconf(name);
    if (res == -1)
        perror(label);
    else
        printf("%s: %ld\n", label, res);
}

int main() {
    show_limit("Maximum argument length for exec", _SC_ARG_MAX);
    show_limit("Maximum simultaneous processes per user ID", _SC_CHILD_MAX);
    show_limit("Clock ticks per second", _SC_CLK_TCK);
    show_limit("Maximum number of open files", _SC_OPEN_MAX);
    show_limit("Page size (bytes)", _SC_PAGESIZE);
    show_limit("Total physical pages", _SC_PHYS_PAGES);
    show_limit("Available physical pages", _SC_AVPHYS_PAGES);
    return 0;
}

/*
============================================================================
uttkarsh-ranjan@uttkarsh-ranjan-ubuntu-vm:~/Desktop/SystemSoftware/HOL-2/5$ gcc 5.c
uttkarsh-ranjan@uttkarsh-ranjan-ubuntu-vm:~/Desktop/SystemSoftware/HOL-2/5$ ./a.out
Maximum argument length for exec: 2097152
Maximum simultaneous processes per user ID: 31450
Clock ticks per second: 100
Maximum number of open files: 1024
Page size (bytes): 4096
Total physical pages: 2033119
Available physical pages: 262952
============================================================================
*/