//----------------------------------------------------------------------
// FILE: bst_collection.h
// NAME: Wesley Muehlhausen
// DATE: 10 / 12 / 2020
// DESC: Implements add, remove, find, sort, keys, size functions with use of hash tables
//----------------------------------------------------------------------

 
#ifndef BST_COLLECTION_H
#define BST_COLLECTION_H

#include "collection.h"
#include "array_list.h"

template<typename K, typename V>
class BSTCollection : public Collection<K,V>
{

public://Public functions
	BSTCollection();//create an empty tree
  	BSTCollection(const BSTCollection<K, V>& rhs);//copy constructor
  	~BSTCollection();//destructor
  	BSTCollection& operator=(const BSTCollection<K, V>& rhs);//assignment operator
    void add(const K& a_key, const V& a_val);//add KV Pair to tree
    void remove(const K& a_key);//remove KV pair to tree
    bool find(const K& search_key, V& the_val) const; //find KV pair in tree and return success condition
    void find(const K& k1, const K& k2, ArrayList<K>& keys) const;//Find Range of values in tree from k1 to k2
    void keys(ArrayList<K>& all_keys) const;//Return all keys in collection
    void sort(ArrayList<K>& all_keys_sorted) const;//sort all keys 
    size_t size() const;//return size of tree
	size_t height() const;//returns height of BST
	void print();

private:
	//the chain of linked list nodes
	struct Node {
		K key;
		V value;
		Node* left;
		Node* right;
	};

	//private member variables
	Node* root;//root node of the tree
	size_t node_count;//collection size: number of kv pairs stored in collection	
	
	//private member functions
	void make_empty(Node* subtree_root);// remove all elements in the bst
    void copy(Node* lhs_subtree_root, const Node* rhs_subtree_root);//copy helper
	Node* remove(Node* subtree_root, const K& a_key);//remove helper
	void find(const Node* subtree_root, const K& k1, const K& k2, ArrayList<K>& keys) const;// helper to recursively build up key list
	void keys(const Node* subtree_root, ArrayList<K>& all_keys) const;// helper to recursively build sorted list of keys
	size_t height(const Node* subtree_root) const;// helper to recursively find height of the tree
	void print(const Node* subtree_root, int level); 

};

//Constructor
template<typename K, typename V>
BSTCollection<K, V>::BSTCollection()
{
  root = nullptr;
  node_count = 0;
}

//Destructor. Defers to make_empty() helper function
template<typename K, typename V>
BSTCollection<K, V>::~BSTCollection()
{
	
	make_empty(root);
}

//Copy Constructor. Defers to copy function
template<typename K, typename V>
BSTCollection<K, V>::BSTCollection(const BSTCollection<K, V>& rhs)
{
	root = nullptr;
	node_count = 0;
	copy(root, rhs.root);
}

//Assignment operator. Defers to make_empty() function to clear, then copies contents over if not same
template<typename K, typename V>
BSTCollection<K, V>& BSTCollection<K, V>::operator=(const BSTCollection<K, V>& rhs)
{
  if(this == &rhs)
	return *this;
	
	make_empty(root); //delete the current list
	root = nullptr;
	copy(root, rhs.root);
	
  return *this;
}

//remove all elements in the bst. Uses recursion
template<typename K, typename V>
void BSTCollection<K,V>::make_empty(Node* subtree_root)
{
	if(!subtree_root)
		return;
	make_empty(subtree_root->left);//go left
	make_empty(subtree_root->right);//go right
	//delete
	delete subtree_root;
	subtree_root = nullptr;
	--node_count;
}


//Copy helper. Recursively goes through rhs tree and adds to lhs tree using add
template<typename K, typename V>
void BSTCollection<K,V>::copy(Node* lhs_subtree_root, const Node* rhs_subtree_root)
{
	if(rhs_subtree_root == nullptr)//if the source is empty
		return;
	add(rhs_subtree_root->key, rhs_subtree_root->value);//add
	if(rhs_subtree_root->left)//go left on rhs only
		copy(lhs_subtree_root, rhs_subtree_root->left);
	if(rhs_subtree_root->right)//go right on rhs only
		copy(lhs_subtree_root, rhs_subtree_root->right);
}

