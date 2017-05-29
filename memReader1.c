/***********************************************************************
Program: memReader1.c

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
#define MESSAGE_SIZE      100  // maximum length the message 

char message[MESSAGE_SIZE];

int main() {

int mfd;  //file descriptor for the shared object
int seg_size = (sizeof(message));   //shared object sized to store message 
char *shared_msg;

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
memcpy(shared_msg, "This should cause an error", 30); //should cause an error, this program has opened memory object as read-only

printf("Shared memory size allocated is %d bytes\n", seg_size);
printf("The message content actually read is: .... %s\n", shared_msg);
printf("The page size for this system is %ld bytes.\n", sysconf(_SC_PAGESIZE));



return 0;
}
