
// ----------------------------------------------------------------------
// FILE: hw3_test.cpp
// NAME: S. Bowers (initial)
// DATE: Fall, 2020
// DESC: Basic array and linked list unit tests for HW3.
// ----------------------------------------------------------------------


#include <iostream>
#include <string>
#include <gtest/gtest.h>
#include "array_list.h"
#include "linked_list.h"



/* Helper function to print an int List*/
void print_list(List<int>& list)
{
  int val = 0;
  for (size_t i = 0; i < list.size(); ++i) {
    list.get(i, val);
    std::cout << val << " ";
  }
  std::cout << std::endl;
}


// Test 1 (a)
TEST(BasicArrayListTest, CorrectSize) {
  ArrayList<int> l;
  ASSERT_EQ(0, l.size());
  l.add(10);
  ASSERT_EQ(1, l.size());  
  l.add(20);
  ASSERT_EQ(2, l.size());
  l.add(30);
  ASSERT_EQ(3, l.size());
}

// Test 1 (b)
TEST(BasicLinkedListTest, CorrectSize) {
  LinkedList<int> l;
  ASSERT_EQ(0, l.size());
  l.add(10);
  ASSERT_EQ(1, l.size());  
  l.add(20);
  ASSERT_EQ(2, l.size());
  l.add(30);
  ASSERT_EQ(3, l.size());
}

// Test 2 (a)
TEST(BasicArrayListTest, AddToEnd) {
  ArrayList<int> l;
  l.add(10);
  int val = 0;
  ASSERT_EQ(1, l.size());
  ASSERT_EQ(true, l.get(0, val));
  ASSERT_EQ(10, val);
  l.add(20);
  ASSERT_EQ(2, l.size());
  ASSERT_EQ(true, l.get(1, val));
  ASSERT_EQ(20, val);
  ASSERT_EQ(false, l.get(2, val));
}

// Test 2 (b)
TEST(BasicLinkedListTest, AddToEnd) {
  LinkedList<int> l;
  l.add(10);
  int val = 0;
  ASSERT_EQ(1, l.size());
  ASSERT_EQ(true, l.get(0, val));
  ASSERT_EQ(10, val);
  l.add(20);
  ASSERT_EQ(2, l.size());
  ASSERT_EQ(true, l.get(1, val));
  ASSERT_EQ(20, val);
  ASSERT_EQ(false, l.get(2, val));
}

// Test 3 (a)
TEST(BasicArrayListTest, SetItem) {
  ArrayList<int> l;
  l.add(10);
  l.add(20);
  l.add(30);
  ASSERT_EQ(true, l.set(0, 40));
  int val = 0;
  ASSERT_EQ(true, l.get(0, val));
  ASSERT_EQ(40, val);
  ASSERT_EQ(true, l.set(1, 50));
  ASSERT_EQ(true, l.get(0, val));
  ASSERT_EQ(40, val);
  ASSERT_EQ(false, l.set(3, 60));
}

// Test 3 (b)
TEST(BasicLinkedListTest, SetItem) {
  LinkedList<int> l;
  l.add(10);
  l.add(20);
  l.add(30);
  ASSERT_EQ(true, l.set(0, 40));
  int val = 0;
  ASSERT_EQ(true, l.get(0, val));
  ASSERT_EQ(40, val);
  ASSERT_EQ(true, l.set(1, 50));
  ASSERT_EQ(true, l.get(0, val));
  ASSERT_EQ(40, val);
  ASSERT_EQ(false, l.set(3, 60));
}