//Print helper function
template<typename K, typename V>
void BSTCollection<K, V>::print()
{
	std::cout << "PRINTED:   (Size: " << size() << ")"<< std::endl;	
   print(root, 0);
}

//Add function
template<typename K, typename V>
void BSTCollection<K, V>::add(const K& a_key, const V& a_val)
{
   //Create a temporary copy node
   Node* copy = new Node; 
   copy->key = a_key;
   copy->value = a_val;
   copy->left = nullptr;
   copy->right = nullptr;
   
   //Condition: completely empty
   if(!root)
   {
	   root = copy;
	   ++node_count;
	   copy = nullptr;
	   return;
   }
   
   //Condition: If only root node
   if(!root->left && !root->right)
   {
		if(a_key > root->key)
			root->right = copy; //put copy node in left 
		else		
			root->left = copy; //put copy node in left 	
		++node_count;
		copy = nullptr;
		return;
   }
   
   //For the rest of the add conditions
   Node* locator = root;//create a pointer for finding where to add
   while(root->right || root->left)//while there is somewhere to go still
   {
	   if(a_key <= locator->key)//if key is less than current node
		{
			if(locator->left)//if there is a node already there, go there and loop again
				locator = locator->left;
			else
			{
				locator->left = copy; //put copy node in left position
				++node_count;
				copy = nullptr;
				locator = nullptr;
				return;
			}
		}
		else//if key is less than current node
		{
			if(locator->right)//if there is a node already there, go there and loop again
				locator = locator->right;
			else
			{
				locator->right = copy; //put copy node in right position 
				++node_count;
				copy = nullptr;
				locator = nullptr;
				return;
			}
		}	
   }
}

//Iteratively searches through the tree top down for key. Changes reference the_val if found
template<typename K, typename V>
bool BSTCollection<K,V>::find(const K& search_key, V& the_val) const
{
	Node* traverse = root;
	while(traverse)//while there is a node here
	{
		if(search_key == traverse->key)//found the key
		{
			the_val = traverse->value;//set val
			return true;
		}
		else if(search_key < traverse->key)//go left
			traverse = traverse->left;
		else
			traverse = traverse->right;//go right
	}
	return false;
}    

//Find RANGE. Calls find range helper function
template<typename K, typename V>
void BSTCollection<K,V>::find(const K& k1, const K& k2, ArrayList<K>& keys) const
{
	find(root, k1, k2, keys);
}

//Keys calls keys helper function
template<typename K, typename V>
void BSTCollection<K,V>::keys(ArrayList<K>& all_keys) const
{
	keys(root, all_keys);
}

//Sort function. Defers to keys helper because tree is already sorted
template<typename K, typename V>
void BSTCollection<K,V>::sort(ArrayList<K>& all_keys_sorted) const
{
	keys(root, all_keys_sorted);
}

//Size, returns the number of nodes in the tree
template<typename K, typename V>
size_t BSTCollection<K,V>::size() const
{
	return node_count;
}

//Returns the height of the tree. Uses height helper function
template<typename K, typename V>
size_t BSTCollection<K,V>::height() const
{
	return height(root);
}

//PRIVATE HELPER FUNCTIONS



template<typename K, typename V>
void BSTCollection<K, V>::remove(const K& a_key)
{
	if(node_count > 0)
	{
		if(root->key == a_key)
			root = remove(root, a_key);
		else
			remove(root, a_key);
	}

}

