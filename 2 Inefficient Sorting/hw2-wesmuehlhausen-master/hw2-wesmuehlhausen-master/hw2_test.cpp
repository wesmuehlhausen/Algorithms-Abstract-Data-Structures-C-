
#include <iostream>
#include <string>
#include <gtest/gtest.h>
#include "array_list.h"
#include "linked_list.h"


using namespace std;


void print_list(ArrayList<int>& list)
{
  int val = -1;
  for (size_t i = 0; i < list.size(); ++i) {
    list.get(i, val);
    cout << val << " ";
  }
  cout << "\n";
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

// Test 10 (a) add to linked list after selection sort
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

// Test 10 (b) add to linked list after insertion sort
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

// Test 11 (a) linked list selection sort same number test
TEST(ExtraTests, SelectionSortSameNum)
{
  LinkedList<int> l1;
  int val1 = 0;
  l1.selection_sort();//test empty list
  l1.add(4);
  l1.add(4);
  l1.add(4);
  l1.add(4);
  l1.selection_sort();//test list of same numbers
  l1.get(0, val1);
  ASSERT_EQ(4, val1);
  bool var1 = l1.add(99, 4);//add to invalid index
  ASSERT_EQ(false, var1);
}

// Test 11 (b) linked list  insertion sort same number test
TEST(ExtraTests, InsertionSortSameNum)
{
  LinkedList<int> l1;
  int val1 = 0;
  l1.insertion_sort();//test empty list
  l1.add(4);
  l1.add(4);
  l1.add(4);
  l1.add(4);
  l1.insertion_sort();//test list of same numbers
  l1.get(0, val1);
  ASSERT_EQ(4, val1);
  bool var1 = l1.add(99, 4);//add to invalid index
  ASSERT_EQ(false, var1);
}


// Test 12 (LinkedList & ArrayList) Insertion Sort 2 element lists
TEST(ExtraTests, InsertionSortSize2)
{
  //Sort 3, 6
  LinkedList<int> l1;
  l1.add(3);
  l1.add(6);
  l1.insertion_sort();
  int v = 0;
  l1.get(0, v);
  ASSERT_EQ(3, v);
  l1.get(1, v);
  ASSERT_EQ(6, v);
  ArrayList<int> l2;
  l2.add(3);
  l2.add(6);
  l2.insertion_sort();
  l2.get(0, v);
  ASSERT_EQ(3, v);
  l2.get(1, v);
  ASSERT_EQ(6, v);
  
  //Sort 6, 3
  LinkedList<int> l3;
  l3.add(6);
  l3.add(3);
  l3.insertion_sort();
  l3.get(0, v);
  ASSERT_EQ(3, v);
  l3.get(1, v);
  ASSERT_EQ(6, v);
  ArrayList<int> l4;
  l4.add(6);
  l4.add(3);
  l4.insertion_sort();
  l4.get(0, v);
  ASSERT_EQ(3, v);
  l4.get(1, v);
  ASSERT_EQ(6, v);
}
// Test 13 (LinkedList & ArrayList) Selection Sort 2 element lists
TEST(ExtraTests, SelectionSortSize2)
{
  //Sort 3, 6
  LinkedList<int> l1;
  l1.add(3);
  l1.add(6);
  l1.selection_sort();
  int v = 0;
  l1.get(0, v);
  ASSERT_EQ(3, v);
  l1.get(1, v);
  ASSERT_EQ(6, v);
  ArrayList<int> l2;
  l2.add(3);
  l2.add(6);
  l2.selection_sort();
  l2.get(0, v);
  ASSERT_EQ(3, v);
  l2.get(1, v);
  ASSERT_EQ(6, v);
  
  //Sort 6, 3
  LinkedList<int> l3;
  l3.add(6);
  l3.add(3);
  l3.selection_sort();
  l3.get(0, v);
  ASSERT_EQ(3, v);
  ArrayList<int> l4;
  l4.add(6);
  l4.add(3);
  l4.selection_sort();
  l4.get(0, v);
  ASSERT_EQ(3, v);
  l4.get(1, v);
  ASSERT_EQ(6, v);
}

// Test 14 (LinkedList & ArrayList) Insertion Sort 3 element lists
TEST(ExtraTests, InsertionSortSize3)
{
  //Sort 3, 6, 9
  LinkedList<int> l1;
  l1.add(3);
  l1.add(6);
  l1.add(9);
  l1.insertion_sort();
  int v = 0;
  l1.get(0, v);
  ASSERT_EQ(3, v);
  l1.get(1, v);
  ASSERT_EQ(6, v);
  ArrayList<int> l2;
  l2.add(3);
  l2.add(6);
  l2.add(9);
  l2.insertion_sort();
  l2.get(0, v);
  ASSERT_EQ(3, v);
  l2.get(1, v);
  ASSERT_EQ(6, v);
  
  //Sort 6, 3, 9
  LinkedList<int> l3;
  l3.add(6);
  l3.add(3);
  l3.add(9);
  l3.insertion_sort();
  l3.get(0, v);
  ASSERT_EQ(3, v);
  l3.get(1, v);
  ASSERT_EQ(6, v);
  ArrayList<int> l4;
  l4.add(6);
  l4.add(3);
  l4.add(9);
  l4.insertion_sort();
  l4.get(0, v);
  ASSERT_EQ(3, v);
  l4.get(1, v);
  ASSERT_EQ(6, v);
}

// Test 15 (LinkedList & ArrayList) Selection Sort 3 element lists
TEST(ExtraTests, SelectionSortSize3)
{
  //Sort 3, 6, 9
  LinkedList<int> l1;
  l1.add(3);
  l1.add(6);
  l1.add(9);
  l1.selection_sort();
  int v = 0;
  l1.get(0, v);
  ASSERT_EQ(3, v);
  l1.get(1, v);
  ASSERT_EQ(6, v);
  ArrayList<int> l2;
  l2.add(3);
  l2.add(6);
  l2.add(9);
  l2.selection_sort();
  l2.get(0, v);
  ASSERT_EQ(3, v);
  l2.get(1, v);
  ASSERT_EQ(6, v);
  
  //Sort 6, 3, 9
  LinkedList<int> l3;
  l3.add(6);
  l3.add(3);
  l3.add(9);
  l3.selection_sort();
  l3.get(0, v);
  ASSERT_EQ(3, v);
  l3.get(1, v);
  ASSERT_EQ(6, v);
  ArrayList<int> l4;
  l4.add(6);
  l4.add(3);
  l4.add(9);
  l4.selection_sort();
  l4.get(0, v);
  ASSERT_EQ(3, v);
  l4.get(1, v);
  ASSERT_EQ(6, v);
}

int main(int argc, char** argv)
{
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

