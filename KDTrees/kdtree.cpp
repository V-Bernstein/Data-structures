/**
 * @file kdtree.cpp
 * Implementation of KDTree class.
 */


template<int Dim>
bool KDTree<Dim>::smallerDimVal(const Point<Dim> & first, const Point<Dim> & second, int curDim) const
{
  if(first[curDim] == second[curDim]){
    return (first < second);
  }else{  
    return (first[curDim] < second[curDim]);
  }
}


template<int Dim>
bool KDTree<Dim>::shouldReplace(const Point<Dim> & target, const Point<Dim> & currentBest, const Point<Dim> & potential) const
{
   
  int cBDist = 0; // Variable to hold the composite distance between currentBest and target
  for(int i = 0; i < Dim; i++){
    cBDist += (target[i] - currentBest[i])*(target[i] - currentBest[i]);
  }
  int pDist = 0; // Variable to hold the composite distance between potential and target
  for(int i = 0; i < Dim; i++){
    pDist += (target[i] - potential[i])*(target[i] - potential[i]);
  }
  if(pDist == cBDist){
    return (potential < currentBest); // or return smallerDimVal(potential...)
  }else{
    return (pDist < cBDist);
  }
}

template<int Dim>
KDTree<Dim>::KDTree(const vector< Point<Dim> > & newPoints)
{
  points = newPoints;
  ctorRecursive(0, points.size()-1, 0);  
}

template<int Dim>
void KDTree<Dim>::ctorRecursive(int first, int last, int dimension){
  if(first >= last){ //Base case
    return;
  }
  int median = (first + last)/2;
  quickSelect(first, last, median, dimension);
  ctorRecursive(first, median-1, (dimension+1)%Dim);
  ctorRecursive(median+1, last, (dimension+1)%Dim);
}

/* Functions to implement quickSort to assist with the KDTree ctor*/
template<int Dim>
void KDTree<Dim>::quickSelect(int left, int right, int median, int dimension){
  if(left >= right){
    return;
  }
  int pivot = partition(left, right, median, dimension);

  if(pivot == median){
    return;
  }else if(pivot > median){
    quickSelect(left, pivot-1, median, dimension);
    return;
  }else{ // pivot < median
    quickSelect(pivot+1, right, median, dimension);
    return;
  }
}

template<int Dim>
int KDTree<Dim>::partition(int first, int last, int median, int dimension){
  
  Point<Dim> medianVal = points[median];
  swap(points[last], points[median]); // putting the pivot in last
  int index = first;
  for(int i = first; i < last; i++){
    if(smallerDimVal(points[i], medianVal, dimension)){ //pts[i] < medianVal
      swap(points[i], points[index]);
      index++;
    }
  }
  swap(points[last], points[index]);
  return index; 
}

template<int Dim>
void KDTree<Dim>::swap(Point<Dim> & first, Point<Dim> & second) const{
  Point<Dim> temp = first;
  first = second;
  second = temp;
  return;
}

template<int Dim>
Point<Dim> KDTree<Dim>::findNearestNeighbor(const Point<Dim> & query) const
{ 
  int median = (points.size()-1)/2;
  Point<Dim> root = points[median];
  return fNNRecursive(query, root, 0, 0, points.size()-1);
 }

/* Recursive helper for fNN*/
template<int Dim>
Point<Dim> KDTree<Dim>::fNNRecursive(const Point<Dim> & query, Point<Dim> & currBest, int dimension, int lower, int upper) const{

  int median = (lower + upper)/2;
  Point<Dim> subroot = points[median];
  if(upper <= lower){ // Base case, at leaf node so return current point    
    if(shouldReplace(query, currBest, points[lower])){
      currBest = points[lower];
    }
    return currBest;
  }

  if(shouldReplace(query, currBest, subroot)){
    currBest = subroot;
  }

  if(smallerDimVal(query, subroot, dimension)){ // query < subroot
    currBest = fNNRecursive(query, subroot, (dimension+1)%Dim, lower, median);
    int currRadius = distance(query, currBest, dimension);
    int checkingRadius = ((query[dimension] - points[median][dimension])*(query[dimension] - points[median][dimension]));   
    if(shouldReplace(query, currBest, subroot)){
      currBest = subroot;
    }
    if(currRadius >= checkingRadius){
      currBest = fNNRecursive(query, subroot, (dimension+1)%Dim, median+1, upper);
    }
  }else{ //In this dimension query is bigger than subroot so check right subtree
    currBest = fNNRecursive(query, currBest,(dimension+1)%Dim, median+1, upper);
    int currRadius = distance(query, currBest, dimension);
    int checkingRadius = ((query[dimension] - points[median][dimension])*(query[dimension] - points[median][dimension]));
    if(shouldReplace(query, currBest, subroot)){
      currBest = subroot;
    }
    if(currRadius >= checkingRadius){
      currBest = fNNRecursive(query, subroot, (dimension+1)%Dim, lower, median);
    } 
  }  
  if(shouldReplace(query, currBest, subroot)){
 // if subroot is closer to query than currBest
    currBest = subroot;
    }
  return currBest; 
}

/* Function that returns the agregate distance between two points*/
template<int Dim>
int KDTree<Dim>::distance(const Point<Dim> target, const Point<Dim> currentBest, int dimension) const{

  int dist = 0; // Variable to hold the composite distance between the two points
  for(int i = 0; i < dimension; i++){
    dist += (target[i] - currentBest[i])*(target[i] - currentBest[i]);
  }
  return dist;
}
