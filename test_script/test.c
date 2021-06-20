#include <stdio.h>
#include <unistd.h>
#include <errno.h>

#define __NR_getuserweight 447
#define __NR_setuserweight 448
int main()
{
    int ret = syscall(__NR_setuserweight, -1, 666); 
    printf("set weight uid -1 status: %d\n", ret);

    ret = syscall(__NR_setuserweight, 3, 108); 
    printf("set weight uid 3 status: %d\n", ret);

    ret = syscall(__NR_getuserweight, 4); 
    printf("weight uid 4: %d\n", ret);

    ret = syscall(__NR_setuserweight, 166, 112); 
    printf("set weight uid 166 status: %d\n", ret);

    ret = syscall(__NR_setuserweight, 19, 2); 
    printf("set weight uid 4 status: %d\n", ret);

    ret = syscall(__NR_getuserweight, 4); 
    printf("weight uid 4: %d\n", ret);

    ret = syscall(__NR_getuserweight, 3); 
    printf("weight uid 3: %d\n", ret);

    ret = syscall(__NR_getuserweight, -1); 
    printf("weight uid -1: %d\n", ret);

    ret = syscall(__NR_getuserweight, 10000); 
    printf("weight uid 10000: %d\n", ret);
    return 0;
}