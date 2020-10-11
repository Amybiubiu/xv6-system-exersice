#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
    if(argc < 2){
        printf("missing sleep time value\n");
        exit();
    }
    // convert string to integer using atoi (see user/ulib.c)
    // pass argv and then use the system call sleep (see user/usys.S and kernel/sysproc.c).
    // exit
    const int time = atoi(argv[1]);
    sleep(time);
    exit();
}