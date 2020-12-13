//----------------------------------------------------------------------
// FILE: linked_list.h
// NAME: Wesley Muehlhausen
// DATE: 9 / 13 / 2020
// DESC: Implements a linked list version of the list class. Elements
//       are added by default to the end of the list via a tail pointer.
//Uses add, add, get, set, remove, size, make_empty
//----------------------------------------------------------------------

#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include "list.h"

template<typename T>
class LinkedList : public List<T>
{
public:
  LinkedList();//Constructor
  LinkedList(const LinkedList<T>& rhs);//Copy Constructor
  ~LinkedList();//Destructor
  LinkedList& operator=(const LinkedList<T>& rhs);//Assignment Operator

  void add(const T& item);//Add to end
  bool add(size_t index, const T& item);//Add by index
  bool get(size_t index, T& return_item) const;//Get by index
  bool set(size_t index, const T& new_item);//set by index
  bool remove(size_t index);//remove by index
  size_t size() const;//get size of list

private://each node is made up of a value and a next pointer
  struct Node {
    T value;
    Node* next;
  };
  //each list has a head and tail pointer and a length
  Node* head;
  Node* tail;
  size_t length;

  void make_empty();// helper to delete linked list

};

//constructor
template<typename T>
LinkedList<T>::LinkedList()
  : head(nullptr), tail(nullptr), length(0)
{

}

//Copy constructor
template<typename T>
LinkedList<T>::LinkedList(const LinkedList<T>& rhs)
  : head(nullptr), tail(nullptr), length(0)
{
  // defer to assignment operator
  *this = rhs;
}


//Destructor, uses the helper function to clear the linked list
template<typename T>
LinkedList<T>::~LinkedList()
{
  make_empty();
}

//Assignment operator 
template<typename T>
LinkedList<T>& LinkedList<T>::operator=(const LinkedList<T>& rhs)
{
  if(&rhs != this)//if they are NOT the same
  { 
    if(rhs.length == 0)//if the list is empty then do nothing
      return *this;
    Node* temp = rhs.head;
    make_empty();
    while(temp != nullptr)//copy the list from rhs
    {
    this->add(temp->value);
    temp = temp->next;
    }
  }  
  return *this;
}

//Add to the end
template<typename T>
void LinkedList<T>::add(const T& item)
{
  Node* n1 = new Node;
  n1->value = item;
  n1->next = nullptr;
  if(length == 0)//if the list is empty...
    {
      head = n1;
      tail = n1;
      length++;
      return;
    }
  tail->next = n1;//put it on the end of the list
  tail = tail->next;
  length++;
}

//Add to an index
template<typename T>
bool LinkedList<T>::add(size_t index, const T& item)
{
  if(index < 0 || index > length)
  {
    return false;
  } 
  Node* n1 = new Node;
  n1->value = item;
  n1->next = nullptr;
  Node* temp = head;
  if(length == 0 && index == 0)//Add into empty list 
  {
    head=n1;
    tail=n1;
  }
  else if(index == 0)//Add at front of list
  {
    n1->next = head;
    head = n1;
  }
  else if(index == length)//Add into end of list
  {
    tail->next = n1;
    tail = n1;
    n1->next = nullptr;
  }
  else//Add into index position
  {
    for(int i = 0; i < index-1; i++)
    {
      temp = temp->next;
    }
    n1->next = temp->next;
    temp->next = n1;
  }
  length++;
  return true;
}

//Get item at index
template<typename T>
bool LinkedList<T>::get(size_t index, T& return_item) const
{
  if(index < 0 || index >= length)//check for valid input
    return false;
  Node* temp = head;
  for(int i = 0; i < index; i++)//traverse to desired node
    temp = temp->next;
  return_item = temp->value;
  return true;
}

//Edit existing item of the list
template<typename T>
bool LinkedList<T>::set(size_t index, const T& new_item)
{
  if(index < 0 || index >= length)//check for valid input
    return false;
  Node* temp = head;
  for(int i = 0; i < index; i++)//traverse to node 
    temp = temp->next;
  temp->value = new_item;//change value
  return true;
}

//Delete node
template<typename T>
bool LinkedList<T>::remove(size_t index)
{
  if(index < 0 || index >= length )//check for valid input
    return false;
  else if(length == 0)
    return false;
  Node* temp = head;
  if(index == 0)//deleting first node in list
  {
      temp = head->next;
      delete head;
      head = temp;
  }
  else if(index == length-1)//deleting last node in list
  {
    while(temp->next->next != nullptr)
      temp = temp->next;
    delete tail;
    tail = temp;
    tail->next = nullptr;
  }
  else//deleting any normal node in list
  {
    for(int i = 0; i < index-1; i++)
      temp = temp->next;
    Node* temp2 = temp->next;
    temp->next = temp2->next;
    delete temp2;
  }
  length--;
  return true;
}


//Helper function to empty list
template<typename T>
void LinkedList<T>::make_empty()
{
  if(length == 0)//check to see if there isn anything in list
    return;
  Node* temp = head;
  while(head != nullptr)//delete nodes while there is a node ahead
  {
    head = head->next;
    delete temp;
    temp = head;
  }
  tail = nullptr;
  length = 0;
}


//Size function
template<typename T>
size_t LinkedList<T>::size() const
{
  return length;//returns length
}

#endif
