//----------------------------------------------------------------------
// FILE: bst_collection.h
// NAME: Wesley Muehlhausen
// DATE: 12 / 1 / 2020
// DESC: Implements add, remove, find, sort, keys, size functions using AVL tree
//----------------------------------------------------------------------

 
#ifndef AVL_COLLECTION_H
#define AVL_COLLECTION_H

#include "collection.h"
#include "array_list.h"

template<typename K, typename V>
class AVLCollection : public Collection<K,V>
{
//public functions
public:
	AVLCollection();//create an empty tree
  	AVLCollection(const AVLCollection<K, V>& rhs);//copy constructor
  	~AVLCollection();//destructor
  	AVLCollection& operator=(const AVLCollection<K, V>& rhs);//assignment operator
    void add(const K& a_key, const V& a_val);//add KV Pair to tree
    void remove(const K& a_key);//remove KV pair to tree
    bool find(const K& search_key, V& the_val) const; //find KV pair in tree and return success condition
    void find(const K& k1, const K& k2, ArrayList<K>& keys) const;//Find Range of values in tree from k1 to k2
    void keys(ArrayList<K>& all_keys) const;//Return all keys in collection
    void sort(ArrayList<K>& all_keys_sorted) const;//sort all keys 
    size_t size() const;//return size of tree
	int height() const;//returns height of BST
	void print();

private:
	//the tree of kv pairs. This time each node has a height
	struct Node {
		K key;
		V value;
		int height;
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
	void print_tree(std::string indent, const Node* subtree_root); 
	Node* add(Node* subtree_root, const K& a_key, const V& a_val);//add KV Pair to tree
	Node* rotate_right(Node* k2);//rotate right helper
	Node* rotate_left(Node* k2);//rotate left helper
	Node* rebalance(Node* k2);//rotate right helper

};

//Print function used to call private helper print
template<typename K, typename V>
void AVLCollection<K, V>::print()
{
  print_tree("", root);
}

//Constructor
template<typename K, typename V>
AVLCollection<K, V>::AVLCollection()
{
  root = nullptr;
  node_count = 0;
}

//Destructor - defers to make_empty()
template<typename K, typename V>
AVLCollection<K, V>::~AVLCollection()
{
	
	make_empty(root);
}

//Copy Constructor - defers to copy() - copies rhs
template<typename K, typename V>
AVLCollection<K, V>::AVLCollection(const AVLCollection<K, V>& rhs)
{
	root = nullptr;
	node_count = 0;
	copy(root, rhs.root);
}

//Assignment operator - clears using make_empty() and copy() helpers
template<typename K, typename V>
AVLCollection<K, V>& AVLCollection<K, V>::operator=(const AVLCollection<K, V>& rhs)
{
  if(this == &rhs)//if same list
	return *this;
	
	make_empty(root); //delete the current list
	root = nullptr; //set root
	copy(root, rhs.root); //copy contents from rhs over
	
  return *this;
}

//remove all elements in the AVL recursively
template<typename K, typename V>
void AVLCollection<K,V>::make_empty(Node* subtree_root)
{
	if(!subtree_root)//if nullptr, done
		return;
	make_empty(subtree_root->left);//go left
	make_empty(subtree_root->right);//go right
	//Delete node
	delete subtree_root;
	subtree_root = nullptr;
	--node_count;
}


//copy helper uses recursion going top down
template<typename K, typename V>
void AVLCollection<K,V>::copy(Node* lhs_subtree_root, const Node* rhs_subtree_root)
{
	if(rhs_subtree_root == nullptr)//if the source is empty
		return;
	add(rhs_subtree_root->key, rhs_subtree_root->value);//add
	if(rhs_subtree_root->left)
		copy(lhs_subtree_root, rhs_subtree_root->left);//go left
	if(rhs_subtree_root->right)
		copy(lhs_subtree_root, rhs_subtree_root->right);//go right
}

//Add function that uses add helper
template<typename K, typename V>
void AVLCollection<K, V>::add(const K& a_key, const V& a_val)
{
	root = add(root, a_key, a_val);
}


//Add private member function uses recursion. Finds node, adds, then calls rebalance 
template<typename K, typename V>
typename AVLCollection<K,V>::Node*
AVLCollection<K,V>::add(Node* subtree_root, const K& a_key, const V& a_val)
{
   //If adding to empty tree or at the bottom of the tree where it should be added…
    if(!subtree_root)
    {
   		Node* copy = new Node; 
   		copy->key = a_key;
   		copy->value = a_val;
   		copy->height = 1;
   		copy->left = nullptr;
   		copy->right = nullptr;
   		subtree_root = copy;
   		++node_count;
   		copy = nullptr;
    }
    //When traversing to the tree
	else
	{
		//going left
		if(a_key < subtree_root->key)
			subtree_root->left = add(subtree_root->left, a_key, a_val);
		else//going right
			subtree_root->right = add(subtree_root->right, a_key, a_val);
		//set heights
		int greater;
		if(subtree_root->left && subtree_root->right)//for if there are two children
		{
			if(subtree_root->left->height > subtree_root->right->height)//left greater
				greater = subtree_root->left->height;
			else//right greater
				greater = subtree_root->right->height;
		}
		else if(subtree_root->left && !subtree_root->right)//if only left child
				greater = subtree_root->left->height;
		else if(!subtree_root->left && subtree_root->right)//if only right child
				greater = subtree_root->right->height;
		subtree_root->height = greater + 1;//one above greatest value
	}
	return rebalance(subtree_root);//rebalance at end always
}



//Find function (iterative)
template<typename K, typename V>
bool AVLCollection<K,V>::find(const K& search_key, V& the_val) const
{
	Node* traverse = root;
	while(traverse)//while there is a node here
	{
		if(search_key == traverse->key)//found the key
		{
			the_val = traverse->value;
			return true;
		}
		else if(search_key < traverse->key)//if less, go left
			traverse = traverse->left;
		else
			traverse = traverse->right;//if greater, go right
	}
	return false;//if not found
}    
 
//Returns size of tree, aka the number of nodes
template<typename K, typename V>
size_t AVLCollection<K,V>::size() const
{
	return node_count;
}

//Returns the height of the tree
template<typename K, typename V>
int AVLCollection<K,V>::height() const
{
	if(!root)
		return 0;
	return root->height;
}

//Remove, calls remove helper function
template<typename K, typename V>
void AVLCollection<K, V>::remove(const K& a_key)
{
	if(node_count > 0)//if tree is not empty
	{
		if(root->key == a_key)//if removing the root
			root = remove(root, a_key);
		else
			remove(root, a_key);//else conditions
	}
}

//remove helper. Recursively goes through and finds the node to remove. Rebalances at the end
template<typename K, typename V>
typename AVLCollection<K,V>::Node*
AVLCollection<K,V>::remove(Node* subtree_root, const K& key)
{
	//Traversal steps: 
	if(subtree_root && key < subtree_root->key)//go left if less than
		subtree_root->left = remove(subtree_root->left, key);
	else if(subtree_root && key > subtree_root->key)//go right if greater than 
		subtree_root->right = remove(subtree_root->right, key);
	else if(subtree_root && key == subtree_root->key)//if equal to: 
	{	
		//if node is a child node
	    if(!subtree_root->right && !subtree_root->left)
		{
			delete subtree_root;
			subtree_root = nullptr;
			--node_count;
		}
		//if node has right child
		else if(subtree_root->right && !subtree_root->left)
		{
			Node* tmp = subtree_root->right;
			delete subtree_root;
			subtree_root = tmp;
			--node_count;
			tmp = nullptr;
		}
		//if node has left child
		else if(!subtree_root->right && subtree_root->left)
		{
			Node* tmp = subtree_root->left;
			delete subtree_root;
			subtree_root = tmp;
			--node_count;
			tmp = nullptr;
		}
		//if node has two children
		else if(subtree_root->left && subtree_root->right)
		{
			Node* searchNode = subtree_root->right;
			if(!searchNode->left)//if right child has no left
			{
				subtree_root->key = searchNode->key;
	 			subtree_root->value = searchNode->value;
	 			subtree_root->right = searchNode->right;
	 			delete searchNode;
	 			searchNode = nullptr;
	 			--node_count;	
			}			
			else//else, go right and all the way left to find in order successor
			{
				while(searchNode->left)
					searchNode = searchNode->left;//find in order successor
				subtree_root->key = searchNode->key;
				subtree_root->value = searchNode->value;
				subtree_root->right = remove(subtree_root->right, subtree_root->key);
			}
		}
		//if subtree is null, return
		if(!subtree_root)
			return subtree_root;
	}
	//set the height
	int largest = 0;
	if(subtree_root->left && subtree_root->right)//if there are two subtrees
	{
		if(subtree_root->left->height > subtree_root->right->height)
			largest = subtree_root->left->height;
		else
			largest = subtree_root->right->height;
	}
	else if(subtree_root->left && !subtree_root->right)//if only left subree
		largest = subtree_root->left->height;
	else if(!subtree_root->left && subtree_root->right)//if only right subree
		largest = subtree_root->right->height;
	//set root height and rebalance
	subtree_root->height = largest + 1;
	return rebalance(subtree_root);
}

//Find RANGE, calls the recursive helper function
template<typename K, typename V>
void AVLCollection<K,V>::find(const K& k1, const K& k2, ArrayList<K>& keys) const
{
	find(root, k1, k2, keys);
}

//Find Range helper to recursively build up key list
template<typename K, typename V>
void AVLCollection<K,V>::find(const Node* subtree_root, const K& k1, const K& k2, ArrayList<K>& keys) const
{
	if(!subtree_root)//if nullptr, done
		return;
		find(subtree_root->left, k1, k2, keys);//go left
	if(k1 <= subtree_root->key && subtree_root->key <= k2)
		keys.add(subtree_root->key);//if in range, add to list
		find(subtree_root->right, k1, k2, keys);//go right
}

//Keys used to gather all keys from tree
template<typename K, typename V>
void AVLCollection<K,V>::keys(ArrayList<K>& all_keys) const
{
	keys(root, all_keys);
}

//Sort (defers to keys because already sorted)
template<typename K, typename V>
void AVLCollection<K,V>::sort(ArrayList<K>& all_keys_sorted) const
{
	keys(root, all_keys_sorted);
}

// helper to recursively build sorted list of keys
template<typename K, typename V>
void AVLCollection<K,V>::keys(const Node* subtree_root, ArrayList<K>& all_keys) const
{
	if(!subtree_root)//if leaf node, return
		return;
	keys(subtree_root->left, all_keys);//go all the way left
	all_keys.add(subtree_root->key);//add this root key
	keys(subtree_root->right, all_keys);//go right
}

//helper to print the tree for testing
template<typename K, typename V>
void AVLCollection<K,V>::print_tree(std::string indent, const Node* subtree_root) 
{
	if(!subtree_root)//if leaf node, return
		return;
	std::cout << indent << subtree_root->key << " (h=" 
			  << subtree_root->height << ")" << std::endl;
 	print_tree(indent + "  ", subtree_root->left);//go all the way left
 	print_tree(indent + "  ", subtree_root->right);
 }

//rotate right of given node
template<typename K, typename V>
typename AVLCollection<K,V>::Node*
AVLCollection<K,V>::rotate_right(Node* k2)
{
	Node* k1 = k2->left;
	k2->left = k1->right;
	k1->right = k2;
	return k1;
}

//rotate left of given node
template<typename K, typename V>
typename AVLCollection<K,V>::Node*
AVLCollection<K,V>::rotate_left(Node* k2)
{
	Node* k1 = k2->right;
	k2->right = k1->left;
	k1->left = k2;
	return k1;
}

//Rebalance helper function to keep the height of the list minimal
template<typename K, typename V>
typename AVLCollection<K,V>::Node*
AVLCollection<K,V>::rebalance(Node* subtree_root)
{
	//if empty, return root
	if(!subtree_root)
		return subtree_root;
	Node* leftptr = subtree_root->left;
	Node* rightptr = subtree_root->right;
	int balance;
	
	//if parent with two childs
	if(leftptr && rightptr)
		balance = leftptr->height - rightptr->height;
	
	//if left child and NO right child and left child height is greater than 1
	if(leftptr && !rightptr && leftptr->height > 1)
	{
		int bal2 = 0;
		if(leftptr->left && leftptr->right)//for two childs
			bal2 = leftptr->left->height - leftptr->right->height;
		else if(!leftptr->left && leftptr->right)//for no left child
			bal2 = 0 - leftptr->right->height;
		//if balance factor less than -1, rotate left
		if(bal2 <= -1)
		{
			subtree_root->left = rotate_left(subtree_root->left);
			--subtree_root->left->left->height;
			++subtree_root->left->height;
		}
		subtree_root = rotate_right(subtree_root);
		int greater;
		//fix heights
		leftptr = subtree_root->left;
		rightptr = subtree_root->right;
		rightptr->height = 1;
		if(rightptr->height > leftptr->height)
			greater = rightptr->height;
		else
			greater = leftptr->height;
		subtree_root->height = greater + 1;	
	}
	
	//if left child and NO right child and left child height is greater than 1
	else if(!leftptr && rightptr && rightptr->height > 1)
	{
		int bal2 = 0;
		if(rightptr->left && rightptr->right)//for two childs
			bal2 = rightptr->left->height - rightptr->right->height;
		else if(rightptr->left && !rightptr->right)//for no left child
			bal2 = rightptr->left->height;
		//if balance factor less than -1, rotate left
		if(bal2 >= 1)
		{
			subtree_root->right = rotate_right(subtree_root->right);
			--subtree_root->right->right->height;
			++subtree_root->right->height;
		}
		subtree_root = rotate_left(subtree_root);
		int greater;
		//fix heights
		leftptr = subtree_root->left;
		rightptr = subtree_root->right;
		leftptr->height = 1;
		if(rightptr->height > leftptr->height)
			greater = rightptr->height;
		else
			greater = leftptr->height;
		subtree_root->height = greater + 1;	
	}
	//if left and right, LEFT is heavy
	else if(leftptr && rightptr && balance > 1)
	{
		//Set second balance factor
		int bal2 = 0;
		if(leftptr->left && leftptr->right)//BAL factor if left and right children
			bal2 = leftptr->left->height - leftptr->right->height;
		else if(!leftptr->left && leftptr->right)//BAL factor if only right
			bal2 = 0 - leftptr->right->height;
		
		//Rotate left subtree, adjust heights
		if(bal2 <= -1)
		{
			subtree_root->left = rotate_left(subtree_root->left);
			--subtree_root->left->left->height;
			++subtree_root->left->height;
		}
		
		//rotate subtree right and adjust pointers
		subtree_root = rotate_right(subtree_root);
		leftptr = subtree_root->left;
		rightptr = subtree_root->right;
		
		//Find which height L/R of rightptr is greatest and set heights
		int greater;
		if(rightptr->left && rightptr->right)//for if there are two children
		{
			if(rightptr->left->height > rightptr->right->height)//left greater
				greater = rightptr->left->height;
			else//right greater
				greater = rightptr->right->height;
		}
		else if(rightptr->left && !rightptr->right)//if only left child
				greater = rightptr->left->height;
		else if(!rightptr->left && rightptr->right)//if only right child
				greater = rightptr->right->height;
		rightptr->height = greater + 1;//one above greatest value
		
		//Find if subtree root L/R is greater, then set height
		if(rightptr->height > leftptr->height)
			greater = rightptr->height;
		else
			greater = leftptr->height;
		subtree_root->height = greater + 1;
	}
	//if left and right, RIGHT is heavy
	else if(leftptr && rightptr && balance < -1)
	{
		//Set second balance factor
		int bal2 = 0;
		if(rightptr->left && rightptr->right)//BAL factor if left and right children
			bal2 = rightptr->left->height - rightptr->right->height;
		else if(rightptr->left && !rightptr->right)//BAL factor if only left
			bal2 = rightptr->left->height;
		
		//Rotate right subtree, adjust heights
		if(bal2 >= 1)
		{
			subtree_root->right = rotate_right(subtree_root->right);
			--subtree_root->right->right->height;
			++subtree_root->right->height;
		}
		
		//rotate subtree left and adjust pointers
		subtree_root = rotate_left(subtree_root);
		leftptr = subtree_root->left;
		rightptr = subtree_root->right;
		
		//Find which height L/R of rightptr is greatest and set heights
		int greater;
		if(leftptr->left && leftptr->right)//for if there are two children
		{
			if(leftptr->left->height > leftptr->right->height)//left greater
				greater = leftptr->left->height;
			else//right greater
				greater = leftptr->right->height;
		}
		else if(leftptr->left && !leftptr->right)//if only left child
				greater = leftptr->left->height;
		else if(!leftptr->left && leftptr->right)//if only right child
				greater = leftptr->right->height;
		leftptr->height = greater + 1;//one above greatest value
		
		//Find if subtree root L/R is greater, then set height
		if(rightptr->height > leftptr->height)
			greater = rightptr->height;
		else
			greater = leftptr->height;
		subtree_root->height = greater + 1;		
	}
	return subtree_root;
	
}

#endif
