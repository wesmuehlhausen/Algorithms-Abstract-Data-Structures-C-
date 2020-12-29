//----------------------------------------------------------------------
// FILE: array_list.h
// NAME: Wesley Muehlhausen
// DATE: 10 / 1 / 2020
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
  ArrayList();
  ArrayList(const ArrayList<T>& rhs);
  ~ArrayList();
  ArrayList& operator=(const ArrayList<T>& rhs);

  void add(const T& item);
  bool add(size_t index, const T& item);
  bool get(size_t index, T& return_item) const;
  bool set(size_t index, const T& new_item);
  bool remove(size_t index);
  size_t size() const;
  void insertion_sort();
  void selection_sort();
  void merge_sort();
  void quick_sort();
  void sort();

private:
  T* items;
  size_t capacity;
  size_t length;
  
  

  // helper to resize items array
  void resize();
  void print();
  void merge_sort(size_t start, size_t end);
  void quick_sort(size_t start, size_t end);
};


template<typename T>
ArrayList<T>::ArrayList()
  : capacity(10), length(0)
{
  items = new T[capacity];
}


template<typename T>
ArrayList<T>::ArrayList(const ArrayList<T>& rhs)
  : capacity(10), length(0), items(nullptr)
{
  // defer to assignment operator
  *this = rhs;
}


// TODO: Finish the remaining functions below

//Destructor
template<typename T>
ArrayList<T>::~ArrayList()
{
	if(items)
		delete[] items;
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
    if(items)
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
  if(this->length == this->capacity)//if length is at capacity, increase size of list
  {
    resize();
  }
  if(this->length < this->capacity)//if parameters fit, add to end
  {
    //print();
    this->items[length] = item;
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
  if(length == 0)//empty list
  {
    add(item);//defer to normal add
    return true;

  }
  else if(index == length)//add to end 
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
  if(index < 0 || index > length-1)//check for valid input
  {
    return false;
  }
  return_item = this->items[index];//get item
  return true;
}

//set item by index
template<typename T>
bool ArrayList<T>::set(size_t index, const T& new_item)
{
  if(index < 0 || index > length-1)//check for valid input
  {
    return false;
  }
  this->items[index] = new_item;//change item at index
  return true;
}

//Remove by index
template<typename T>
bool ArrayList<T>::remove(size_t index)
{
  if(index < 0 || index > length)//check for valid input
    return false;
  if(length <= 0)
    return false;
  //delete items[index];
  for(int i = index; i < length; i++)//remove and move list back one
    this->items[i] = this->items[i+1];
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
  {
    items2[i] = items[i];
  }
  delete [] items;//delete items
  items = items2;//items becomes new items array
}

template<typename T>
void ArrayList<T>::print()
{
  std::cout << "Length: " << length << "   Capacity: " << capacity << std::endl;
  std::cout << "Start: ";
  for(int i = 0; i < length; i++)
  {
      std::cout << items[i];
      std::cout << " ";
  }
    std::cout << "END" << std::endl;
    std::cout << " " << std::endl;

  

}

template<typename T>
void ArrayList<T>::insertion_sort()
{
  // if(length > 1)
  // {
  //   T temp;
  //   T temp_index;
  //   for(int i = 1; i < length; i++)
  //   {
  //     temp_index = i;
  //     while(items[temp_index] < items[temp_index-1] && temp_index > 0)
  //     {
  //       temp = items[temp_index];
  //       items[temp_index] = items[temp_index-1];
  //       items[temp_index-1] = temp;
  //       temp_index--;
  //     }
  //   }
  // }

}

template<typename T>
void ArrayList<T>::selection_sort()
{
  if(length > 1){
    for(int i = length; i > 1; i--)
    {
      T temp = items[0];
      int temp_index = 0;
      for(int j = 1; j < i; j++)
      {
        if(temp < items[j])
        {
          temp = items[j];
          temp_index = j;
        }
      }
      items[temp_index] = items[i-1];
      items[i-1] = temp;
    }
  }
}

//MAIN MERGESORT
template<typename T>
void ArrayList<T>::merge_sort()
{
  size_t start = 0;
  size_t end = length-1;
  merge_sort(start, end);//call merge sort recursive
}

//MERGE RECURSIVE
template<typename T>
void ArrayList<T>::merge_sort(size_t start, size_t end)//start/end
{
  int median = 0;
  if(start < end)
  {
    median = (start + end) / 2; //set midpoint
    //recursive call
    merge_sort(start, median);
    merge_sort(median+1, end);

    //init values
    int merge_size = end - start + 1;//size of merged partion
    int merge_position = 0;//position of merge insert
    int left = 0;//pos of left partition
    int right = 0;//pos of right partition
    T tmp[merge_size]; //temp array

    left = start;    //init left and right partition 
    right = median+1;
    //add lowest value to temp list
    while(left <= median && right <= end)
    {
      if(items[left] <= items[right])
      {
        tmp[merge_position] = items[left];
        ++left;
      }
      else
      {
        tmp[merge_position] = items[right];
        ++right;
      }
      ++merge_position;
    }
    while(left <= median)//if left partition is not empty, add to merged
    {
      tmp[merge_position] = items[left];
      ++left;
      ++merge_position;
    }
    while(right <= end)//if left partition is not empty, add to merged
    {
      tmp[merge_position] = items[right];
      ++right;
      ++merge_position;
    }
    for(int merge_position = 0; merge_position < merge_size; ++merge_position)//copy numbers back from temp
    {
      items[start+merge_position] = tmp[merge_position];
    }
  }  
}

//SORT
template<typename T>
void ArrayList<T>::sort()
{
 if(length <= 1)
    return;
  else if(length >= 2)
  {
    size_t start = 0;
    size_t end = length-1;
    quick_sort(start, end);//start recursion
  }
}

//MAIN QUICKSORT
template<typename T>
void ArrayList<T>::quick_sort()
{
  if(length <= 1)
    return;
  else if(length >= 2)
  {
    size_t start = 0;
    size_t end = length-1;
    quick_sort(start, end);//start recursion
  }
}


//Recursive Quicksort
template<typename T>
void ArrayList<T>::quick_sort(size_t start, size_t end)
{
  
  T temp; //temp value used later
  if(start  < end)
  {
    T pivot = items[start];     //set pivot to FIRST value
    size_t last_index_pt1 = start;   //last index, first part
    for(size_t i = start + 1; i <= end; i++) //test <= vs <
    {
      if(items[i] < pivot)
      {
        last_index_pt1++;
        temp = items[i]; //SWAP items[i] and items[last_index_pt1]
        items[i] = items[last_index_pt1];
        items[last_index_pt1] = temp;
      }
    }
    temp = items[start]; //MOVE pivot: SWAP items[start] and items[last_index_pt1]
    items[start] = items[last_index_pt1];
    items[last_index_pt1] = temp;
    
    if(last_index_pt1 > 0)//keep in bounds
    {
    quick_sort(start, last_index_pt1-1);//recursive step
    }
    quick_sort(last_index_pt1 + 1, end);
  }
  

}

#endif
