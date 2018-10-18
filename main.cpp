#include <iostream>
#include "fit.cpp"

using namespace std;

int firstCase ();
int nextCase ();
int bestCase ();
int worstCase ();
void display (Jobs &, Partitions &);

void skipLines(int n) {
  for(int i = 0; i < n; i++) {
    cout << endl;
  }
}

int main () {
	int input = 0;
	bool loop = false;

  // Loop for partitions list size.
  int partitionsListSize;
  loop = true;
  while (loop) {

    // Prompt for number of partitions.
    cout << "How many partitions?" << endl;
    cout << "count: ";
    cin >> partitionsListSize;

    // If given valid input break loop.
    if (partitionsListSize > 0) {
      loop = false;
    }
    // Else prompt error and loop.
    else {
      skipLines(2);
      cout << "That was an incorrect input, try again with values greater than 0." << endl;
    }

  }

  skipLines(2);

  // Set up partitions list.
  Partitions partitions (partitionsListSize);

  // Loop for partitions.
  for (int i = 0; i < partitionsListSize; i++) {

    // The number for the partition.
    int number;

    // Thee size of the partition.
    float size;
    
    // Loop for partition @ i.
    loop = true;
    while (loop) {
      
      // Prompt number of partition.
      cout << "Partition #" << i << " number: ";
      cin >> number;
      
      // Prompt size of partition.
      cout << "Size of partition: ";
      cin >> size;

      // If given valid input, break loop.
      if (number > -1 && size >= 0)
        loop = false;

      // Else if given invalid input, prompt error and try again.
      else {
        skipLines(2);
        cout << "That was an incorrect input, try again with a partition number greater than -1 and a size greater than or equal to 0" << endl;
      }
      
    }

    // Set partition.
    partitions.create(number, size);
    skipLines(2);
  }

  // Loop for jobs list size.
  int jobsListSize;
  loop = true;
  while (loop) {

    // Prompt for number of jobs.
    cout << "How many jobs?" << endl;
    cout << "count: ";
    cin >> jobsListSize;

    // If given valid input break loop.
    if (jobsListSize > 0) {
      loop = false;
    }
    // Else prompt error and loop.
    else {
      skipLines(2);
      cout << "That was an incorrect input, try again with values greater than 0." << endl;
    }

  }

  skipLines(2);

  // Set up jobs list.
  Jobs jobs (jobsListSize);

  // Loop for jobs.
  for (int i = 0; i < jobsListSize; i++) {

    // The name for the job.
    string name;

    // Thee size of the job.
    float size;
    
    // Loop for job @ i.
    loop = true;
    while (loop) {
      
      // Prompt name of job.
      cout << "Job #" << i << " name: ";
      cin >> name;
      
      // Prompt size of job.
      cout << "Size of job: ";
      cin >> size;

      // If given valid input, break loop.
      if (name.length() > 0 && size >= 0)
        loop = false;

      // Else if given invalid input, prompt error and try again.
      else {
        skipLines(2);
        cout << "That was an incorrect input, try again with a name of at least 1 character and a size greater than or equal to 0" << endl;
      }
      
    }

    // Set job.
    jobs.create(name, size);
    skipLines(2);
  }

  // Loop for method of algorithm.
  input = 0;
  loop = true;
	while (loop) {

    // Prompt for algorithm selection.
    cout << "Which algorithm will be used?" << endl; 
		cout << "1) First-fit" << endl;
		cout << "2) Next-fit" << endl;
		cout << "3) Best-fit" << endl;
		cout << "4) Worst-fit" << endl;
		cout << "case: ";
		cin >> input;

    // If given valid input, break loop.
		if (input > 0 && input < 5)
			loop = false;
    // Else prompt error and loop.
    else {
      skipLines(2);
      cout << "That was an incorrect input, try again with values of 1 thru 4." << endl;
    }
	}

  // Run algorithm based in input.
	switch (input) {
		case 1:
			Fit::firstFit(jobs, partitions);
      break;
		case 2:
			Fit::nextFit(jobs, partitions);
      break;
		case 3:
			Fit::bestFit(jobs, partitions);
      break;
		case 4:
			Fit::worstFit(jobs, partitions);
      break;
		default:
			return -1;
	}

  display(jobs, partitions);

  jobs.~Jobs();
  partitions.~Partitions();

  return 0;
}

void display (Jobs & jobs, Partitions & partitions) {
  cout << "::FINAL OUTPUT::" << endl;
  skipLines(2);

  for (int i = 0; i < jobs.size(); i++) {
    cout << "Job name: " << jobs.get(i)->getName();
    cout << ", size: " << jobs.get(i)->getSize();
    cout << ", status: " << jobs.get(i)->getStatus() << endl;

    if (jobs.get(i)->getPartition() == -1) {
      cout << "no partition assigned to this job" << endl;
    }
    else {
      cout << "assigned to partition # " << jobs.get(i)->getPartition() << endl;
    }
    cout << endl;
  }

  cout << endl;

  for (int i = 0; i < partitions.size(); i++) {
    cout << "Partition #" << partitions.get(i)->getNumber() << endl;
    cout << "size: " << partitions.get(i)->getSize();
    cout << ", status: " << partitions.get(i)->isFree() << endl;

    // If there is no job assigned to this partition.
    if (partitions.get(i)->isFree()) {
      cout << "no job assigned to this partition" << endl;
    }
    // Else if there is a job assigned.
    else {
      cout << "job name: " << partitions.get(i)->getJob();
      cout << ", job size: " << partitions.get(i)->getJobSize() << endl;
      cout << "memory wasted: " << partitions.get(i)->getUnused() << endl;
    }
    cout << endl;
  }
}