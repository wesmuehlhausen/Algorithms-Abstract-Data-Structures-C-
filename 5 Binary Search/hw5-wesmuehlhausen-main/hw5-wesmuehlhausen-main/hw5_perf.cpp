// ----------------------------------------------------------------------
// NAME: S. Bowers
// FILE: hw5_perf.cpp
// DATE: Fall 2020

// DESC: Performs basic performance tests over the resizable array
// collection implementation and the sorted resizable array collection
// implementation (via binary search). Operations tested are
// specified by an input test number:
//     1 = add 
//     2 = remove
//     3 = find value
//     4 = find range
//     5 = sort
// Output consists of average operation times for different sized
// input lists for both implementations.
//----------------------------------------------------------------------


#include <stdlib.h>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <chrono>
#include <string>
#include <cassert>
#include "collection.h"
#include "array_list_collection.h"
#include "bin_search_collection.h"

using namespace std;
using namespace std::chrono;

// Test generation params
const int ITERATIONS = 3;       // runs to average
const int SHUFFLINGS = 3;       // amount of "randomness"
  
// Implementation types
const int ARRAYLIST = 0;
const int LINKEDLIST = 1;

// KV value choices
const int KEYVALS_SIZE = 16;
const string KEYVALS[] = {"aa", "ab", "ac", "ad", "ba", "bb", "bc", "bd",
                          "ca", "cb", "cc", "cd", "da", "db", "dc", "dd"};

// Helper functions: 
unsigned long sum(unsigned long array[], int n);
void create_pairs(pair<int,string> array[], int n); 

// Test cases:
double add(pair<int,string> array[], int size, int type);
double remove(pair<int,string> array[], int size, int type);
double find_value(pair<int,string> array[], int size, int type);
double find_range(pair<int,string> array[], int size, int type);
double sort(pair<int,string> array[], int size, int type);

