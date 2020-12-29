//----------------------------------------------------------------------
// Name: Wesley Muehlhausen
// File: rbt_collection.h
// Date: Fall, 2020
// Desc: A Key-Value Collection implementation using a Red-Black tree.
//----------------------------------------------------------------------


#ifndef RBT_COLLECTION_H
#define RBT_COLLECTION_H


#include "string.h"
#include "collection.h"
#include "array_list.h"


template<typename K, typename V>
class RBTCollection : public Collection<K,V>
{
public:

  // create an empty collection
  RBTCollection();
  
  // copy constructor
  RBTCollection(const RBTCollection<K,V>& rhs);

  // assignment operator
  RBTCollection<K,V>& operator=(const RBTCollection<K,V>& rhs);

  // delete collection
  ~RBTCollection();
  
  // add a new key-value pair into the collection 
  void add(const K& a_key, const V& a_val);

  // remove a key-value pair from the collectiona
  void remove(const K& a_key);

  // find and return the value associated with the key
  bool find(const K& search_key, V& the_val) const;

  // find and return each key >= k1 and <= k2 
  void find(const K& k1, const K& k2, ArrayList<K>& keys) const;
  
  // return all of the keys in the collection 
  void keys(ArrayList<K>& all_keys) const;

  // return all of the keys in ascending (sorted) order
  void sort(ArrayList<K>& all_keys_sorted) const;

  // return the number of key-value pairs in the collection
  size_t size() const;

  // return the height of the tree
  int height() const;

  // for testing:

  // check if tree satisfies the red-black tree constraints
  bool valid_rbt() const;
  
  // pretty-print the red-black tree (with heights)
  void print() const;

  
private:
  
  // RBT node structure
  enum color_t {RED, BLACK};
  struct Node {
    K key;
    V value;
    Node* left;
    Node* right;
    Node* parent;
    color_t color;
  };

  // root node
  Node* root;

  // number of k-v pairs stored in the collection
  size_t node_count;

  // helper to empty entire hash table
  void make_empty(Node* subtree_root);

  // copy helper
  void copy(Node* lhs_subtree_root, const Node* rhs_subtree_root); 
    
  // helper to recursively find range of keys
  void find(const Node* subtree_root, const K& k1, const K& k2,
            ArrayList<K>& keys) const;

  // helper to build sorted list of keys (used by keys and sort)
  void keys(const Node* subtree_root, ArrayList<K>& all_keys) const;

  // rotate right helper
  void rotate_right(Node* k2);

  // rotate left helper
  void rotate_left(Node* k2);

  // restore red-black constraints in add
  void add_rebalance(Node* x);

  // restore red-black constraints in remove
  void remove_rebalance(Node* x, bool going_right);
  
  // height helper
  size_t height(Node* subtree_root) const;
 
  
  
  // ------------
  // for testing:
  // ------------
  
  // validate helper
  bool valid_rbt(Node* subtree_root) const;

  // validate helper
  size_t black_node_height(Node* subtree_root) const;
  
  // recursive pretty-print helper
  void print_tree(std::string indent, Node* subtree_root) const;
};


  // create an empty collection
template<typename K, typename V>
RBTCollection<K, V>::RBTCollection()
{
  root = nullptr;
  node_count = 0;
}
  
// copy constructor
template<typename K, typename V>
RBTCollection<K, V>::RBTCollection(const RBTCollection<K, V>& rhs)
{
	root = nullptr;
	node_count = 0;
	//copy(root, rhs.root);
	*this = rhs;
}

//Assignment operator - clears using make_empty() and copy() helpers
template<typename K, typename V>
RBTCollection<K, V>& RBTCollection<K, V>::operator=(const RBTCollection<K, V>& rhs)
{
  if(this == &rhs)//if same list
	return *this;
	
	make_empty(root); //delete the current list
	root = nullptr; //set root
	node_count = rhs.node_count;
	
	if(rhs.root != nullptr)
	{
		//create a root node copy then ensue the copying method
		Node* root_node = new Node;
		root_node->left = nullptr;
		root_node->right = nullptr;
		root_node->color = rhs.root->color;
		root_node->key = rhs.root->key;
		root_node->value = rhs.root->value;
		root_node->parent = rhs.root->parent;
		root = root_node;
		copy(root, rhs.root); //copy contents from rhs over
	}

  return *this;
}

