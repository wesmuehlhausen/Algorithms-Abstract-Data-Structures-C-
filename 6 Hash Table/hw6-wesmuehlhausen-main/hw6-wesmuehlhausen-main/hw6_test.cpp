//----------------------------------------------------------------------
// Name: Wesley Muehlhausen
// File: hw6_test.cpp
// Date: Fall 2020
// Desc: Unit tests for HashTable key-value collection implementation
//----------------------------------------------------------------------


#include <iostream>
#include <string>
#include <gtest/gtest.h>
#include "array_list.h"
#include "hash_table_collection.h"

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


// Test 1: Check add and size
TEST(BasicHashTableCollectionTest, CorrectSize) {
  HashTableCollection<string,int> c;
  ASSERT_EQ(0, c.size());
  c.add("b", 10);
  ASSERT_EQ(1, c.size());
  c.add("a", 20);
  ASSERT_EQ(2, c.size());
  c.add("c", 20);
  ASSERT_EQ(3, c.size());
}


// Test 2: Test add and find
TEST(BasicHashTableCollectionTest, SimpleFind) {
  HashTableCollection<string,int> c;
  int v;
  ASSERT_EQ(false, c.find("b", v));
  c.add("b", 10);
  ASSERT_EQ(true, c.find("b", v));
  ASSERT_EQ(10, v);
  //cout << "YOOLO1" << endl;//////////////////////////////////
  ASSERT_EQ(false, c.find("a", v));
  c.add("a", 20);
  ASSERT_EQ(true, c.find("a", v));
  ASSERT_EQ(20, v);
  //cout << "YOOLO2" << endl;//////////////////////////////////
  ASSERT_EQ(false, c.find("c", v));
  //cout << "YOOLO2.5" << endl;/////////////////////////////////
  c.add("c", 30);
  ASSERT_EQ(true, c.find("c", v));
  //cout << "YOOLO2.75" << endl;/////////////////////////////////
  ASSERT_EQ(30, v);
  //cout << "YOOLO3" << endl;//////////////////////////////////
}

