#ifndef JOBS
#define JOBS

#include "job.cpp"
#include <vector>

class Jobs {

public:

  // Construct with max size of job list.
  Jobs(int);

  // Clear memory.
  ~Jobs();

  // Create new job in list.
  int create (string, float);

  // Retrieve job by index number.
  Job * get (int);

  // Returns length of job list.
  int size ();

private:

  // Container for job list.
  std::vector<Job> jobs;

};

#endif

// Construct with max size of job list.
Jobs::Jobs (int maxSize) {
  jobs.reserve(maxSize);
}

// Clear memory.
Jobs::~Jobs () {
  jobs.clear();
  jobs.swap(jobs);
}

// Create new job in list.
int Jobs::create (string name, float size) {
  // If we have reached max capacity, return early.
  if (jobs.size() >= jobs.max_size()) return -1;

  // Create reference pointer for new job.
  Job * job;
  job = new Job(name, size);

  // Add reference to job to list.
  jobs.push_back(*job);

  // Send back number assigned to job.
  return jobs.size() - 1;
}

// Return job by index number.
Job * Jobs::get (int number) {
  if (number >= jobs.size()) return & jobs.data()[0];
  return & jobs.data()[number];
}

int Jobs::size() {
  return jobs.size();
}