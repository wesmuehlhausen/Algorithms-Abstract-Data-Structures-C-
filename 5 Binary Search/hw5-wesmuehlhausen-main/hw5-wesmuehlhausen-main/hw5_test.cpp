//----------------------------------------------------------------------
// Name: 
// File: hw5_test.cpp
// Date: Fall 2020
// Desc: Unit tests for ArrayList and BinSearch key-value collection
//       implementations
//----------------------------------------------------------------------


#include <iostream>
#include <string>
#include <gtest/gtest.h>
#include "array_list.h"
#include "array_list_collection.h"
#include "bin_search_collection.h"

using namespace std;


// Helper function to print out a key-value collection
template<typename K,typename V>
void print(const Collection<K,V>& kv_list)
{
  cout << "{";
  ArrayList<K> the_keys;
  kv_list.keys(the_keys);
  for (size_t i = 0; i < the_keys.size(); ++i) {
    K key;
    V val;
    the_keys.get(i, key);
    kv_list.find(key, val);
    cout << key << ": " << val;
    if (i < the_keys.size() - 1)
      cout << ", ";
  }
  cout << "}";
}

// Helper function to check membership in a list
template<typename T>
bool member(const T& member_val, const List<T>& list)
{
  for (int i = 0; i < list.size(); ++i) {
    T list_val;
    list.get(i, list_val);
    if (list_val == member_val)
      return true;
  }
  return false;
}


// Test 1 (a): Check add and size
TEST(BasicArrayCollectionTest, CorrectSize) {
  ArrayListCollection<string,int> c;
  ASSERT_EQ(0, c.size());
  c.add("b", 10);
  ASSERT_EQ(1, c.size());
  c.add("a", 20);
  ASSERT_EQ(2, c.size());
  c.add("c", 20);
  ASSERT_EQ(3, c.size());
}

// Test 1 (b): Check add and size
TEST(BasicBinSearchCollectionTest, CorrectSize) {
  BinSearchCollection<string,int> c;
  ASSERT_EQ(0, c.size());
  c.add("b", 10);
  ASSERT_EQ(1, c.size());
  c.add("a", 20);
  ASSERT_EQ(2, c.size());
  c.add("c", 20);
  ASSERT_EQ(3, c.size());
}

// Test 2(a): Test add and find
TEST(BasicArrayCollectionTest, SimpleFind) {
  ArrayListCollection<string,int> c;
  int v;
  ASSERT_EQ(false, c.find("b", v));
  c.add("b", 10);
  ASSERT_EQ(true, c.find("b", v));
  ASSERT_EQ(10, v);
  ASSERT_EQ(false, c.find("a", v));
  c.add("a", 20);
  ASSERT_EQ(true, c.find("a", v));
  ASSERT_EQ(20, v);
  ASSERT_EQ(false, c.find("c", v));
  c.add("c", 30);
  ASSERT_EQ(true, c.find("c", v));
  ASSERT_EQ(30, v);
}

// Test 2(b): Test add and find
TEST(BasicBinSearchCollectionTest, SimpleFind) {
  BinSearchCollection<string,int> c;
  int v;
  ASSERT_EQ(false, c.find("b", v));
  c.add("b", 10);
  ASSERT_EQ(true, c.find("b", v));
  ASSERT_EQ(false, c.find("4", v));

  c.add("a", 20);
  ASSERT_EQ(true, c.find("a", v));
  ASSERT_EQ(20, v);
  ASSERT_EQ(false, c.find("c", v));
  c.add("c", 30);
  ASSERT_EQ(true, c.find("c", v));
  ASSERT_EQ(30, v);
}

