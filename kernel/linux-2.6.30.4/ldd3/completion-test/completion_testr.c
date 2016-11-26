#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>

int main()
{
	int sculltest;
	int code;
	
	sculltest = open("/dev/complete",O_RDONLY );

		if ((code=read(sculltest , NULL , 0)) < 0) printf("read error! code=%d \n",code);
		else   printf("read ok! code=%d \n",code);

	close(sculltest);
 
 exit(0);
}
