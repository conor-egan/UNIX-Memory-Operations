/***********************************************************************
Program: memReader2.c

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

#define SHARED_OBJ_PATH   "don1337"   // pathname to shared object  
#define MESSAGE_SIZE      20000  // maximum length the message 

char message[MESSAGE_SIZE];

int main() {

int mfd;  //file descriptor for the shared object
int seg_size = (sizeof(message));   //shared object sized to store message 
char *shared_msg;
off_t  len;

// open the shared memory object for reading  only  
mfd = shm_open(SHARED_OBJ_PATH, O_RDONLY, S_IRWXU | S_IRWXG);
    if (mfd < 0) {
        perror("error shm_open(): forgot to run memWriter?");
        exit(1) ;
    }

printf("Opened the shared memory object (read only): %s\n", SHARED_OBJ_PATH);
   
// map the shared memory object to this process    
    shared_msg = mmap(NULL, seg_size, PROT_READ, MAP_SHARED, mfd, 0);
    if (shared_msg == NULL) {
        perror("error in  mmap()") ;
        exit(1);
    }

// print out the contents of memory that represents the file contents
printf("First five characters in array:\n");
for (len = 0; len < 5; len++){
	putchar (shared_msg[len]);
        printf("\n");
}
printf("Last three characters in array:\n");
for (len = (sizeof(shared_msg) - 3); len < sizeof(shared_msg); len++){
	putchar (shared_msg[len]);
        printf("\n");
}


return 0;
}
