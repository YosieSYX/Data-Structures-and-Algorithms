#ifndef TREE_H
#define TREE_H

#include <algorithm>
#include <cassert>
#include <functional>
#include <string>
#include <iostream>

using std::string;

template <typename T>
std::string my_to_string(const T& t) {
  return std::to_string(t);
}

template <>
std::string my_to_string(const std::string& t) {
  return "\"" + t + "\"";
}

template <typename T> struct Node {
  T element;
  int height;
  Node<T> *left;
  Node<T> *right;
  T _sst;
  Node(T element)
      : element{element}, height{0}, left{nullptr}, right{nullptr}, _sst{element} {}
  Node(T element, int height)
      : element{element}, height{height}, left{nullptr}, right{nullptr} {}
};

template <typename T> class Tree {
private:
  size_t m_size;
  Node<T> *m_root;

public:
  // Constructor
  Tree();

  // Rule of three:
  // If a class requires a user-defined destructor, a user-defined copy
  // constructor, or a user-defined copy assignment operator, it almost
  // certainly requires all three.
  void delete_node(Node<T> **node);
  // Destructor
  ~Tree();

  // Returns a pointer to the root
  Node<T> *root();

  // Checks whether the tree is empty
  bool empty() const;

  // Returns the number of elements
  size_t size() const;

  // Returns the height of the tree
  int height() const;

  // Inserts the specified element
  void insert(T element);

  // Checks whether the container contains the specified element
  bool contains(T element) const;

  // Returns the maximum element
  T max() const;

  // Returns the minimum element
  T min() const;

  // Returns the successor of the specified element
  T successor(T element);

  // Convert each element in the tree to string in pre-order.
  string pre_order();

  // Convert each element in the tree to string in order.
  string in_order();

  // Convert each element in the tree to string in post-order.
  string post_order();

  T sumLE(T n);

  T sum_current(T n, T sum, Node<T> *node);

  // Returns a string equivalent of the tree
  string to_string(bool with_height = true) const {
    return m_to_string(with_height, m_root, 0);
  }

private:
  string m_to_string(bool with_height, Node<T> *node, int ident) const {
    string res;
    if (node == nullptr) {
      return res;
    }
    if (node->right != nullptr) {
      res += m_to_string(with_height, node->right, ident + 2);
    }
    for (int i = 0; i < ident; i++) {
      res += " ";
    }
    res += my_to_string(node->element);
    if (with_height) {
      res += "(h=" + my_to_string(node->height) + ")";
    }
    res += "\n";
    if (node->left != nullptr) {
      res += m_to_string(with_height, node->left, ident + 2);
    }
    return res;
  }

  // Feel free to declare helper functions here, if necessary
  };

// Constructor
template <typename T> Tree<T>::Tree() {
  m_root = nullptr;
  m_size = 0;
}

template <typename T> void Tree<T> :: delete_node(Node<T> **node)
{
  if((*node) == nullptr)
  {
    return;
  }
  if((*node) -> left == nullptr)
  {
    if((*node) -> right == nullptr)
    {
      Node<T> *temp = (*node);
      delete temp;
      *node = nullptr;
      m_size -= 1;
      return;
    }
    delete_node(&((*node) -> right));
    delete_node(node);
    return;
  }
  delete_node(&((*node) -> left));
  delete_node(&((*node) -> right));
  delete_node(node);
  return;
}
// Destructor
template <typename T> Tree<T>::~Tree() {
  delete_node(&m_root);
}

// Returns a pointer to the root
template <typename T> Node<T> *Tree<T>::root() {
  Node<T> *ptr_root = m_root;
  return ptr_root;
}

// Checks whether the tree is empty
template <typename T> bool Tree<T>::empty() const {
  if(m_root == nullptr)
    return true;
  return false;
}

// Returns the number of elements
template <typename T> size_t Tree<T>::size() const {
  return m_size;
}

// Returns the height of the tree
template <typename T> int Tree<T>::height() const {
  if(empty())
    return -1;
  return m_root -> height;
}