//Destructor - defers to make_empty()
template<typename K, typename V>
RBTCollection<K, V>::~RBTCollection()
{
	make_empty(root);
}

// find and return the value associated with the key
template<typename K, typename V>
bool RBTCollection<K,V>::find(const K& search_key, V& the_val) const
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

template<typename K, typename V>
void RBTCollection<K,V>::find(const K& k1, const K& k2, ArrayList<K>& keys) const
{
	find(root, k1, k2, keys);
}
  
//Keys used to gather all keys from tree
template<typename K, typename V>
void RBTCollection<K,V>::keys(ArrayList<K>& all_keys) const
{
	keys(root, all_keys);
}

//Sort (defers to keys because already sorted)
template<typename K, typename V>
void RBTCollection<K,V>::sort(ArrayList<K>& all_keys_sorted) const
{
	keys(root, all_keys_sorted);
}

//Returns size of tree, aka the number of nodes
template<typename K, typename V>
size_t RBTCollection<K,V>::size() const
{
	return node_count;
}
  
//Returns the height of the tree int height() const;
template<typename K, typename V>
int RBTCollection<K,V>::height() const
{
	if(!root)
		return 0;
	int tmp = height(root);
	return tmp;
} 
  

  // for testing:

//remove all elements in the AVL recursively
template<typename K, typename V>
void RBTCollection<K,V>::make_empty(Node* subtree_root)
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
void RBTCollection<K,V>::copy(Node* lhs_subtree_root, const Node* rhs_subtree_root)
{
	//if node doens't exist
	if(rhs_subtree_root == nullptr)//if the source is empty
		return;
	
	//if node exists and left child
	if(rhs_subtree_root->left)
	{
		Node* t = new Node;
		t->left = nullptr;
		t->right = nullptr;
		t->parent = lhs_subtree_root;
		t->key = rhs_subtree_root->left->key;
		t->value = rhs_subtree_root->left->value;
		t->color = rhs_subtree_root->left->color;
		lhs_subtree_root->left = t;
		copy(lhs_subtree_root->left, rhs_subtree_root->left);
	}
	//if node exists and right child
	if(rhs_subtree_root->right)
	{
		Node* t = new Node;
		t->left = nullptr;
		t->right = nullptr;
		t->parent = lhs_subtree_root;
		t->key = rhs_subtree_root->right->key;
		t->value = rhs_subtree_root->right->value;
		t->color = rhs_subtree_root->right->color;
		lhs_subtree_root->right = t;
		copy(lhs_subtree_root->right, rhs_subtree_root->right);
	}
}
    
//Find Range helper to recursively build up key list
template<typename K, typename V>
void RBTCollection<K,V>::find(const Node* subtree_root, const K& k1, const K& k2, ArrayList<K>& keys) const
{
	if(!subtree_root)//if nullptr, done
		return;
		find(subtree_root->left, k1, k2, keys);//go left
	if(k1 <= subtree_root->key && subtree_root->key <= k2)
		keys.add(subtree_root->key);//if in range, add to list
		find(subtree_root->right, k1, k2, keys);//go right
}

// helper to recursively build sorted list of keys
template<typename K, typename V>
void RBTCollection<K,V>::keys(const Node* subtree_root, ArrayList<K>& all_keys) const
{
	if(!subtree_root)//if leaf node, return
		return;
	keys(subtree_root->left, all_keys);//go all the way left
	all_keys.add(subtree_root->key);//add this root key
	keys(subtree_root->right, all_keys);//go right
}

//rotate right of given node
template<typename K, typename V>
void RBTCollection<K,V>::rotate_right(Node* k2)
{
	Node* k1 = k2->left;
	k2->left = k1->right;
	if(k2->left != nullptr)
		k2->left->parent = k2;
	k1->parent = k2->parent;
	//determine if k2 is parent's left or right child
	if(k2->parent == nullptr)//means k2 is the root
		root = k1;	
	else if(k2->parent->left == k2)
		k2->parent->left = k1;
	else
		k2->parent->right = k1;
	
	k1->right = k2;
	k2->parent = k1;
}

