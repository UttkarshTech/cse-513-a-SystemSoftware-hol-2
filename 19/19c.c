/*
============================================================================
Name : 19c.c
Author : Uttkarsh Ranjan
Description : Create a FIFO file by
                a. mknod command
                b. mkfifo command
                c. use strace command to find out, which command (mknod or mkfifo) is better.
                c. mknod system call
                d. mkfifo library function
Date: 19th September 2025
============================================================================
*/

#define _XOPEN_SOURCE 700
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>

int main() {
    const char *fname = "19_syscall";

    if (mknod(fname, S_IFIFO | 0666, 0) == -1) {
        perror("mknod");
        exit(1);
    }

    printf("FIFO created using mknod system call: %s\n", fname);
    return 0;
}

/*
============================================================================
uttkarsh-ranjan@uttkarsh-ranjan-ubuntu-vm:~/Desktop/SystemSoftware/HOL-2/19$ gcc 19c.c -o 19c.out
uttkarsh-ranjan@uttkarsh-ranjan-ubuntu-vm:~/Desktop/SystemSoftware/HOL-2/19$ gcc 19d.c -o 19d.out
uttkarsh-ranjan@uttkarsh-ranjan-ubuntu-vm:~/Desktop/SystemSoftware/HOL-2/19$ ls -l
total 56
-rw-rw-r-- 1 uttkarsh-ranjan uttkarsh-ranjan 18060 Sep 19 00:51 19c.c
-rwxrwxr-x 1 uttkarsh-ranjan uttkarsh-ranjan 16088 Sep 19 00:53 19c.out
-rw-rw-r-- 1 uttkarsh-ranjan uttkarsh-ranjan   283 Sep 19 00:51 19d.c
-rwxrwxr-x 1 uttkarsh-ranjan uttkarsh-ranjan 16088 Sep 19 00:53 19d.out
uttkarsh-ranjan@uttkarsh-ranjan-ubuntu-vm:~/Desktop/SystemSoftware/HOL-2/19$ strace mknod 19_mknod p
execve("/usr/bin/mknod", ["mknod", "19_mknod", "p"], 0x7ffc7f2bfe00 /* 49 vars ) = 0
brk(NULL)                               = 0x633874e31000
mmap(NULL, 8192, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0) = 0x70bac8690000
access("/etc/ld.so.preload", R_OK)      = -1 ENOENT (No such file or directory)
openat(AT_FDCWD, "/etc/ld.so.cache", O_RDONLY|O_CLOEXEC) = 3
fstat(3, {st_mode=S_IFREG|0644, st_size=64675, ...}) = 0
mmap(NULL, 64675, PROT_READ, MAP_PRIVATE, 3, 0) = 0x70bac8680000
close(3)                                = 0
openat(AT_FDCWD, "/lib/x86_64-linux-gnu/libselinux.so.1", O_RDONLY|O_CLOEXEC) = 3
read(3, "\177ELF\2\1\1\0\0\0\0\0\0\0\0\0\3\0>\0\1\0\0\0\0\0\0\0\0\0\0\0"..., 832) = 832
fstat(3, {st_mode=S_IFREG|0644, st_size=174472, ...}) = 0
mmap(NULL, 181960, PROT_READ, MAP_PRIVATE|MAP_DENYWRITE, 3, 0) = 0x70bac8653000
mmap(0x70bac8659000, 118784, PROT_READ|PROT_EXEC, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 3, 0x6000) = 0x70bac8659000
mmap(0x70bac8676000, 24576, PROT_READ, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 3, 0x23000) = 0x70bac8676000
mmap(0x70bac867c000, 8192, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 3, 0x29000) = 0x70bac867c000
mmap(0x70bac867e000, 5832, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_FIXED|MAP_ANONYMOUS, -1, 0) = 0x70bac867e000
close(3)                                = 0
openat(AT_FDCWD, "/lib/x86_64-linux-gnu/libc.so.6", O_RDONLY|O_CLOEXEC) = 3
read(3, "\177ELF\2\1\1\3\0\0\0\0\0\0\0\0\3\0>\0\1\0\0\0\220\243\2\0\0\0\0\0"..., 832) = 832
pread64(3, "\6\0\0\0\4\0\0\0@\0\0\0\0\0\0\0@\0\0\0\0\0\0\0@\0\0\0\0\0\0\0"..., 784, 64) = 784
fstat(3, {st_mode=S_IFREG|0755, st_size=2125328, ...}) = 0
pread64(3, "\6\0\0\0\4\0\0\0@\0\0\0\0\0\0\0@\0\0\0\0\0\0\0@\0\0\0\0\0\0\0"..., 784, 64) = 784
mmap(NULL, 2170256, PROT_READ, MAP_PRIVATE|MAP_DENYWRITE, 3, 0) = 0x70bac8400000
mmap(0x70bac8428000, 1605632, PROT_READ|PROT_EXEC, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 3, 0x28000) = 0x70bac8428000
mmap(0x70bac85b0000, 323584, PROT_READ, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 3, 0x1b0000) = 0x70bac85b0000
mmap(0x70bac85ff000, 24576, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 3, 0x1fe000) = 0x70bac85ff000
mmap(0x70bac8605000, 52624, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_FIXED|MAP_ANONYMOUS, -1, 0) = 0x70bac8605000
close(3)                                = 0
openat(AT_FDCWD, "/lib/x86_64-linux-gnu/libpcre2-8.so.0", O_RDONLY|O_CLOEXEC) = 3
read(3, "\177ELF\2\1\1\0\0\0\0\0\0\0\0\0\3\0>\0\1\0\0\0\0\0\0\0\0\0\0\0"..., 832) = 832
fstat(3, {st_mode=S_IFREG|0644, st_size=625344, ...}) = 0
mmap(NULL, 627472, PROT_READ, MAP_PRIVATE|MAP_DENYWRITE, 3, 0) = 0x70bac8366000
mmap(0x70bac8368000, 450560, PROT_READ|PROT_EXEC, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 3, 0x2000) = 0x70bac8368000
mmap(0x70bac83d6000, 163840, PROT_READ, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 3, 0x70000) = 0x70bac83d6000
mmap(0x70bac83fe000, 8192, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 3, 0x97000) = 0x70bac83fe000
close(3)                                = 0
mmap(NULL, 12288, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0) = 0x70bac8650000
arch_prctl(ARCH_SET_FS, 0x70bac8650800) = 0
set_tid_address(0x70bac8650ad0)         = 26349
set_robust_list(0x70bac8650ae0, 24)     = 0
rseq(0x70bac8651120, 0x20, 0, 0x53053053) = 0
mprotect(0x70bac85ff000, 16384, PROT_READ) = 0
mprotect(0x70bac83fe000, 4096, PROT_READ) = 0
mprotect(0x70bac867c000, 4096, PROT_READ) = 0
mprotect(0x633855970000, 4096, PROT_READ) = 0
mprotect(0x70bac86ce000, 8192, PROT_READ) = 0
prlimit64(0, RLIMIT_STACK, NULL, {rlim_cur=8192*1024, rlim_max=RLIM64_INFINITY}) = 0
munmap(0x70bac8680000, 64675)           = 0
statfs("/sys/fs/selinux", 0x7ffde1319260) = -1 ENOENT (No such file or directory)
statfs("/selinux", 0x7ffde1319260)      = -1 ENOENT (No such file or directory)
getrandom("\x3a\x84\xc1\x68\x24\xe2\xa9\xec", 8, GRND_NONBLOCK) = 8
brk(NULL)                               = 0x633874e31000
brk(0x633874e52000)                     = 0x633874e52000
openat(AT_FDCWD, "/proc/filesystems", O_RDONLY|O_CLOEXEC) = 3
fstat(3, {st_mode=S_IFREG|0444, st_size=0, ...}) = 0
read(3, "nodev\tsysfs\nnodev\ttmpfs\nnodev\tbd"..., 1024) = 389
read(3, "", 1024)                       = 0
close(3)                                = 0
access("/etc/selinux/config", F_OK)     = -1 ENOENT (No such file or directory)
openat(AT_FDCWD, "/usr/lib/locale/locale-archive", O_RDONLY|O_CLOEXEC) = 3
fstat(3, {st_mode=S_IFREG|0644, st_size=14596880, ...}) = 0
mmap(NULL, 14596880, PROT_READ, MAP_PRIVATE, 3, 0) = 0x70bac7400000
close(3)                                = 0
mknodat(AT_FDCWD, "19_mknod", S_IFIFO|0666) = 0
close(1)                                = 0
close(2)                                = 0
exit_group(0)                           = ?
+++ exited with 0 +++
uttkarsh-ranjan@uttkarsh-ranjan-ubuntu-vm:~/Desktop/SystemSoftware/HOL-2/19$ strace mkfifo 19_mkfifo
execve("/usr/bin/mkfifo", ["mkfifo", "19_mkfifo"], 0x7ffc685cd988 /* 49 vars ) = 0
brk(NULL)                               = 0x61109148d000
mmap(NULL, 8192, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0) = 0x79a8cb40a000
access("/etc/ld.so.preload", R_OK)      = -1 ENOENT (No such file or directory)
openat(AT_FDCWD, "/etc/ld.so.cache", O_RDONLY|O_CLOEXEC) = 3
fstat(3, {st_mode=S_IFREG|0644, st_size=64675, ...}) = 0
mmap(NULL, 64675, PROT_READ, MAP_PRIVATE, 3, 0) = 0x79a8cb3fa000
close(3)                                = 0
openat(AT_FDCWD, "/lib/x86_64-linux-gnu/libselinux.so.1", O_RDONLY|O_CLOEXEC) = 3
read(3, "\177ELF\2\1\1\0\0\0\0\0\0\0\0\0\3\0>\0\1\0\0\0\0\0\0\0\0\0\0\0"..., 832) = 832
fstat(3, {st_mode=S_IFREG|0644, st_size=174472, ...}) = 0
mmap(NULL, 181960, PROT_READ, MAP_PRIVATE|MAP_DENYWRITE, 3, 0) = 0x79a8cb3cd000
mmap(0x79a8cb3d3000, 118784, PROT_READ|PROT_EXEC, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 3, 0x6000) = 0x79a8cb3d3000
mmap(0x79a8cb3f0000, 24576, PROT_READ, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 3, 0x23000) = 0x79a8cb3f0000
mmap(0x79a8cb3f6000, 8192, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 3, 0x29000) = 0x79a8cb3f6000
mmap(0x79a8cb3f8000, 5832, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_FIXED|MAP_ANONYMOUS, -1, 0) = 0x79a8cb3f8000
close(3)                                = 0
openat(AT_FDCWD, "/lib/x86_64-linux-gnu/libc.so.6", O_RDONLY|O_CLOEXEC) = 3
read(3, "\177ELF\2\1\1\3\0\0\0\0\0\0\0\0\3\0>\0\1\0\0\0\220\243\2\0\0\0\0\0"..., 832) = 832
pread64(3, "\6\0\0\0\4\0\0\0@\0\0\0\0\0\0\0@\0\0\0\0\0\0\0@\0\0\0\0\0\0\0"..., 784, 64) = 784
fstat(3, {st_mode=S_IFREG|0755, st_size=2125328, ...}) = 0
pread64(3, "\6\0\0\0\4\0\0\0@\0\0\0\0\0\0\0@\0\0\0\0\0\0\0@\0\0\0\0\0\0\0"..., 784, 64) = 784
mmap(NULL, 2170256, PROT_READ, MAP_PRIVATE|MAP_DENYWRITE, 3, 0) = 0x79a8cb000000
mmap(0x79a8cb028000, 1605632, PROT_READ|PROT_EXEC, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 3, 0x28000) = 0x79a8cb028000
mmap(0x79a8cb1b0000, 323584, PROT_READ, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 3, 0x1b0000) = 0x79a8cb1b0000
mmap(0x79a8cb1ff000, 24576, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 3, 0x1fe000) = 0x79a8cb1ff000
mmap(0x79a8cb205000, 52624, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_FIXED|MAP_ANONYMOUS, -1, 0) = 0x79a8cb205000
close(3)                                = 0
openat(AT_FDCWD, "/lib/x86_64-linux-gnu/libpcre2-8.so.0", O_RDONLY|O_CLOEXEC) = 3
read(3, "\177ELF\2\1\1\0\0\0\0\0\0\0\0\0\3\0>\0\1\0\0\0\0\0\0\0\0\0\0\0"..., 832) = 832
fstat(3, {st_mode=S_IFREG|0644, st_size=625344, ...}) = 0
mmap(NULL, 627472, PROT_READ, MAP_PRIVATE|MAP_DENYWRITE, 3, 0) = 0x79a8cb333000
mmap(0x79a8cb335000, 450560, PROT_READ|PROT_EXEC, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 3, 0x2000) = 0x79a8cb335000
mmap(0x79a8cb3a3000, 163840, PROT_READ, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 3, 0x70000) = 0x79a8cb3a3000
mmap(0x79a8cb3cb000, 8192, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 3, 0x97000) = 0x79a8cb3cb000
close(3)                                = 0
mmap(NULL, 12288, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0) = 0x79a8cb330000
arch_prctl(ARCH_SET_FS, 0x79a8cb330800) = 0
set_tid_address(0x79a8cb330ad0)         = 26354
set_robust_list(0x79a8cb330ae0, 24)     = 0
rseq(0x79a8cb331120, 0x20, 0, 0x53053053) = 0
mprotect(0x79a8cb1ff000, 16384, PROT_READ) = 0
mprotect(0x79a8cb3cb000, 4096, PROT_READ) = 0
mprotect(0x79a8cb3f6000, 4096, PROT_READ) = 0
mprotect(0x6110571cb000, 4096, PROT_READ) = 0
mprotect(0x79a8cb448000, 8192, PROT_READ) = 0
prlimit64(0, RLIMIT_STACK, NULL, {rlim_cur=8192*1024, rlim_max=RLIM64_INFINITY}) = 0
munmap(0x79a8cb3fa000, 64675)           = 0
statfs("/sys/fs/selinux", 0x7fff05a62e90) = -1 ENOENT (No such file or directory)
statfs("/selinux", 0x7fff05a62e90)      = -1 ENOENT (No such file or directory)
getrandom("\x93\x0c\xbe\x2f\xb3\x13\xf1\xb4", 8, GRND_NONBLOCK) = 8
brk(NULL)                               = 0x61109148d000
brk(0x6110914ae000)                     = 0x6110914ae000
openat(AT_FDCWD, "/proc/filesystems", O_RDONLY|O_CLOEXEC) = 3
fstat(3, {st_mode=S_IFREG|0444, st_size=0, ...}) = 0
read(3, "nodev\tsysfs\nnodev\ttmpfs\nnodev\tbd"..., 1024) = 389
read(3, "", 1024)                       = 0
close(3)                                = 0
access("/etc/selinux/config", F_OK)     = -1 ENOENT (No such file or directory)
openat(AT_FDCWD, "/usr/lib/locale/locale-archive", O_RDONLY|O_CLOEXEC) = 3
fstat(3, {st_mode=S_IFREG|0644, st_size=14596880, ...}) = 0
mmap(NULL, 14596880, PROT_READ, MAP_PRIVATE, 3, 0) = 0x79a8ca200000
close(3)                                = 0
mknodat(AT_FDCWD, "19_mkfifo", S_IFIFO|0666) = 0
close(1)                                = 0
close(2)                                = 0
exit_group(0)                           = ?
+++ exited with 0 +++
uttkarsh-ranjan@uttkarsh-ranjan-ubuntu-vm:~/Desktop/SystemSoftware/HOL-2/19$ ./19c.out
FIFO created using mknod system call: 19_syscall
uttkarsh-ranjan@uttkarsh-ranjan-ubuntu-vm:~/Desktop/SystemSoftware/HOL-2/19$ ./19d.out
FIFO created using mkfifo library function: 19_lib
uttkarsh-ranjan@uttkarsh-ranjan-ubuntu-vm:~/Desktop/SystemSoftware/HOL-2/19$ ls -l 
total 56
-rw-rw-r-- 1 uttkarsh-ranjan uttkarsh-ranjan 18060 Sep 19 00:51 19c.c
-rwxrwxr-x 1 uttkarsh-ranjan uttkarsh-ranjan 16088 Sep 19 00:53 19c.out
-rw-rw-r-- 1 uttkarsh-ranjan uttkarsh-ranjan   283 Sep 19 00:51 19d.c
-rwxrwxr-x 1 uttkarsh-ranjan uttkarsh-ranjan 16088 Sep 19 00:53 19d.out
prw-rw-r-- 1 uttkarsh-ranjan uttkarsh-ranjan     0 Sep 19 00:57 19_lib
prw-rw-r-- 1 uttkarsh-ranjan uttkarsh-ranjan     0 Sep 19 00:57 19_mkfifo
prw-rw-r-- 1 uttkarsh-ranjan uttkarsh-ranjan     0 Sep 19 00:56 19_mknod
prw-rw-r-- 1 uttkarsh-ranjan uttkarsh-ranjan     0 Sep 19 00:57 19_syscall

============================================================================
*/