// Test 4 (a)
TEST(BasicArrayListTest, RemoveItem) {
  ArrayList<int> l;
  l.add(10);
  l.add(20);
  l.add(30);
  l.add(40);
  // remove 20
  ASSERT_EQ(true, l.remove(1)); 
  ASSERT_EQ(3, l.size());
  int val = 0;
  l.get(1, val);
  ASSERT_EQ(30, val);
  // remove 40
  ASSERT_EQ(true, l.remove(2));
  ASSERT_EQ(2, l.size());
  // remove 10
  ASSERT_EQ(true, l.remove(0));
  ASSERT_EQ(1, l.size());
  l.get(0, val);
  ASSERT_EQ(30, val);
  // remove 30
  ASSERT_EQ(true, l.remove(0));
  ASSERT_EQ(0, l.size());
  // remove invalid index
  ASSERT_EQ(false, l.remove(0));
  ASSERT_EQ(0, l.size());
}

// Test 4 (b)
TEST(BasicLinkedListTest, RemoveItem) {
  LinkedList<int> l;
  l.add(10);
  l.add(20);
  l.add(30);
  l.add(40);
  // remove 20
  ASSERT_EQ(true, l.remove(1)); 
  ASSERT_EQ(3, l.size());
  int val = 0;
  l.get(1, val);
  ASSERT_EQ(30, val);
  // remove 40
  ASSERT_EQ(true, l.remove(2));
  ASSERT_EQ(2, l.size());
  // remove 10
  ASSERT_EQ(true, l.remove(0));
  ASSERT_EQ(1, l.size());
  l.get(0, val);
  ASSERT_EQ(30, val);
  // remove 30
  ASSERT_EQ(true, l.remove(0));
  ASSERT_EQ(0, l.size());
  // remove invalid index
  ASSERT_EQ(false, l.remove(0));
  ASSERT_EQ(0, l.size());
}

// Test 5 (a)
TEST(BasicArrayListTest, ResizeTest) {
  ArrayList<int> l;
  int val = 0;
  for (int i = 10; i <= 310; i += 10) {
    l.add(i);
    ASSERT_EQ(true, l.get(i/10 - 1, val));
    ASSERT_EQ(i, val);
    ASSERT_EQ(i/10, l.size());
  }
}

// Test 6 (a)
TEST(BasicArrayListTest, AddItemByIndex) {
  ArrayList<int> l;
  // add to empty
  l.add(0, 20);
  // add to end
  l.add(1, 40);
  // add to list: 20, 40, 60, 80, ..., 240
  for (size_t i = 3; i <= 12; ++i)
    l.add(i * 20);
  // add missing: 10, 20, 30, 40, ..., 240
  for (size_t i = 12; i > 0; --i) 
    l.add(i - 1, ((i - 1) * 20) + 10);
  // check result
  for (size_t i = 0; i < l.size(); ++i) {
    int v = 0;
    l.get(i, v);
    ASSERT_EQ((i + 1) * 10, v);
  }
}

// Test 6 (b)
TEST(BasicLinkedListTest, AddItemByIndex) {
  LinkedList<int> l;
  // add to empty
  l.add(0, 20);
  // add to end
  l.add(1, 40);
  // add to list: 20, 40, 60, 80, ..., 240
  for (size_t i = 3; i <= 12; ++i)
    l.add(i * 20);
  // add missing: 10, 20, 30, 40, ..., 240
  for (size_t i = 12; i > 0; --i) 
    l.add(i - 1, ((i - 1) * 20) + 10);
  // check result
  for (size_t i = 0; i < l.size(); ++i) {
    int v = 0;
    l.get(i, v);
    ASSERT_EQ((i + 1) * 10, v);
  }
}

// Test 7 (a)
TEST(BasicArrayListTest, CopyAndAssignment) {
  ArrayList<int> l1;
  l1.add(10);
  l1.add(20);
  l1.add(30);
  ArrayList<int> l2(l1);
  ASSERT_EQ(l1.size(), l2.size());
  l2.add(40);
  ASSERT_NE(l1.size(), l2.size());
  l1 = l2;
  ASSERT_EQ(l1.size(), l2.size());
  l1 = l1;
  ASSERT_EQ(l1.size(), l2.size());
  ArrayList<int> l3;
  l3.add(50);
  l3 = l2 = l1;
  ASSERT_EQ(l3.size(), l1.size());
  for (size_t i = 0; i < l1.size(); ++i) {
    int v1 = 0;
    int v2 = 0;
    l1.get(i, v1);
    l3.get(i, v2);
    ASSERT_EQ(v1, v2);
  }
}

