#ifndef PARTITIONS
#define PARTITIONS

#include "partition.cpp"
#include <vector>
#include <iostream>
using namespace std;

class Partitions {
public:
  // Construct with max size of partition list.
  Partitions(int);

  // Clear memory.
  ~Partitions();

  // Create new partition in list.
  int create (int, float);

  // Retrieve partition by index number.
  Partition * get (int);

  // Returns length of partition list.
  int size ();

private:

  // Container for partition list.
  std::vector<Partition> partitions;

};

#endif

Partitions::Partitions (int maxSize) {
  partitions.reserve(maxSize);
}
Partitions::~Partitions () {
  for (int i = 0; i < partitions.size(); i++) {
    delete & partitions[i];
  }
  partitions.clear();
  partitions.swap(partitions);
}

int Partitions::create (int number, float size) {
  // If we have reached max capacity, return early.
  if (partitions.size() >= partitions.max_size()) return -1;

  // Create new partition.
  Partition * partition;
 	partition = new Partition (number, size);

  // Add partition to end of list.
  partitions.push_back(*partition);

  // Send back number assigned to partition.
  return partitions.size() -1;
}

/*
  Returns a pointer to a partition in the partitions list by number.
*/
Partition * Partitions::get(int number) {
  if (number >= partitions.size()) return & partitions.data()[0];
  return & partitions.data()[number];
}

int Partitions::size () {
  return partitions.size();
}