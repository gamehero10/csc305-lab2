#ifndef FIT
#define FIT

#include "partitions.cpp"
#include "jobs.cpp"

class Fit {
public:
  Fit ();
  ~Fit ();
  static void firstFit (Jobs &, Partitions &);
  static int nextFit (Jobs &, Partitions &, int);
  static void bestFit (Jobs &, Partitions &);
  static void worstFit (Jobs &, Partition &);
};
#endif

Fit::Fit () {}
Fit::~Fit () {}

void Fit::firstFit (Jobs & jobs, Partitions & partitions) {
  
  // Iterate through jobs.
  for (int j = 0; j < jobs.size(); j++) {

    // Iterate through partitions.
    for (int i = 0; i < partitions.size(); i++) {

      // If parition has enough space and is available.
      if ( partitions.get(i)->isFree() && (partitions.get(i)->getSize() >= jobs.get(j)->getSize()) ) {

        // Add reference of job to partition.
        partitions.get(i)->setJob( jobs.get(j)->getName(), jobs.get(j)->getSize() );

        // Add reference of partition to job.
        jobs.get(j)->setPartition( partitions.get(i)->getNumber() );

        // Break out of paritions loop since job has been assigned.
        i = partitions.size();

      }
    }

  }

  return;
}

int Fit::nextFit (Jobs & jobs, Partitions & partitions, int nextPartition) {

  // Iterate through jobs.
  for (int j = 0; j < jobs.size(); j++) {

    // Iterate through partitions.
    for (int i = nextPartition; i < partitions.size(); i++) {

      // If the partition is free and has enough space.
      if ( partitions.get(i)->isFree() && (partitions.get(i)->getSize() >= jobs.get(j)->getSize()) ) {

        // Add reference of job to partition.
        partitions.get(i)->setJob(jobs.get(j)->getName(), jobs.get(j)->getSize());

        // Add reference of partition to job.
        jobs.get(j)->setPartition(i);
        
        // Assign next partition.
        nextPartition = i + 1;

        // Break out of paritions loop since job has been assigned.
        break;
      }
    }

  }

  return;
}

void Fit::bestFit (Jobs & job, Partitions & partitions) {
  int best = -1;
  // Loop through partitions.
  for (int i = 0; i < partitions.size(); i++) {
    // If the current partition has enough storage to hold the job.
    // And the current partition doesn't already have a job.
    // And if the best fit index is either -1, or the current partition has less
    // difference than the previous partition. (better fit)
    bool available = (partitions.get(i)->getJob() == -1);
    bool hasSpace = (partitions.get(i)->getSize() >= job->getSize());
    bool betterFit = (
      (best == -1) ||
      (partitions.get(i)->getSize() - job->getSize()) < (partitions.get(best)->getSize() - job->getSize())
    );
    if ( available && hasSpace && betterFit  ) {
      best = i;
    }
  }
  // If our best fit index is still -1, there was no available partition for this job.
  if (best == -1) {
    return;
  }
  // Else if there is a fit, link them.
  else {
    job->setPartition( partitions.get(best)->getNumber() );
    job->setStatus(1);
    partitions.get(best)->setJob( job->getNumber(), job->getSize() );
    partitions.get(best)->setStatus(1);
    return;
  }
}

void Fit::worstFit (Job * job, Partitions & partitions) {
  int best = -1;
  // Loop through partitions.
  for (int i = 0; i < partitions.size(); i++) {
    // If the current partition has enough storage to hold the job.
    // And the current partition doesn't already have a job.
    // And if the best fit index is either -1, or the current partition has greater
    // difference than the previous partition. (better fit)
    bool available = (partitions.get(i)->getJob() == -1);
    bool hasSpace = (partitions.get(i)->getSize() >= job->getSize());
    bool betterFit = (
      (best == -1) ||
      (partitions.get(i)->getSize() - job->getSize()) > (partitions.get(best)->getSize() - job->getSize())
    );
    if ( available && hasSpace && betterFit  ) {
      best = i;
    }
  }
  // If our best fit index is still -1, there was no available partition for this job.
  if (best == -1) {
    return;
  }
  // Else if there is a fit, link them.
  else {
    job->setPartition( partitions.get(best)->getNumber() );
    job->setStatus(1);
    partitions.get(best)->setJob( job->getNumber(), job->getSize() );
    partitions.get(best)->setStatus(1);
  }
}