// Test 7 (b)
TEST(BasicLinkedListTest, CopyAndAssignment) {
  LinkedList<int> l1;
  l1.add(10);
  l1.add(20);
  l1.add(30);
  LinkedList<int> l2(l1);
  ASSERT_EQ(l1.size(), l2.size());
  l2.add(40);
  ASSERT_NE(l1.size(), l2.size());
  l1 = l2;
  ASSERT_EQ(l1.size(), l2.size());
  l1 = l1;
  ASSERT_EQ(l1.size(), l2.size());
  LinkedList<int> l3;
  l3.add(50);
  l3 = l2 = l1;
  ASSERT_EQ(l3.size(), l1.size());
  for (size_t i = 0; i < l1.size(); ++i) {
    int v1 = 0;
    int v2 = 0;
    l1.get(i, v1);
    l3.get(i, v2);
    ASSERT_EQ(v1, v2);
  }
}

// Test 8 (a) basic selection sort test
TEST(ArrayListSortTest, SelectionSort)
{
  ArrayList<int> l1;
  for (int i = 10; i > 0; --i)
    l1.add(i);
  ASSERT_EQ(10, l1.size());
  l1.selection_sort();
  for (int i = 0; i < 9; ++i) {
    int val1 = 0;
    int val2 = 0;
    l1.get(i, val1);
    l1.get(i+1, val2);
    ASSERT_LT(val1, val2);
  }
}

// Test 8 (b) basic selection sort test
TEST(LinkedListSortTest, SelectionSort)
{
  LinkedList<int> l1;
  for (int i = 6; i > 0; --i)
    l1.add(i);
  ASSERT_EQ(6, l1.size());
  l1.selection_sort();
  for (int i = 0; i < 5; ++i) {
    int val1 = 0;
    int val2 = 0;
    l1.get(i, val1);
    l1.get(i+1, val2);
    ASSERT_LT(val1, val2);
  }
}

// Test 9 (a) basic insertion sort test
TEST(ArrayListSortTest, InsertionSort)
{
  ArrayList<int> l1;
  for (int i = 10; i > 0; --i)
    l1.add(i);
  ASSERT_EQ(10, l1.size());
  l1.insertion_sort();
  for (int i = 0; i < 9; ++i) {
    int val1 = 0;
    int val2 = 0;
    l1.get(i, val1);
    l1.get(i+1, val2);
    ASSERT_LT(val1, val2);
  }
}

// Test 9 (b) basic insertion sort test
TEST(LinkedListSortTest, InsertionSort)
{
  LinkedList<int> l1;
  for (int i = 10; i > 0; --i)
    l1.add(i);
  ASSERT_EQ(10, l1.size());
  l1.insertion_sort();
  for (int i = 0; i < 9; ++i) {
    int val1 = 0;
    int val2 = 0;
    l1.get(i, val1);
    l1.get(i+1, val2);
    ASSERT_LT(val1, val2);
  }
}


// Test 10 (a) basic merge sort test
TEST(ArrayListSortTest, MergeSort)
{
  ArrayList<int> l1;
  for (int i = 10; i > 0; --i)
    l1.add(i);
  ASSERT_EQ(10, l1.size());
  //std::cout << "A" << std::endl; 
  l1.merge_sort();
  //std::cout << "B" << std::endl;
  for (int i = 0; i < 9; ++i) {
    int val1 = 0;
    int val2 = 0;
    l1.get(i, val1);
    l1.get(i+1, val2);
    //std::cout << "Val1: " << val1 << std::endl;
    //std::cout << "Val2: " << val2 << std::endl;
    ASSERT_LT(val1, val2);
  }
  //std::cout << "C" << std::endl;
}

