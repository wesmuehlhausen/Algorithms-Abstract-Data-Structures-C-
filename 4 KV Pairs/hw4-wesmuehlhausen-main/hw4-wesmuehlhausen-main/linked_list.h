//----------------------------------------------------------------------
// FILE: linked_list.h
// NAME: Wesley Muehlhausen  
// DATE: 10 / 1 / 2020
// DESC: Implements a linked list version of the list class. Elements
//       are added by default to the end of the list via a tail pointer.
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
  void insertion_sort();//insertion sort
  void selection_sort();//selection sort
  void merge_sort();//calls merge sort helper
  void quick_sort();//calls quick sort helper
  void sort();//defers to merge sort

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
  void print();//helper to test
  Node* merge_sort(Node* left, int len);//recursive part of merge sort
  Node* quick_sort(Node* start, int len);//recursive part of quick sort
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

//Size function
template<typename T>
size_t LinkedList<T>::size() const
{
  return length;//returns length
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

//SORT
template<typename T>
void LinkedList<T>::sort()
{
  	if(length <= 1)	
  		return;
  	head = merge_sort(head, length);
	tail = head;
	while(tail->next != nullptr)
		tail = tail->next;
			
}

//MERGE SORT
template<typename T>
void LinkedList<T>::merge_sort()
{
  	if(length <= 1)	
  		return;
  	head = merge_sort(head, length);
	tail = head;
	while(tail->next != nullptr)
		tail = tail->next;
			
}

//Merge Sort recursive
template<typename T>
typename LinkedList<T>::Node*
LinkedList<T>::merge_sort(Node* left, int len)
{
	//std::cout << len << std::endl;
	if(len <= 1)//if list is size 1, its sorted
	{
		return left;
	}
		
	//INIT POINTERS
	int mid_len = len/2;//set midpoint
	Node* right = left;//set pointers 
	Node* tmp = left;
	
	//SPLIT LIST
	//set pointers at mid and before mid to split
	for(int i = 0; i < mid_len-1; ++i)//set tmp at mid-1 and right on node after
		tmp = tmp->next;
	right = tmp->next;	
	tmp->next = nullptr;//set tmp to null which means end of list
	
	//RECURSION splitting
	left = merge_sort(left, mid_len);
	right = merge_sort(right, len-mid_len);
	
	Node* new_list = nullptr;
	Node* new_list_tail = new_list;
	Node* temp = nullptr;
	//Case: While left and right, if left less than right, add left of tail of the new list (firstNode) and 
	//      advance left and vice versa
	while(left != nullptr and right != nullptr)
	{
		if(left->value < right->value)//add left
		{
			temp = left;
			left = left->next;
		}
		else//add right
		{
			temp = right;
			right = right->next;
		}
		if(!new_list)//for first add
		{
			new_list = temp;
			new_list_tail = temp;
		}
		else//normal cases
		{
			temp->next = nullptr;
			new_list_tail->next = temp;
			new_list_tail = new_list_tail->next;
		}		
		
	}
	
	if(left)//Case: If left, add the left to the tail
		new_list_tail->next = left;	
	else//else right
		new_list_tail->next = right;
		
	return new_list;
}

//QUICK SORT
template<typename T>
void LinkedList<T>::quick_sort()
{
  	if(length > 1)
  	{
  		head = quick_sort(head, length);
		tail = head;
		while(tail->next != nullptr)
			tail = tail->next;
	}
}

//Recursive sort using quicksort
template<typename T>
typename LinkedList<T>::Node*
LinkedList<T>::quick_sort(Node* start, int len)
{
	//SMALL LIST CONDITIONS
	if(len <= 1)//if the list is size 1 then it is sorted
		return start;
	if(len == 2)//for size 2:
	{
		if(start->value > start->next->value)//if the second is smaller than first, swap
		{
			start->next->next = start;
			start = start->next;
			start->next->next = nullptr;
		}		
		return start;
	}

	//SET POINTERS
	Node* pivot = start;//set pivot to start of list
	start = start->next;//start is one past pivot
	pivot->next = nullptr;//pivot is sorted
	
	//stays at the end of the SMALLER list which is where the new nodes get added
	Node* small = nullptr;//points to the beginning of the SMALLER list
	
	//stays at the end of the LARGER list which is where the new nodes get added
	Node* large = nullptr;//points to the beginning of the LARGER list
	
	//Set list sizes
	int small_size = 0; //size of small list
	int large_length = 0;	 //size of large list
	
	//MAIN SORTING
	while(start)//iterate through list:
	{
		//General Cases: 
		if(start->value <= pivot->value)//if smaller/= than pivot value
		{
			Node* tmp = start;
			start = start->next;
			tmp->next = small;
			small = tmp;
			++small_size;
		}
		else //if larger than pivot
		{
			Node* tmp = start;
			start = start->next;
			tmp->next = large;
			large = tmp;
			++large_length;
		}
	}
	//recursive part
	if(small_size > 0)//if the SMALLER list has more than 1 element(unsorted) go through again
	{
		small = quick_sort(small, small_size);
		Node* small_traverse = small;
		while(small_traverse->next != nullptr)
			small_traverse = small_traverse->next;
		small_traverse->next = pivot;
	}
	if(large_length > 0)//if the LARGER list has more than 1 element(unsorted) go through again
	{
		large = quick_sort(large, large_length);
		pivot->next = large;
	}
	if(small)
		return small;
	else
		return pivot;
}






//sort list by insertion sort
template<typename T>
void LinkedList<T>::insertion_sort()
{
  //check for proper length of list
  if(length < 2)
		return;
  //Main iteration through
	for(int i = 1; i < length; i++)
	{
		//Puts pointers on Nodes needed for a potential swap
		Node* temp = head;
    //move temp from start to marker
		for(int j = 0; j < i; j++)
		{
			temp = temp->next;
		}
		Node* traverse = head;
		Node* traverse2 = head;
    //if node value ahead of traverse is less than temp value, traverse
    //traverse2 moves behinds temp
		for(int j = 0; j < i-1; j++)
		{
			if(traverse->next->value < temp->value)
				traverse = traverse->next;
			traverse2 = traverse2->next;
		}

		//Main Case 1: if traverse is head
		if(traverse == head)
		{
			//Sub Case 1:if temp and traverse are touching
			if(traverse->next == temp)
			{
				if(temp->value < traverse->value)
				{
					traverse->next = temp->next;
					temp->next = traverse;
					head = temp;
					continue;
				}
				continue;
			}
			//Put temp ahead of head Node
			if(temp->value > traverse->value)
			{
				traverse2->next = temp->next;
				temp->next = traverse->next;
				traverse->next = temp;
				continue;
			}
			//Put temp before head Node
			if(temp->value < traverse->value)
			{
				traverse2->next = temp->next;
				temp->next = traverse;
				head = temp;
				continue;
			}
		}
		
    //reset and restart
		traverse2->next = temp->next;
		temp->next = traverse->next;
		traverse->next = temp;
		temp = nullptr;
		traverse2 = nullptr;
		traverse = nullptr;
	}	
	//Moves tail pointer to end of list
	Node* temp = head;
	for(int i = 0; i < length-1; ++i)
	{
		temp = temp->next;
	}
	tail = temp;
}

//sort using selectio sort
template<typename T>
void LinkedList<T>::selection_sort()
{
  //check if list is already sorted or too small
	if(length < 2)//for sorted list
		return;
	
  	else if(length == 2)//for list size 2
  	{
  		if(head->value > tail->value)
  		{
  			Node* extra = head;
  			head = tail;
  			tail = extra; 
  		}
  		return;
  	}
  	else
  	{
  		//start at beginning of list and go until only one node left
		for(int i = 0; i < length-1; i++)
		{
			T val;//temporary storage of value
			
			//traverse to nodes that will be swapped
			Node* temp = head;
			for(int j = 0; j < i; j++)
				temp = temp->next;
			
	
			Node* traverse = temp;
			val = traverse->value;
    		//start at start of unsorted and go through and find smallest value
			for(int j = i; j < length-1; j++)
			{
				traverse = traverse->next;
				if(traverse->value < val)
				{
					val = traverse->value;
				}
			}
			
			if(temp->value != val)//for when we need to do a splice
			{
				traverse = temp->next;
				while(traverse->value != val)
					traverse = traverse->next;
	
				//Main Case 1: if need to swap with end of list
				if(tail == traverse)
				{
					traverse = temp;
					while(traverse->next != tail)
						traverse = traverse->next;
					
        		//Sub Case 1: swap the first and last nodes
					if(i == 0)
					{
						tail->next = head->next;
						traverse->next = head;
						head->next = nullptr;
						head = tail;
						tail = temp;
						continue;
					}
					
        		//splice the nodes using extra trailer pointer 
					Node* trailer = head;
					while(trailer->next != temp)
						trailer = trailer->next;
					trailer->next = tail;
					tail->next = temp->next;
					temp->next = nullptr;
					traverse->next = temp;
					tail = temp;
					trailer = nullptr;
					continue;
				}
	
				//Main Case 2: Swapping first node with a middle node
				if(i == 0)
				{
					//Sub Case 2.1 swapping first and second nodes
					if(temp->next == traverse)
					{
						temp->next = traverse->next;
						traverse->next = temp;
						head = traverse;
						continue;
					}
					Node* before = head;
					while(before->next != traverse)
						before = before->next;
					Node* after = traverse->next;
					traverse->next = temp->next;
					temp->next = after;
					before->next = temp;
					head = traverse;
					before = nullptr;
					after = nullptr;
					continue;
				}	
				//Main Case 3: for if temp needs to swap with the node next to it
				if(temp->next == traverse)
				{
					Node* trailer = head;
					while(trailer->next != temp)
						trailer = trailer->next;
					temp->next = traverse->next;
					traverse->next = temp;
					trailer->next = traverse;
					trailer = nullptr;
					continue;
				}
				//Main Case 4: Normal middle to middle node
				Node* trailer = head;
				while(trailer->next != temp)
					trailer = trailer->next;
				Node* before = head;
				while(before->next != traverse)
					before = before->next;
				Node* after = traverse->next;
				traverse->next = temp->next;
				trailer->next = traverse;
				before->next = temp;
				temp->next = after;
				trailer = nullptr;
				before = nullptr;
				after = nullptr;
			}
		}
	}	
}

//personal hemper function
template<typename T>
void LinkedList<T>::print()
{
  Node* temp = head;
  std::cout << "Length: " << length << std::endl;
  std::cout << "Start: ";
  for(int i = 0; i < length; i++)
  {
      std::cout << temp->value << " + ";
      temp = temp->next;
  }
    std::cout << "END" << std::endl;
    std::cout << " " << std::endl;
}



#endif
