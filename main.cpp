#include <iostream>
#include "partitions.cpp"
#include "jobs.cpp"
#include "fit.cpp"

using namespace std;

int firstCase ();
int nextCase ();
int bestCase ();
int worstCase ();
void display (Jobs &, Partitions &);

int main () {
	int input = 0;
	bool loop = true;

	while (loop) {
		cout << "1) first case" << endl;
		cout << "2) next case" << endl;
		cout << "3) best case" << endl;
		cout << "4) worst case" << endl;
		cout << "case: " << endl;
		cin >> input;
		if (input > 0 && input < 5)
			loop = false;
	}

	switch (input) {
		case 1:
			return firstCase();
		case 2:
			return nextCase();
		case 3:
			return bestCase();
		case 4:
			return worstCase();
		default:
			return -1;
	}
}

int firstCase () {
  cout << "First Fit Case" << endl << endl;
  // Partitions
  Partitions partitions (5);
  partitions.create(16.0f, 0); // Partition # 0
  partitions.create(32.0f, 1); // Partition # 1
  partitions.create(64.0f, 2); // Partition # 2
  partitions.create(256.0f, 3); // Partition # 3
  partitions.create(128.0f, 4); // Partition # 4
  // Jobs
  Jobs jobs (5);
  jobs.create(30.0f, 0); // Job # 0, which should assign to partition # 1
  jobs.create(16.0f, 1); // Job # 1, which should assign to partition # 0
  jobs.create(200.0f, 2); // Job # 2, which should assign to partition # 3
  jobs.create(60.0f, 3); // Job # 3, which should assign to partition # 2
  jobs.create(130.0f, 4); // Job # 4, which should not assign to any partition at all.
  // Fit
  for (int i = 0; i < 5; i++) {
    Fit::firstFit(jobs.get(i), partitions);
  }
  // Display
  display(jobs, partitions);
  return 0;
}

int nextCase () {
  cout << "Next Fit Case" << endl << endl;
  // Partitions
  Partitions partitions (5);
  partitions.create(16.0f, 0); // Partition # 0
  partitions.create(32.0f, 1); // Partition # 1
  partitions.create(64.0f, 2); // Partition # 2
  partitions.create(256.0f, 3); // Partition # 3
  partitions.create(128.0f, 4); // Partition # 4
  // Jobs
  Jobs jobs (5);
  jobs.create(30.0f, 0); // Job # 0, which should assign to partition # 1
  jobs.create(16.0f, 1); // Job # 1, which should assign to partition # 0
  jobs.create(200.0f, 2); // Job # 2, which should assign to partition # 3
  jobs.create(60.0f, 3); // Job # 3, which should assign to partition # 2
  jobs.create(130.0f, 4); // Job # 4, which should not assign to any partition at all.
  // Fit
  int nextPartition = -1;
  for (int i = 0; i < 5; i++) {
    nextPartition = Fit::nextFit(jobs.get(i), partitions, nextPartition);
  }
  // Display
  display(jobs, partitions);
  return 0;
}

int bestCase () {
  cout << "Best Fit Case" << endl << endl;
  // Partitions
  Partitions partitions (5);
  partitions.create(256.0f, 0); // Partition # 0
  partitions.create(128.0f, 1); // Partition # 1
  partitions.create(64.0f, 2); // Partition # 2
  partitions.create(32.0f, 3); // Partition # 3
  partitions.create(16.0f, 4); // Partition # 4
  // Jobs
  Jobs jobs (5);
  jobs.create(120.0f, 0); // Job # 0, which should assign to partition # 1
  jobs.create(30.0f, 1); // Job # 1, which should assign to partition # 3
  jobs.create(60.0f, 2); // Job # 2, which should assign to partition # 2
  jobs.create(15.0f, 3); // Job # 3, which should assign to partition # 4
  jobs.create(300.0f, 4); // Job # 4, which should not assign to any partition at all.
  // Fit
  for (int i = 0; i < 5; i++) {
    Fit::bestFit(jobs.get(i), partitions);
  }
  // Display
  display(jobs, partitions);
  return 0;
}

int worstCase () {
  cout << "Worst Fit Case" << endl << endl;
  // Partitions
  Partitions partitions (5);
  partitions.create(16.0f, 0); // Partition # 0
  partitions.create(32.0f, 1); // Partition # 1
  partitions.create(64.0f, 2); // Partition # 2
  partitions.create(128.0f, 3); // Partition # 3
  partitions.create(256.0f, 4); // Partition # 4
  // Jobs
  Jobs jobs (5);
  jobs.create(30.0f, 0); // Job # 0, which should assign to partition # 4
  jobs.create(16.0f, 1); // Job # 1, which should assign to partition # 3
  jobs.create(5.0f, 2); // Job # 2, which should assign to partition # 2
  jobs.create(8.0f, 3); // Job # 3, which should assign to partition # 1
  jobs.create(100.0f, 4); // Job # 4, which should not assign to any partition at all.
  // Fit
  for (int i = 0; i < 5; i++) {
    Fit::worstFit(jobs.get(i), partitions);
  }
  // Display
  display(jobs, partitions);
  return 0;
}

void display (Jobs & jobs, Partitions & partitions) {
  for (int i = 0; i < 5; i++) {
    cout << "Job #" << jobs.get(i)->getNumber();
    cout << ", size: " << jobs.get(i)->getSize();
    cout << ", status: " << jobs.get(i)->getStatusString() << endl;

    if (jobs.get(i)->getPartition() == -1) {
      cout << "no partition assigned to this job" << endl;
    }
    else {
      cout << "assigned to partition # " << jobs.get(i)->getPartition() << endl;
    }
    cout << endl;
  }

  cout << endl;

  for (int i = 0; i < 5; i++) {
    cout << "Partition #" << partitions.get(i)->getNumber() << endl;

    cout << "size: " << partitions.get(i)->getSize();
    cout << ", status: " << partitions.get(i)->getStatusString() << endl;

    // If there is no job assigned to this partition.
    if (partitions.get(i)->getJob() == -1) {
      cout << "no job assigned to this partition" << endl;
    }
    // Else if there is a job assigned.
    else {
      cout << "job #" << jobs.get( partitions.get(i)->getJob() )->getNumber();
      cout << ", job size: " << jobs.get( partitions.get(i)->getJob() )->getSize() << endl;
      cout << "memory wasted: " << partitions.get(i)->getUnused() << endl;
    }
    cout << endl;
  }
}