// Test driver:
int main(int argc, char* argv[])
{
  // check command line args
  if (argc != 2) {
    cerr << "usage: " << argv[0] << " test-number (1-5)" << endl;
    exit(1);
  }
  string test_number = argv[1];
  // configure output
  cout << fixed << showpoint;
  cout << setprecision(2);
  
  // test 1: add operation
  if (test_number.compare("1") == 0) {
    const int START = 0;            // initial test data size
    const int STOP = 35000;         // max test data size
    const int STEP = 1024;          // data size increments
    cout << "# Column 1 = Input data size" << endl
         << "# Column 2 = Avg time for ArrayList add function\n"
         << "# Column 3 = Avg time for BinSearch add function\n"
         << "# All times are measured in milliseconds" << endl;
    for (int size = START; size <= STOP; size += STEP) {
      // create data set
      pair<int,string> array[size];
      create_pairs(array, size);
      double avg1 = 0;//add(array, size, ARRAYLIST);
      double avg2 = add(array, size, LINKEDLIST);
      cout << size << " " << (avg1/1000.0) << " " << (avg2/1000.0) << endl;
    }
  }
  // test 2: remove operation
  else if (test_number.compare("2") == 0) {
    const int START = 0;            // initial test data size
    const int STOP = 35000;         // max test data size
    const int STEP = 1024;          // data size increments
    cout << "# Column 1 = Input data size" << endl
         << "# Column 2 = Avg time for ArrayList remove function\n"
         << "# Column 3 = Avg time for BinSearch remove function\n"
         << "# All times are measured in microseconds" << endl;
    for (int size = START; size <= STOP; size += STEP) {
      // create data set
      pair<int,string> array[size];
      create_pairs(array, size);
      double avg1 = remove(array, size, ARRAYLIST);
      double avg2 = remove(array, size, LINKEDLIST);
      cout << size << " " << (avg1/1000.0) << " " << (avg2/1000.0) << endl;
    }
  }
  // test 3: find-value operation
  else if (test_number.compare("3") == 0) {
    const int START = 0;            // initial test data size
    const int STOP = 35000;         // max test data size
    const int STEP = 1024;          // data size increments
    cout << "# Column 1 = Input data size" << endl
         << "# Column 2 = Avg time for ArrayList find-value function\n"
         << "# Column 3 = Avg time for BinSearch find-value function\n"
         << "# All times are measured in microseconds" << endl;
    for (int size = START; size <= STOP; size += STEP) {
      // create data set
      pair<int,string> array[size];
      create_pairs(array, size);
      double avg1 = find_value(array, size, ARRAYLIST);
      double avg2 = find_value(array, size, LINKEDLIST);
      cout << size << " " << (avg1/1000.0) << " " << (avg2/1000.0) << endl;
    }
  }
  // test 4: find-range operation
  else if (test_number.compare("4") == 0) {
    const int START = 0;            // initial test data size
    const int STOP = 35000;         // max test data size
    const int STEP = 1024;          // data size increments
    cout << "# Column 1 = Input data size" << endl
         << "# Column 2 = Avg time for ArrayList find-value function\n"
         << "# Column 3 = Avg time for BinSearch find-value function\n"
         << "# All times are measured in microseconds" << endl;
    for (int size = START; size <= STOP; size += STEP) {
      // create data set
      pair<int,string> array[size];
      create_pairs(array, size);
      double avg1 = find_range(array, size, ARRAYLIST);
      double avg2 = find_range(array, size, LINKEDLIST);
      cout << size << " " << (avg1/1000.0) << " " << (avg2/1000.0) << endl;
    }
  }
  // test 5: sort operation
  else if (test_number.compare("5") == 0) {
    const int START = 0;            // initial test data size
    const int STOP = 35000;         // max test data size
    const int STEP = 1024;          // data size increments
    cout << "# Column 1 = Input data size" << endl
         << "# Column 2 = Avg time for ArrayList sort function\n"
         << "# Column 3 = Avg time for BinSearch sort function\n"
         << "# All times are measured in microseconds" << endl;
    for (int size = START; size <= STOP; size += STEP) {
      // create data set
      pair<int,string> array[size];
      create_pairs(array, size);
      double avg1 = sort(array, size, ARRAYLIST);
      double avg2 = sort(array, size, LINKEDLIST);
      cout << size << " " << (avg1/1000.0) << " " << (avg2/1000.0) << endl;
    }
  }
  else {
    cerr << "error: invalid test number" << endl;
    exit(1);
  }
}


unsigned long sum(unsigned long array[], int n)
{
  unsigned long sum = 0;
  for (int i = 0; i < n; ++i)
    sum += array[i];
  return sum;
}

// helpers
void create_pairs(pair<int,string> array[], int n)
{
  // make n even 
  n = (n % 2) ? n + 1 : n;
  int half = n/2;
  int values[n];      
  int pile1[half];
  int pile2[half];
  // init values
  for (int i = 0; i < n; ++i)
    values[i] = i + 1;
  // shuffle indexes
  for (int i = 0; i < SHUFFLINGS; ++i) {
    for (int j = 0; j < half; ++j)
      pile1[j] = values[j];
    for (int j = half; j < n; ++j)
      pile2[j - half] = values[j];
    int k = 0;
    for (int j = 0; j < half; ++j) {
      int val1 = pile1[j];
      int val2 = pile2[j];
      values[k++] = (i % 2) ? val1 : val2;
      values[k++] = (i % 2) ? val2 : val1;
    }
  }
  // create return array
  for (int i = 0; i < n; ++i)
    array[i] = pair<int,string>(values[i], KEYVALS[values[i] % KEYVALS_SIZE]);
}


