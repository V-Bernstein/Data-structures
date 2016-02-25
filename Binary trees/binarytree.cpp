/**
 * @file binarytree.cpp
 * Definitions of the binary tree functions you'll be writing for this lab.
 * You'll need to modify this file.
 */

/**
 * @return The height of the binary tree. Recall that the height of a binary tree
 *  is just the length of the longest path from the root to a leaf, and that the
 *  height of an empty tree is -1.
 */
template <typename T>
int BinaryTree<T>::height() const
{
	// Call recursive helper function on root
	return height(root);
}

/**
 * Private helper function for the public height function.
 * @param subRoot
 * @return The height of the subtree
 */
template <typename T>
int BinaryTree<T>::height(const Node * subRoot) const
{
	// Base case
	if (subRoot == NULL)
        return -1;
	
	// Recursive definition
	return 1 + max(height(subRoot->left), height(subRoot->right));
}

/**
 * Prints out the values of the nodes of a binary tree in order.
 * That is, everything to the left of a node will be printed out before that node
 *  itself, and everything to the right of a node will be printed out after that node.
 */
template <typename T>
void BinaryTree<T>::printLeftToRight() const
{
	// Call recursive helper function on the root
	printLeftToRight(root);

	// Finish the line
	cout << endl;
}

/**
 * Private helper function for the public printLeftToRight function.
 * @param subRoot
 */
template <typename T>
void BinaryTree<T>::printLeftToRight(const Node * subRoot) const
{
	// Base case - null node
	if (subRoot == NULL)
		return;

	// Print left subtree
	printLeftToRight(subRoot->left);

	// Print this node
	cout << subRoot->elem << ' ';

	// Print right subtree
	printLeftToRight(subRoot->right);
}

/**
 * Flips the tree over a vertical axis, modifying the tree itself
 *  (not creating a flipped copy).
 */
template <typename T>
void BinaryTree<T>::mirror()
{
 
     mirror(root);

}

/* Helper function that allows us to use mirror recursively*/

template <typename T>
void BinaryTree<T>::mirror(Node* subRoot){
  
  if(subRoot->left == NULL && subRoot->right == NULL){ // checks to see if there are no children
    return;
  }else{
    flip(subRoot); // flip can deal with NULL cases
   if(subRoot->left != NULL){
     mirror(subRoot->left);
   }
   if(subRoot->right != NULL){
     mirror(subRoot->right);
   }
 }
  return;
}

/* Helper function that flips the position of the left and right node chains*/

template <typename T>
void BinaryTree<T>::flip(Node* subRoot){
  Node* temp = subRoot->left;
  subRoot->left = subRoot->right;
  subRoot->right = temp;
  temp = NULL;
  return;
}

/**
 * @return True if an in-order traversal of the tree would produce a nondecreasing list
 *  output values, and false otherwise. This is also the criterion for a binary tree to be
 *  a binary search tree.
 */
template <typename T>
bool BinaryTree<T>::isOrdered() const
{
  vector<T> order;
  inOrderVector(root, order); // Stores in-order values in a vector
  
  for(size_t i = 0; i < order.size()-1; i++){
    // checks to see the values are proper
    if(order[i] > order[i+1]){     
      return false;
    }    
  } 
  return true;
}

/*Helper function to make a vector with the in-order values*/

template <typename T>
void BinaryTree<T>::inOrderVector(Node* subRoot, vector<T> & order) const{

  if(subRoot == NULL){ // base case
    return;
  }

  inOrderVector(subRoot->left, order);

  order.push_back(subRoot->elem); // store value in vector

  inOrderVector(subRoot->right, order);
}

/**
 * Prints out all the possible paths from the root of the tree to any leaf node.
 * That is, all sequences starting at the root node and continuing downwards, ending at a
 *  leaf node. Paths ending in a left node should be printed before paths ending in a node
 *  further to the right.
 */
template <typename T>
void BinaryTree<T>::printPaths() const
{
  vector<T> output;
  printPaths(root, output);

}

/*printPaths private helper function. Allows recursion*/

template <typename T>
void BinaryTree<T>::printPaths(Node* subRoot, vector<T> & output) const{
 
 if(subRoot == NULL){ // base case
    return;
  } 

  output.push_back(subRoot->elem);

  printPaths(subRoot->left, output);

  printPaths(subRoot->right, output);

  if(subRoot->left == NULL && subRoot->right == NULL){
    cout << "Path: ";
    for(size_t i = 0; i < output.size(); i++){
      cout << output[i] << " ";
    }
    cout << endl;
  }

  output.pop_back(); 
}

/**
 * Each node in a tree has a distance from the root node - the depth of that node,
 *  or the number of edges along the path from that node to the root. This function returns
 *  the sum of the distances of all nodes to the root node (the sum of the depths of all
 *  the nodes). Your solution should take O(n) time, where n is the number of nodes in the tree.
 * @return The sum of the distances of all nodes to the root
 */

template <typename T>
int BinaryTree<T>::sumDistances() const
{

  /* not working, algorithm I'm using invalid*/
   vector<T> numbers;
   inOrderVector(root, numbers);
   int sum = 0;
   size_t rootIndex;

   for(size_t i = 0; i < numbers.size(); i++){
     if(numbers[i] == root->elem){
       rootIndex = i;
     }
   }
   

   for(size_t i = 0; i < numbers.size(); i++){
     if(i < rootIndex){
       sum += rootIndex - i;
     }
     if(i > rootIndex){
       sum += i - rootIndex;
     }
   }

   return sum;
  
}
