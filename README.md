Programming Assignment #1
In this programming assignment, you must provide the source codes, documents, and examples ;in detail on Github. They will be counted for the final score.  Please submit the link to the project on Github.

Requirements:
- You are required to use C/C++ in Linux/Unix. You can consider installing VirtualBox in your non-Linux environment.
- Programs must succeed in compilation and execution as required (80 points)
- Readme, documentation and example are required (20 points).

Topic: Producer-Consumer Problem

The producer generates items and puts items onto the table. The consumer will pick up items. The table can only hold two items at the same time. When the table is complete, the producer will wait. When there are no items, the consumer will wait. We use semaphores to synchronize producer and consumer. Mutual exclusion should be considered. We use threads in the producer program and consumer program. Shared memory is used for the “table”.

We expect to use these two programs (producer and consumer) like this:

$ gcc producer.c -pthread -lrt -o producer
$ gcc consumer.c -pthread -lrt -o consumer
$ ./producer & ./consumer &

# **Overview**:
this project demonstrates the producer consumer problem by using shared memory and semaphores in C++.  the producer creates items and places them into a buffer array of size 2.  the consumer will pick these items up after they are inside the array.  using syncronization logic the producer waits if the buffer is full and the consumer waits if the buffer is empty.  this is an example of mutual exclusion.

# **Requirements**:
Linux distro Ubuntu

C++ compiler
 
POSIX semaphore and sharememory C++ library

# **Compilation**:
g++ -std=c++17 -o producer producer.cpp -lpthread

g++ -std=c++17 -o consumer consumer.cpp -lpthread

# **Execution**:
./producer & ./consumer &

# **Troubleshooting**:
the code has some potential for bugs.  it tends to work just fine but the producer and consumer can both fail when shm_open file exists/does not exist.
if a bug is experienced, press enter to finish the process.  then try again running the execution command:

./producer & ./consumer &