// Test 10 (b) basic merge sort test
TEST(LinkedListSortTest, MergeSort)
{
  LinkedList<int> l1;
  for (int i = 10; i > 0; --i)
    l1.add(i);
  ASSERT_EQ(10, l1.size());
  l1.merge_sort();
  //std::cout << "A" << std::endl; 
  for (int i = 0; i < 9; ++i) {
    int val1 = 0;
    int val2 = 0;
    l1.get(i, val1);
    l1.get(i+1, val2);
    ASSERT_LT(val1, val2);
  }
}

// Test 11 (a) basic quick sort test
TEST(ArrayListSortTest, QuickSort)
{
  ArrayList<int> l1;
  for (int i = 10; i > 0; --i)
    l1.add(i);
  ASSERT_EQ(10, l1.size());
  l1.quick_sort();
  for (int i = 0; i < 9; ++i) {
    int val1 = 0;
    int val2 = 0;
    l1.get(i, val1);
    l1.get(i+1, val2);
    ASSERT_LT(val1, val2);
  }
}

// Test 11 (b) basic quick sort test
TEST(LinkedListSortTest, QuickSort)
{
  LinkedList<int> l1;
  for (int i = 10; i > 0; --i)
    l1.add(i);
  ASSERT_EQ(10, l1.size());
  l1.quick_sort();
  for (int i = 0; i < 9; ++i) {
    int val1 = 0;
    int val2 = 0;
    l1.get(i, val1);
    l1.get(i+1, val2);
    ASSERT_LT(val1, val2);
  }
}



// Test 12 (a) add to linked list after selection sort
TEST(LinkedListSortTest, SelectionSortAddEnd)
{
  LinkedList<int> l1;
  for (int i = 6; i > 0; --i)
    l1.add(i);
  l1.selection_sort();
  l1.add(7);
  int val1 = 0;
  l1.get(6, val1);
  ASSERT_EQ(7, val1);
}

// Test 12 (b) add to linked list after insertion sort
TEST(LinkedListSortTest, InsertionSortAddEnd)
{
  LinkedList<int> l1;
  for (int i = 6; i > 0; --i)
    l1.add(i);
  l1.insertion_sort();
  l1.add(7);
  int val1 = 0;
  l1.get(6, val1);
  ASSERT_EQ(7, val1);
}

// Test 12 (c) add to linked list after merge sort
TEST(LinkedListSortTest, MergeSortAddEnd)
{
  LinkedList<int> l1;
  for (int i = 6; i > 0; --i)
    l1.add(i);
  l1.merge_sort();
  l1.add(7);
  int val1 = 0;
  l1.get(6, val1);
  ASSERT_EQ(7, val1);
}

// Test 12 (d) add to linked list after quick sort
TEST(LinkedListSortTest, QuickSortAddEnd)
{
  LinkedList<int> l1;
  for (int i = 6; i > 0; --i)
    l1.add(i);
  l1.quick_sort();
  // Example of calling print_list:
  // print_list(l1);
  l1.add(7);
  int val1 = 0;
  l1.get(6, val1);
  ASSERT_EQ(7, val1);
}

//TEST 13A: MOSTLY MATCHING NUMBERS
TEST(ArrayListSortTest, MergeSortMostlyMatching)
{
  //Makes list of same numbers and two unsorted at end
  //[10, 10, ... , 10, 10, 2, 1]
  //checks to see if can get past two numbers being the same
  ArrayList<int> l1;
  for (int i = 10; i > 2; --i)
    l1.add(10);
  l1.add(2);
  l1.add(1);
  l1.merge_sort();
  int val1 = 0;
  l1.get(9, val1);
  ASSERT_EQ(10, val1);
  int val2 = 0;
  l1.get(0, val2);
  ASSERT_EQ(1, val2);
}

