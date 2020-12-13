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
  void insertion_sort();//insertion sort
  void selection_sort();//selection sort
  void merge_sort();//merge sort which uses helper
  void quick_sort();//quick sort which uses helper
  void sort();//used for when Hash_Table or ArrayList Collection inherit from ArrayList. 
  			  //Defers to quicksort 

private://list consists of: 
  T* items;
  size_t capacity;
  size_t length;
  
  //Private helper functions
  void resize();// helper to resize items array
  void print();//for testing purposes
  void merge_sort(size_t start, size_t end);//Merge sort helper recursive
  void quick_sort(size_t start, size_t end);//Quick sort helper recursive
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

//Insertion sort
template<typename T>
void ArrayList<T>::insertion_sort()
{
   if(length > 1)//size 1 is sorted
   {
     T temp;
     T temp_index;
     for(int i = 1; i < length; i++)//iterate through list
     {
       temp_index = i;
       while(items[temp_index] < items[temp_index-1] && temp_index > 0)//if greater, swap
       {
         temp = items[temp_index];//swapping
         items[temp_index] = items[temp_index-1];
         items[temp_index-1] = temp;
         temp_index--;
       }
     }
   }

}

//selection sort
template<typename T>
void ArrayList<T>::selection_sort()
{
  if(length <= 1)
  	return;
  else if(length == 2)//for size 2
  {
  	if(items[0] > items[1])//if item 2 is less than item 1, swap
  	{
  		T tmp = items[0];
  		items[0] = items[1];
  		items[1] = tmp;
  	}
  	return;
  }
  else
  {
    for(int i = length; i > 1; i--)//sorted region starts at end of list and go to start
    {
      T temp = items[0];
      int temp_index = 0;
      for(int j = 1; j < i; j++)//start at index 1 and go to end of sorted region (i)
      {
        if(temp < items[j])//find the value that is the highest. If bigger than temp then copy
        {
          temp = items[j];
          temp_index = j;
        }
      }
      items[temp_index] = items[i-1];//swap
      items[i-1] = temp;
    }
  }
}

//MAIN MERGESORT
template<typename T>
void ArrayList<T>::merge_sort()
{
  if(length <= 1)
    return;
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
    int merge_size = (end - start) + 1;//size of merged portion
    int merge_position = 0;//position of merge insert
    int left = start;//pos of left partition
    int right = median + 1;//pos of right partition
    T tmp[merge_size]; //temp array

    //add lowest value to temp list
    while(left <= median && right <= end)
    {
      if(items[left] < items[right])
        tmp[merge_position++] = items[left++];
      else
        tmp[merge_position++] = items[right++];
    }
    while(left <= median)//if left partition is not empty, add to merged
      tmp[merge_position++] = items[left++];

    while(right <= end)//if left partition is not empty, add to merged
      tmp[merge_position++] = items[right++];
      
    for(int i = 0; i <= (end-start); ++i)//copy numbers back from temp
      items[start+i] = tmp[i];
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
    	quick_sort(start, last_index_pt1-1);//recursive step
    quick_sort(last_index_pt1 + 1, end);
  }
  

}

#endif