double add(pair<int,string> array[], int size, int type)
{
  unsigned long times[ITERATIONS]; 
  Collection<int,string>* collection;
  if (type == ARRAYLIST)
    collection = new ArrayListCollection<int,string>;
  else
    collection = new BinSearchCollection<int,string>;
  for (int i = 0; i < size; ++i)
    collection->add(array[i].first, array[i].second);
  assert(collection->size() == size);
  for (int i = 0; i < ITERATIONS; ++i) {
    auto start = high_resolution_clock::now();
    collection->add(size/2 + 5, "aa");
    auto end = high_resolution_clock::now();
    times[i] = duration_cast<microseconds>(end - start).count();
    collection->remove(size/2 + 5);
  }
  delete collection;
  return sum(times, ITERATIONS) / (ITERATIONS*1.0);
}

double remove(pair<int,string> array[], int size, int type)
{
  unsigned long times[ITERATIONS]; 
  Collection<int,string>* collection;
  if (type == ARRAYLIST)
    collection = new ArrayListCollection<int,string>;
  else
    collection = new BinSearchCollection<int,string>;
  for (int i = 0; i < size; ++i)
    collection->add(array[i].first, array[i].second);
  assert(collection->size() == size);
  for (int i = 0; i < ITERATIONS; ++i) {
    auto start = high_resolution_clock::now();
    collection->remove(size/2);
    auto end = high_resolution_clock::now();
    collection->add(size/2, "aa");
    times[i] = duration_cast<microseconds>(end - start).count();
  }
  delete collection;
  return sum(times, ITERATIONS) / (ITERATIONS*1.0);
}

double find_value(pair<int,string> array[], int size, int type)
{
  unsigned long times[ITERATIONS]; 
  Collection<int,string>* collection;
  if (type == ARRAYLIST)
    collection = new ArrayListCollection<int,string>;
  else
    collection = new BinSearchCollection<int,string>;
  for (int i = 0; i < size; ++i)
    collection->add(array[i].first, array[i].second);
  assert(collection->size() == size);
  for (int i = 0; i < ITERATIONS; ++i) {
    auto start = high_resolution_clock::now();
    string val;
    collection->find(size/2, val);
    auto end = high_resolution_clock::now();
    times[i] = duration_cast<microseconds>(end - start).count();
  }
  delete collection;
  return sum(times, ITERATIONS) / (ITERATIONS*1.0);
}

double find_range(pair<int,string> array[], int size, int type)
{
  unsigned long times[ITERATIONS]; 
  Collection<int,string>* collection;
  if (type == ARRAYLIST)
    collection = new ArrayListCollection<int,string>;
  else
    collection = new BinSearchCollection<int,string>;
  for (int i = 0; i < size; ++i)
    collection->add(array[i].first, array[i].second);
  assert(collection->size() == size);
  for (int i = 0; i < ITERATIONS; ++i) {
    int k1 = (size/2) - (size/10);
    int k2 = (size/2) + (size/10);
    ArrayList<int> keys;
    auto start = high_resolution_clock::now();
    collection->find(k1, k2, keys);
    auto end = high_resolution_clock::now();
    times[i] = duration_cast<microseconds>(end - start).count();
  }
  delete collection;  
  return sum(times, ITERATIONS) / (ITERATIONS*1.0);
}

double sort(pair<int,string> array[], int size, int type)
{
  unsigned long times[ITERATIONS]; 
  Collection<int,string>* collection;
  if (type == ARRAYLIST)
    collection = new ArrayListCollection<int,string>;
  else
    collection = new BinSearchCollection<int,string>;
  for (int i = 0; i < size; ++i)
    collection->add(array[i].first, array[i].second);
  assert(collection->size() == size);
  for (int i = 0; i < ITERATIONS; ++i) {
    ArrayList<int> keys;
    auto start = high_resolution_clock::now();
    collection->sort(keys);
    auto end = high_resolution_clock::now();
    if (size > 0)
      for (int i = 0; i < keys.size() -1; ++i) {
        int val1 = 0, val2 = 0;
        keys.get(i, val1);
        keys.get(i + 1, val2);
        assert(val1 < val2);
      }
    times[i] = duration_cast<microseconds>(end - start).count();
  }
  delete collection;
  return sum(times, ITERATIONS) / (ITERATIONS*1.0);
}






