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
 * @class Queue
 * @brief estrucuta de datos de tipo lista ligada hacia adelante
 * @template T es el tipo de datos a almacenar
 */
template <class T>
class Queue {
  private:
    /**
     * @class Node
     * @brief clase que permite almacenar un dato y un apuntador a otro nodo
     */
    class Node {
      private: 
        T m_data;
        Node* m_pNext;
        friend class Queue;
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
    Queue<T>() noexcept {
      m_pRoot = nullptr;
    }
    void enqueue(T p_data);
    void dequeue();
    T peek();
    void traverse();
};

// explicar esto
template <class T>
typename Queue<T>::Node* Queue<T>::m_pRoot = nullptr;

/**
 * @brief Agrega nodos al Queue al inicio (push_front)
 *
 */
template <class T>
void Queue<T>::enqueue(T p_data) {
  Node* pNodeTemp = generateNode(p_data);
  // no tenemos root
  if (!getRootNode()) {
    getRootNode() = pNodeTemp;
    getLastNode() = pNodeTemp;
  } else if (getRootNode() == getLastNode()) { // sólo hay un elemento
    getLastNode() = pNodeTemp;
    getRootNode()->m_pNext = getLastNode();
  } else { // hay más de un nodo en la lista
    getLastNode()->m_pNext = pNodeTemp;
    getLastNode() = getLastNode()->m_pNext;
  }
  m_size++;
}


/**
 * @brief Saca nodos del Queue al final (pop_back)
 *
 */
template <class T>
void Queue<T>::dequeue() {
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
 * @brief Regresa el dato en el primer nodo del Queue
 *
 */
template <class T>
T Queue<T>::peek() {
  if (!getRootNode()) {
    return NULL;
  }
  return getRootNode()->m_data;
}

/**
 *
 *
 */
template <class T>
void Queue<T>::traverse() {
  Node* pNewLast = getRootNode();
  while(pNewLast) {
    cout << pNewLast->m_data << (pNewLast->m_pNext ? ", ": "\n");
    pNewLast = pNewLast->m_pNext;
  }
}