// ----------------------------------------------------------------------
// FILE: hw2_perf.cpp
// NAME: S. Bowers
// DATE: September, 2020
// DESC: Performs basic sorting performance tests over a linked and a
// resizable array implementation of the list interface. Tests are
// specified by an input number:
//     1 = selection vs insertion sort on a reverse-sorted list
//     2 = selection vs insertion sort on a shuffle-sorted list
//     3 = reverse vs shuffle sorted lists for selection sort
//     4 = reverse vs shuffle sorted lists for insertion sort
// Output consists of average operation times for different sized
// input lists for both impleemntations.
// ----------------------------------------------------------------------


#include <stdlib.h>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <chrono>
#include <string>
#include <cassert>
#include "list.h"
#include "array_list.h"
#include "linked_list.h"

using namespace std;
using namespace std::chrono;

// number of test iterations per test
const int ITERATIONS = 5;
const int SHUFFLINGS = 2;

const int ARRAYLIST = 0;
const int LINKEDLIST = 1;

unsigned long sum(unsigned long array[], int n);

double selection_sort_reverse(int size, int type);
double insertion_sort_reverse(int size, int type);
double selection_sort_shuffle(int size, int type);
double insertion_sort_shuffle(int size, int type);


int main(int argc, char* argv[])
{
  // check command line args
  if (argc != 2) {
    cerr << "usage: " << argv[0] << " test-number (1-4)" << endl;
    exit(1);
  }

  string test_number = argv[1];
  int start = 0;
  int stop = 10000; 
  int step = 500; 
  
  // configure output
  cout << fixed << showpoint;
  cout << setprecision(2);

  // test 1: reverse sorted
  if (test_number.compare("1") == 0) {
    cout << "# Column 1 = Input data size" << endl
         << "# Column 2 = Array avg time reverse sorted, selection sort\n"
         << "# Column 3 = Linked avg time reverse sorted, selection sort\n"
         << "# Column 4 = Array avg time reverse sorted, insertion sort\n"
         << "# Column 5 = Linked avg time reverse sorted, insertion sort\n"
         << "# All times are measured in milliseconds" << endl;
    for (int size = start; size <= stop; size += step) {
      double avg1 = selection_sort_reverse(size, ARRAYLIST);
      double avg2 = selection_sort_reverse(size, LINKEDLIST);
      double avg3 = insertion_sort_reverse(size, ARRAYLIST);      
      double avg4 = insertion_sort_reverse(size, LINKEDLIST);      
      cout << size << " " << (avg1/1000.0) << " " << (avg2/1000.0) << " " 
           << (avg3/1000.0) << " " << (avg4/1000.0) << endl;
    }
  }
  // test 2: shuffle sorted
  else if (test_number.compare("2") == 0) {
    cout << "# Column 1 = Input data size" << endl
         << "# Column 2 = Array avg time shuffle sorted, selection sort\n"
         << "# Column 3 = Linked avg time shuffle sorted, selection sort\n"
         << "# Column 4 = Array avg time shuffle sorted, insertion sort\n"
         << "# Column 5 = Linked avg time shuffle sorted, insertion sort\n"
         << "# All times are measured in milliseconds" << endl;
    for (int size = start; size <= stop; size += step) {
      double avg1 = selection_sort_shuffle(size, ARRAYLIST);
      double avg2 = selection_sort_shuffle(size, LINKEDLIST);
      double avg3 = insertion_sort_shuffle(size, ARRAYLIST);      
      double avg4 = insertion_sort_shuffle(size, LINKEDLIST);      
      cout << size << " " << (avg1/1000.0) << " " << (avg2/1000.0) << " " 
           << (avg3/1000.0) << " " << (avg4/1000.0) << endl;
    }
  }
  // test 3: selection sort
  else if (test_number.compare("3") == 0) {
    cout << "# Column 1 = Input data size" << endl
         << "# Column 2 = Array avg time shuffle sorted, selection sort\n"
         << "# Column 3 = Array avg time reverse sorted, selection sort\n"
         << "# Column 4 = Linked avg time shuffle sorted, selection sort\n"
         << "# Column 5 = Linked avg time reverse sorted, selection sort\n"
         << "# All times are measured in milliseconds" << endl;
    for (int size = start; size <= stop; size += step) {
      double avg1 = selection_sort_reverse(size, ARRAYLIST);
      double avg2 = selection_sort_shuffle(size, ARRAYLIST);
      double avg3 = selection_sort_reverse(size, LINKEDLIST);      
      double avg4 = selection_sort_shuffle(size, LINKEDLIST);      
      cout << size << " " << (avg1/1000.0) << " " << (avg2/1000.0) << " " 
           << (avg3/1000.0) << " " << (avg4/1000.0) << endl;
    }
  }
  // test 4: insertion sort
  else if (test_number.compare("4") == 0) {
    cout << "# Column 1 = Input data size" << endl
         << "# Column 2 = Array avg time shuffle sorted, insertion sort\n"
         << "# Column 3 = Array avg time reverse sorted, insertion sort\n"
         << "# Column 4 = Linked avg time shuffle sorted, insertion sort\n"
         << "# Column 5 = Linked avg time reverse sorted, insertion sort\n"
         << "# All times are measured in milliseconds" << endl;
    for (int size = start; size <= stop; size += step) {
      double avg1 = insertion_sort_reverse(size, ARRAYLIST);
      double avg2 = insertion_sort_shuffle(size, ARRAYLIST);
      double avg3 = insertion_sort_reverse(size, LINKEDLIST);      
      double avg4 = insertion_sort_shuffle(size, LINKEDLIST);      
      cout << size << " " << (avg1/1000.0) << " " << (avg2/1000.0) << " " 
           << (avg3/1000.0) << " " << (avg4/1000.0) << endl;
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


double selection_sort_reverse(int size, int type)
{
  unsigned long times[ITERATIONS]; 
  for (int i = 0; i < ITERATIONS; ++i) {
    List<int>* list;
    if (type == ARRAYLIST)
      list = new ArrayList<int>;
    else
      list = new LinkedList<int>;
    for (int i = size; i >= 0; --i)
      list->add(i);
    // check list size
    assert(list.size() == size);
    auto start = high_resolution_clock::now();
    list->selection_sort();
    auto end = high_resolution_clock::now();
    // check list was sorted
    for (int i = 0; i < size - 1; ++i) {
      int val1 = 0;
      int val2 = 0;
      list->get(i, val1);
      list->get(i+1, val2);
      assert(val1 < val2);
    }
    times[i] = duration_cast<microseconds>(end - start).count();
    delete list;
  }
  return sum(times, ITERATIONS) / (ITERATIONS*1.0);
}


double insertion_sort_reverse(int size, int type)
{
  unsigned long times[ITERATIONS]; 
  for (int i = 0; i < ITERATIONS; ++i) {
    List<int>* list;
    if (type == ARRAYLIST)
      list = new ArrayList<int>;
    else
      list = new LinkedList<int>;
    for (int i = size; i >= 0; --i)
      list->add(i);
    // check list size
    assert(list.size() == size);
    auto start = high_resolution_clock::now();
    list->insertion_sort();
    auto end = high_resolution_clock::now();
    // check list was sorted
    for (int i = 0; i < size - 1; ++i) {
      int val1 = 0;
      int val2 = 0;
      list->get(i, val1);
      list->get(i+1, val2);
      assert(val1 < val2);
    }
    times[i] = duration_cast<microseconds>(end - start).count();
    delete list;
  }
  return sum(times, ITERATIONS) / (ITERATIONS*1.0);
}


// helper
void shuffle(List<int>& list, bool first)
{
  ArrayList<int>* list1 = new ArrayList<int>;
  ArrayList<int>* list2 = new ArrayList<int>;
  size_t mid = list.size()/2;
  size_t len = list.size();
  for (size_t i = 0; i < mid; ++i) {
    int val = 0;
    list.get(i, val);
    list1->add(val);
  }
  for (size_t i = mid; i < len; ++i) {
    int val = 0;
    list.get(i, val);
    list2->add(val);
  }
  size_t index = 0;
  for (size_t i = 0; i < mid; ++i) {
    int val1 = 0;
    int val2 = 0;
    list1->get(i, val1);
    list2->get(i, val2);
    list.set(index++, first ? val1 : val2);
    list.set(index++, first ? val2 : val1);
  }
  delete list1;
  delete list2;
}


double selection_sort_shuffle(int size, int type)
{
  unsigned long times[ITERATIONS]; 
  for (int i = 0; i < ITERATIONS; ++i) {
    List<int>* list;
    if (type == ARRAYLIST)
      list = new ArrayList<int>;
    else
      list = new LinkedList<int>;
    for (size_t i = 1; i <= size; ++i)
      list->add(i);
    // check list size
    assert(list.size() == size);
    // shuffle the list
    for (int i = 0; i < SHUFFLINGS; ++i)
      shuffle(*list, (i%2));
    auto start = high_resolution_clock::now();
    list->selection_sort();
    auto end = high_resolution_clock::now();
    // check list was sorted
    for (int i = 0; i < size - 1; ++i) {
      int val1 = 0;
      int val2 = 0;
      list->get(i, val1);
      list->get(i+1, val2);
      assert(val1 < val2);
    }
    times[i] = duration_cast<microseconds>(end - start).count();
    delete list;
  }
  return sum(times, ITERATIONS) / (ITERATIONS*1.0);
}


double insertion_sort_shuffle(int size, int type)
{
  unsigned long times[ITERATIONS]; 
  for (int i = 0; i < ITERATIONS; ++i) {
    List<int>* list;
    if (type == ARRAYLIST)
      list = new ArrayList<int>;
    else
      list = new LinkedList<int>;
    for (size_t i = 1; i <= size; ++i)
      list->add(i);
    // check list size
    assert(list.size() == size);
    // shuffle the list
    for (int i = 0; i < SHUFFLINGS; ++i)
      shuffle(*list, (i%2));
    auto start = high_resolution_clock::now();
    list->insertion_sort();
    auto end = high_resolution_clock::now();
    // check list was sorted
    for (int i = 0; i < size - 1; ++i) {
      int val1 = 0;
      int val2 = 0;
      list->get(i, val1);
      list->get(i+1, val2);
      assert(val1 < val2);
    }
    times[i] = duration_cast<microseconds>(end - start).count();
    delete list;
  }
  return sum(times, ITERATIONS) / (ITERATIONS*1.0);
}






