#ifndef TREE_H
#define TREE_H

#include <algorithm>
#include <cassert>
#include <functional>
#include <string>

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

  Node(T element)
      : element{element}, height{0}, left{nullptr}, right{nullptr} {}
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

// Destructor
template <typename T> Tree<T>::~Tree() {
  // TODO: Implement this method
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
    return 0;
  return m_root -> height;
}

template <typename T> void insert_after_node(Node<T> *node, T element, int NewHeight)
{
  Node<T> *NewNode = new Node(element,NewHeight + 1);
  if(element >= (node -> element))
  {
     if(node -> right == nullptr)
     {
      node -> right = NewNode;
      return;
     }
     insert_after_node(node->right, element, NewHeight + 1);
     /*if(node -> left == nullptr && (node -> right) -> height > 0)
     {
       left_rotate(node);
     }
     else if((node -> left) -> height - (node -> right) -> height > 1) 
     {
       right_rotate(node);
     }
     else if((node -> right) -> height - (node -> left) -> height > 1)
     {
       left_rotate(node);
     }*/
  }
  else
  {
    if(node -> left == nullptr)
    {
      node -> left = NewNode;
      return;
    }
    insert_after_node(node->left, element, NewHeight + 1);
    /*if(node -> right == nullptr && (node -> left) -> height > 0)
     {
       right_rotate(node);
     }
     else if((node -> left) -> height - (node -> right) -> height > 1) 
     {
       right_rotate(node);
     }
     else if((node -> right) -> height - (node -> left) -> height > 1)
     {
       left_rotate(node);
     }*/
  }
}

template<typename T> void right_rotate(Node<T> *node)
{
  Node<T> *temp = node;
  node = node -> left;
  while(node -> right != nullptr)
  {
    node = node -> right;
  } 
  node -> right = temp;
}

template <typename T> void left_rotate(Node<T> *node)
{
  Node<T> *temp = node;
  node = node -> right;
  while(node -> left != nullptr)
  {
    node = node -> left;
  } 
  node -> left = temp;
}

template <typename T> void balance(Node<T> *node, T element)
{
  Node<T> *current = node;
  while(current != nullptr)
  {
    if(current -> left != nullptr )
    {
      if((current -> left) -> height > 0 && current -> right == nullptr)
      {
        right_rotate(current);
      }
      else if((current -> left) -> height - (current -> right) -> height > 1)
      {
        right_rotate(current);
      }
      else if((current -> right) -> height - (current -> left) -> height > 1)
      {
        left_rotate(current);
      }
      if(element >= current -> element)
      {
        current = current -> right;
      }
      if(element < current -> element)
      {
        current = current -> left;
      }
    }
    else
    {
      if((current -> right) -> height > 0)
      {
        left_rotate(current);
      }
      if(element >= (current -> element))
      {
        current = current -> right;
      }
      if(element < (current -> element))
      {
        current = current -> left;
      }
    }
  }
}

// Inserts an element
template <typename T> void Tree<T>::insert(T element) {
  if(m_root == nullptr)
  {
    m_root = new Node(element, 0);
  }
  else
  {
    insert_after_node(m_root, element, 0);
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
  int TempSuccessor;
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
    return "" + my_to_string(node -> element) + (node->right == nullptr ? "" : " " + _in_order(node->right));
  }
  return (_in_order(node -> left) + " ") + my_to_string(node -> element) + (node->right == nullptr ? "" : " " + _in_order(node->right));
}

template <typename T>
string Tree<T>::in_order() {
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

#endif