//rotate left of given node
template<typename K, typename V>
void RBTCollection<K,V>::rotate_left(Node* k2)
{
	Node* k1 = k2->right;
	k2->right = k1->left;
	if(k2->right != nullptr)
		k2->right->parent = k2;
	k1->parent = k2->parent;
	//determine if k2 is parent's left or right child
	if(k2->parent == nullptr)//means k2 is the root
		root = k1;	
	else if(k2->parent->left == k2)
		k2->parent->left = k1;
	else
		k2->parent->right = k1;
	k1->left = k2;
	k2->parent = k1;
}
 
//Add function that uses add helper
template<typename K, typename V>
void RBTCollection<K, V>::add(const K& a_key, const V& a_val)
{
	//std::cout << "Adding: " << a_key << std::endl;
	//create new node with kv	
	Node* n = new Node;
	n->key = a_key;
	n->value = a_val;
	n->color = RED;//Always give the insertion node color red	
	n->left = nullptr;
	n->right = nullptr;
	n->parent = nullptr;
	Node* x = root;//current node being traversed
	Node* p = nullptr;//parent of x
	//std::cout << "1" << a_key << std::endl;
	//iteratively find the insertion point
	while(x != nullptr)
	{
		add_rebalance(x);
		p = x;
		if(a_key < x->key)//if less, go left
			x = x->left;
		else
			x = x->right;
	}
	//std::cout << "2" << a_key << std::endl;
	//Add new node
	if(root == nullptr && node_count == 0)//if inserting at root, just color black and done.
		root = n;	
	else if(a_key < p->key)//insert left
	{
		p->left = n;
		n->parent = p;
	}
	else//insert right
	{
		p->right = n;	
		n->parent = p;
	}
	//std::cout << "3" << a_key << std::endl;
	//rebalance last node and recolor
	add_rebalance(n);//rebalance n
	root->color = BLACK;//color root black
	++node_count;
	//std::cout << "Done adding: " << a_key << std::endl;
} 
 
// restore red-black constraints in add
template<typename K, typename V>
void RBTCollection<K,V>::add_rebalance(Node* x) 
{
	//if x is the root and the tree is empty, return
	if(x->parent == nullptr && node_count == 0)//for root node
		return;
	
	Node* p = x->parent;//set p as x's parent 	
	//std::cout << "z" << std::endl;
	//CASE 1: COLOR FLIP
	// if x is black, and x has two red children
	if(x->left && x->right)
	{
		if(x->color == BLACK && (x->left->color == RED && x->right->color == RED))
		{
			//std::cout << "!!!!!!!" << std::endl;
			//color flip
			x->color = RED;
			x->left->color = BLACK;
			x->right->color = BLACK;
		}
	}
	//std::cout << "y" << std::endl;
	//CASE 2/3 single and double rotation
	if(x->color == RED && (p && p->color == RED))//if x and x's parent is red, apply case 2 or 3
	{
		if(p->parent)//p exists, if gp exits
		{
			//std::cout << "@@@@@@@" << std::endl;
			//Sub Case 2: single rotation right at granparent
			if(x == p->left && p == p->parent->left)//if left left from grandparent
			{
				p->color = BLACK;//set parent to black
				p->parent->color = RED;//set grandfather to red
				rotate_right(p->parent);//rotate around grandfather
			}
			//Sub Case 2: single rotation left at granparent
			else if(x == p->right && p == p->parent->right)//if right right from grandparent
			{
				x->parent->color = BLACK;//set parent to black
				x->parent->parent->color = RED;//set grandfather to red
				rotate_left(x->parent->parent);//rotate around grandfather																		
			}
			//Sub Case 3: double rotation left then right
			else if(x == p->right && p == p->parent->left)//rotate left at p, then right at g
			{
				rotate_left(x->parent);
				rotate_right(x->parent);
				x->color = BLACK;//set colors
				x->right->color = RED;
			}
			//Sub Case 3: double rotation right then left
			else if(x == p->left && p == p->parent->right)//rotate left at p, then right at g
			{
				rotate_right(x->parent);
				rotate_left(x->parent);
				x->color = BLACK;//set colors
				x->left->color = RED;
			}
		}
	}	
}

