#ifndef STACK
#define STACK

template <class T> 
class Stack
{
private: 
  int _size;
  T *array;
public:
  Stack(){
    _size = 0;
    array = new int [100];
  }
  bool isEmpty()
  {
    if(_size == 0)
    {
      return true;
    }
    return false;
  }
  
  void push(T item)
  {
    array[_size] = item;
    _size += 1;
  }
  void pop()
  {
    if(isEmpty())
    {
      throw :: std :: out_of_range("no element");
    }
    else
    {
      _size -= 1;
    }
  }
};
