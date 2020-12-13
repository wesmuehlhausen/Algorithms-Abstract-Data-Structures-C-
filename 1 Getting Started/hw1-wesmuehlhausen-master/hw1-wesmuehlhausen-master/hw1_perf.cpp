// ----------------------------------------------------------------------
// FILE: hw1_perf.cpp
// NAME: S. Bowers
// DATE: August, 2020
// DESC: Performs basic performance tests over a linked and a
// resizable array implementation of the list interface. List
// operations to test are specified by an input number: 
//     1 = add to end
//     2 = add to the middle
//     3 = add to the front
//     4 = get middle element
//     5 = set middle element  
//     6 = remove element at end
//     7 = remove element in middle
//     8 = remove element in front
// Output consists of average operation times for different sized
// input lists for both impleemntations.
// ----------------------------------------------------------------------


#include <stdlib.h>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <chrono>
#include <string>
#include "list.h"
#include "array_list.h"
#include "linked_list.h"

using namespace std;
using namespace std::chrono;

// number of test iterations per test
const int ITERATIONS = 7;

const int ARRAYLIST = 0;
const int LINKEDLIST = 1;

unsigned long sum(unsigned long array[], int n);
double add_end(int size, int type);
double add_mid(int size, int type);
double add_front(int size, int type);
double get_mid(int size, List<int>& list);
double set_mid(int size, List<int>& list);
double rem_end(int size, List<int>& list);
double rem_mid(int size, List<int>& list);
double rem_front(int size, List<int>& list);


