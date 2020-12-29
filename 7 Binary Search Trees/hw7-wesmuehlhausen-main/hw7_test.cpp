//----------------------------------------------------------------------
// Name: Wesley Muehlhausen
// File: hw7_test.cpp
// Date: Fall 2020
// Desc: Unit tests for BST key-value collection implementation
//----------------------------------------------------------------------


#include <iostream>
#include <string>
#include <gtest/gtest.h>
#include "array_list.h"
#include "bst_collection.h"


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
TEST(BSTCollectionTest, CorrectSize) {
  BSTCollection<string,int> c;
  ASSERT_EQ(0, c.size());
  c.add("b", 10);
  ASSERT_EQ(1, c.size());
  c.add("a", 20);
  ASSERT_EQ(2, c.size());
  c.add("c", 20);
  ASSERT_EQ(3, c.size());
}


// Test 2: Test add and find
TEST(BSTCollectionTest, SimpleFind) {
  BSTCollection<string,int> c;
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

// Test 3: Test add, size, and remove
TEST(BSTCollectionTest, SimpleRemove) {
  BSTCollection<string,int> c;
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
TEST(BSTCollectionTest, SimpleRange) {
  BSTCollection<string,int> c;
  c.add("e", 50);
  c.add("c", 30);
  c.add("d", 40);
  c.add("f", 60);
  c.add("b", 20);
  //c.print();
  // search for proper sublist of keys
  ArrayList<string> s1;
  c.find("c", "e", s1);
  //cout << "1111111111111111" << endl;
  ASSERT_EQ(3, s1.size());
  //cout << "2222222222222222" << endl;
  ASSERT_EQ(true, member(string("c"), s1));
  ASSERT_EQ(true, member(string("d"), s1));
  //cout << "333333333333333" << endl;
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
TEST(BSTCollectionTest, SimpleSort) {
  BSTCollection<string,int> c;
  c.add("a", 10);
  //c.print();
  //cout << endl;
  c.add("e", 50);
  //c.print();
  //cout << endl;
  c.add("c", 30);
  //c.print();
  //cout << endl;
  c.add("b", 20);
  //c.print();
  //cout << endl;
  c.add("d", 40);
  //c.print();
  //cout << endl;
  ArrayList<string> sorted_keys;
  c.sort(sorted_keys);
  //cout << "Size: " << sorted_keys.size() << endl;///////////////////////////
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
TEST(BSTCollectionTest, ResizeTest) {
  size_t len = 49;
  BSTCollection<int,int> c;
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
TEST(BSTCollectionTest, CopyAndAssignment) {
  BSTCollection<string,int> c1;
  c1.add("b", 20);
  c1.add("a", 10);
  c1.add("c", 30);
  BSTCollection<string,int> c2(c1);
  int val1;
  string key1 = "b";
  
  ASSERT_EQ(c1.size(), c2.size());
  c2.add("e", 50);
  ASSERT_NE(c1.size(), c2.size());
  c1 = c2;
  ASSERT_EQ(c1.size(), c2.size());
  c1 = c1;
  ASSERT_EQ(c1.size(), c2.size());
  BSTCollection<string,int> c3;
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

// Test 8: remove of node with two children
TEST(BSTCollectionTest, RemoveNodeWithTwoChildren) {
  BSTCollection<string,int> c;
  c.add("b", 10);
  c.add("a", 20);
  c.add("d", 40);
  c.add("c", 30);
  c.add("e", 50);
  c.add("f", 60);
  ASSERT_EQ(6, c.size());
  // remove d (where right child has no left child)
  c.remove("d");
  ASSERT_EQ(5, c.size());
  ASSERT_EQ(3, c.height());
  // remove b (with right child having a left child)
  c.remove("b");
  ASSERT_EQ(4, c.size());
  ASSERT_EQ(3, c.height());
}

// Test 9: remove of node with two children, with left
TEST(BSTCollectionTest, RemoveNodeWithTwoChildrenWithLeft) {
  BSTCollection<string,int> c;
  c.add("b", 10);
  c.add("a", 20);
  c.add("d", 40);
  c.add("c", 30);
  c.add("e", 50);
  c.add("f", 60);
  ASSERT_EQ(6, c.size());
  // remove d
  c.remove("d");
  ASSERT_EQ(5, c.size());
  int v;
  ASSERT_EQ(true, c.find("f", v));
  ASSERT_EQ(60, v);
  ASSERT_EQ(3, c.height());
}


// WES Test 1: Test adding to the tree and then multiple remove operations
TEST(BSTWesTest, RemoveCases) {
BSTCollection<int,int> c;
  c.add(10, 10);
  c.add(30, 10);
  c.add(50, 10);
  c.add(40, 10);
  c.add(60, 10);
  c.add(20, 10);
  c.add(70, 10);
  BSTCollection<int,int> c1(c);//make extra trees
  BSTCollection<int,int> c2(c);
  ASSERT_EQ(7, c1.size());
  ASSERT_EQ(7, c2.size());
  //remove in order
  c.remove(10);
  c.remove(30);
  c.remove(50);
  c.remove(40);
  c.remove(60);
  c.remove(20);
  c.remove(70);
  ASSERT_EQ(0, c.size());
  //remove in reverse order
  c1.remove(70);
  c1.remove(20);
  c1.remove(60);
  c1.remove(40);
  c1.remove(50);
  c1.remove(30);
  c1.remove(10);
  ASSERT_EQ(0, c1.size());
  //remove in random order
  c2.remove(40);
  c2.remove(30);
  c2.remove(60);
  c2.remove(20);
  c2.remove(70);
  c2.remove(50);
  c2.remove(10);
  ASSERT_EQ(0, c2.size());
}

// WES Test 2: Test the sorting function
TEST(BSTWesTest, MoreSorting) {
BSTCollection<int,int> c;
  for(int i = 0; i < 100; ++i)
  	c.add(i, i);
  ArrayList<int> sorted_keys;
  c.sort(sorted_keys);
  int v;
  for(int i = 0; i < 100; ++i)//check to see if every node is in the tree
  	ASSERT_EQ(true, sorted_keys.get(i, v));
}

//Wes Test 3: Primarily meant for testing Assignment and Copy but also tests size and add.
//This makes a tree by adding keys 1-25 and also makes another by adding from 25-1
//It then does a series of copys and assignments
TEST(BSTWesTest, FurtherAssignmentAndCopy) {
  BSTCollection<int,int> c1;
  //ADD
  for(int i = 1; i <= 25; ++i)//Add 1-25 to tree
  {
  	c1.add(i, i);
  	ASSERT_EQ(i, c1.size());
  }
  ASSERT_EQ(25, c1.height());//Tree should be height 25
  BSTCollection<int,int> c2;
  for(int i = 25; i >= 1; --i)//Add 25-1 to tree
  	c2.add(i, i);
  ASSERT_EQ(25, c2.height());
  ASSERT_EQ(25, c1.size());//Tree 1 should be size 25
  ASSERT_EQ(25, c2.size());//Tree 2 should be size 25
  //ASSIGNMENT OP AND COPY CONSTRUCT
  BSTCollection<int,int> c3;//create a new tree
  c3 = c1;//copy using assig opp
  BSTCollection<int,int> c4(c2);//copy const
  ASSERT_EQ(25, c3.height());
  ASSERT_EQ(25, c4.height());
  ASSERT_EQ(25, c3.size());//Tree 3 should be size 25
  ASSERT_EQ(25, c4.size());//Tree 4 should be size 25
  BSTCollection<int,int> c5(c3);//construct 5 from 3
  c5.remove(5);//alter 5
  c5.remove(10);
  BSTCollection<int,int> c6;//construct 6
  c1 = c2 = c3 = c6 = c5;//assignment operator
  ASSERT_EQ(23, c1.size());//Tree 3 should be size 25
  ASSERT_EQ(25, c4.size());//Tree 4 should be size 25
}


// WES Test 4: Test the range function
TEST(BSTWesTest, MoreRange) {
BSTCollection<int,int> c;
  for(int i = 0; i < 100; ++i)
  	c.add(i, i);
  ArrayList<int> keys;
  c.find(0, 100, keys);
  int v;
  for(int i = 0; i < 100; ++i)//check to see if every node is in the list
  	ASSERT_EQ(true, keys.get(i, v));
  ASSERT_EQ(false, keys.get(150, v));
  ASSERT_EQ(false, keys.get(101, v));
  ASSERT_EQ(false, keys.get(-5, v));
}

// WES Test 5: Test the resizing at a large capacity
TEST(BSTWesTest, LargeResize) {
BSTCollection<int,int> c;
  for(int i = 1; i < 10000; ++i)//add 10,000 elements
  {
  	c.add(i, i);
  	ASSERT_EQ(i, c.size());//Tree should be correctly resizing. 
  }
}


int main(int argc, char** argv)
{
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

