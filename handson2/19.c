// a) mknod <fifoname> p
// b) mkfifo myfio
// c) run in different terminal
//    strace mknod myfifo1 p
//    strace mkfifo myfifo2

// d)

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include<stdio.h>

int main() {
    int result = mknod("myfifo", S_IFIFO | 0666, 0);
    if (result == -1) {
        perror("mknod");
        return 1;
    }
    return 0;
}

// e)
// int main(){
	
// 	int mkfifo_val = mkfifo("mkfifo" , 0666);
// 	if(mkfifo_val == -1){
// 		perror("couldn't create FIFO file");
// 	}
// }