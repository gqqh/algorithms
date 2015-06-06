 /*
	测试代码如下：
	Main.c:
*/
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <error.h>
#include <stdlib.h>

#define DEVNAME "/dev/gehu"

int main()
{
	int fd;
	extern int errno;
	fd = open(DEVNAME, O_RDWR);
	if(fd == -1){
		perror("open /dev/gehu ");
		printf("file %s is opening......failure!\n", DEVNAME);
		exit(1);
	}
	printf("file %s is opening......successfully!\nits fd is %d\n", DEVNAME, fd);
	
	getchar();
	close(fd);

	return 0;
}