// Test 3: Test add, size, and remove
TEST(BasicHashTableCollectionTest, SimpleRemove) {
  HashTableCollection<string,int> c;
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

// Test 4: Test add, size, and find range
TEST(BasicHashTableCollectionTest, SimpleRange) {
  HashTableCollection<string,int> c;
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



// Test 5: Test add and sort
TEST(BasicHashTableCollectionTest, SimpleSort) {
  HashTableCollection<string,int> c;
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


// Test 6: Test add and resize
TEST(BasicHashTableCollectionTest, ResizeTest) {
  size_t len = 49;
  HashTableCollection<int,int> c;
  for (int i = 0; i < len; ++i) {
    c.add(i, i+10);
  }
  ASSERT_EQ(len, c.size());
  for (int i = 0; i < len; ++i) {
    int val = 0;
    ASSERT_EQ(true, c.find(i, val));
    ASSERT_EQ(i+10, val);
  }
}

// Test 7: copy and assignment operator
TEST(BasicHashTableCollectionTest, CopyAndAssignment) {
  //cout << " 1 " << endl;
  HashTableCollection<string,int> c1;
  c1.add("b", 20);
  c1.add("a", 10);
  c1.add("c", 30);
  //cout << " 2 " << endl;
  HashTableCollection<string,int> c2(c1);
  //cout << " 3 " << endl;
  ASSERT_EQ(c1.size(), c2.size());
  //cout << " 4 " << endl;
  c2.add("e", 50);
  ASSERT_NE(c1.size(), c2.size());
  c1 = c2;
  ASSERT_EQ(c1.size(), c2.size());
  c1 = c1;
  ASSERT_EQ(c1.size(), c2.size());
  HashTableCollection<string,int> c3;
  c3.add("d", 40);
  c3 = c2 = c1;
  ASSERT_EQ(c3.size(), c2.size());
  ASSERT_EQ(c2.size(), c1.size());
  string keys[4] = {"a", "b", "c", "e"};
  for (int i = 0; i < c1.size(); ++i) {
    int v1, v2, v3;
    ASSERT_EQ(true, c1.find(keys[i], v1));
    ASSERT_EQ(true, c2.find(keys[i], v2));
    ASSERT_EQ(true, c3.find(keys[i], v3));
    ASSERT_EQ(v1, v2);
    ASSERT_EQ(v2, v3);
  }
}


//Test 1: Primarily meant for removing. This tests the 
// removing. This tests many remove cases 
TEST(HashTestByWes, RemoveMultiKeys) {
  HashTableCollection<int,int> c1;
  //ADD
  for(int i = 1; i <= 25; ++i)//Add 1-25 to tree
  {
  	c1.add(i, i);
  	ASSERT_EQ(i, c1.size());
  }
  //REMOVE
  c1.remove(16);//Remove 17
  c1.remove(14);//Remove 14
  c1.remove(13);//Remove 13
  c1.remove(8);//Remove 8
  c1.remove(25);//remove 25
  ASSERT_EQ(20, c1.size());
  ASSERT_EQ(1, c1.min_chain_length());//should be min and max size 1
  ASSERT_EQ(1, c1.max_chain_length());
  int a;
  ASSERT_EQ(false, c1.find(16, a));//Find values that were removed
  ASSERT_EQ(false, c1.find(13, a));
}

//Test 2: Tests load factor management (Wes)/ Adds keys and tests load factor,
//then removes each node and the average chain length should always be decreasing: 
TEST(HashTestByWes, TestLoadFactor) {
  HashTableCollection<int,int> c1;
  //ADD
  for(int i = 1; i <= 250; ++i)//Add 1-250
  {
  	c1.add(i, i);
  	ASSERT_EQ(i, c1.size());
	//make sure the average chain length never is greater than 1
  	ASSERT_LT(c1.avg_chain_length(), 1.1);//not 0.75 because doens't count size 0
  }
  //REMOVE
  double current_average;
  double next_average;
  for(int i = 1; i <= 250; ++i)//Add 1-250
  {
    current_average = c1.avg_chain_length();
  	c1.remove(i);
  	next_average = c1.avg_chain_length();
	//make sure the average chain length never is greater than 1
  	ASSERT_LT(next_average, current_average);
  }
  ASSERT_EQ(0, c1.size());
  
}
//Test 3: Tests Constructor and Assignment Operator (Wes)
TEST(HashTestByWes, FurtherAssignmentAndCopy) {
  HashTableCollection<int,int> c1;
  //ADD
  for(int i = 1; i <= 25; ++i)//Add 1-25
  {
  	c1.add(i, i);
  	ASSERT_EQ(i, c1.size());
  }
  HashTableCollection<int,int> c2;
  for(int i = 25; i >= 1; --i)//Add 25-1 to table
  	c2.add(i, i);
  ASSERT_EQ(25, c1.size());//Table 1 should be size 25
  ASSERT_EQ(25, c2.size());//Table 2 should be size 25
  //ASSIGNMENT OP AND COPY CONSTRUCT
  HashTableCollection<int,int> c3;//create a new table
  c3 = c1;//copy using assig opp
  HashTableCollection<int,int> c4(c2);//copy const
  ASSERT_EQ(25, c3.size());//Table 3 should be size 25
  ASSERT_EQ(25, c4.size());//Table 4 should be size 25
  HashTableCollection<int,int> c5(c3);//construct 5 from 3
  c5.remove(5);//alter 5
  c5.remove(10);
  HashTableCollection<int,int> c6;//construct 6
  c1 = c2 = c3 = c6 = c5;//assignment operator
  ASSERT_EQ(23, c1.size());//Table 3 should be size 25
  ASSERT_EQ(25, c4.size());//Table 4 should be size 25
}

//Test 4: Large adding and then sorting scenarios
TEST(HashTestByWes, LargeAddingSorting) {
  HashTableCollection<int,int> c1;
  for(int i = 0; i < 100; ++i)//from 0-100
  {
  	for(int j = 1000; j > 900; --j)//add 1000-900 - i value
  	{
  		c1.add(j-i, j-i);
  	}
  }
  ArrayList<int> sorted_keys;
  c1.sort(sorted_keys);
  int v;
  ASSERT_EQ(true, c1.find(1000, v));
  ASSERT_EQ(true, c1.find(802, v));
  ASSERT_EQ(false, c1.find(801, v));
  ASSERT_EQ(10000, c1.size());//Table size 10000
}


//Test 5: Tests all of: add, remove, find, range, sort, copy/assgn
TEST(HashTestByWes, TestAll) {
  //Test ADD
  HashTableCollection<int,int> c1;
  for(int i = 100; i > 0; --i)//from 100-0
  { 	
  		c1.add(i, i);
  }
  //Test Copy and Assignment
  HashTableCollection<int,int> c2(c1);
  HashTableCollection<int,int> c;
  c = c2;
  //Test Sort and find
  ArrayList<int> sorted_keys;
  c1.sort(sorted_keys);
  int v;
  ASSERT_EQ(true, c1.find(100, v));
  ASSERT_EQ(true, c1.find(50, v));
  ASSERT_EQ(false, c1.find(200, v));
  ASSERT_EQ(100, c1.size());//Table size 100
  //Test Range
  ArrayList<int> range_keys;
  c2.find(25, 75, range_keys);
  ASSERT_EQ(range_keys.size(), 51);//size 50
  //Test Remove
  c.remove(100);
  c.remove(90);
  c.remove(5);
  c.remove(250);//should not remove anything
  ASSERT_EQ(false, c.find(100, v));
}

int main(int argc, char** argv)
{
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