template <typename T> int CheckBalance(Node<T> *node)
{
  if(node -> left == nullptr)
  {
    if((node -> right) == nullptr || (node -> right) -> height == 0)
    {
      return 0;
    }
    return 1;
  }
  if(node -> right == nullptr)
  {
    if(((node -> left) -> height == 0))
    {
      return 0;
    }
    return -1;
  }
  if((node -> left) -> height - (node -> right) -> height > 1)
  {
    return -1; 
  }
  if((node -> left) -> height - (node -> right) -> height < -1)
  {
    return 1;
  }
  return 0;
}

template<typename T> int CheckHeavy(Node<T> *node)
{
  if(node -> left == nullptr)
  {
    if(node -> right == nullptr)
    {
      return 0;
    }
    return 1;
  }
  if(node -> right == nullptr)
  {
    return -1;
  }
  if((node -> left) -> height == (node -> right) -> height)
  {
    return 0;
  }
  if((node -> left) -> height > (node -> right) -> height)
  {
    return -1;
  }
  return 1;
}

template <typename T> int update_height(Node<T> *node)
{
  if(node -> left == nullptr)
  {
    if(node -> right == nullptr)
    {
      return 0;
    }
    return (node -> right) -> height + 1;
  }
  if(node -> right == nullptr)
  {
    return (node -> left) -> height + 1;
  }
  if((node -> right) -> height > (node -> left) -> height)
  {
    return (node -> right) -> height + 1;
  }
  return (node -> left) -> height + 1;
}

template <typename T> void insert_after_node(Node<T> **node, T element)
{
  Node<T> *NewNode = new Node<T>(element);
  if(element >= ((*node) -> element))
  {
     if((*node) -> right == nullptr)
     {
      (*node) -> right = NewNode;
      (*node) -> height = 1;
      (*node) -> _sst += element;
      return;
     }
     insert_after_node(&((*node) -> right), element);
  }
  else
  {
    if((*node) -> left == nullptr)
    {
      (*node) -> left = NewNode;
      (*node) -> height = 1;
      (*node) -> _sst += element;
      return;
    }
    insert_after_node(&((*node)->left), element);
  }
  (*node) -> height = update_height((*node));
  if(CheckBalance((*node)) == 0)
  {
    (*node) -> _sst = (*node) -> element + ((*node) -> left == nullptr ? 0 : (*node) -> left -> _sst) + ((*node) -> right == nullptr ? 0 : (*node) -> right -> _sst);
    return;
  }
  if(CheckBalance((*node)) == 1) 
  {
    if(CheckHeavy((*node) -> right) == -1)
    {
      right_rotate(&((*node) -> right));
      ((*node) -> right) -> height = update_height((*node) -> right);
      left_rotate(node);
      (*node) -> height = update_height((*node));
      return;
    }
    left_rotate(node);
    (*node) -> height = update_height((*node));
    return;
  }
  if(CheckHeavy((*node) -> left) == 1)
  {
    left_rotate(&(*node) -> left);
    ((*node) -> left) -> height = update_height(((*node) -> left));
    right_rotate(node);
    (*node) -> height = update_height((*node));
  }
  right_rotate(node);
  (*node) -> height = update_height((*node));
  return;
}

template<typename T> void right_rotate(Node<T> **node)
{
  Node<T> *temp1 = (*node);
  (*node) = (*node) -> left;
  temp1 -> left = (*node) -> right;
  (*node) -> right = temp1;
  temp1 -> height = update_height(temp1);
  (*node) -> height = update_height(*node);
  (temp1) -> _sst = (temp1) -> element + ((temp1) -> left == nullptr ? 0 : (temp1) -> left -> _sst) + ((temp1) -> right == nullptr ? 0 : (temp1) -> right -> _sst);
  (*node) -> _sst = (*node) -> element + ((*node) -> left == nullptr ? 0 : (*node) -> left -> _sst) + ((*node) -> right == nullptr ? 0 : (*node) -> right -> _sst);
}

template <typename T> void left_rotate(Node<T> **node)
{
  Node<T> *temp1 = (*node);
  (*node) = (*node) -> right;
  temp1 -> right = (*node) -> left;
  (*node) -> left = temp1;
  temp1 -> height = update_height(temp1);
  (*node) -> height = update_height(*node);
  (temp1) -> _sst = (temp1) -> element + ((temp1) -> left == nullptr ? 0 : (temp1) -> left -> _sst) + ((temp1) -> right == nullptr ? 0 : (temp1) -> right -> _sst);
  (*node) -> _sst = (*node) -> element + ((*node) -> left == nullptr ? 0 : (*node) -> left -> _sst) + ((*node) -> right == nullptr ? 0 : (*node) -> right -> _sst);
}


