//----------------------------------------------------------------------
// FILE: bin_search_collection.h
// NAME: Wesley Muehlhausen
// DATE: 10 / 12 / 2020
// DESC: Implements add, remove, find, sort, keys, size functions with use of binary search
//----------------------------------------------------------------------

 
#ifndef BIN_SEARCH_COLLECTION_H
#define BIN_SEARCH_COLLECTION_H

#include "collection.h"
#include "array_list.h"

template<typename K, typename V>
class BinSearchCollection : public Collection<K, V>
{

public:
    void add(const K& a_key, const V& a_val);
    void remove(const K& a_key);
    bool find(const K& search_key, V& the_val) const;
    void find(const K& k1, const K& k2, ArrayList<K>& keys) const;
    void keys(ArrayList<K>& all_keys) const;
    void sort(ArrayList<K>& all_keys_sorted) const;
    size_t size() const;
	void print();//just used for testing


private:
    ArrayList<std::pair<K, V>> kv_list;
	bool bin_search(const K& key, size_t& index) const;
};



//This add function adds based on sorting so it will be added to the correct place 
//through the use of Binary Search which finds the correct index
template<typename K, typename V>
void BinSearchCollection<K, V>::add(const K& a_key, const V& a_val)
{
    std::pair<K, V> p(a_key, a_val);//create pair
	size_t index = 0;
	bin_search(a_key, index); //set value of index where it needs to go
		kv_list.add(index, p); // add at index
}

//Delete uses binary search to find the correct key and remove it 
template<typename K, typename V>
void BinSearchCollection<K, V>::remove(const K& a_key)
{
	if(kv_list.size() >= 1)//if the list is greater than zero
	{
		size_t index = 0;
		bin_search(a_key, index);//set correct index
		kv_list.remove(index);//delete
	}
}

//This find function finds a key and its value using binary search
template<typename K, typename V>
bool BinSearchCollection<K,V>::find(const K& search_key, V& the_val) const
{
	size_t index = 0;
	bool found = bin_search(search_key, index); //find if there is a matching KV pair
	if(found)//if match
	{
		std::pair<K, V> p;
		kv_list.get(index, p);//get index to check
		the_val = p.second;
		return true;
	}
	return false; //if no match
}    

//Find Range goes through the list starting at the index of k1 and when the keys become larger
//than k2, then it exits the loop 
template<typename K, typename V>
void BinSearchCollection<K,V>::find(const K& k1, const K& k2, ArrayList<K>& keys) const
{
	size_t indexLow = 0;
	bin_search(k1, indexLow);//get targeted index

	for(size_t i = indexLow; i < kv_list.size(); ++i)//iterate from k1 location to end of list
	{
		std::pair<K, V> p;
	    kv_list.get(i, p);
		if(p.first <= k2)//if keys are less than k2, continue
			keys.add(p.first);
		else//if not end the loop because out of range
			break;
	}
}

//Copies all of the keys into an arraylist of keys
template<typename K, typename V>
void BinSearchCollection<K,V>::keys(ArrayList<K>& all_keys) const
{
for(size_t i = 0; i < kv_list.size(); ++i)//binary search Not needed for this. just iterate through and add
	{
		std::pair<K, V> p;
		kv_list.get(i, p);//create and add
		all_keys.add(p.first);
	}
}

//Sort does not actaully sort because all of the keys are already in order
template<typename K, typename V>
void BinSearchCollection<K,V>::sort(ArrayList<K>& all_keys_sorted) const
{
	keys(all_keys_sorted);//return all of the keys
}

//Returns size of the KV List
template<typename K, typename V>
size_t BinSearchCollection<K,V>::size() const
{
	return kv_list.size();
}

//Not used in any of the functions, this function is just used for testing to see the contents of the list
template<typename K, typename V>
void BinSearchCollection<K,V>::print()
{
	std::cout << "Size: " << kv_list.size() << std::endl;
	for(int i = 0; i < kv_list.size(); ++i)
	{
		std::pair<K, V> p;
		kv_list.get(i, p);
		std::cout << p.first;
	} 
	std::cout << " " << std::endl;
}

//Binary Search takes in a key and index and finds the index of that key and will return true or false based on if it is in 
//the list or not
template<typename K, typename V>
bool BinSearchCollection<K,V>::bin_search(const K& key, size_t& index) const
{
	size_t low = 0;
	size_t high = kv_list.size() -1;
	size_t mid = 0;

	if(kv_list.size() == 0)//if size zero, not found
	{
		index = 0;
		return false;
	}

	while(low <= high)
	{
		//set mid
		mid = (high+low)/2;
		
		//get kp at mid
		std::pair<K, V> p;
    	kv_list.get(mid, p);
		
		//1. chech if key is equal to mid
		if(p.first == key)
		{
			index = mid;
			return true;
		}
		//2. check if mid is less than key
		else if(p.first < key)
		{
			low = mid + 1;	
		}
		//3. check if mid is greater than key
		else if(p.first > key)
		{
			if(mid == 0)
			break;

			high = mid - 1;
		}
	}

	
	std::pair<K, V> p;
    kv_list.get(mid, p);
	if(p.first < key)// for the case when adding to the start of the list to make sure of correct index ab vs ba situatiom
		index = mid+1;
	else
		index = mid;
	return false; //if not in the array, return false
}

#endif
