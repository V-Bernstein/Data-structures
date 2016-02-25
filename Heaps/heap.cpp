/**
 * @file heap.cpp
 * Implementation of a heap class.
 */

template <class T, class Compare>
size_t heap<T, Compare>::root() const {
    /// @todo Update to return the index you are choosing to be your root.
    return 1;
}

template <class T, class Compare>
size_t heap<T, Compare>::leftChild( size_t currentIdx ) const {
  /// @todo Update to return the index of the left child.
  if((currentIdx*2) < _elems.size()){
    return (currentIdx*2);
  }else{
    return _elems.size()-1;
  }
}

template <class T, class Compare>
size_t heap<T, Compare>::rightChild( size_t currentIdx ) const {
  /// @todo Update to return the index of the right child.
  if((currentIdx*2+1) < _elems.size()){
    return (currentIdx*2 + 1);
  }else{
    return _elems.size()-1;
  }
}

template <class T, class Compare>
size_t heap<T, Compare>::parent( size_t currentIdx ) const {
  /// @todo Update to return the index of the parent.
  if(currentIdx > 1){
    return (currentIdx/2);
  }else{
    return 1;
  }
}

template <class T, class Compare>
bool heap<T, Compare>::hasAChild( size_t currentIdx ) const {
  /// @todo Update to return whether the given node has a child
    bool retVal = false;
  if(_elems.size()-1 >= currentIdx*2){ //checking that left child idx is valid
    retVal = (_elems[currentIdx*2] != T()); // true if there is a left child    
  }
  if(_elems.size()-1 >= (currentIdx*2 + 1)){ //checking that right child idx is valid   
    retVal = (retVal || (_elems[currentIdx*2 + 1] != T())); //true if there is a right child or a left child
    }
    return retVal;
}

template <class T, class Compare>
size_t heap<T, Compare>::maxPriorityChild( size_t currentIdx ) const {
    /// @todo Update to return the index of the child with highest priority
    ///   as defined by higherPriority()
  
  return (higherPriority(_elems[leftChild(currentIdx)], _elems[rightChild(currentIdx)]) ? leftChild(currentIdx) : rightChild(currentIdx));
}

template <class T, class Compare>
void heap<T, Compare>::heapifyDown( size_t currentIdx ) {
  /// @todo Implement the heapifyDown algorithm.

  if(hasAChild(currentIdx)){
    size_t mpChildIdx = maxPriorityChild(currentIdx);
    if(higherPriority(_elems[mpChildIdx], _elems[currentIdx])){
      std::swap(_elems[currentIdx], _elems[mpChildIdx]);
      heapifyDown(mpChildIdx);
    }
  }
}

template <class T, class Compare>
void heap<T, Compare>::heapifyUp( size_t currentIdx ) {
  if( currentIdx == root() ){
        return;
  }
    size_t parentIdx = parent( currentIdx );
    if( higherPriority( _elems[ currentIdx ], _elems[ parentIdx ] ) ) {
        std::swap( _elems[ currentIdx ], _elems[ parentIdx ] );
        heapifyUp( parentIdx );
    }
}

template <class T, class Compare>
heap<T, Compare>::heap() {
    /// @todo Depending on your implementation, this function may or may
    ///   not need modifying
  _elems.push_back(T());
}

template <class T, class Compare>
heap<T, Compare>::heap( const std::vector<T> & elems ) {
    /// @todo Construct a heap using the buildHeap algorithm
  _elems.push_back(T()); // Init. the garbage 0 index
  _elems.resize(elems.size()-1); //Setting _elems size to elems. Ultimately reduces run time
  for(size_t i = 1; i < elems.size(); i++){ // initializing the values
    _elems[i] = elems[i];
  }
  for(size_t i = (_elems.size()-1)/2; i >= 1; i--){
    heapifyDown(i);
  }
}

template <class T, class Compare>
T heap<T, Compare>::pop() {
  /// @todo Remove, and return, the element with highest priority
  T retVal = _elems[1];
  _elems[1] = _elems[_elems.size()-1];
  _elems.pop_back(); //Deletes the last element in the vector
  heapifyDown(1);
  return retVal;
}

template <class T, class Compare>
T heap<T, Compare>::peek() const {
    /// @todo Return, but do not remove, the element with highest priority
    return _elems[1];
}

template <class T, class Compare>
void heap<T, Compare>::push( const T & elem ) {
  /// @todo Add elem to the heap
  _elems.push_back(elem);
  heapifyUp(_elems.size()-1);
}

template <class T, class Compare>
bool heap<T, Compare>::empty() const {
    /// @todo Determine if the heap is empty
  return (_elems.size() <= 1);
}
