#include "dsets.h"

DisjointSets::DisjointSets(){

}
/* Creates -num- unconnected root nodes at the end of the vector. */
void DisjointSets::addelements(int num){
  elems.insert(elems.end(), num, -1);

}
 /* This function compresses paths.
     Returns: the index of the root of the up-tree in which the parameter element resides */
int DisjointSets::find(int elem){
  if(elems[elem] < 0){
    return elem;
  }
  return find(elems[elem]);
}
 /* This function is implemented as union-by-size.
That is, when you setunion two disjoint sets, the smaller (in terms of number of nodes) points at the larger. You should not assume that the arguments to setunion are roots of existing uptrees.

setunion finds the roots of its arguments before combining the trees. If the two sets are the same size, the tree containing the second argument points to the tree containing the first.

Parameters:
a	Index of the first element to union
b	Index of the second element to union  */

void DisjointSets::setunion(int a, int b){
  int fA = find(a);
  int fB = find(b);
  int newSize = elems[fA] + elems[fB];
  if(elems[fA] <= elems[fB]){
    elems[fB] = a;
    elems[fA] = newSize;
  }else{ // number of elements in subtree of a < elements in subtree of b
    elems[fA] = b;
    elems[fB] = newSize;
  }

}
