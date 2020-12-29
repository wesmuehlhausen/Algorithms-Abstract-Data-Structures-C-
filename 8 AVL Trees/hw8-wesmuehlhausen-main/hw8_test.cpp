//----------------------------------------------------------------------
// Name: 
// File: hw8_test.cpp
// Date: Fall 2020
// Desc: Unit tests for AVL tree collection implementation
//----------------------------------------------------------------------


#include <iostream>
#include <string>
#include <gtest/gtest.h>
#include "array_list.h"
#include "avl_collection.h"


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
TEST(AVLCollectionTest, CorrectSize) {
  AVLCollection<string,int> c;
  ASSERT_EQ(0, c.size());
  c.add("b", 10);
  ASSERT_EQ(1, c.size());
  c.add("a", 20);
  ASSERT_EQ(2, c.size());
  c.add("c", 20);
  ASSERT_EQ(3, c.size());
}


// Test 2: Test add and find
TEST(AVLCollectionTest, SimpleFind) {
  AVLCollection<string,int> c;
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
TEST(AVLCollectionTest, SimpleRemove) {
  AVLCollection<string,int> c;
  c.add("b", 10);
  c.add("a", 20);
  c.add("c", 30);
  //c.print();
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
TEST(AVLCollectionTest, SimpleRange) {
  AVLCollection<string,int> c;
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
TEST(AVLCollectionTest, SimpleSort) {
  AVLCollection<string,int> c;
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

// Test 6: copy and assignment operator
TEST(AVLCollectionTest, CopyAndAssignment) {
  AVLCollection<string,int> c1;
  c1.add("b", 20);
  c1.add("a", 10);
  c1.add("c", 30);
  AVLCollection<string,int> c2(c1);
  ASSERT_EQ(c1.size(), c2.size());
  c2.add("e", 50);
  ASSERT_NE(c1.size(), c2.size());
  c1 = c2;
  ASSERT_EQ(c1.size(), c2.size());
  c1 = c1;
  ASSERT_EQ(c1.size(), c2.size());
  AVLCollection<string,int> c3;
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

// Test 7: remove of node with two children
TEST(AVLCollectionTest, RemoveNodeWithTwoChildren) {
  AVLCollection<string,int> c;
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

// Test 8: remove of node with two children, with left
TEST(AVLCollectionTest, RemoveNodeWithTwoChildrenWithLeft) {
  AVLCollection<string,int> c;
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

// Test 9: rebalance after add check
TEST(AVLCollectionTest, AddRebalanceCheck) {
  // left rotation
  AVLCollection<string,int> c1;
  c1.add("a", 10);
  c1.add("b", 20);
  c1.add("c", 30);
  ASSERT_EQ(2, c1.height());
  // right rotation
  AVLCollection<string,int> c2;
  c2.add("c", 30);
  c2.add("b", 20);
  c2.add("a", 10);
  ASSERT_EQ(2, c2.height());
  // left-right rotation
  AVLCollection<string,int> c3;
  c3.add("c", 30);
  c3.add("a", 10);
  c3.add("b", 20);
  ASSERT_EQ(2, c3.height());
  // right-left rotation
  AVLCollection<string,int> c4;
  c4.add("a", 10);
  c4.add("c", 30);
  c4.add("b", 20);
  ASSERT_EQ(2, c4.height());
  // right rotation
  AVLCollection<string,int> c5;
  c5.add("e", 50);
  c5.add("f", 60);
  c5.add("c", 30);
  c5.add("d", 40);
  c5.add("b", 20);
  c5.add("a", 10);
  ASSERT_EQ(3, c5.height());
  // right-left rotation
  AVLCollection<string,int> c6;
  c6.add("e", 50);
  c6.add("f", 60);
  c6.add("b", 20);
  c6.add("d", 40);
  c6.add("a", 10);
  c6.add("c", 30);
  ASSERT_EQ(3, c6.height());
  // right rotation
  AVLCollection<string,int> c7;
  c7.add("b", 20);
  c7.add("a", 10);
  c7.add("d", 40);
  c7.add("c", 30);
  c7.add("e", 50);
  c7.add("f", 60);
  ASSERT_EQ(3, c7.height());
  // left-right rotation
  AVLCollection<string,int> c8;
  c8.add("b", 20);
  c8.add("a", 10);
  c8.add("e", 50);
  c8.add("d", 40);
  c8.add("f", 60);
  c8.add("c", 30);
  ASSERT_EQ(3, c8.height());
}

// Test 10: rebalance after remove check
TEST(AVLCollectionTest, RemoveRebalanceCheck) {
  // no children, rebalance
  AVLCollection<string,int> c1;
  c1.add("c", 30);
  c1.add("b", 20);
  c1.add("d", 40);
  c1.add("a", 10);
  ASSERT_EQ(3, c1.height());
  c1.remove("c");
  ASSERT_EQ(2, c1.height());
  // one child, rebalance
  AVLCollection<string,int> c2;
  c2.add("e", 50);
  c2.add("c", 30);
  c2.add("f", 60);
  c2.add("a", 10);
  c2.add("d", 40);
  c2.add("b", 20);
  c2.add("g", 70);
  ASSERT_EQ(4, c2.height());
  c2.remove("f");
  ASSERT_EQ(3, c2.height());
  // two children, rebalance
  AVLCollection<string,int> c3;
  c3.add("e", 50);
  c3.add("b", 20);
  c3.add("g", 70);
  c3.add("a", 10);
  c3.add("d", 40);
  c3.add("f", 60);
  c3.add("c", 30);
  ASSERT_EQ(4, c3.height());
  c3.remove("e");
  ASSERT_EQ(3, c3.height());
}

//Wes Test 1: Tests the add function primarily (also some size, and remove), 
//adding heavily to the right side of the list which tests the tree's 
//ability to rebalance in this case relying on left rotations
TEST(AVLTestByWes, AddHeavyRightSide) {
AVLCollection<string,int> c;
  //TEST ADD AND SIZE
  ASSERT_EQ(0, c.size());//check initial size 0
  c.add("b", 10);//add at root
  ASSERT_EQ(1, c.size());//size check
  c.add("a", 20);//add at root left
  ASSERT_EQ(2, c.size());//size check
  c.add("c", 20);//add at root right
  ASSERT_EQ(3, c.size());//size check
  c.add("f", 10);//add at c right
  c.add("g", 20);//add at f right (left rotation at f)
  c.add("h", 30);//add at g right (lett rotation at root)
  c.add("i", 10);//add at h right (left rotation at g) should be perfect tree after this
  c.add("n", 20);//add at i right
  c.add("z", 30);//add at n right (left rotation at i)
  //TEST SIZE AND FIND VALUES
  ASSERT_EQ(9, c.size());//Should be size 9
  int v;
  ASSERT_EQ(true, c.find("a", v));//Check a, g, z, to be in tree
  ASSERT_EQ(true, c.find("g", v));
  ASSERT_EQ(true, c.find("z", v));  
  c.remove("f");//Remove root f
  ASSERT_EQ(8, c.size());//Should be size 8
  ASSERT_EQ(false, c.find("f", v));//f shouldn't be in tree anymore
  ASSERT_EQ(true, c.find("b", v));//Check if b, c, f, h, in list
  ASSERT_EQ(true, c.find("c", v));  
  ASSERT_EQ(true, c.find("i", v));
  ASSERT_EQ(true, c.find("h", v));  
  c.remove("z");//Remove leaf z
  ASSERT_EQ(7, c.size());//Should be size 7
  ASSERT_EQ(false, c.find("z", v));//z shouldn't be found 
}

//Wes Test 2: Tests the add function primarily loading the left side of the 
//tree which tests left and right shifts at parents and root node. Also tests 
//sort to see if adding correctly and keys works correctly
TEST(AVLTestByWes, AddHeavyLeftSide) {
AVLCollection<string,int> c;
  //TEST ADD
  c.add("n", 90);//Add as root 
  c.add("j", 10);//Add at root left 
  c.add("r", 50);//Add at root right 
  c.add("u", 30);//Add at r right
  c.add("q", 20);//Add at r left
  c.add("p", 40);//Add at q left (requires new tree root q)
  c.add("r", 10);//Add at u left (requires subtree shift)
  c.add("p", 10);//Add at leaf p right
  c.add("o", 10);//Add at parent p left
  c.add("p", 10);//Add at leaf p right (requires left shift at n)
  c.add("o", 10);//Add at leaf o right (requires right shift at root q)
  //TEST SORT
  ArrayList<string> sorted_keys;
  c.sort(sorted_keys);
  ASSERT_EQ(11, sorted_keys.size());//check size 11 correct
  bool match;
  for (size_t i = 1; i < sorted_keys.size(); ++i) {//test to see if 
    string k1;
    string k2;
    ASSERT_EQ(true, sorted_keys.get(i-1, k1));//find both keys
    ASSERT_EQ(true, sorted_keys.get(i, k2));
    if(k1 <= k2)//for when dublicate keys are added,
    	match = true;
    else
    	match = false;
    ASSERT_EQ(true, match);
  }
}


//Wes Test 3: Primarily meant for testing Assignment and Copy but also tests size and add.
//This makes a tree by adding keys 1-25 and also makes another by adding from 25-1
//It then does a series of copys and assignments
TEST(AVLTestByWes, FurtherAssignmentAndCopy) {
  AVLCollection<int,int> c1;
  //ADD
  for(int i = 1; i <= 25; ++i)//Add 1-25 to tree
  {
  	c1.add(i, i);
  	ASSERT_EQ(i, c1.size());
  }
  ASSERT_EQ(5, c1.height());//Tree should be height 5
  AVLCollection<int,int> c2;
  for(int i = 25; i >= 1; --i)//Add 25-1 to tree
  	c2.add(i, i);
  ASSERT_EQ(5, c2.height());//Tree should be height 5
  ASSERT_EQ(25, c1.size());//Tree 1 should be size 25
  ASSERT_EQ(25, c2.size());//Tree 2 should be size 25
  //ASSIGNMENT OP AND COPY CONSTRUCT
  AVLCollection<int,int> c3;//create a new tree
  c3 = c1;//copy using assig opp
  AVLCollection<int,int> c4(c2);//copy const
  ASSERT_EQ(5, c3.height());//Tree 1 should be height 5
  ASSERT_EQ(5, c4.height());//Tree 2 should be height 5
  ASSERT_EQ(25, c3.size());//Tree 3 should be size 25
  ASSERT_EQ(25, c4.size());//Tree 4 should be size 25
  AVLCollection<int,int> c5(c3);//construct 5 from 3
  c5.remove(5);//alter 5
  c5.remove(10);
  AVLCollection<int,int> c6;//construct 6
  c1 = c2 = c3 = c6 = c5;//assignment operator
  ASSERT_EQ(23, c1.size());//Tree 3 should be size 25
  ASSERT_EQ(25, c4.size());//Tree 4 should be size 25
}

//Wes Test 4: Primarily meant for removing. This tests the trees ability to rebalance
//After removing. This tests many remove cases such as root, parent, and leaf removes which
//Require rotations. 
TEST(AVLTestByWes, RemoveMultiNodes) {
  AVLCollection<int,int> c1;
  //ADD
  for(int i = 1; i <= 25; ++i)//Add 1-25 to tree
  {
  	c1.add(i, i);
  	ASSERT_EQ(i, c1.size());
  }
  ASSERT_EQ(5, c1.height());//Tree should be height 5
  //REMOVE
  c1.remove(16);//Remove root 16 (copy 17 to root and delete 17)
  c1.remove(14);//Remove 14, 13 gets promoted
  c1.remove(13);//Remove 13, (rebalance with right rotation at node 12)
  c1.remove(8);//Remove 8 which is the roots left child, 9 is the in order successor which
  			   //deletes 9 after copy and left rotation at 10
  c1.remove(25);//remove 25
  ASSERT_EQ(5, c1.height());//Tree 1 should be height 5
  ASSERT_EQ(20, c1.size());//Tree 1 should be size 23
  int a;
  ASSERT_EQ(false, c1.find(16, a));//Find values that were removed
  ASSERT_EQ(false, c1.find(13, a));
}


//Wes Test 5: Primarily trying to break it sorting nothing or sorting the same value or 
//With a wierd assignment and copy steps
TEST(AVLTestByWes, OddConditions) {
AVLCollection<string,int> c;
  c = c = c;
  ArrayList<string> sorted_keys;
  c.sort(sorted_keys);//sort empty tree
  c.add("a", 90);
  c.sort(sorted_keys);//sort single node tree
  c.add("a", 90);
  c.sort(sorted_keys);//sort two of same
  c.add("a", 90);
  c.sort(sorted_keys);//sort three of same
  AVLCollection<string,int> c2(c);
  AVLCollection<string,int> c3(c2);
  c = c3;
  c2 = c;
  c3 = c2;
  ASSERT_EQ(3, c.size());//Tree 1 should be size 3
  ASSERT_EQ(3, c2.size());//Tree 2 should be size 3
  ASSERT_EQ(3, c3.size());//Tree 3 should be size 3
  int a;
  ASSERT_EQ(false, c.find("b", a));//Find b: false
  ASSERT_EQ(true, c.find("a", a));//Find a: true
  ASSERT_EQ(false, c2.find("b", a));//Find b: false
  ASSERT_EQ(true, c2.find("a", a));//Find a: true
  ASSERT_EQ(false, c3.find("b", a));//Find b: false
  ASSERT_EQ(true, c3.find("a", a));//Find a: true
}


int main(int argc, char** argv)
{
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

