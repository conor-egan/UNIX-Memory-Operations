/***********************************************************************
Program: memWriter1.c

A simple example on shared memory.
Create/open a shared memory object, map to that object and write to it. Unlink object.
Uses write() instead of memcpy() to write to the shared memory object

Donal Heffernan 6/November/2014     Updated 22/October/2015
Edited by Conor Egan (13138782)     18 April 2016
************************************************************************/
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <string.h>

#define SHARED_OBJ_PATH  "don1337"  // pathname to shared object       
#define MESSAGE_SIZE      100     // maximum length the message 

char message[MESSAGE_SIZE];

int main() {

int mfd; //file descriptor for the shared object
int seg_size = (sizeof(message));   //shared object sized to store message 
char *shared_msg; 

// create the shared memory object with shm_open()  
mfd = shm_open(SHARED_OBJ_PATH, O_CREAT | O_RDWR, S_IRWXU | S_IRWXG);
    if (mfd < 0) {
        perror("error in shm_open()");
        exit(1);
    }

printf("I have created a lucky shared memory object:  %s\n", SHARED_OBJ_PATH);
    
ftruncate(mfd, seg_size) ; // define size of shared memory object

// map the shared memory object to this process    
shared_msg = mmap(NULL, seg_size, PROT_READ | PROT_WRITE, MAP_SHARED, mfd, 0);
    if (shared_msg == NULL) {
        perror("error in mmap()");
        exit(1);
    }
    
printf("Shared memory is now allocated %d bytes\n", seg_size);

write(mfd, "University of Limerick", 30); //put something onto the memory

printf("Message content is: %s\n\n Hit any key to finish!\n", shared_msg) ;
getchar() ; // wait for user to hit any key
   
shm_unlink(SHARED_OBJ_PATH) ;  // unlink - better to add error check

return 0 ;
}