//Remove
template<typename K, typename V>
void RBTCollection<K, V>::remove(const K& a_key)
{
	//Create a sentinal node pointing at root
	Node* sentinal = new Node;
	sentinal->left = nullptr;
	sentinal->right = root;
	sentinal->parent = nullptr;
	sentinal->color = RED;
	
	//make current and parent pointer
	bool found = false;
	Node* x = root;//cur
	Node* p = sentinal;//parent
	
	while (found != true && x != nullptr)//while on a node and node isn't the correct one, loop 
	{
		if (a_key < x->key)//if less than current key, go left
		{
			remove_rebalance(x,false);
			x = x->left;
		}
		else if (a_key > x->key)//if more than current key, go right 
		{
			remove_rebalance(x,true);//if more than current key, go right
			x = x->right;
		}
		else//key is found 
		{
		 	remove_rebalance(x,x->left);
		 	found = true;
		 	p = x->parent;//set the parent on the node above current
		}
	}
	
	//If at the end of list and didn't find, exit
	if(!found) 
		return;
		
	//MAIN Case: NOT TWO CHILDREN (1 or 0)	
	if (x->left == nullptr || x->right == nullptr) 
	{
		//Case: if removing root node
		if (x == root)
		{
			if (x->left)//node with left child and no right 		
				sentinal->right = x->left;
			else if (x->right)//node with right chil and no left 
				sentinal->right = x->right;
			else//single root node 
				sentinal->right = nullptr;
		}
		//Case: x is the left of its parent
		else if (x == p->left) 
		{
			sentinal->right = root;
			p->left = nullptr;
		}
		//Case: x is the right of its parent
		else 
		{
			sentinal->right = root;
			p->right = nullptr;
		}
		delete x;//delete x
	}
	//MAIN Case: TWO children
	else 
	{
		//Create a search node
		Node* traverse = x->right;
		remove_rebalance(traverse,false);
		
		//Find in order successor
		while (traverse->left != nullptr) 
		{
			traverse = traverse->left;
			remove_rebalance(traverse,false);
		}
		
		//Copy the value into node
		x->key = traverse->key;
		x->value = x->value;
		sentinal->right = root;//make sure the root is in the right spot still
		
		//Remove In Order Successor
		if(traverse->parent->key > traverse->key)//if parent's left
			traverse->parent->left = nullptr;
		else //if parent's right
			traverse->parent->right = nullptr;
		delete traverse;
	}
	
	root = sentinal->right;//set root
	if (root != nullptr) //set the color of the root to black always
		root->color = BLACK;
	delete sentinal;
	--node_count;

}
 
