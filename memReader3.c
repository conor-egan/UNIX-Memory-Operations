/***********************************************************************
Program: memReader3.c

Open a shared a shared memory object, map to that object and read it.

Donal Heffernan 6/November/2014   Updated 22/October/2015
Edited by Conor Egan 22 April
************************************************************************/
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <string.h>
#include <sys/time.h>

#define SHARED_OBJ_PATH  "don1337"  // pathname to shared object       
#define MESSAGE_SIZE      100     // maximum length the message 

int main (int argc, char *argv[])
{
        struct stat st;
        off_t  len;
        char *pt;
        int fd;
	char character;
	unsigned long t1;
	unsigned long t2;
	unsigned long t;
	unsigned long iterations = 0;
	struct timeval startVal;
 	struct timeval endVal;
	
	gettimeofday(&startVal, NULL);

        fd = open (argv[1], O_RDONLY); // open file for reading
        
        fstat (fd, &st); // get stat info to 'st' structure
        printf("File size in bytes is: %lu\n", st.st_size); // print file's size

        // map file to memory - full length of the file
        
	pt = mmap(NULL, 20000, PROT_READ, MAP_SHARED, fd, 0);
        // print out the contents of memory that represents the file contents
        printf("Contents of file:\n ");
	for (len = 0; len < st.st_size; len++)
                putchar (pt[len]);

	
	close(fd); // close file descriptor 
    
	// the file will automatically unmap on program exit.

	gettimeofday(&endVal, NULL);

	//subtract loop start time from loop end time
	t1 = startVal.tv_sec * 1000000 + startVal.tv_usec;
	t2 = endVal.tv_sec * 1000000  + endVal.tv_usec;
	t = t2 -t1;
	
	printf("Execution time: %lu microseconds\n", t);

        return 0;
}
