//----------------------------------------------------------------------
// FILE: linked_list_collection.h
// NAME: Wesley Muehlhausen
// DATE: 10 / 12 / 2020
// DESC: Key Value pair collection using Linked List implementation with add, remove, find
//range, sort, and size operations.
//----------------------------------------------------------------------

 
#ifndef LINKED_LIST_COLLECTION_H
#define LINKED_LIST_COLLECTION_H

#include "collection.h"
#include "linked_list.h"


template<typename K, typename V>
class LinkedListCollection : public Collection<K, V>
{

public:
    void add(const K& a_key, const V& a_val);//add
    void remove(const K& a_key);//remove given key
    bool find(const K& search_key, V& the_val) const;//find specific key
    void find(const K& k1, const K& k2, ArrayList<K>& keys) const;//find range of keys
    void keys(ArrayList<K>& all_keys) const;//gather all keys in list
    void sort(ArrayList<K>& all_keys_sorted) const;//sort keys using ArrayList quicksort 
    size_t size() const;//returns size of list

private:
    LinkedList<std::pair<K, V>> kv_list;//create list of kv pairs
};

//Add to the end
template<typename K, typename V>
void LinkedListCollection<K, V>::add(const K& a_key, const V& a_val)
{
  std::pair<K, V> p(a_key, a_val);
  kv_list.add(p);
}

//Delete node
template<typename K, typename V>
void LinkedListCollection<K, V>::remove(const K& a_key)
{
    for(int i = 0; i < kv_list.size(); ++i)
    {
        std::pair<K, V> p;
		kv_list.get(i, p); //same as using brackets
        if(p.first == a_key)
            kv_list.remove(i);
    }
}

//finds key and if found return true
template<typename K, typename V>
bool LinkedListCollection<K,V>::find(const K& search_key, V& the_val) const
{
    //case to make sure key is in the list
	for(int i = 0; i < kv_list.size(); ++i)
    {
        std::pair<K, V> p;
		kv_list.get(i, p); 
        if(p.first == search_key)
        {
            the_val = p.second;
            return true;
        }
    }
    return false;
}    

//Goes through and finds all keys in range
template<typename K, typename V>
void LinkedListCollection<K,V>::find(const K& k1, const K& k2, ArrayList<K>& keys) const
{
    for(int i = 0; i < kv_list.size(); ++i)//go through list
    {
        std::pair<K, V> p;
		kv_list.get(i, p); 
        if(p.first >= k1 && p.first <= k2)//if in range, add
            keys.add(p.first);
    }
}

//goes through and gathers all keys
template<typename K, typename V>
void LinkedListCollection<K,V>::keys(ArrayList<K>& all_keys) const
{
    for(int i = 0; i < kv_list.size(); ++i)
    {
        std::pair<K, V> p;
		kv_list.get(i, p); //get the pair and add
        all_keys.add(p.first);
    }
}

//gathers keys and then sorts using arraylist quicksort
template<typename K, typename V>
void LinkedListCollection<K,V>::sort(ArrayList<K>& all_keys_sorted) const
{
    keys(all_keys_sorted);
	all_keys_sorted.sort();
}

//Returns size of list
template<typename K, typename V>
size_t LinkedListCollection<K,V>::size() const
{
	return kv_list.size();
}


#endif