// restore red-black constraints in remove
template<typename K, typename V>
void RBTCollection<K,V>::remove_rebalance(Node* x, bool going_right) 
{

  if (x->color == RED)//if node is red, were done
    return;
    
  Node * p = x->parent;//parent node pointer
  Node * t = nullptr;//sibling node pointer
  
  if (!p)//if no parent, skip 
  	exit;
  else if (x->key < p->key)//if cur is parents left t is right 
	t = p->right;
  else //opposite case
	t = p->left;
 
  //MAIN CASE: x has two children
  if (x->right && x->left) 
  {
    //Check if x has 2 different colored children
	if (x->right->color != x->left->color) 
	{
		//case 1 situatiom where left child is red. set left as subtree root and color adjust
		if (going_right && x->left->color == RED) 
		{
	   		rotate_right(x);
	   		x->color = RED;
	   		x->parent->color = BLACK;
	   		x->right->color = BLACK;
	 	}
	 	else if (x->right->color == RED && !going_right)//opposite case 
	 	{
			rotate_left(x);
		   	x->parent->color = BLACK;
		   	x->color = RED;
		   	x->left->color = BLACK;
		   	if (x == root)//if x is root then set root on it 
				root = x->parent;
	 	}
	}
	//if sibling doesnt exist or sibling is red or has red child, done
	else if (t == nullptr) 
 		return;
	else if (t->color == RED || (x->right->color == RED || x->left->color == RED)) 
 		return;
 	//SIBLING CONDITIONS
 	else if(!t->right && !t->left) //no children, so color flip
	{
 		p->color = BLACK;
 		t->color = RED;
 		x->color = RED;
	}
 	else if (t->left && !t->right)//only sibling left 
	{
		if (t->left->color == BLACK)//if left is black, then color flip 
		{
			p->color = BLACK;
			t->color = RED;
			x->color = RED;
		}
		else//check for possible case 3 or 4 
		{
			if (t->key < x->key)//case 3 at p 
			{
				rotate_right(p);
				t->color = RED;
				t->left->color = BLACK;
			}
			else//case 4 at p 
			{
				rotate_right(t);
				rotate_left(p);
			}
			p->color = BLACK;
			x->color = RED;
		}
	}
	else if (t->right && !t->left)//only sibling right 
	{
 		if (t->right->color == BLACK)//check for possible color flip
 		{
   			t->color = RED;
   			x->color = RED;
   			p->color = BLACK;
 		}
 		else //check for possible case 3 or 4
 		{
			if (t->key < x->key) //CASE 3
			{
 				rotate_left(t);
     			rotate_right(p);
			}
			else //CASE 4
			{
 				rotate_left(p);
     			t->color = RED;
     			t->right->color = BLACK;
			}
			p->color = BLACK;
   			x->color = RED;
 		}
	}
	else//both sibling left and right 
	{
		if(t->right->color == BLACK && t->left->color == BLACK)//sibling has two black children: color flip
		{
	   		x->color = RED;
	   		t->color = RED;
	   		p->color = BLACK;
		}
		else if(t->left->color == RED) //siblling left is red
		{
			if (t->key < x->key) 
			{
		 		rotate_right(p);//case 3
				t->color = RED;
				t->left->color = BLACK;
			}
			else //case 4
			{
		 		rotate_right(t);
				rotate_left(p);
			}
			p->color = BLACK;
			x->color = RED;
		}		
		else//same case but sibling right is red
		{
			if (t->key < x->key)//double rotation left case 4
			{
		 		rotate_left(t);
				rotate_right(p);
			}
			else//single rotation left case 3
			{
			 	rotate_left(p);
			 	t->color = RED;
			 	t->right->color = BLACK;
			}
			p->color = BLACK;
			x->color = RED;
		}

	}

  }
//MAIN CASE: x has only a right child
else if (x->right && !x->left) 
{
	if ((x->right->color == RED) && ((!going_right && x->right->color == RED)))//check case 1 
	{
			rotate_left(x);
			x->parent->color = BLACK;
			x->color = RED;
	}
	//exit cases: if no sibling node or sib is red or x right is black
	else if (t == nullptr)
		return;
	else if (x->right->color == BLACK || t->color == RED ) 
		return;	
	
	else if(!t->right && !t->left) 
	{
		p->color = BLACK;
		t->color = RED;
		x->color = RED;
	}
	//case where sibling has two chiildren
	else if (t->right && t->left) 
	{
		if (t->left->color == BLACK && t->right->color == BLACK)//case 1 color flup
		{
			p->color = BLACK;
			t->color = RED;
			x->color = RED;
		}
		else if (t->right->color == RED)//if right is red then possible case 3 or 4 
		{
			if (t->key < x->key) //case 4
			{
				rotate_left(t);
				rotate_right(p);
			}
			else //case 5
			{
				rotate_left(p);
				t->color = RED;
				t->right->color = BLACK;
			}
			p->color = BLACK;
			x->color = RED;
		}
		else //reversed case
		{
			if (t->key < x->key) //case 3
			{
				rotate_right(p);
				t->color = RED;
				t->left->color = BLACK;
			}
			else //case 4
			{
				rotate_right(t);
				rotate_left(p);
			}
			p->color = BLACK;
			x->color = RED;
		}
	}
	else if (t->right && !t->left)//SIBLING RIGHT ONLY 
	{
		if (t->right->color == BLACK)//check for color flip case 
		{
			p->color = BLACK;
			t->color = RED;
			x->color = RED;
		}
		else //check for case 3 or 4
		{
			if (t->key < x->key) //case 4
			{
				rotate_left(t);
				rotate_right(p);
			}
			else //case 3
			{
				rotate_left(p);
				t->color = RED;
				t->right->color = BLACK;
			}
			p->color = BLACK;
			x->color = RED;
		}
	}
	else//SIBLING LEFT ONLY
	{
		if (t->left->color == BLACK)//check for color flip if left is black 
		{
			p->color = BLACK;
			t->color = RED;
			x->color = RED;
		}
		else //otherwise check for case 3 or 4
		{
			if (t->key < x->key) //case 3
			{
				rotate_right(p);
				t->color = RED;
				t->left->color = BLACK;
			}
			else //case 4
			{
				rotate_right(t);
				rotate_left(p);
			}
			p->color = BLACK;
			x->color = RED;
		}
	}

}
else if (!x->right && x->left)//CASE RIGHT SIBLING 
{
	if (x->left->color == RED)//cases for left red 
	{
		if (going_right && x->left->color == RED) //case 1 if left is red and going right is true
		{
			rotate_right(x);
			x->parent->color = BLACK;
			x->color = RED;
			if (x->right)//extra case if right node exits set color to black 
				x->right->color = BLACK;
		}
	}
	//if sibling does not exist or x has a red node, were donzo
	else if (t == nullptr)
		return;
	else if (t->color == RED || x->left->color == RED)
		return;
		
	else if (t->right && t->left)//sibling has both children 
	{
		if (t->right->color == BLACK)//check for case 2 
		{
			p->color = BLACK;
			t->color = RED;
			x->color = RED;
		}
		else if (t->right->color == RED)//check for case 3 or 4 
		{
			if (t->key < x->key)//case 4 
			{
				rotate_left(t);
				rotate_right(p);
			}
			else //case 3
			{
				rotate_left(p);
				t->color = RED;
				t->right->color = BLACK;
			}
			p->color = BLACK;
			x->color = RED;
		}
		else //check for case 3 or 4 but on left
		{
			if (t->key < x->key) 
			{
				rotate_right(p);
				t->color = RED;
				t->left->color = BLACK;
			}
			else 
			{
				rotate_right(t);
				rotate_left(p);
			}
			p->color = BLACK;
			x->color = RED;
		}
	}
	else if (t->right) 
	{
		// Only the right child of x's sibiling exists
		if (t->right->color == BLACK) 
		{
			// CASE 2: Color Flip, all children are black !
			p->color = BLACK;
			t->color = RED;
			x->color = RED;
		}
		else 
		{
			// t has only a red right child
			// CASE 3 OR 4: Outside or inside red child
			if (t->key < x->key)
			{
				// Left-Right Case
				rotate_left(t);
				rotate_right(p);
			}
			else 
			{
				// Right-Right Case
				rotate_left(p);
				t->color = RED;
				t->right->color = BLACK;
			}
			p->color = BLACK;
			x->color = RED;
		}
	}
	else if (t->left) 
	{
		// Only the left child of x's sibiling exists
		if (t->left->color == BLACK) 
		{
			// CASE 2: Color Flip, all children are black !
			p->color = BLACK;
			t->color = RED;
			x->color = RED;
		}
		else 
		{
			// t has only a red left child
			// CASE 3 OR 4: Outside or inside red child
			if (t->key < x->key) 
			{
				// Left-Left Case
				rotate_right(p);
				t->color = RED;
				t->left->color = BLACK;
			}
			else 
			{
				// Right-Left Case
				rotate_right(t);
				rotate_left(p);
			}
			p->color = BLACK;
			x->color = RED;
		}
	}
	else //color flip final case 
	{
			p->color = BLACK;
			t->color = RED;
			x->color = RED;
	}
}
//MAIN CASE: x has no children
else 
{
	//exit if no sibling or if sibling is red
	if (t == nullptr) 
		return;
	else if (t->color == RED) 
		return;
		
	else if (t->right && t->left)//test case if sibling has two children 
	{
		if (t->right->color == BLACK && t->left->color == BLACK)//check for case 2
		{//color flip
			t->color = RED;
			x->color = RED;
			p->color = BLACK;
		}
		else if (t->right->color == RED) //if sibling has a left red, check for case 3 or 4
		{
			if (t->key < x->key) //case 4
			{
				rotate_left(t);
				rotate_right(p);
			}
			else //case 3
			{
				rotate_left(p);
				t->color = RED;
				t->right->color = BLACK;
			}
			p->color = BLACK;
			x->color = RED;
		}
		else //reverse case for 3 and 4
		{
			if (t->key < x->key) //case 3
			{
				rotate_right(p);
				t->color = RED;
				t->left->color = BLACK;
			}
			else //case 4
			{
				rotate_right(t);
				rotate_left(p);
			}
			p->color = BLACK;
			x->color = RED;
		}
	}
	else if (t->right)//if sibling has a right child
	{
		if (t->right->color == BLACK) //if sibling right child is black case color flip
		{
			p->color = BLACK;
			t->color = RED;
			x->color = RED;
		}
		else //if red, check for case 3 or 4
		{
			if (t->key < x->key) //case 4
			{
				rotate_left(t);
				rotate_right(p);
			}
			else //case 5
			{
				rotate_left(p);
				t->color = RED;
				t->right->color = BLACK;
			}
			p->color = BLACK;
			x->color = RED;
		}
	}
	else if (t->left) //if sibling has a left child
	{
		if (t->left->color == BLACK) //case color flip if left is black
		{
			p->color = BLACK;
			t->color = RED;
			x->color = RED;
		}
		else //if left is red, case 3 or 4
		{
			if (t->key < x->key) //case 3
			{
				rotate_right(p);
				t->color = RED;
				t->left->color = BLACK;
			}
			else //case 4
			{
				rotate_right(t);
				rotate_left(p);
			}
			p->color = BLACK;
			x->color = RED;
		}
	}
	else //case color flip because both black
	{
		p->color = BLACK;
		t->color = RED;
		x->color = RED;
	}
  }

}

