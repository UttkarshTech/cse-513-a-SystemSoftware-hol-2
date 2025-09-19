/*
============================================================================
Name : 4.c
Author : Uttkarsh Ranjan
Description : Write a program to measure how much time is taken to execute 100 getppid ( )
system call. Use time stamp counter.
Date: 19th September 2025
============================================================================
*/

#include <stdio.h>
#include <unistd.h>
#include <stdint.h>

static inline uint64_t read_tsc() {
    unsigned int low, high;
    __asm__ __volatile__("rdtsc" : "=a"(low), "=d"(high));
    return ((uint64_t)high << 32) | low;
}

uint64_t measure_syscalls(int n) {
    uint64_t begin = read_tsc();
    for (int j = 0; j < n; j++) {
        getppid();
    }
    uint64_t finish = read_tsc();
    return finish - begin;
}

int main() {
    int count = 100;
    uint64_t cycles = measure_syscalls(count);
    printf("Cycles for %d getppid() calls: %llu\n", count, (unsigned long long)cycles);
    printf("Average cycles per call: %llu\n", (unsigned long long)(cycles / count));
    return 0;
}

/*
============================================================================
uttkarsh-ranjan@uttkarsh-ranjan-ubuntu-vm:~/Desktop/SystemSoftware/HOL-2/4$ gcc 4.c
uttkarsh-ranjan@uttkarsh-ranjan-ubuntu-vm:~/Desktop/SystemSoftware/HOL-2/4$ ./a.out
Cycles for 100 getppid() calls: 51896
Average cycles per call: 518
============================================================================
*/