//TEST 13B: MOSTLY MATCHING NUMBERS
TEST(ArrayListSortTest, QuickSortMostlyMatching)
{
  //Makes list of same numbers and two unsorted at end
  //[10, 10, ... , 10, 10, 2, 1]
  //checks to see if can get past two numbers being the same
  ArrayList<int> l1;
  for (int i = 10; i > 2; --i)
    l1.add(10);
  l1.add(2);
  l1.add(1);
  l1.quick_sort();
  int val1 = 0;
  l1.get(9, val1);
  ASSERT_EQ(10, val1);
  int val2 = 0;
  l1.get(0, val2);
  ASSERT_EQ(1, val2);
}

//TEST 13C: MOSTLY MATCHING NUMBERS
TEST(LinkedListSortTest, MergeSortMostlyMatching)
{
  //Makes list of same numbers and two unsorted at end
  //[10, 10, ... , 10, 10, 2, 1]
  //checks to see if can get past two numbers being the same
  LinkedList<int> l1;
  for (int i = 10; i > 2; --i)
    l1.add(10);
  l1.add(2);
  l1.add(1);
  l1.merge_sort();
  int val1 = 0;
  l1.get(9, val1);
  ASSERT_EQ(10, val1);
  int val2 = 0;
  l1.get(0, val2);
  ASSERT_EQ(1, val2);
}

//TEST 13D: MOSTLY MATCHING NUMBERS
TEST(LinkedListSortTest, QuickSortMostlyMatching)
{
  //Makes list of same numbers and two unsorted at end
  //[10, 10, ... , 10, 10, 2, 1]
  //checks to see if can get past two numbers being the same
  LinkedList<int> l1;
  for (int i = 10; i > 2; --i)
    l1.add(10);
  l1.add(2);
  l1.add(1);
  l1.quick_sort();
  int val1 = 0;
  l1.get(9, val1);
  ASSERT_EQ(10, val1);
  int val2 = 0;
  l1.get(0, val2);
  ASSERT_EQ(1, val2);
}

//TEST 14A: LARGE LIST REVERSE ORDER
TEST(ArrayListSortTest, QuickSortLargeReverse)
{
  //Makes list: 
  //[250, 99, 98, 97, ... 3, 2, 0]
  //checks to see if can get past two numbers being the same
  ArrayList<int> l1;
  l1.add(250);
  for (int i = 99; i > 1; --i)
    l1.add(i);
  l1.add(0);
  l1.quick_sort();
  int val1 = 0;
  l1.get(99, val1);
  ASSERT_EQ(250, val1);//tests for the first and last value are correct
  int val2 = 0;
  l1.get(0, val2);
  ASSERT_EQ(0, val2);
}

//TEST 14B: LARGE LIST REVERSE ORDER
TEST(ArrayListSortTest, MergeSortLargeReverse)
{
  //Makes list: 
  //[250, 99, 98, 97, ... 3, 2, 0]
  //checks to see if can get past two numbers being the same
  ArrayList<int> l1;
  l1.add(250);
  for (int i = 99; i > 1; --i)
    l1.add(i);
  l1.add(0);
  l1.merge_sort();
  int val1 = 0;
  l1.get(99, val1);
  ASSERT_EQ(250, val1);//tests for the first and last value are correct
  int val2 = 0;
  l1.get(0, val2);
  ASSERT_EQ(0, val2);
}

//TEST 14C: LARGE LIST REVERSE ORDER
TEST(LinkedListSortTest, QuickSortLargeReverse)
{
  //Makes list: 
  //[250, 99, 98, 97, ... 3, 2, 0]
  //checks to see if can get past two numbers being the same
  LinkedList<int> l1;
  l1.add(250);
  for (int i = 99; i > 1; --i)
    l1.add(i);
  l1.add(0);
  l1.quick_sort();
  int val1 = 0;
  l1.get(99, val1);
  ASSERT_EQ(250, val1);//tests for the first and last value are correct
  int val2 = 0;
  l1.get(0, val2);
  ASSERT_EQ(0, val2);
}

