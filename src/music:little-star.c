#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <math.h>
#include <stdlib.h>
#include "../include/speaker.h"

void main()
{
	int fd;
	short i, j, tone[43];
	short f[43] = {262, 262, 392, 293, 440, 440, 392, 349, 349, 330, 330, 294, 294, 262, 392, 392, 349, 349, 330, 330, 294, 392, 392, 349, 349, 330, 330, 294, 262, 262, 392, 392, 440, 440, 392, 349, 349, 330, 330, 294, 294, 262, 0};//the score of the little star
	for(i = 0; i < 43; i++)
	{
		tone[i] = (1193182.0 / (1.0 * f[i]));//Frequency division value and the clock signal is 11.9MHz
	}
	fd = open(DEVICE_NAME, O_RDWR);//open the device with the name
	if( fd == -1)
	{
		//open device error
		printf("Can't open device file: %s\n", DEVICE_NAME);
		goto end;
	}
	while(1)
	{
		for(j = 0; j < 43; j++)
		{
			if((j % 7) == 0)
				usleep(500000);//Delay of half a second every seven notes
			write(fd, &tone[j], 2);//write the value 
			usleep(500000);
			printf("Note: %d\n", f[j]);
		}
	}
end:	close(fd);//close the device
}
