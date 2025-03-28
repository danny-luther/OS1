// producer.cpp
// Mark Luther
// 3-27-25

#include "shared.hpp"
#include <iostream>
#include <cstring>    // memset

// shared memory
constexpr const char* shmName = "/prod_cons_shm";

int main() {

    // unlink to avoid file error
    shm_unlink(shmName);

    // create shared memory
    int shm_fd = shm_open(shmName, O_CREAT | O_EXCL | O_RDWR, S_IRUSR | S_IWUSR);
    if (shm_fd < 0) {
        perror("Producer: shm_open failed");
        exit(EXIT_FAILURE);
    }

    // set shared memory to SharedMemory
    if (ftruncate(shm_fd, sizeof(SharedMemory)) == -1) {
        perror("Producer: ftruncate failed");
        exit(EXIT_FAILURE);
    }

    // put shared memory onto map
    SharedMemory* shm = reinterpret_cast<SharedMemory*>(
        mmap(nullptr, sizeof(SharedMemory), PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0)
    );
    if (shm == MAP_FAILED) {
        perror("Producer: mmap failed");
        exit(EXIT_FAILURE);
    }

    shm->count = 0;
    memset(shm->data, 0, sizeof(shm->data));

    // semaphores
    // empty = 2
    if (sem_init(&shm->empty, 1, 2) == -1) {
        perror("Producer: sem_init(empty) failed");
        exit(EXIT_FAILURE);
    }
    // full = 0
    if (sem_init(&shm->full, 1, 0) == -1) {
        perror("Producer: sem_init(full) failed");
        exit(EXIT_FAILURE);
    }

    // produce items

    for (int i = 0; i < 10; ++i) {
        // wait
        if (sem_wait(&shm->empty) == -1) {
            perror("Producer: sem_wait(empty) failed");
            exit(EXIT_FAILURE);
        }

        // critical section
        // count = new item index
        if (shm->count < 2) {
            shm->data[shm->count] = i;
            std::cout << "Producer: produced " << i
                      << " at index " << shm->count << std::endl;
            ++shm->count;
        } else {
            std::cerr << "Producer: unexpected buffer overflow!" << std::endl;
        }

        // signal
        if (sem_post(&shm->full) == -1) {
            perror("Producer: sem_post(full) failed");
            exit(EXIT_FAILURE);
        }
    }

    //sleep(1);

    // delete semaphores and shared memory
    sem_destroy(&shm->empty);
    sem_destroy(&shm->full);
    if (shm_unlink(shmName) == -1) {
        perror("Producer: shm_unlink failed");
        exit(EXIT_FAILURE);
    }

    return 0;
}
