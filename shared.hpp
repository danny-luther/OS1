// shared.hpp
// Mark Luther
// 3-27-25

#ifndef SHARED_HPP
#define SHARED_HPP

#include <fcntl.h>           // file control
#include <semaphore.h>       // semaphore functions sem_t
#include <sys/mman.h>        // memory mapping
#include <sys/stat.h>        // shared memory
#include <unistd.h>          // ftruncate, sleep
#include <cstdlib>           
#include <cstdio>

// shared memory 

struct SharedMemory {
    int data[2];      // buffer
    int count;        // items currently in buffer

    sem_t full;       // items available for consumer
    sem_t empty;      // empty slots available for producer
};

#endif 
