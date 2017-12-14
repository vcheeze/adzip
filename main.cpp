/**
 * Operating Systems Project 4
 */

#include <iostream>


using namespace std;


int main(int argc, char *argv[]) {
  // cout << "Creating the shared segment!" << endl;

  int shmid = 0;
  // sem_t *sem;
  int *mem, *data;

  // Create shared memory segment: size of semaphores + int
  shmid = shmget(IPC_PRIVATE, CTRL_SIZE + DATA_SIZE*sizeof(int), 0666); // instantiate with size for int[20]
  if (shmid == -1) {
    cerr << "Shared Memory: Creation failed" << endl;
  } else {
    cout << "Allocated Shared Memory with ID: " << shmid << endl;
  }

  // Attach the segment
  mem = (int *) shmat(shmid, nullptr, 0);
  if (*mem == -1) {
    cerr << "Shared Memory: Attachment failed" << endl;
  } else {
    cout << "Attached Shared Memory" << endl;
  }
  // sem = mem;
	// /* Initialize the semaphore. */
	// retval = sem_init(&sem, 1, 2);
	// if (retval != 0) {
	// 	perror("Couldn't initialize.");
	// 	exit(3);
	// }

  data = mem + CTRL_SIZE;

  for (int i = 0; i < DATA_SIZE; i++) {
    data[i] = i;
  }

  return 0;
}
