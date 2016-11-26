#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>

int main()
{

	int sculltest;
	int code;
	
	sculltest = open("/dev/complete",O_WRONLY );

		if ((code=write(sculltest , NULL , 0)) < 0 ) printf("write error! code=%d \n",code);
		else   printf("write ok! code=%d \n",code);

	close(sculltest);

  exit(0);
}