//TEST 14D: LARGE LIST REVERSE ORDER
TEST(LinkedListSortTest, MergeSortLargeReverse)
{
  //Makes list: 
  //[250, 99, 98, 97, ... 3, 2, 0]
  //checks to see if can get past two numbers being the same
  LinkedList<int> l1;
  l1.add(250);
  for (int i = 99; i > 1; --i)
    l1.add(i);
  l1.add(0);
  l1.merge_sort();
  int val1 = 0;
  l1.get(99, val1);
  ASSERT_EQ(250, val1);//tests for the first and last value are correct
  int val2 = 0;
  l1.get(0, val2);
  ASSERT_EQ(0, val2);
}

//TEST 15A: SMALL LIST SIZE
TEST(ArrayListSortTest, MergeSortSmallSize)
{
  //Makes and tests list: 
  //[1] and [1,9]
  //tests for 1 and 9
  ArrayList<int> l1;
  l1.add(1);
  l1.merge_sort();
  int val2 = 0;
  l1.get(0, val2);
  ASSERT_EQ(1, val2);
  l1.add(9);
  l1.merge_sort();
  int val1 = 0;
  l1.get(1, val1);
  ASSERT_EQ(9, val1);
}

//TEST 15B: SMALL LIST SIZE
TEST(ArrayListSortTest, QuickSortSmallSize)
{
  //Makes and tests list: 
  //[1] and [1,9]
  //tests for 1 and 9
  ArrayList<int> l1;
  l1.add(1);
  l1.quick_sort();
  int val2 = 0;
  l1.get(0, val2);
  ASSERT_EQ(1, val2);
  l1.add(9);
  l1.quick_sort();
  int val1 = 0;
  l1.get(1, val1);
  ASSERT_EQ(9, val1);
}

//TEST 15C: SMALL LIST SIZE
TEST(LinkedListSortTest, MergeSortSmallSize)
{
  //Makes and tests list: 
  //[1] and [1,9]
  //tests for 1 and 9
  LinkedList<int> l1;
  l1.add(1);
  l1.merge_sort();
  int val2 = 0;
  l1.get(0, val2);
  ASSERT_EQ(1, val2);
  l1.add(9);
  l1.merge_sort();
  int val1 = 0;
  l1.get(1, val1);
  ASSERT_EQ(9, val1);
}

//TEST 15D: SMALL LIST SIZE
TEST(LinkedListSortTest, QuickSortSmallSize)
{
  //Makes and tests list: 
  //[1] and [1,9]
  //tests for 1 and 9
  LinkedList<int> l1;
  l1.add(1);
  l1.quick_sort();
  int val2 = 0;
  l1.get(0, val2);
  ASSERT_EQ(1, val2);
  l1.add(9);
  l1.quick_sort();
  int val1 = 0;
  l1.get(1, val1);
  ASSERT_EQ(9, val1);
}

//TEST 16A: DOUBLE STEP
TEST(ArrayListSortTest, MergeSortDoubleStep)
{
  //Makes and tests list: 
  //[100, 100, 99, 99, ... , 2, 2, 1, 1]
  //tests for 100 and 1
  ArrayList<int> l1;
  for(int i = 100; i > 0; --i)
  {
    l1.add(i);
    l1.add(i);
  }
  l1.merge_sort();
  int val1 = 0;
  l1.get(0, val1);
  ASSERT_EQ(1, val1);
  int val2 = 100;
  l1.get(199, val1);
  ASSERT_EQ(100, val1);
}

