// consumer.cpp
// Mark Luther
// 3-27-25

#include "shared.hpp"
#include <iostream>

constexpr const char* shmName = "/prod_cons_shm";


int main() {
    
    // existing shared memory
    int shm_fd = shm_open(shmName, O_RDWR, 0);
    if (shm_fd < 0) {
        perror("Consumer: shm_open failed");
        exit(EXIT_FAILURE);
    }

    // put shared memory onto map
    SharedMemory* shm = reinterpret_cast<SharedMemory*>(
        mmap(nullptr, sizeof(SharedMemory), PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0)
    );
    if (shm == MAP_FAILED) {
        perror("Consumer: mmap failed");
        exit(EXIT_FAILURE);
    }

    
    for (int i = 0; i < 10; ++i) {
        // wait
        if (sem_wait(&shm->full) == -1) {
            perror("Consumer: sem_wait(full) failed");
            exit(EXIT_FAILURE);
        }

        // critical section
        if (shm->count > 0) {
            --shm->count;  // Decrement count first.
            int item = shm->data[shm->count];  // Retrieve the item.
            std::cout << "Consumer: consumed " << item
                      << " from index " << shm->count << std::endl;
        } else {
            std::cerr << "Consumer: unexpected buffer underflow!" << std::endl;
        }

        // signal
        if (sem_post(&shm->empty) == -1) {
            perror("Consumer: sem_post(empty) failed");
            exit(EXIT_FAILURE);
        }
    }
    return 0;
}