// Inserts an element
template <typename T> void Tree<T>::insert(T element) {
  if(m_root == nullptr)
  {
    m_root = new Node<T>(element, 0);
  }
  else
  {
    insert_after_node(&m_root, element);
  }
  m_size += 1;
}

// Checks whether the container contains the specified element
template <typename T> bool Tree<T>::contains(T element) const {
  Node<T> *current = m_root;
  while(current != nullptr)
  {
    if(element == current -> element)
    {
      return true;
    }
    if(element > current -> element)
    {
      current = current -> right;
    }
    else if(element < current -> element)
    {
      current = current -> left;
    }
  }
  return false;
}


// Returns the maximum element
template <typename T> T Tree<T>::max() const {
  Node<T> *current = m_root;
  if(m_root == nullptr)
  {
    throw std:: out_of_range("list is empty");
  }
  while(current -> right != nullptr)
  {
    current = current -> right;
  }
  return current -> element;
}

// Returns the minimum element
template <typename T> T Tree<T>::min() const {
  Node<T> *current = m_root;
  if(m_root == nullptr)
  {
    throw std:: out_of_range("list is empty");
  }
  while(current -> left != nullptr)
  {
    current = current -> left;
  }
  return current -> element;
}

// Returns the successor of the specified element
template <typename T> T Tree<T>::successor(T element) {
  Node<T> *current = m_root;
  bool HaveSuccessor = false;
  T TempSuccessor;
  while(current != nullptr)
  {
    if(element >= current -> element)
    {
      current = current -> right;
    }  
    else
    {
      TempSuccessor = current -> element;
      current = current -> left;
      HaveSuccessor = true;
    }
  }
  if(HaveSuccessor)
  {
    return TempSuccessor;
  }
  throw std :: out_of_range("no successor");
}

template <typename T>
string _pre_order(Node<T> *node) {
  return my_to_string(node->element)
    + (node->left == nullptr ? "" : " " + _pre_order(node->left))
    + (node->right == nullptr ? "" : " " + _pre_order(node->right));
}

template <typename T>
string Tree<T>::pre_order() {
  if (m_root == nullptr) {
    return "";
  }
  return _pre_order(m_root);
}

template <typename T> string _in_order(Node<T> *node)
{
  if(node == nullptr)
  {
    return "";
  }
  if(node -> left == nullptr)
  {
    return "" + my_to_string(node -> element)  + (node->right == nullptr ? "" : " " + _in_order(node->right));
  }
  return (_in_order(node -> left) + " " ) + my_to_string(node -> element) + (node->right == nullptr ? "" : " " + _in_order(node->right));
}

template <typename T>
string Tree<T>::in_order() {
  std::cout << sumLE(6) << std :: endl;
   std::cout << m_root -> element<< std :: endl;
  std::cout << m_root -> right -> _sst << std :: endl;
  return _in_order(m_root);
}

template <typename T> string _post_order(Node<T> *node)
{
  if(node == nullptr)
  {
    return "";
  }
  if(node -> left == nullptr)
  {
    if(node -> right == nullptr)
    {
      return "" + my_to_string(node -> element);
    }
    return _post_order(node -> right) + " " + my_to_string(node -> element);
  }
  return _post_order(node -> left) + " " + _post_order(node -> right) + " " + my_to_string(node -> element);
}
template <typename T>
string Tree<T>::post_order() {
  return _post_order(m_root);
}

template < typename T>
T Tree<T> :: sum_current(T n, T sum, Node<T> *node)
{
  if(n == node -> element)
  {
    return sum + (node -> left == nullptr ? node -> element : node -> element + node -> left -> _sst);
  }
  if(n < node -> element)
  {
    return node -> left == nullptr ? sum : sum_current(n,sum,node -> left);
  }
  return node -> right == nullptr ? (sum + node -> _sst) : sum_current(n,sum + (node -> left == nullptr ? node -> element : node -> element + node -> left -> _sst), node -> right);
}

template < typename T>
T Tree<T> :: sumLE(T n)
{
  return sum_current(n,0,m_root);
}
#endif