//TEST 16B: DOUBLE STEP
TEST(ArrayListSortTest, QuickSortDoubleStep)
{
  //Makes and tests list: 
  //[100, 100, 99, 99, ... , 2, 2, 1, 1]
  //tests for 100 and 1
  ArrayList<int> l1;
  for(int i = 100; i > 0; --i)
  {
    l1.add(i);
    l1.add(i);
  }
  l1.quick_sort();
  int val1 = 0;
  l1.get(0, val1);
  ASSERT_EQ(1, val1);
  int val2 = 100;
  l1.get(199, val1);
  ASSERT_EQ(100, val1);
}

//TEST 16C: DOUBLE STEP
TEST(LinkedListSortTest, MergeSortDoubleStep)
{
  //Makes and tests list: 
  //[100, 100, 99, 99, ... , 2, 2, 1, 1]
  //tests for 100 and 1
  LinkedList<int> l1;
  for(int i = 100; i > 0; --i)
  {
    l1.add(i);
    l1.add(i);
  }
  l1.merge_sort();
  int val1 = 0;
  l1.get(0, val1);
  ASSERT_EQ(1, val1);
  int val2 = 100;
  l1.get(199, val1);
  ASSERT_EQ(100, val1);
}

//TEST 16D: DOUBLE STEP
TEST(LinkedListSortTest, QuickSortDoubleStep)
{
  //Makes and tests list: 
  //[100, 100, 99, 99, ... , 2, 2, 1, 1]
  //tests for 100 and 1
  LinkedList<int> l1;
  for(int i = 100; i > 0; --i)
  {
    l1.add(i);
    l1.add(i);
  }
  l1.quick_sort();
  int val1 = 0;
  l1.get(0, val1);
  ASSERT_EQ(1, val1);
  int val2 = 100;
  l1.get(199, val1);
  ASSERT_EQ(100, val1);
}


//TEST 17: Linked List Merge Sort Size 2
TEST(LinkedListSortTest, QuickSortSize2)
{
  LinkedList<int> l1;
  l1.add(1);
  l1.add(2);
  l1.quick_sort();
  LinkedList<int> l2;
  l2.add(1);
  l2.add(1);
  l2.quick_sort();
  LinkedList<int> l3;
  l3.add(3);
  l3.add(2);
  l3.quick_sort(); 
}

//TEST 17: Linked List Merge Sort Size 3
TEST(LinkedListSortTest, QuickSortSize3)
{
  LinkedList<int> l1;
  l1.add(3);
  l1.add(2);
  l1.add(1);
  l1.quick_sort();
  //std::cout << "Got to here?" << std::endl;
  LinkedList<int> l2;
  l2.add(1);
  l2.add(3);
  l2.add(2);
  l2.quick_sort();
  //std::cout << "Got to here?" << std::endl;
  LinkedList<int> l3;
  l3.add(2);
  l3.add(3);
  l3.add(1);
  l3.quick_sort(); 
  //std::cout << "Got to here?" << std::endl;
}

//TEST 17: Linked List Merge Sort Size 2
TEST(LinkedListSortTest, MergeSortSize2)
{
  LinkedList<int> l1;
  l1.add(1);
  l1.add(2);
  l1.merge_sort();
  LinkedList<int> l2;
  l2.add(1);
  l2.add(1);
  l2.merge_sort();
  LinkedList<int> l3;
  l3.add(3);
  l3.add(2);
  l3.merge_sort(); 
}

//TEST 17: Linked List Merge Sort Size 3
TEST(LinkedListSortTest, MergeSortSize3)
{
  LinkedList<int> l1;
  l1.add(3);
  l1.add(2);
  l1.add(1);
  l1.merge_sort();
  //std::cout << "Got to here?" << std::endl;
  LinkedList<int> l2;
  l2.add(1);
  l2.add(3);
  l2.add(2);
  l2.merge_sort();
  //std::cout << "Got to here?" << std::endl;
  LinkedList<int> l3;
  l3.add(2);
  l3.add(3);
  l3.add(1);
  l3.merge_sort(); 
  //std::cout << "Got to here?" << std::endl;
}

int main(int argc, char** argv)
{
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

