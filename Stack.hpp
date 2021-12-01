#pragma once
#include <iostream>

using std::cout; 
using std::endl; 
using std::cin;

/**
 * @author Vladimir Sánchez
 *
 */

/**
 * @class Stack
 * @brief estrucuta de datos de tipo lista ligada hacia adelante
 * @template T es el tipo de datos a almacenar
 */
template <class T>
class Stack {
  private:
    /**
     * @class Node
     * @brief clase que permite almacenar un dato y un apuntador a otro nodo
     */
    class Node {
      private: 
        T m_data;
        Node* m_pNext;
        friend class Stack;
    };

    /**
     * Genera un nodo con almacenanto un dato
     * @param p_data es el dato a almacenar en el nodo
     */
    Node* generateNode(T p_data) {
      Node* newNode = new Node;
      newNode->m_data = p_data;
      newNode->m_pNext = nullptr;
      return newNode;
    }

    Node*& getRootNode() {
      return m_pRoot;
    }

    Node*& getLastNode() {
      return m_pLast;
    }

    static Node* m_pRoot;
    Node* m_pLast = nullptr;
    size_t m_size;

  public:
    Stack<T>() noexcept {
      m_pRoot = nullptr;
      m_pLast = nullptr;
    }
    
    void push(T p_data);
    void pop();
    void traverse();
};

// explicar esto
template <class T>
typename Stack<T>::Node* Stack<T>::m_pRoot = nullptr;

/**
 *
 */
template <class T>
void Stack<T>::push(T data) {
  Node* pNodeTemp = generateNode(data);
  if (!getRootNode()) {
    getRootNode() = pNodeTemp;
    getLastNode() = getRootNode();
  } else if (getRootNode() == getLastNode()) {
    getRootNode() = pNodeTemp;
    getRootNode()->m_pNext = getLastNode();
  } else {
    Node* pList = getRootNode();
    getRootNode() = pNodeTemp;
    getRootNode()->m_pNext = pList;
  }
  m_size++;
}

/**
 *
 *
 */
template <class T>
void Stack<T>::pop() {
  if (!getRootNode()){
    return;
  } else if (getLastNode() == getRootNode()) {
    delete[] getRootNode();
    getRootNode() = nullptr;
    getLastNode() = getRootNode();
  } else {
    Node* pList = getRootNode()->m_pNext;
    delete[] getRootNode();
    getRootNode() = pList;
  }
  m_size--;
}

/**
 *
 *
 */
template <class T>
void Stack<T>::traverse() {
  Node* pNewLast = getRootNode();
  while(pNewLast) {
    cout << pNewLast->m_data << (pNewLast->m_pNext ? ", ": "\n");
    pNewLast = pNewLast->m_pNext;
  }
}