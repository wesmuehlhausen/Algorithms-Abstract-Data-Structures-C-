//----------------------------------------------------------------------
// Name: 
// File: hw4_test.cpp
// Date: Fall 2020
// Desc: Unit tests for ArrayList and LinkedList key-value collection
//       implementations
//----------------------------------------------------------------------


#include <iostream>
#include <string>
#include <gtest/gtest.h>
#include "array_list.h"
#include "array_list_collection.h"
#include "linked_list_collection.h"

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
TEST(BasicLinkedCollectionTest, CorrectSize) {
  LinkedListCollection<string,int> c;
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
TEST(BasicLinkedCollectionTest, SimpleFind) {
  LinkedListCollection<string,int> c;
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
TEST(BasicLinkedCollectionTest, SimpleRemove) {
  LinkedListCollection<string,int> c;
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
TEST(BasicLinkedCollectionTest, SimpleRange) {
  LinkedListCollection<string,int> c;
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
TEST(BasicLinkedCollectionTest, SimpleSort) {
  LinkedListCollection<string,int> c;
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

//Test 1: Basic Sorting for the ArrayList Collection
TEST(WesTests, BasicArrayListCollectionSort)
{
  ArrayListCollection<int,int> l1;
  for (int i = 10; i > 0; --i)
    l1.add(i, i);
  ASSERT_EQ(10, l1.size());
  ArrayList<int> sorted_keys;
  l1.sort(sorted_keys);
  for (int i = 0; i < 9; ++i) {
    int val1 = 0;
    int val2 = 0;
    l1.find(i, val1);
    l1.find(i+1, val2);
    ASSERT_LT(val1, val2);
  }
}

//Test 2: Basic Sorting for the LinkedList Collection
TEST(WesTests, BasicLinkedListCollectionSort)
{
  LinkedListCollection<int,int> l1;
  for (int i = 10; i > 0; --i)
    l1.add(i, i);
  ASSERT_EQ(10, l1.size());
  ArrayList<int> sorted_keys;
  l1.sort(sorted_keys);
  for (int i = 0; i < 9; ++i) {
    int val1 = 0;
    int val2 = 0;
    l1.find(i, val1);
    l1.find(i+1, val2);
    ASSERT_LT(val1, val2);
  }
}

//Test 3: Sort Size 2 ArrayList Collection
TEST(WesTests, ArrayListCollectionSortSize2)
{
ArrayListCollection<int,int> l1;//
    ArrayList<int> sorted_keys;
    int val1 = 0;
    int val2 = 0;
    //Sort 1, 2
    l1.add(1, 1);//
    l1.add(2, 2);//
  	ASSERT_EQ(2, l1.size());
  	l1.sort(sorted_keys);
    l1.find(1, val1);//
    l1.find(2, val2);//
    ASSERT_LT(val1, val2);//
    l1.remove(1);//
    l1.remove(2);//
    ASSERT_EQ(0, l1.size());
    //Sort 1, 1
    l1.add(1, 1);//
    l1.add(1, 1);//
  	ASSERT_EQ(2, l1.size());
  	l1.sort(sorted_keys);
    l1.find(1, val1);//
    l1.find(1, val2);//
    ASSERT_EQ(val1, val2);//
    l1.remove(1);//
    l1.remove(1);//
    ASSERT_EQ(0, l1.size());
    //Sort 2, 1
    l1.add(2, 2);//
    l1.add(1, 1);//
  	ASSERT_EQ(2, l1.size());
  	l1.sort(sorted_keys);
    l1.find(1, val1);//
    l1.find(2, val2);//
    ASSERT_LT(val1, val2);//
    l1.remove(1);//
    l1.remove(2);//
    ASSERT_EQ(0, l1.size());
}

//Test 4: Sort Size 2 for the LinkedList Collection
TEST(WesTests, LinkedListCollectionSortSize2)
{
  LinkedListCollection<int,int> l1;//
    ArrayList<int> sorted_keys;
    int val1 = 0;
    int val2 = 0;
    //Sort 1, 2
    l1.add(1, 1);//
    l1.add(2, 2);//
  	ASSERT_EQ(2, l1.size());
  	l1.sort(sorted_keys);
    l1.find(1, val1);//
    l1.find(2, val2);//
    ASSERT_LT(val1, val2);//
    l1.remove(1);//
    l1.remove(2);//
    ASSERT_EQ(0, l1.size());
    //Sort 1, 1
    l1.add(1, 1);//
    l1.add(1, 1);//
  	ASSERT_EQ(2, l1.size());
  	l1.sort(sorted_keys);
    l1.find(1, val1);//
    l1.find(1, val2);//
    ASSERT_EQ(val1, val2);//
    l1.remove(1);//
    l1.remove(1);//
    ASSERT_EQ(0, l1.size());
    //Sort 2, 1
    l1.add(2, 2);//
    l1.add(1, 1);//
  	ASSERT_EQ(2, l1.size());
  	l1.sort(sorted_keys);
    l1.find(1, val1);//
    l1.find(2, val2);//
    ASSERT_LT(val1, val2);//
    l1.remove(1);//
    l1.remove(2);//
    ASSERT_EQ(0, l1.size());
}


//Test 5: Sort Size 3 ArrayList Collection
TEST(WesTests, ArrayListCollectionSortSize3)
{
ArrayListCollection<int,int> l1;//
    ArrayList<int> sorted_keys;
    int val1 = 0;
    int val2 = 0;
    int val3 = 0;
    //Sort 3, 2, 1
    l1.add(3, 3);//
    l1.add(2, 2);//
    l1.add(1, 1);//
  	ASSERT_EQ(3, l1.size());
  	l1.sort(sorted_keys);
    l1.find(1, val1);//
    l1.find(2, val2);//
    l1.find(3, val3);//
    ASSERT_LT(val1, val2);//
    ASSERT_LT(val2, val3);//
    l1.remove(1);//
    l1.remove(2);//
    l1.remove(3);//
    ASSERT_EQ(0, l1.size());
    //Sort 1, 3, 2
    l1.add(1, 1);//
    l1.add(3, 3);//
    l1.add(2, 2);//
  	ASSERT_EQ(3, l1.size());
  	l1.sort(sorted_keys);
    l1.find(1, val1);//
    l1.find(2, val2);//
    l1.find(3, val3);//
    ASSERT_LT(val1, val2);//
    ASSERT_LT(val2, val3);//
    l1.remove(1);//
    l1.remove(2);//
    l1.remove(3);//
    ASSERT_EQ(0, l1.size());   
    //Sort 3, 1, 2
    l1.add(3, 3);//
    l1.add(1, 1);//
    l1.add(2, 2);//
  	ASSERT_EQ(3, l1.size());
  	l1.sort(sorted_keys);
    l1.find(1, val1);//
    l1.find(2, val2);//
    l1.find(3, val3);//
    ASSERT_LT(val1, val2);//
    ASSERT_LT(val2, val3);//
    l1.remove(1);//
    l1.remove(2);//
    l1.remove(3);//
    ASSERT_EQ(0, l1.size()); 
}

//Test 6: Sort Size 3 LinkedList Collection
TEST(WesTests, LinkedListCollectionSortSize3)
{
LinkedListCollection<int,int> l1;//
    ArrayList<int> sorted_keys;
    int val1 = 0;
    int val2 = 0;
    int val3 = 0;
    //Sort 3, 2, 1
    l1.add(3, 3);//
    l1.add(2, 2);//
    l1.add(1, 1);//
  	ASSERT_EQ(3, l1.size());
  	l1.sort(sorted_keys);
    l1.find(1, val1);//
    l1.find(2, val2);//
    l1.find(3, val3);//
    ASSERT_LT(val1, val2);//
    ASSERT_LT(val2, val3);//
    l1.remove(1);//
    l1.remove(2);//
    l1.remove(3);//
    ASSERT_EQ(0, l1.size());
    //Sort 1, 3, 2
    l1.add(1, 1);//
    l1.add(3, 3);//
    l1.add(2, 2);//
  	ASSERT_EQ(3, l1.size());
  	l1.sort(sorted_keys);
    l1.find(1, val1);//
    l1.find(2, val2);//
    l1.find(3, val3);//
    ASSERT_LT(val1, val2);//
    ASSERT_LT(val2, val3);//
    l1.remove(1);//
    l1.remove(2);//
    l1.remove(3);//
    ASSERT_EQ(0, l1.size());   
    //Sort 3, 1, 2
    l1.add(3, 3);//
    l1.add(1, 1);//
    l1.add(2, 2);//
  	ASSERT_EQ(3, l1.size());
  	l1.sort(sorted_keys);
    l1.find(1, val1);//
    l1.find(2, val2);//
    l1.find(3, val3);//
    ASSERT_LT(val1, val2);//
    ASSERT_LT(val2, val3);//
    l1.remove(1);//
    l1.remove(2);//
    l1.remove(3);//
    ASSERT_EQ(0, l1.size()); 
}

//Test 7: Adding and removing from different parts in the list
TEST(WesTests, ArrayListCollectionMultipleRemoves)
{
ArrayListCollection<int,int> l1;//
    ArrayList<int> sorted_keys;
    for(int i = 0; i < 100; ++i) //make a list of keys from 0 - 99
    	l1.add(i, i);
    ASSERT_EQ(100, l1.size());
    //remove from FRONT
    l1.remove(0); 
    l1.remove(1); 
    l1.remove(2); 
    //remove from MIDDLE
    l1.remove(49); 
    l1.remove(50); 
    l1.remove(51); 
    //remove from END
    l1.remove(97); 
    l1.remove(98); 
    l1.remove(99);
    ASSERT_EQ(91, l1.size());
}

//Test 8: Adding and removing from different parts in the list
TEST(WesTests, LinkedListCollectionMultipleRemoves)
{
LinkedListCollection<int,int> l1;//
    ArrayList<int> sorted_keys;
    for(int i = 0; i < 100; ++i) //make a list of keys from 0 - 99
    	l1.add(i, i);
    ASSERT_EQ(100, l1.size());
    //remove from FRONT
    l1.remove(0); 
    l1.remove(1); 
    l1.remove(2); 
    //remove from MIDDLE
    l1.remove(49); 
    l1.remove(50); 
    l1.remove(51); 
    //remove from END
    l1.remove(97); 
    l1.remove(98); 
    l1.remove(99);
    ASSERT_EQ(91, l1.size());
}


//Test 9: Finding different Ranges and values for linked list
TEST(WesTests, LinkedListCollectionMultipleRanges)
{
LinkedListCollection<int,int> l1;//
    for(int i = 0; i < 100; ++i) //make a list of keys from 0 - 99
    	l1.add(i, i);
    ArrayList<int> s1;
    ArrayList<int> s2;
    ArrayList<int> s3;
    ASSERT_EQ(100, l1.size());
    //Find range of all keys
    l1.find(0, 99, s1); 
    ASSERT_EQ(100, s1.size());
    //Find range of all keys
    l1.find(10, 20, s2); 
    ASSERT_EQ(11, s2.size());
    //Find range of all keys
    l1.find(80, 90, s3); 
    ASSERT_EQ(11, s3.size());    
}

//Test 10: make list from 1-200. Remove all evens, then odds
TEST(WesTests, WeirdRemovingPattern)
{
LinkedListCollection<int,int> l1;
LinkedListCollection<int,int> a1;
    for(int i = 0; i < 100; ++i) //make a list of keys from 0 - 99
    {
    	l1.add(i, i);
    	a1.add(i, i);	
    }
    for(int i = 100; i < 200; ++i) //add keys from 0 - 99
    {
    	l1.add(i, i);
    	a1.add(i, i);	
    }
    for(int i = 0; i < 200; i+=2)//remove evens
    {
    	l1.remove(i);
    	a1.remove(i);
    }
    for(int i = 1; i < 200; i+=2)//remove odds
    {
    	l1.remove(i);
    	a1.remove(i);
    }      
}


int main(int argc, char** argv)
{
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

