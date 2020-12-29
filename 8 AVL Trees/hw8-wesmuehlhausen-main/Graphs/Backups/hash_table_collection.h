//----------------------------------------------------------------------
// FILE: hash_table_collection.h
// NAME: Wesley Muehlhausen
// DATE: 10 / 12 / 2020
// DESC: Implements add, remove, find, sort, keys, size functions with use of hash tables
//----------------------------------------------------------------------

 
#ifndef HASH_TABLE_COLLECTION_H
#define HASH_TABLE_COLLECTION_H

#include "collection.h"
#include "array_list.h"
#include <functional>

template<typename K, typename V>
class HashTableCollection : public Collection<K, V>
{

public:
	HashTableCollection();//create an empty hash table with 10 buckets
  	HashTableCollection(const HashTableCollection<K, V>& rhs);//copy constructor
  	~HashTableCollection();//destructor
  	HashTableCollection& operator=(const HashTableCollection<K, V>& rhs);//assignment operator

    void add(const K& a_key, const V& a_val);//add KV Pair
    void remove(const K& a_key);//remove KV pair
    bool find(const K& search_key, V& the_val) const; //find KV pair
    void find(const K& k1, const K& k2, ArrayList<K>& keys) const;//Find Range
    void keys(ArrayList<K>& all_keys) const;//Return all keys in collection
    void sort(ArrayList<K>& all_keys_sorted) const;//sort all keys 
    size_t size() const;//return size of list
	void print();//just used for testing
	size_t min_chain_length();//
	size_t max_chain_length();
	double avg_chain_length();


private:
	//the chain of linked list nodes
	struct Node {
		K key;
		V value;
		Node* next;
	};

	//private member variables
	Node** hash_table;//the resizable hash table
	size_t length;//number of k-v pairs stored in the collection	
	size_t table_capacity;//current number of buckets in the hash table
	double load_factor_threshold = 0.75;//current load factor of the hash table
	
	//private member functions
	void resize_and_rehash();//double the size and rehash the hash table
	void make_empty();
    
};


template<typename K, typename V>
HashTableCollection<K, V>::HashTableCollection()
{
  length = 0;//set length to zero
  table_capacity = 16;//initial capacity to 10
  hash_table = new Node*[table_capacity];//create new arraylist of Type Node* of size capacity
  for(size_t i = 0; i < table_capacity; ++i)//iterate through table and set each node to null
	hash_table[i] = nullptr;

}

template<typename K, typename V>
HashTableCollection<K, V>::HashTableCollection(const HashTableCollection<K, V>& rhs)
{
  table_capacity = rhs.table_capacity;
  ;//set table size and length
  length = 0;
  hash_table = new Node*[table_capacity];
  for(size_t i = 0; i < table_capacity; ++i)// all point nodes to null 
	hash_table[i] = nullptr;
  ArrayList<K> all_keys; //create new arraylist 
  rhs.keys(all_keys);    //copy all keys to new arraylist
  V val;
  K tmp_key;
  for(size_t i = 0; i < all_keys.size(); ++i)
  {
	  all_keys.get(i, tmp_key);
	  rhs.find(tmp_key, val);//add all Values to arraylist
	  add(tmp_key, val);
	//   rhs.find(all_keys[i], val);
	//   add(all_keys[i], val);
	//fast to nav
  }
}

//Destructor
template<typename K, typename V>
HashTableCollection<K, V>::~HashTableCollection()
{
  make_empty();//clear
  delete [] hash_table;//delete
}

//Assignment operator
template<typename K, typename V>
HashTableCollection<K, V>& HashTableCollection<K, V>::operator=(const HashTableCollection<K, V>& rhs)
{
  if(this != &rhs) //if not the same
  {
	  make_empty();
	  table_capacity = rhs.table_capacity;

  		length = 0;
  		hash_table = new Node*[table_capacity];
  		for(size_t i = 0; i < table_capacity; ++i)// all point nodes to null 
		hash_table[i] = nullptr;
	  ArrayList<K> all_keys;
	  rhs.keys(all_keys);
	  V val;
	  K tmp_key;
	  for(size_t i = 0; i < all_keys.size(); ++i)
	  {
		  all_keys.get(i, tmp_key);
		  rhs.find(tmp_key, val); //all_keys.get(i)
		  add(tmp_key, val);
		//   rhs.find(all_keys[i], val); //all_keys.get(i)
		//   add(all_keys[i], val);
	  }
	  return *this;
  }  
  //std::cout << "ERRORRRRRRRRRRR" << std::endl;
return *this;
}



