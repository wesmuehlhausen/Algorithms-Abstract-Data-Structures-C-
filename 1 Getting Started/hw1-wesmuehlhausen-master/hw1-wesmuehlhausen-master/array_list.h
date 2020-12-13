//----------------------------------------------------------------------
// FILE: array_list.h
// NAME: Wesley Muehlhausen
// DATE: 9 / 13 / 2020
// DESC: Implements a resizable array version of the list
//       class. Elements are added by default to the last available
//       index in the array. 
//----------------------------------------------------------------------

#ifndef ARRAY_LIST_H
#define ARRAY_LIST_H

#include "list.h"

template<typename T>
class ArrayList : public List<T>
{
public:
  ArrayList();//constructor
  ArrayList(const ArrayList<T>& rhs);//copy constructor
  ~ArrayList();//destructor
  ArrayList& operator=(const ArrayList<T>& rhs);//assignment operator

  void add(const T& item);//add to end
  bool add(size_t index, const T& item);//add by index
  bool get(size_t index, T& return_item) const;//get by index
  bool set(size_t index, const T& new_item);//set by index
  bool remove(size_t index);//remove by index
  size_t size() const;//return size of list


private://list consists of: 
  T* items;
  size_t capacity;
  size_t length;
  
  //Private helper functions
  void resize();// helper to resize items array
};

//Constructor
template<typename T>
ArrayList<T>::ArrayList()
  : capacity(10), length(0)
{
  items = new T[capacity];
}

//Copy Constructor
template<typename T>
ArrayList<T>::ArrayList(const ArrayList<T>& rhs)
  : capacity(10), length(0), items(nullptr)
{
  // defer to assignment operator
  *this = rhs;
}

//Destructor
template<typename T>
ArrayList<T>::~ArrayList()
{
  delete [] items;
}

//Assignment operator
template<typename T>
ArrayList<T>& ArrayList<T>::operator=(const ArrayList<T>& rhs)
{
  if(this == &rhs)//if they are the same
  {
    return *this;
  }
  if(rhs.length == 0)//if there is nothing to copy.
  {
    length = 0;
    if(items)//delete the list
    {
      delete [] items;
    }
    capacity = 10;
    items = new T[capacity];
    return *this;
  }

  length = rhs.length;//the normal copy stuff
  delete [] items;
  capacity = rhs.capacity;
  items = new T[rhs.capacity];
  for(int i = 0; i < rhs.length; i++)
  {
    items[i] = rhs.items[i];
  }

  return *this;
}

//Add to end function
template<typename T>
void ArrayList<T>::add(const T& item)
{
  if(length == capacity)//if length is at capacity, increase size of list
    resize();
  if(length < capacity)//if parameters fit, add to end
  {
    items[length] = item;
    length++;
  }
}

//Add to index value
template<typename T>
bool ArrayList<T>::add(size_t index, const T& item)
{
  if(index > length)//invalid index
    return false;
  if(length == capacity)//expand if needed
    resize();
  if(length == 0 || index == length)//empty list
  {
    add(item);//defer to normal add
    return true;
  }
  else
  {
    for(int i = length; i > index; i--)
    {
      items[i] = items[i-1];//move contents over
    }
    items[index] = item;//insert number
  }
  length++;
  return true;

}

//Get item by index
template<typename T>
bool ArrayList<T>::get(size_t index, T& return_item) const
{
  if(index > length-1)//check for valid input
    return false;
  return_item = items[index];//get item
  return true;
}

//set item by index
template<typename T>
bool ArrayList<T>::set(size_t index, const T& new_item)
{
  if(index > length-1)//check for valid input
    return false;
  items[index] = new_item;//change item at index
  return true;
}

//Remove by index
template<typename T>
bool ArrayList<T>::remove(size_t index)
{
  if(length <= 0 || index > length)//check for valid input
    return false;
  for(int i = index; i < length-1; i++)//remove and move list back one
    items[i] = items[i+1];
  length--;
  return true;
}

//size function
template<typename T>
size_t ArrayList<T>::size() const
{
  return length; //return size
}

//Resize helper function 
template<typename T>
void ArrayList<T>::resize()
{
  capacity = capacity*2;//capacity x2
  T* items2 = new T[capacity];//create new items array with new capacity
  for(int i = 0; i < length; i++)//copy items into the new items (up to length)
    items2[i] = items[i];
  delete [] items;//delete items
  items = items2;//items becomes new items array
}

#endif
