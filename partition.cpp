#ifndef PARTITION
#define PARTITION

#include <string>
using namespace std;

class Partition {
public:
  Partition (int, float);
  ~Partition ();

  /*
    GETTERS
  */

  // Returns index number.
  int getNumber ();

  // Returns memory capacity.
  float getSize ();

  // Returns availability. TODO change to boolean.
  bool isFree ();

  // Returns name of job.
  string getJob ();

  // Returns used/job memory size.
  float getJobSize ();

  // Returns free memory size.
  float getUnused ();

  /*
    SETTERS
  */
  int setJob (string, float);

private:
  int number;
  float size;
  bool free; // Partition status { false: busy, true: available }

  string job;
  float jobSize;
};
#endif

Partition::Partition (int number, float size) {
  this->number = number;
  this->size = size;
  this->free = true;
}
Partition::~Partition () {}

/*
  GETTERS
*/
float Partition::getSize () {
  return this->size;
}
int Partition::getNumber () {
  return this->number;
}
bool Partition::isFree () {
  return this->free;
}

string Partition::getJob () {
  return this->job;
}
float Partition::getJobSize () {
  return this->jobSize;
}
float Partition::getUnused () {
  return this->size - this->jobSize;
}
/*
  GETTERS
*/

/*
  DATA SETTERS
*/

/*
  Assigns a job to this partition.
  Requires a job name and job size.
  Will return 1 if the job does not fit into the partition.
  Will return 0 if successfully assigned.
*/
int Partition::setJob (string job, float jobSize) {
  if (jobSize > this->size)
    return 1;
  this->job = job;
  this->jobSize = jobSize;
  this->free = false;
  return 0;
}
/*
  DATA SETTERS
*/