// Test 3(a): Test add, size, and remove
TEST(BasicArrayCollectionTest, SimpleRemove) {
  ArrayListCollection<string,int> c;
  c.add("b", 10);
  c.add("a", 20);
  c.add("c", 30);
  ASSERT_EQ(3, c.size());
  int v;
  // all three pairs in collection
  ASSERT_EQ(true, c.find("a", v));
  ASSERT_EQ(true, c.find("b", v));
  ASSERT_EQ(true, c.find("c", v));  
  // remove one
  c.remove("a");
  ASSERT_EQ(2, c.size());
  ASSERT_EQ(false, c.find("a", v));
  ASSERT_EQ(true, c.find("b", v));
  ASSERT_EQ(true, c.find("c", v));  
  // remove another
  c.remove("b");
  ASSERT_EQ(1, c.size());
  ASSERT_EQ(false, c.find("a", v));
  ASSERT_EQ(false, c.find("b", v));
  ASSERT_EQ(true, c.find("c", v));  
  // remove last one
  c.remove("c");
  ASSERT_EQ(0, c.size());
  ASSERT_EQ(false, c.find("a", v));
  ASSERT_EQ(false, c.find("b", v));
  ASSERT_EQ(false, c.find("c", v));  
}

// Test 3(b): Test add, size, and remove
TEST(BasicBinSearchCollectionTest, SimpleRemove) {
  BinSearchCollection<string,int> c;
  c.add("b", 10);
  c.print();
  c.add("a", 20);
  c.print();
  c.add("c", 30);
  c.print();
  ASSERT_EQ(3, c.size());
  int v;
  // all three pairs in collection
  ASSERT_EQ(true, c.find("a", v));
  ASSERT_EQ(true, c.find("b", v));
  ASSERT_EQ(true, c.find("c", v));  
  // remove one
  c.remove("a");
  ASSERT_EQ(2, c.size());
  ASSERT_EQ(false, c.find("a", v));
  ASSERT_EQ(true, c.find("b", v));
  ASSERT_EQ(true, c.find("c", v));  
  // remove another
  c.remove("b");
  ASSERT_EQ(1, c.size());
  ASSERT_EQ(false, c.find("a", v));
  ASSERT_EQ(false, c.find("b", v));
  ASSERT_EQ(true, c.find("c", v));  
  // remove last one
  c.remove("c");
  ASSERT_EQ(0, c.size());
  ASSERT_EQ(false, c.find("a", v));
  ASSERT_EQ(false, c.find("b", v));
  ASSERT_EQ(false, c.find("c", v));  
}

// Test 4(a): Test add, size, and find range
TEST(BasicArrayCollectionTest, SimpleRange) {
  ArrayListCollection<string,int> c;
  c.add("e", 50);
  c.add("c", 30);
  c.add("d", 40);
  c.add("f", 60);
  c.add("b", 20);
  // search for proper sublist of keys
  ArrayList<string> s1;
  c.find("c", "e", s1);
  ASSERT_EQ(3, s1.size());
  ASSERT_EQ(true, member(string("c"), s1));
  ASSERT_EQ(true, member(string("d"), s1));
  ASSERT_EQ(true, member(string("e"), s1));
  // search for overlapping prefix
  ArrayList<string> s2;
  c.find("a", "c", s2);
  ASSERT_EQ(2, s2.size());
  ASSERT_EQ(true, member(string("b"), s2));
  ASSERT_EQ(true, member(string("c"), s2));
  // search for overlapping suffix
  ArrayList<string> s3;
  c.find("e", "g", s3);
  ASSERT_EQ(2, s3.size());
  ASSERT_EQ(true, member(string("e"), s3));
  ASSERT_EQ(true, member(string("f"), s3));
  // search for empty sublist of keys
  ArrayList<string> s4;
  c.find("f", "b", s4);
  ASSERT_EQ(0, s4.size());
}

// Test 4(a): Test add, size, and find range
TEST(BasicBinSearchCollectionTest, SimpleRange) {
  BinSearchCollection<string,int> c;
  c.add("e", 50);
  c.add("c", 30);
  c.add("d", 40);
  c.add("f", 60);
  c.add("b", 20);
  // search for proper sublist of keys
  ArrayList<string> s1;
  c.find("c", "e", s1);
  ASSERT_EQ(3, s1.size());
  ASSERT_EQ(true, member(string("c"), s1));
  ASSERT_EQ(true, member(string("d"), s1));
  ASSERT_EQ(true, member(string("e"), s1));
  // search for overlapping prefix
  ArrayList<string> s2;
  c.find("a", "c", s2);
  ASSERT_EQ(2, s2.size());
  ASSERT_EQ(true, member(string("b"), s2));
  ASSERT_EQ(true, member(string("c"), s2));
  // search for overlapping suffix
  ArrayList<string> s3;
  c.find("e", "g", s3);
  ASSERT_EQ(2, s3.size());
  ASSERT_EQ(true, member(string("e"), s3));
  ASSERT_EQ(true, member(string("f"), s3));
  // search for empty sublist of keys
  ArrayList<string> s4;
  c.find("f", "b", s4);
  ASSERT_EQ(0, s4.size());
}

