#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>

#define FPGA_DEV "/dev/fpga"
#define PAGE_SIZE 10

int main(void)
{
	int           fd,i,res;
	unsigned char buf[PAGE_SIZE];

	fd=open(FPGA_DEV, O_RDWR);
	if (fd < 0)
	{
		printf("Can't Open %s !!\n", FPGA_DEV);
		return -1;
	}

	for(i = 0; i < sizeof(buf); i++)
	{
		buf[i] = i;
	}

	write(fd, &buf, PAGE_SIZE);

	close(fd);

	return 0;
}
