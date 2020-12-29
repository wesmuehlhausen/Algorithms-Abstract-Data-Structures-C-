//----------------------------------------------------------------------
// FILE: array_list_collection.h
// NAME: Wesley Muehlhausen
// DATE: 10 / 12 / 2020
// DESC: implements add, remove, find, find range, and sort functions for a KV collection
//----------------------------------------------------------------------

 
#ifndef ARRAY_LIST_COLLECTION_H
#define ARRAY_LIST_COLLECTION_H

#include "collection.h"
#include "array_list.h"


template<typename K, typename V>
class ArrayListCollection : public Collection<K, V>
{

public://public functions
    void add(const K& a_key, const V& a_val);
    void remove(const K& a_key);
    bool find(const K& search_key, V& the_val) const;
    void find(const K& k1, const K& k2, ArrayList<K>& keys) const;
    void keys(ArrayList<K>& all_keys) const;
    void sort(ArrayList<K>& all_keys_sorted) const;
    size_t size() const;


private:
    ArrayList<std::pair<K, V>> kv_list; //create kv_list
};



//Simple add to end function
template<typename K, typename V>
void ArrayListCollection<K, V>::add(const K& a_key, const V& a_val)
{
    std::pair<K, V> p(a_key, a_val);//create and add KV
    kv_list.add(p);
}

//Iterates to key and Deletes given key
template<typename K, typename V>
void ArrayListCollection<K, V>::remove(const K& a_key)
{
   for(int i = 0; i < kv_list.size(); ++i)//find the key
	{
		std::pair<K, V> p;
		kv_list.get(i, p); //same as using brackets
		if(p.first == a_key)//see if key matches given key
		{
			kv_list.remove(i);//remove
			return;
		}
	}
}

//Returns whether you found the key or not. Finds Key
template<typename K, typename V>
bool ArrayListCollection<K,V>::find(const K& search_key, V& the_val) const
{
    for(int i = 0; i < kv_list.size(); ++i)//iterate through list
	{
		std::pair<K, V> p;//create pair
		kv_list.get(i, p);
		if(p.first == search_key)//if key exists
		{
			the_val = p.second;//set value for second
			return true;
		}
	}
	return false;//if key doesnt exist
}    

//go through kv list, starting at K1, go until K2, add all keys in that range to arraylist keys
template<typename K, typename V>
void ArrayListCollection<K,V>::find(const K& k1, const K& k2, ArrayList<K>& keys) const
{
	for(int i = 0; i < kv_list.size(); ++i)//go through list
	{
		std::pair<K, V> p;
		kv_list.get(i, p);//create pair
		if(p.first >= k1 && p.first <= k2)//if key is within list, add to keys
		{
			keys.add(p.first);
		}       
	}
}

//creates a list of keys based on KV list
template<typename K, typename V>
void ArrayListCollection<K,V>::keys(ArrayList<K>& all_keys) const
{
for(size_t i = 0; i < kv_list.size(); ++i)//go through list 
	{
		std::pair<K, V> p;//create pair
		kv_list.get(i, p);
		all_keys.add(p.first);//add to new list
	}
}

//Calls the quicksort function from Arraylist and sorts Keys
template<typename K, typename V>
void ArrayListCollection<K,V>::sort(ArrayList<K>& all_keys_sorted) const
{
	{
		keys(all_keys_sorted);//collect keys
		all_keys_sorted.sort();//sort keys
	}
}

//returns size of kv_list
template<typename K, typename V>
size_t ArrayListCollection<K,V>::size() const
{
	return kv_list.size();
}


#endif