// Test 5(a): Test add and sort
TEST(BasicArrayCollectionTest, SimpleSort) {
  ArrayListCollection<string,int> c;
  c.add("a", 10);
  c.add("e", 50);
  c.add("c", 30);
  c.add("b", 20);
  c.add("d", 40);
  ArrayList<string> sorted_keys;
  c.sort(sorted_keys);
  ASSERT_EQ(5, sorted_keys.size());
  // check if in sorted order
  for (size_t i = 1; i < sorted_keys.size(); ++i) {
    string k1;
    string k2;
    ASSERT_EQ(true, sorted_keys.get(i-1, k1));
    ASSERT_EQ(true, sorted_keys.get(i, k2));
    ASSERT_LT(k1, k2);
  }
}

// Test 5(b): Test add and sort
TEST(BasicBinSearchCollectionTest, SimpleSort) {
  BinSearchCollection<string,int> c;
  c.add("a", 10);
  c.add("e", 50);
  c.add("c", 30);
  c.add("b", 20);
  c.add("d", 40);
  ArrayList<string> sorted_keys;
  c.sort(sorted_keys);
  ASSERT_EQ(5, sorted_keys.size());
  // check if in sorted order
  for (size_t i = 1; i < sorted_keys.size(); ++i) {
    string k1;
    string k2;
    ASSERT_EQ(true, sorted_keys.get(i-1, k1));
    ASSERT_EQ(true, sorted_keys.get(i, k2));
    ASSERT_LT(k1, k2);
  }
}

////////////////////////////////////////////////////////////////////////
//Test 1: check to see if the binary search will add b to the right spot
//if done correctly it will be ab not ba
TEST(BasicBinSearchCollectionTest, InsertBeginningCorrectly) {
  BinSearchCollection<string,int> c;
  int v;
  c.add("a", 10);
  c.add("b", 20);
  ASSERT_EQ(true, c.find("a", v));
  ASSERT_EQ(10, v);
}
//ArrayListCollection Version
TEST(BasicArrayCollectionTest, InsertBeginningCorrectly) {
  ArrayListCollection<string,int> c;
  int v;
  c.add("a", 10);
  c.add("b", 20);
  ASSERT_EQ(true, c.find("a", v));
  ASSERT_EQ(10, v);
}
////////////////////////////////////////////////////////////////////////
//Test 2: Large add and large sort in reverse order. mostly made to test
//if the size function works for large amounts of adding.
TEST(BasicBinSearchCollectionTest, LargeReverseOrderAdding) {
  BinSearchCollection<string,int> c;
  int v;
  for(int i = 100; i > 0; --i)
  {
    if(i > 66)
      c.add("c", 10);
    else if(i > 33)
      c.add("b", 15);
    else
      c.add("a", 20);
  }
  ASSERT_EQ(100, c.size());
}
//For A.L.C
TEST(BasicArrayCollectionTest, LargeReverseOrderAdding) {
  ArrayListCollection<string,int> c;
  int v;
  for(int i = 100; i > 0; --i)
  {
    if(i > 66)
      c.add("c", 10);
    else if(i > 33)
      c.add("b", 15);
    else
      c.add("a", 20);
  }
  ASSERT_EQ(100, c.size());
}

////////////////////////////////////////////////////////////////////////
//Test 3: Tests the case where the list is size zero and you try to remove 
//an element
TEST(BasicBinSearchCollectionTest, RemoveSizeZero) {
  BinSearchCollection<string,int> c;
  int v;
  ASSERT_EQ(false, c.find("a", v));
  ASSERT_EQ(0, c.size());
}
//For A.L.C
TEST(BasicArrayCollectionTest, RemoveSizeZero) {
  ArrayListCollection<string,int> c;
  int v;
  ASSERT_EQ(false, c.find("a", v));
  ASSERT_EQ(0, c.size());
}

