#ifndef DSETS_H
#define DSETS_H

#include <vector>

using std::vector;

class DisjointSets{

 public:

  DisjointSets();  //Default constructor

  /* Creates -num- unconnected root nodes at the end of the vector. */
  void addelements(int num); 

  /* This function compresses paths.
     Returns: the index of the root of the up-tree in which the parameter element resides */
  int find(int elem);

  /* This function is implemented as union-by-size.
That is, when you setunion two disjoint sets, the smaller (in terms of number of nodes) points at the larger. You should not assume that the arguments to setunion are roots of existing uptrees.

setunion finds the roots of its arguments before combining the trees. If the two sets are the same size, the tree containing the second argument points to the tree containing the first.

Parameters:
a	Index of the first element to union
b	Index of the second element to union
  */
  void setunion(int a, int b);

 private:
  std::vector <int> elems; // Private member variable to represent the Disjoint-sets

};
#endif