template<typename K, typename V>
void HashTableCollection<K, V>::add(const K& a_key, const V& a_val)
{
    //1) check if need to rehash
    if(length/table_capacity >= load_factor_threshold)
   		resize_and_rehash();
	//2) then do the hash
	Node* temp = new Node;
	temp->key = a_key;
	temp->value = a_val;
	std::hash<K> hash_function;
	size_t value = hash_function(a_key);
	size_t index = value % table_capacity;//find index
	if(!hash_table[index])//if no collision
	{
		hash_table[index] = temp;
		hash_table[index]->next = nullptr;
	}
	else // if there is a collision
	{
		Node* location = hash_table[index];
		while(location->next != nullptr)//locate the insertion point
			location = location->next;
		location->next = temp;
		temp->next = nullptr;
		location = nullptr;		
	}
	++length;
	temp = nullptr;
}

template<typename K, typename V>
void HashTableCollection<K, V>::remove(const K& a_key)
{
	std::hash<K> hash_function;
	size_t value = hash_function(a_key);
	size_t index = value % table_capacity;//find index
    
	//1) is empty
	if(!hash_table[index])
		return;
	//2)start of list
	else if(hash_table[index]->key == a_key)//if the first value
	{
		if(!hash_table[index]->next)//if list is one element
		{
			delete hash_table[index];
			hash_table[index] = nullptr;
		}
		else//if the list is more than one element
		{
			Node* temp_location = hash_table[index];
			hash_table[index] = hash_table[index]->next;
			delete temp_location;
			temp_location = nullptr;
		}	
	}
	//3)delete an end or middle Node
	else
	{
		Node* location = hash_table[index];
		//locate the insertion point
		while(location->next)
		{
			if(location->next->key == a_key)//check to see if next node is the key
			{
				Node* temp2 = location->next;//set to key node
				location->next = temp2->next;
				delete temp2;
				temp2 = nullptr;
				break;
			}
		location = location->next;//incriment
		}
		location = nullptr;
	}
	--length;
}

//finds a key and returns the value into the_val
template<typename K, typename V>
bool HashTableCollection<K,V>::find(const K& search_key, V& the_val) const
{

	std::hash<K> hash_function;
	size_t value = hash_function(search_key);
	size_t index = value % table_capacity;//find index

	if(!hash_table[index])//if the list is empty at location
		return false;
	else if(hash_table[index]->key == search_key)
	{
		the_val = hash_table[index]->value;
		return true;//if the first key is a match	
	}
	else
	{
        Node* location = hash_table[index];
		while(location->next)//locate the insertion point
		{
			location = location->next;//incriment
			if(location->key == search_key)//check to see if next node is the key
			{
				the_val = location->value;
				return true;
			}
			
		}
		location = nullptr;
	}
	return false;//if no key is found
}    
 
template<typename K, typename V>
void HashTableCollection<K,V>::find(const K& k1, const K& k2, ArrayList<K>& keys) const
{

	
	for(int i = 0; i < table_capacity; ++i)
	{
		if(hash_table[i])//if there is a value here
		{
			Node* location = hash_table[i];//set to bucket
			if(k1 <= hash_table[i]->key && hash_table[i]->key <= k2)//if its the first bucket
				keys.add(hash_table[i]->key);
			while(location->next)//while there is a key
			{
				location = location->next;
				if(k1 <= location->key && location->key <= k2)
					keys.add(location->key);
				else if(location->key > k2)
					return;
			}
			location = nullptr;
		}
	}
}


template<typename K, typename V>
void HashTableCollection<K,V>::keys(ArrayList<K>& all_keys) const
{
	int total_size = 0;
	for(int i = 0; i < table_capacity; ++i)
	{
		if(hash_table[i])//if there is a value here
		{
			all_keys.add(hash_table[i]->key);
			++total_size;
			if(total_size >= length)
				return;
			Node* location = hash_table[i];
			while(location->next)//while there is a key
			{
				location = location->next;
				all_keys.add(location->key);
				++total_size;
				if(total_size >= length)
					return;
			}
			location = nullptr;
		}
	}
}


