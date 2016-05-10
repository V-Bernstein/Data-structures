#include "dsets.h"

DisjointSets::DisjointSets(){

}
/* Creates num unconnected root nodes at the end of the vector. */
void DisjointSets::addelements(int num){
  elems.insert(elems.end(), num, -1);

}
 /* This function should compress paths and works as described in lecture.
     Returns:
     the index of the root of the up-tree in which the parameter element resides */

int DisjointSets::find( int elem ){
  if ( sets[elem] < 0 ) return elem;
  else return ( sets[elem] = find ( sets[elem] ) ); // returns the index of the root
}

 /* This function should be implemented as union-by-size.
That is, when you setunion two disjoint sets, the smaller (in terms of number of nodes) should point at the larger. This function works as described in lecture, except that you should not assume that the arguments to setunion are roots of existing uptrees.

Your setunion function SHOULD find the roots of its arguments before combining the trees. If the two sets are the same size, make the tree containing the second argument point to the tree containing the first. (Note that normally we could break this tie arbitrarily, but in this case we want to control things for grading.)

Parameters:
a	Index of the first element to union
b	Index of the second element to union
  */
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