//remove helper. Recursively goes through the tree to find Node to remove
//Removes with condition of adjusting the tree so its still in order.
template<typename K, typename V>
typename BSTCollection<K,V>::Node*
BSTCollection<K,V>::remove(Node* subtree_root, const K& a_key)
{
	 if(subtree_root && a_key < subtree_root->key)//go left
	 	subtree_root->left = remove(subtree_root->left, a_key);

	 else if(subtree_root && a_key > subtree_root->key)//go right
	 	subtree_root->right = remove(subtree_root->right, a_key);

	 else if(subtree_root && subtree_root->key == a_key)//if found
	 {
	 	//if leaf node
	 	if(!subtree_root->left && !subtree_root->right)
	 	{
	 		delete subtree_root;
	 		subtree_root = nullptr;
	 		--node_count;
	 	}
	 	//if left is missing
	 	else if(!subtree_root->left && subtree_root->right)
	 	{
	 		Node* temp = subtree_root->right;
	 		delete subtree_root;
	 		subtree_root = temp;
	 		--node_count;
	 		temp = nullptr;
	 	}
	 	//if right is missing
	 	else if(subtree_root->left && !subtree_root->right)
	 	{
	 		Node* temp = subtree_root->left;
	 		delete subtree_root;
	 		subtree_root = temp;
	 		--node_count;
	 		temp = nullptr;
	 	}
	 	//if two children
	 	else if(subtree_root->left && subtree_root->right)
	 	{
	 		Node* replace = subtree_root->right; 
	 	    //condition: if right child doenst have a left child, its the in order successor	
	 		if(!replace->left)
	 		{
	 			subtree_root->key = replace->key;
	 			subtree_root->value = replace->value;
	 			subtree_root->right = replace->right;
	 			delete replace;
	 			replace = nullptr;
	 			--node_count;
	 		}
	 		else//for two children and right child has left child
	 		{
	 			while(replace->left != nullptr)
	 				replace = replace->left;
	 			K tKey = replace->key;
	 			V tVal = replace->value;
	 			remove(root, replace->key);
	 			subtree_root->key = tKey;
	 			subtree_root->value = tVal;
	 		}
	 	}
	 	
	 }
	 return subtree_root;
}

// helper to recursively build up key list
template<typename K, typename V>
void BSTCollection<K,V>::find(const Node* subtree_root, const K& k1, const K& k2, ArrayList<K>& keys) const
{
	if(!subtree_root)//if no node, return
		return;
	if(k1 < subtree_root->key)//go left if can
		find(subtree_root->left, k1, k2, keys);
	if(k1 <= subtree_root->key && subtree_root->key <= k2)
		keys.add(subtree_root->key);//if in range, add
	if(k2 > subtree_root->key)//go right if can
		find(subtree_root->right, k1, k2, keys);
}

// helper to recursively build sorted list of keys
template<typename K, typename V>
void BSTCollection<K,V>::keys(const Node* subtree_root, ArrayList<K>& all_keys) const
{
	if(!subtree_root)//if leaf node, return
		return;
	keys(subtree_root->left, all_keys);//go all the way left
	all_keys.add(subtree_root->key);//add this root key
//	std::cout << subtree_root->key << std::endl;
	keys(subtree_root->right, all_keys);
}

//helper function used to print the tree recursively
template<typename K, typename V>
void BSTCollection<K,V>::print(const Node* subtree_root, int level) 
{
	if(!subtree_root)//if leaf node, return
		return;
	++level;
	std::cout << "Level " << level << " " << subtree_root->key << std::endl;
 	print(subtree_root->left, level);//go all the way left
 	print(subtree_root->right, level);
 }

// helper to recursively find height of the tree
template<typename K, typename V>
size_t BSTCollection<K,V>::height(const Node* subtree_root) const
{
	if(!subtree_root)//if null, height is zero
		return 0;
	int num1 = 1 + height(subtree_root->left);//go down recursively, add 1 each level
	int num2 = 1 + height(subtree_root->right);
	if(num1 > num2)//find and return the largest
		return num1;
	else
		return num2;
	
}

#endif