template<typename K, typename V>
void HashTableCollection<K,V>::sort(ArrayList<K>& all_keys_sorted) const
{
	keys(all_keys_sorted);//return all of the keys
	all_keys_sorted.sort();//sort keys
}

template<typename K, typename V>
size_t HashTableCollection<K,V>::size() const
{
 return length;
}


template<typename K, typename V>
void HashTableCollection<K,V>::print()
{

}

//double the size and rehash the hash table
template<typename K, typename V>
void HashTableCollection<K,V>::resize_and_rehash()
{
	//ArrayList<K> all_keys;
	//keys(all_keys);//gather all of the keys from hashtable
	int new_capacity = table_capacity*2;
	Node **larger_hash_table = new Node*[new_capacity];//create new hashtable
	for(size_t i = 0; i < new_capacity; ++i)
		larger_hash_table[i] = nullptr; //init buckets
	//std::cout << "T1" << std::endl;
	V temp_value;//transfer KV pairs over
	for(size_t i = 0; i < table_capacity; ++i)
	{
		//std::cout << "T1.5" << std::endl;
		//put KV pair in temp node
		Node* ptr = hash_table[i];
		if(ptr)
		{
			//std::cout << "T1.75" << std::endl;
			Node* temp = new Node;
			temp->key = ptr->key;
			temp->value = ptr->value;
			//rehash
			std::hash<K> new_hash;
			size_t value = new_hash(temp->key);
			size_t index = value % new_capacity;
			temp->next = larger_hash_table[index];
			larger_hash_table[index] = temp;
		}

	}
	//std::cout << "T2" << std::endl;
	size_t temp_length = length;
	make_empty();
	table_capacity = new_capacity;
	delete [] hash_table;
	hash_table = larger_hash_table;
	length = temp_length;
	//std::cout << "T3" << std::endl;
}


template<typename K, typename V>
size_t HashTableCollection<K,V>::min_chain_length()
{
	size_t min = 0;
	for(size_t i = 0; i < table_capacity; ++i)
	{
		size_t cur_total = 0;
		if(hash_table[i])//if there is a value here
		{
			Node* location = hash_table[i];//set to bucket
			if(location)//if its the first bucket
				++cur_total;
			while(location->next)//while there is a key
			{
				location = location->next;
				++cur_total;
			}
		}
		if(min == 0 && cur_total != 0)
			min = cur_total;
		else if(cur_total < min && cur_total != 0)
			min = cur_total;
	}
	return min;
}

template<typename K, typename V>
size_t HashTableCollection<K,V>::max_chain_length()
{
	size_t max = 0;
	for(size_t i = 0; i < table_capacity; ++i)
	{
		size_t cur_total = 0;
		if(hash_table[i])//if there is a value here
		{
			Node* location = hash_table[i];//set to bucket
			if(location)//if its the first bucket
				++cur_total;
			while(location->next)//while there is a key
			{
				location = location->next;
				++cur_total;
			}
		}
		if(cur_total > max)
			max = cur_total;
	}
	return max;
}

template<typename K, typename V>
double HashTableCollection<K,V>::avg_chain_length()
{
	double total = 0;
	double ave;
	for(size_t i = 0; i < table_capacity; ++i)
	{
		if(hash_table[i])//if there is a value here
		{
			Node* location = hash_table[i];//set to bucket
			if(location)//if its the first bucket
				++total;
			while(location->next)//while there is a key
			{
				location = location->next;
				++total;
			}
		}
		
		ave = total / table_capacity;
	}
	return ave;
}

template<typename K, typename V>
void HashTableCollection<K,V>::make_empty()
{
	ArrayList<K> all_keys;
	keys(all_keys);
	K tmp_key;
	for(size_t i = 0; i < all_keys.size(); ++i)
	{
		all_keys.get(i, tmp_key);
		remove(tmp_key);
		//remove(all_keys2[i]);
	}
		
}

#endif