//recursively find height
template<typename K, typename V>
size_t RBTCollection<K,V>::height(Node* subtree_root) const 
{
	if(subtree_root == nullptr)//if no children, stop
		return 0;
	if(height(subtree_root->left) > height(subtree_root->right))//if left is bigger, use left 
		return 1 + height(subtree_root->left);
	else//if right is bigger, use right
		return 1 + height(subtree_root->right);
}

//----------------------------------------------------------------------
//Helper Functions:
//----------------------------------------------------------------------

template<typename K, typename V>
bool RBTCollection<K,V>::valid_rbt() const
{
  return !root or (root->color == BLACK and valid_rbt(root));
}


template<typename K, typename V>
bool RBTCollection<K,V>::valid_rbt(Node* subtree_root) const
{
  if (!subtree_root)
    return true;
  color_t rc = subtree_root->color;
  color_t lcc = subtree_root->left ? subtree_root->left->color : BLACK;
  color_t rcc = subtree_root->right ? subtree_root->right->color : BLACK;  
  size_t lbh = black_node_height(subtree_root->left);
  size_t rbh = black_node_height(subtree_root->right);
  bool lv = valid_rbt(subtree_root->left);
  bool rv = valid_rbt(subtree_root->right);
  // check equal black node heights, no two consecutive red nodes, and
  // left and right are valid RBTs
  return (lbh == rbh) and (rc != RED or (lcc != RED and rcc != RED)) and lv and rv;
}


