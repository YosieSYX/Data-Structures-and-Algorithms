#include "linked_list.h"

// Returns the value at head
int List::head() {
  if(m_head == NULL)
  {
    throw std::out_of_range("list is empty");
  }
  else
    return m_head -> element;
}

// Checks whether the container is empty
bool List::empty() const {
  if(m_head == NULL)
  {
    return true;
  }
  return false;
}

// Returns the number of elements
size_t List::size() const {
  return (size_t)(m_size);
}
// Inserts an element to the head
void List::push_head(int element) {
  Node *node_ptr = new Node(element,m_head);
  m_head = node_ptr;
  m_size += 1;
}

// Removes the head element
int List::pop_head() {
  if(m_size == 0)
  {
    throw std::out_of_range("list is empty");
  }
  else
  {
    Node *temp = m_head; 
    int number = m_head -> element;
    m_head = m_head -> next;
    delete temp;
    m_size -= 1;
    return number;
  }
}

// Checks whether the container contains the specified element
bool List::contains(int new_element) const {
  Node *curr = m_head;
  while(curr != NULL)
  {
    if((curr -> element) == new_element)
    return true;
    curr = curr -> next;
  }
  return false;
}

// Returns a std::string equivalent of the container
std::string List::to_string() const {
  Node *curr = m_head;
  if(curr == NULL)
  {
    return "{}";
  }
  std :: string str1 = "{";
  for(int i = 0; i < m_size - 1; i += 1)
  {
    std :: string str2 = std :: to_string(curr -> element);
    str1 += str2;
    str1 += ", ";
    curr = curr -> next;
  }
  std :: string str2 = std :: to_string(curr -> element);
  str1 += str2;
  str1 += "}";
  return str1;
}