int main(int argc, char* argv[])
{
  // check command line args
  if (argc != 2) {
    cerr << "usage: " << argv[0] << " test-number (1-8)" << endl;
    exit(1);
  }

  string test_number = argv[1];
  int start = 0;
  int stop = 100000; 
  int step = 1024; 
  
  // configure output
  cout << fixed << showpoint;
  cout << setprecision(2);

  // test 1: add to end of list
  if (test_number.compare("1") == 0) {
    cout << "# Column 1 = Input data size" << endl
         << "# Column 2 = Average time for array add to end" << endl
         << "# Column 3 = Average time for linked list add to end" << endl
         << "# All times are measured in microseconds" << endl;
    double avg1, avg2;
    for (int size = start; size <= stop; size += step) {
      avg1 = add_end(size, ARRAYLIST);
      avg2 = add_end(size, LINKEDLIST);
      cout << size << " " << avg1 << " " << avg2 << endl;
    }
  }
  // test 2: add to middle of list
  else if (test_number.compare("2") == 0) {
    cout << "# Column 1 = Input data size" << endl
         << "# Column 2 = Average time for array add to middle" << endl
         << "# Column 3 = Average time for linked list add to middle" << endl
         << "# All times are measured in microseconds" << endl;
    double avg1, avg2;
    for (int size = start; size <= stop; size += step) {
      avg1 = add_mid(size, ARRAYLIST);
      avg2 = add_mid(size, LINKEDLIST);
      cout << size << " " << avg1 << " " << avg2 << endl;
    }
  }
  // test 3: add to front of list
  else if (test_number.compare("3") == 0) {
    cout << "# Column 1 = Input data size" << endl
         << "# Column 2 = Average time to add to front of array" << endl
         << "# Column 3 = Average time to add to front of linked list" << endl
         << "# All times are measured in microseconds" << endl;
    double avg1, avg2;
    for (int size = start; size <= stop; size += step) {
      avg1 = add_front(size, ARRAYLIST);
      avg2 = add_front(size, LINKEDLIST);
      cout << size << " " << avg1 << " " << avg2 << endl;
    }
  }
  // test 4: get the middle item in the list
  else if (test_number.compare("4") == 0) {
    cout << "# Column 1 = Input data size" << endl
         << "# Column 2 = Average time to get middle array element" << endl
         << "# Column 3 = Average time to get middle linked list element" << endl
         << "# All times are measured in microseconds" << endl;
    double avg1, avg2;
    for (int size = start; size <= stop; size += step) {
      ArrayList<int>* list1 = new ArrayList<int>;
      avg1 = get_mid(size, *list1);
      delete list1;
      LinkedList<int>* list2 = new LinkedList<int>;
      avg2 = get_mid(size, *list2);
      delete list2;
      cout << size << " " << avg1 << " " << avg2 << endl;
    }
  }
  // test 5: set the middle item in the list
  else if (test_number.compare("5") == 0) {
    cout << "# Column 1 = Input data size" << endl
         << "# Column 2 = Average time to set middle array element" << endl
         << "# Column 3 = Average time to set middle linked list element" << endl
         << "# All times are measured in microseconds" << endl;
    double avg1, avg2;
    for (int size = start; size <= stop; size += step) {
      ArrayList<int>* list1 = new ArrayList<int>;
      avg1 = set_mid(size, *list1);
      delete list1;
      LinkedList<int>* list2 = new LinkedList<int>;
      avg2 = set_mid(size, *list2);
      delete list2;
      cout << size << " " << avg1 << " " << avg2 << endl;
    }
  }
  // test 6: remove last element in list
  else if (test_number.compare("6") == 0) {
    cout << "# Column 1 = Input data size" << endl
         << "# Column 2 = Average time to remove last array element" << endl
         << "# Column 3 = Average time to remove last linked list element" << endl
         << "# All times are measured in microseconds" << endl;
    double avg1, avg2;
    for (int size = start; size <= stop; size += step) {
      ArrayList<int>* list1 = new ArrayList<int>;
      avg1 = rem_end(size, *list1);
      delete list1;
      LinkedList<int>* list2 = new LinkedList<int>;
      avg2 = rem_end(size, *list2);
      delete list2;
      cout << size << " " << avg1 << " " << avg2 << endl;
    }
  }
  // test 7: remove middle element in list
  else if (test_number.compare("7") == 0) {
    cout << "# Column 1 = Input data size" << endl
         << "# Column 2 = Average time to remove middle array element" << endl
         << "# Column 3 = Average time to remove middle linked list element" << endl
         << "# All times are measured in microseconds" << endl;
    double avg1, avg2;
    for (int size = start; size <= stop; size += step) {
      ArrayList<int>* list1 = new ArrayList<int>;
      avg1 = rem_mid(size, *list1);
      delete list1;
      LinkedList<int>* list2 = new LinkedList<int>;
      avg2 = rem_mid(size, *list2);
      delete list2;
      cout << size << " " << avg1 << " " << avg2 << endl;
    }
  }
  // test 8: remove first element in list
  else if (test_number.compare("8") == 0) {
    cout << "# Column 1 = Input data size" << endl
         << "# Column 2 = Average time to remove first array element" << endl
         << "# Column 3 = Average time to remove first linked list element" << endl
         << "# All times are measured in microseconds" << endl;
    double avg1, avg2;
    for (int size = start; size <= stop; size += step) {
      ArrayList<int>* list1 = new ArrayList<int>;
      avg1 = rem_front(size, *list1);
      delete list1;
      LinkedList<int>* list2 = new LinkedList<int>;
      avg2 = rem_front(size, *list2);
      delete list2;
      cout << size << " " << avg1 << " " << avg2 << endl;
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


double add_end(int size, int type)
{
  unsigned long times[ITERATIONS]; 
  for (int i = 0; i < ITERATIONS; ++i) {
    List<int>* list;
    if (type == ARRAYLIST)
      list = new ArrayList<int>;
    else
      list = new LinkedList<int>;
    for (int i = 0; i < size; ++i)
      list->add(i);
    auto start = high_resolution_clock::now();
    list->add(i);
    auto end = high_resolution_clock::now();
    times[i] = duration_cast<microseconds>(end - start).count();
    delete list;
  }
  return sum(times, ITERATIONS) / (ITERATIONS*1.0);
}


double add_front(int size, int type)
{
  unsigned long times[ITERATIONS]; 
  for (int i = 0; i < ITERATIONS; ++i) {
    List<int>* list;
    if (type == ARRAYLIST)
      list = new ArrayList<int>;
    else
      list = new LinkedList<int>;
    for (int i = 0; i < size; ++i)
      list->add(i);
    auto start = high_resolution_clock::now();
    list->add(0, i);
    auto end = high_resolution_clock::now();
    times[i] = duration_cast<microseconds>(end - start).count();
    delete list;
  }
  return sum(times, ITERATIONS) / (ITERATIONS*1.0);
}


double add_mid(int size, int type)
{
  unsigned long times[ITERATIONS]; 
  for (int i = 0; i < ITERATIONS; ++i) {
    List<int>* list;
    if (type == ARRAYLIST)
      list = new ArrayList<int>;
    else
      list = new LinkedList<int>;
    for (int i = 0; i < size; ++i)
      list->add(i);
    auto start = high_resolution_clock::now();
    list->add(size/2, 42);
    auto end = high_resolution_clock::now();
    times[i] = duration_cast<microseconds>(end - start).count();
    delete list;    
  }
  return sum(times, ITERATIONS) / (ITERATIONS*1.0);
}


double get_mid(int size, List<int>& list)
{
  for (int i = 0; i < size; ++i)
    list.add(i);
  unsigned long times[ITERATIONS]; 
  for (int i = 0; i < ITERATIONS; ++i) {
    auto start = high_resolution_clock::now();
    int v = 0;
    list.get(size/2, v);
    auto end = high_resolution_clock::now();
    times[i] = duration_cast<microseconds>(end - start).count();
  }
  return sum(times, ITERATIONS) / (ITERATIONS*1.0);
}

double set_mid(int size, List<int>& list)
{
  for (int i = 0; i < size; ++i)
    list.add(i);
  unsigned long times[ITERATIONS]; 
  for (int i = 0; i < ITERATIONS; ++i) {
    auto start = high_resolution_clock::now();
    int v = 0;
    list.set(size/2, 42);
    auto end = high_resolution_clock::now();
    times[i] = duration_cast<microseconds>(end - start).count();
  }
  return sum(times, ITERATIONS) / (ITERATIONS*1.0);
}


double rem_end(int size, List<int>& list)
{
  for (int i = 0; i < size; ++i)
      list.add(i);
  unsigned long times[ITERATIONS]; 
  for (int i = 0; i < ITERATIONS; ++i) {
    auto start = high_resolution_clock::now();
    list.remove(list.size() - 1);
    auto end = high_resolution_clock::now();
    times[i] = duration_cast<microseconds>(end - start).count();
    list.add(1);
  }
  return sum(times, ITERATIONS) / (ITERATIONS*1.0);
}


double rem_mid(int size, List<int>& list)
{
  for (int i = 0; i < size; ++i)
    list.add(i);
  unsigned long times[ITERATIONS]; 
  for (int i = 0; i < ITERATIONS; ++i) {
    auto start = high_resolution_clock::now();
    list.remove(size/2);
    auto end = high_resolution_clock::now();
    times[i] = duration_cast<microseconds>(end - start).count();
    list.add(1);
  }
  return sum(times, ITERATIONS) / (ITERATIONS*1.0);
}


double rem_front(int size, List<int>& list)
{
  for (int i = 0; i < size; ++i)
    list.add(i);
  unsigned long times[ITERATIONS]; 
  for (int i = 0; i < ITERATIONS; ++i) {
    auto start = high_resolution_clock::now();
    list.remove(0);
    auto end = high_resolution_clock::now();
    times[i] = duration_cast<microseconds>(end - start).count();
    list.add(1);
  }
  return sum(times, ITERATIONS) / (ITERATIONS*1.0);
}

