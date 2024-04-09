#include "queue_simulator.h"
#pragma once
#include <math.h>

#include <iostream>
using namespace std;

#ifndef HEAPHPP
#define HEAPHPP

#define DEFAULTHEAPSIZE 1023

template <class T>
class Heap {
 protected:
  T* _heap;
  int _size;
  friend QueueSimulator;

 public:
  Heap() { _heap = new T[DEFAULTHEAPSIZE]; _size = 0;}

  int size() const {
    return _size;
  }

  bool empty() const {
    if(_size == 0)
      return true;
    return false;
  }
  
  void insert(const T&);
  T extractMax();
  T peekMax() const;
  void printHeapArray() const;
  void printTree() const;
  void changeKey(const T& from, const T& to);
  void deleteItem(const T&);

  ~Heap() { delete[] _heap; };
};

template <class T>
void swap(int i, int j, T *heap)
{
  T temp = heap[i];
  heap[i] = heap[j];
  heap[j] = temp;
}

template <class T>
void Heap<T>::insert(const T& item) {
  _heap[_size] = item;
  _size += 1;
  int parent = (_size - 2) / 2;
  int child = _size - 1;
  while(parent >= 0 && item > _heap[parent])
  {
    swap(parent, child, _heap);
    parent = (parent - 1) / 2;
    child = (child - 1) / 2;
  }
}

template <class T>
T Heap<T>::extractMax() {
  if(_size == 0)
  {
    throw std :: out_of_range("no element");
  }
  else if(_size == 1)
  {
    T max = _heap[0];
    _size = 0;
    return max;
  }
  T max = _heap[0];
  _size -= 1;
  swap(0, _size, _heap);
  int child = 0; 
  int parent1 = (child * 2) + 1;
  int parent2 = (child * 2) + 2;
  while(parent1 < _size)
  {
    if(parent2 >= _size)
    {
      if(_heap[parent1] > _heap[child])
      {
        swap(child, parent1, _heap);
      }
      return max;
    }
    if (_heap[parent1] > _heap[child] || _heap[parent2] > _heap[child])
    {
      if(_heap[parent1] > _heap[parent2])
      {
        swap(child, parent1, _heap);
        child = parent1;
      }
      else
      {
        swap(child, parent2, _heap);
        child = parent2;
      }
      parent1 = (child * 2) + 1;
      parent2 = (child * 2) + 2;
    }
    else
    {
      return max;
    }
  }
  return max;
}

template <class T>
T Heap<T>::peekMax() const {
   if(_size == 0)
  {
    throw std :: out_of_range("no element");
  }
  else
  {
    return _heap[0];
  }
};

template <class T>
void Heap<T>::printHeapArray() const {
  for (int i = 0; i < size(); i++) {
    cout << _heap[i] << " ";
  }
  cout << endl;
}

template <class T>
void Heap<T>::changeKey(const T& from, const T& to) {
  if(_size == 0)
  {
    throw std :: out_of_range("no element");
    return;
  }
  int j = -1;
  for(int i = 0;i < _size; i += 1)
  {
    if(_heap[i] == from)
    {
      _heap[i] = to;
      j = i;
    }
  }
  if(j == -1)
  {
    throw std :: out_of_range("element is not inside");
    return;
  }
  if(to < from)
  {
    int child = j; 
    int parent1 = (child * 2) + 1;
    int parent2 = (child * 2) + 2;
    while(parent1 < _size)
    {
      if(parent2 >= _size)
      {
        if(_heap[child] < _heap[parent1])
        {
          swap(child, parent1, _heap);
        }
        return;
      }
      if (_heap[child] < _heap[parent1] || _heap[child] < _heap[parent2])
      {
        if(_heap[parent1] > _heap[parent2])
        {
          swap(child, parent1, _heap);
          child = parent1;
        }
        else
        {
          swap(child, parent2, _heap);
          child = parent2;
         }
        parent1 = (child * 2) + 1;
        parent2 = (child * 2) + 2;
      }
      else
      {
        return;
      }
    }
  }
  else
  {
    int parent = (j - 1) / 2;
    int child = j;
    while(parent >= 0 && to > _heap[parent])
    {
      swap(parent, child, _heap);
      child = parent;
      parent = (child - 1) / 2;
    }
  }
}

template <class T> 
void Heap<T>::deleteItem(const T& x) {
  if(_size == 0)
  {
    throw std::out_of_range("no element");
    return;
  }
  int j = 0;
  T item = _heap[_size - 1];
  for(int i = 0; i < _size; i += 1)
  {
    if(_heap[i] == x)
    {
      changeKey(x, _heap[_size - 1]);
      _size -= 1;
      return;
    }
  }
}
#endif

vector<Customer> QueueSimulator::simulateQueue(
    const vector<Customer>& customers) {
  Heap<Customer> *servers = new Heap<Customer> [_num_servers];
  int *service_time = new int[_num_servers];
  int _num_customers = customers.size();
  vector<Customer> new_queue;
  if(_priority_order == false)
  {
    int min_service = 0;
    for(int i = 0; i < _num_customers; i += 1)
    {
      int min_server = 0;
      int j = 0;
      for(; j < _num_servers; j += 1)
      {
        if(service_time[j] < min_service)
        {
          min_service = service_time[j];
          min_server = j;
        }
      }
      j -= 1;
      if(customers[i].arrival_time() > min_service)
      {
        min_service = customers[i].arrival_time();
        service_time[min_server] = min_service;
      }
      new_queue.push_back(customers[i]);
      new_queue[i].set_service_time(min_service);
      service_time[min_server] += new_queue[i].processing_time();
      min_service = service_time[min_server];
    }
    return new_queue;
  }
  for(int k = 0; k < _num_customers; k += 1)
  {
    customers[k].set_compare_by_processing_time(true);
  }
  int min_service = customers[0].arrival_time() + customers[0].processing_time();
  for(int t = 0; t < _num_servers; t += 1)
  {
    service_time[t] = customers[t].arrival_time() + customers[t].processing_time();
    new_queue.push_back(customers[t]);
    new_queue[t].set_service_time(customers[t].arrival_time());
  }
  int q = _num_servers;
  for(int j = _num_servers; j < _num_customers; j += 1)
  {
    int min_server = 0;
    int p = 0;
    for(; p < _num_servers; p += 1)
    {
      if(service_time[p] <= min_service)
      {
        min_service = service_time[p];
        min_server = p;
      }
    }
    p -= 1;
    while(q < _num_customers && customers[q].arrival_time() <= min_service)
    {
      servers[p].insert(customers[q]);
      q += 1;
    }
    Customer new_customer = servers[p].extractMax();
    new_queue.push_back(new_customer);
    int curr = new_queue.size() - 1;
    (new_queue[curr]).set_service_time(min_service);
    service_time[min_server] += new_queue[curr].processing_time();
    min_service = service_time[min_server];
  }
  return new_queue;
}