////////////////////////////////////////////////////////////////////////
//Test 4: This tests that given two of the same keys but with different values, you can find the 
//correct key if they have two different values
TEST(BasicBinSearchCollectionTest, SameKeyDifferentValue) {
  BinSearchCollection<string,int> c;
  int v;
  c.add("a", 10);
  c.add("b", 10);
  c.add("c", 15);
  c.add("c", 20);
  
  //20 should come first even though added second
  ASSERT_EQ(true, c.find("c", v));
  ASSERT_EQ(20, v);
}
//For A.L.C
TEST(BasicArrayCollectionTest, SameKeyDifferentValue) {
  ArrayListCollection<string,int> c;
    int v;
  c.add("a", 10);
  c.add("b", 10);
  c.add("c", 15);
  c.add("c", 20);
  
  //15 should come first unlike binsearch
  ASSERT_EQ(true, c.find("c", v));
  ASSERT_EQ(15, v);
}

////////////////////////////////////////////////////////////////////////
//Test 5: This tests the sorting at a medium difficulty level
TEST(BasicBinSearchCollectionTest, MediumSimpleSort) {
  BinSearchCollection<string,int> c;
  c.add("a", 10);
  c.add("f", 60);
  c.add("e", 50);
  c.add("g", 70);
  c.add("c", 30);
  c.add("h", 80);
  c.add("b", 20);
  c.add("i", 90);
  c.add("d", 40);
  ArrayList<string> sorted_keys;
  c.sort(sorted_keys);
  ASSERT_EQ(9, sorted_keys.size());
  // check if in sorted order
  for (size_t i = 1; i < sorted_keys.size(); ++i) {
    string k1;
    string k2;
    ASSERT_EQ(true, sorted_keys.get(i-1, k1));
    ASSERT_EQ(true, sorted_keys.get(i, k2));
    ASSERT_LT(k1, k2);
  }
}
//For A.L.C
TEST(BasicArrayCollectionTest, MediumSimpleSort) {
  ArrayListCollection<string,int> c;
  c.add("a", 10);
  c.add("f", 60);
  c.add("e", 50);
  c.add("g", 70);
  c.add("c", 30);
  c.add("h", 80);
  c.add("b", 20);
  c.add("i", 90);
  c.add("d", 40);
  ArrayList<string> sorted_keys;
  c.sort(sorted_keys);
  ASSERT_EQ(9, sorted_keys.size());
  // check if in sorted order
  for (size_t i = 1; i < sorted_keys.size(); ++i) {
    string k1;
    string k2;
    ASSERT_EQ(true, sorted_keys.get(i-1, k1));
    ASSERT_EQ(true, sorted_keys.get(i, k2));
    ASSERT_LT(k1, k2);
  }
}

////////////////////////////////////////////////////////////////////////
//Test 6: Try to sort an empty list 
//What im testing here is whether there is an error here or not. 
TEST(BasicBinSearchCollectionTest, SortNothing) {
  BinSearchCollection<string,int> c;
  ArrayList<string> sorted_keys;
  c.sort(sorted_keys);
  ASSERT_EQ(0, sorted_keys.size());
}
//For A.L.C
TEST(BasicArrayCollectionTest, SortNothing) {
  ArrayListCollection<string,int> c;
   ArrayList<string> sorted_keys;
  c.sort(sorted_keys);
  ASSERT_EQ(0, sorted_keys.size());
}

////////////////////////////////////////////////////////////////////////
//Test 7: Try to sort a list that is  length 1 
//What im testing here is whether there is an error here or not. 
//Should not change the list 
TEST(BasicBinSearchCollectionTest, SortSingleVariable) {
  BinSearchCollection<string,int> c;
  ArrayList<string> sorted_keys;
  c.add("a", 10);
  c.sort(sorted_keys);
  ASSERT_EQ(1, sorted_keys.size());
}
//For A.L.C
TEST(BasicArrayCollectionTest, SortSingleVariable) {
  ArrayListCollection<string,int> c;
  ArrayList<string> sorted_keys;
  c.add("a", 10);
  c.sort(sorted_keys);
  ASSERT_EQ(1, sorted_keys.size());
}


