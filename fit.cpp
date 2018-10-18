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
  static void worstFit (Jobs &, Partitions &);
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

void Fit::bestFit (Jobs & jobs, Partitions & partitions) {

  // Iterate through jobs.
  for (int j = 0; j < jobs.size(); j++) {

    // Used to keep track of best partition fit for each job.
    int best = -1;

    // Iterate through through partitions.
    for (int i = 0; i < partitions.size(); i++) {

      // If the has enough space, is free, and the best fit is either -1 or is smaller than the previous best fit.
      bool available = (partitions.get(i)->isFree());
      bool hasSpace = (partitions.get(i)->getSize() >= jobs.get(j)->getSize());
      bool betterFit = (best == -1) || (partitions.get(i)->getSize() < partitions.get(best)->getSize() );
      if ( available && hasSpace && betterFit ) {
        
        // Keep track of best fitting partition.
        best = i;

        // Break out of partitions iteration.
        break;
      }
    }

    // If there was a best fit.
    if (best != -1) {
      // Add reference of job to partition.
      partitions.get(best)->setJob(jobs.get(j)->getName(), jobs.get(j)->getSize());

      // Add reference of partition to job.
      jobs.get(j)->setPartition(best);
    }

  }

  return;

}

void Fit::worstFit (Jobs & jobs, Partitions & partitions) {

  // Iterate through jobs.
  for (int j = 0; j < jobs.size(); j++) {

    // Used to keep track of best partition fit for each job.
    int best = -1;

    // Iterate through through partitions.
    for (int i = 0; i < partitions.size(); i++) {

      // If the has enough space, is free, and the best fit is either -1 or is greater than the previous best fit.
      bool available = (partitions.get(i)->isFree());
      bool hasSpace = (partitions.get(i)->getSize() >= jobs.get(j)->getSize());
      bool betterFit = (best == -1) || (partitions.get(i)->getSize() > partitions.get(best)->getSize() );
      if ( available && hasSpace && betterFit ) {
        
        // Keep track of best fitting partition.
        best = i;

        // Break out of partitions iteration.
        break;
      }
    }

    // If there was a best fit.
    if (best != -1) {
      // Add reference of job to partition.
      partitions.get(best)->setJob(jobs.get(j)->getName(), jobs.get(j)->getSize());

      // Add reference of partition to job.
      jobs.get(j)->setPartition(best);
    }

  }

  return;
}