template<typename K, typename V>
size_t RBTCollection<K,V>::black_node_height(Node* subtree_root) const
{
  if (!subtree_root)
    return 1;
  size_t hl = black_node_height(subtree_root->left);
  size_t hr = black_node_height(subtree_root->right);
  size_t h = hl > hr ? hl : hr;
  if (subtree_root->color == BLACK)
    return 1 + h;
  else
    return h;
}


template<typename K, typename V>
void RBTCollection<K,V>::print() const
{
  print_tree("", root);
}


template<typename K, typename V>
void RBTCollection<K,V>::print_tree(std::string indent, Node* subtree_root) const
{
  if (!subtree_root)
    return;
    
  std::string pos = "";
  K nodeKey = subtree_root->key;
  if(!subtree_root->parent)
  	pos = "Root}";
  else if(subtree_root == subtree_root->parent->left)
  	 pos = "'s left}";
  else
  	 pos = "'s right}";
  
  std::string color = "[BLACK]";
  if (subtree_root->color == RED)
    color = "[RED]";
  std::cout << indent << subtree_root->key << " "
	    << color << " (h="
	    << height(subtree_root) << ")  ";
  if(!subtree_root->parent)
  	std::cout << "{" << pos << std::endl; 
  else
  	std::cout << "{" << subtree_root->parent->key << pos << std::endl; 

  print_tree(indent + "  ", subtree_root->left);
  print_tree(indent + "  ", subtree_root->right);
}


#endif