////////////////////////////////////////////////////////////////////////
//Test 8: This tests the sorting at a reverse order from 100->1
TEST(BasicBinSearchCollectionTest, LargeReverseSort) {
  BinSearchCollection<int,int> c;
  for(int i = 100; i > 100; --i)
    c.add(i, i);
  
  ArrayList<int> sorted_keys;
  c.sort(sorted_keys);
  
  // check if in sorted order
  for (size_t i = 1; i < sorted_keys.size(); ++i) {
    int k1;
    int k2;
    ASSERT_EQ(true, sorted_keys.get(i-1, k1));
    ASSERT_EQ(true, sorted_keys.get(i, k2));
    ASSERT_LT(k1, k2);
  }
}
//For A.L.C
TEST(BasicArrayCollectionTest, LargeReverseSort) {
  ArrayListCollection<int,int> c;
  for(int i = 100; i > 100; --i)
    c.add(i, i);
  
  ArrayList<int> sorted_keys;
  c.sort(sorted_keys);
  
  // check if in sorted order
  for (size_t i = 1; i < sorted_keys.size(); ++i) {
    int k1;
    int k2;
    ASSERT_EQ(true, sorted_keys.get(i-1, k1));
    ASSERT_EQ(true, sorted_keys.get(i, k2));
    ASSERT_LT(k1, k2);
  }
}


////////////////////////////////////////////////////////////////////////
//Test 9: This tests the sorting at a constant value
TEST(BasicBinSearchCollectionTest, AllTheSameSort) {
  BinSearchCollection<int,int> c;
  for(int i = 100; i > 0; --i)
    c.add(100, i);
  
  ArrayList<int> sorted_keys;
  c.sort(sorted_keys);
  ASSERT_EQ(100, sorted_keys.size());
  // check if in sorted order
  for (size_t i = 1; i < sorted_keys.size(); ++i) {
    int k1;
    int k2;
    ASSERT_EQ(true, sorted_keys.get(i-1, k1));
    ASSERT_EQ(true, sorted_keys.get(i, k2));
    ASSERT_EQ(k1, k2);
  }
}
//For A.L.C
TEST(BasicArrayCollectionTest, AllTheSameSort) {
  ArrayListCollection<int,int> c;
  for(int i = 100; i > 0; --i)
    c.add(100, i);
  
  ArrayList<int> sorted_keys;
  c.sort(sorted_keys);
  ASSERT_EQ(100, sorted_keys.size());
  // check if in sorted order
  for (size_t i = 1; i < sorted_keys.size(); ++i) {
    int k1;
    int k2;
    ASSERT_EQ(true, sorted_keys.get(i-1, k1));
    ASSERT_EQ(true, sorted_keys.get(i, k2));
    ASSERT_EQ(k1, k2);
  }
}


////////////////////////////////////////////////////////////////////////
//Test 10: This tests the sorting at a reverse order from 1000->1
TEST(BasicBinSearchCollectionTest, VeryLargeReverseSort) {
  BinSearchCollection<int,int> c;
  for(int i = 1000; i > 0; --i)
    c.add(i, i);
  
  ArrayList<int> sorted_keys;
  c.sort(sorted_keys);
  ASSERT_EQ(1000, sorted_keys.size());
  // check if in sorted order
  for (size_t i = 1; i < sorted_keys.size(); ++i) {
    int k1;
    int k2;
    ASSERT_EQ(true, sorted_keys.get(i-1, k1));
    ASSERT_EQ(true, sorted_keys.get(i, k2));
    ASSERT_LT(k1, k2);
  }
}
//For A.L.C
TEST(BasicArrayCollectionTest, VeryLargeReverseSort) {
  ArrayListCollection<int,int> c;
  for(int i = 1000; i > 0; --i)
    c.add(i, i);
  
  ArrayList<int> sorted_keys;
  c.sort(sorted_keys);
  ASSERT_EQ(1000, sorted_keys.size());
  // check if in sorted order
  for (size_t i = 1; i < sorted_keys.size(); ++i) {
    int k1;
    int k2;
    ASSERT_EQ(true, sorted_keys.get(i-1, k1));
    ASSERT_EQ(true, sorted_keys.get(i, k2));
    ASSERT_LT(k1, k2);
  }
}



int main(int argc, char** argv)
{
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
