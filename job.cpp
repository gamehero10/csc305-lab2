#ifndef JOB
#define JOB

#include <string>
using namespace std;

class Job {
public:
  Job (string, float);
  ~Job ();

  /*
    GETTERS
  */
  string getName ();
  float getSize ();
  bool getStatus ();
  int getPartition ();

  /*
    SETTERS
  */
  int setPartition (int);
private:
  string name;
  float size;
  bool status; // { false: waiting, true: running }
  int partition;
};
#endif

Job::Job (string name, float size) {
  this->name = name;
  this->size = size;
  this->status = false;
}
Job::~Job () {}

/*
  DATA GETTERS
*/
string Job::getName () {
  return this->name;
}
float Job::getSize () {
  return this->size;
}
bool Job::getStatus () {
  return this->status;
}
int Job::getPartition () {
  return this->partition;
}

/*
  SETTERS
*/
int Job::setPartition (int partition) {
  this->partition = partition;
  this->status = true;
  return 0;
}