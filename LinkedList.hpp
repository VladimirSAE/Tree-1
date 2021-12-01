#include <iostream>

using std::cout; 
using std::endl; 
using std::cin;

/**
 * @author Vladimir Sánchez
 *
 */

/**
 * @class LinkedList
 * @brief estrucuta de datos de tipo lista ligada hacia adelante
 * @template T es el tipo de datos a almacenar
 */
template <class T>
class LinkedList {
  private:
    /**
     * @class Node
     * @brief clase que permite almacenar un dato y un apuntador a otro nodo
     */
    class Node {
      private: 
        T m_data;
        Node* m_pNext;
        friend class LinkedList;
    };

    /**
     * Genera un nodo con almacenanto un dato
     * @param p_data es el dato a almacenar en el nodo
     */
    Node* generateNode(T& p_data) {
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
    size_t m_size = 0;

  public:
    LinkedList<T>() noexcept {
      m_pRoot = nullptr;
      m_pLast = nullptr;
    }
    size_t size();
    void push_back(T p_data);
    void push_front(T p_data);
    void insert(size_t p_index, T p_data);
    void pop_front();
    void pop_back();
    bool find(T p_data);
    void remove(T p_data);
    void removeAll(T p_data);
    void removeAt(size_t p_index);
    void traverse();
    T& at(const size_t& p_index);
    T& operator[](const size_t& p_index);
};


// explicar esto
template <class T>
typename LinkedList<T>::Node* LinkedList<T>::m_pRoot = nullptr;

/**
 *
 *
 */
template <class T>
size_t LinkedList<T>::size() {
  return m_size;
}

/**
 *
 *
 */
template <class T>
T& LinkedList<T>::at(const size_t& p_index) {
  if (p_index >= m_size) {
    throw std::out_of_range("Índice fuera del rango");
  }
  
  size_t tmp = p_index;
  Node* pNodeTemp = getRootNode();
  if (pNodeTemp) {
    while (tmp > 0) {
      pNodeTemp = pNodeTemp->m_pNext;
      tmp--;
    }
  }
  return pNodeTemp->m_data;
}

template <class T>
T& LinkedList<T>::operator[](const size_t& p_index) {
  if (p_index >= m_size) {
    throw std::out_of_range("Índice fuera del rango");
  }
  size_t tmp = p_index;
  Node* pNodeTemp = getRootNode();
  if (pNodeTemp) {
    while (tmp > 0) {
      pNodeTemp = pNodeTemp->m_pNext;
      tmp--;
    }
  }
  return pNodeTemp->m_data;
}

/**
 *
 *
 */
template <class T>
void LinkedList<T>::push_back(T p_data) {
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
 *
 */
template <class T>
void LinkedList<T>::push_front(T data) {
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

template <class T>
void LinkedList<T>::insert(size_t p_index, T p_data) {
  if (p_index > m_size) {
    throw std::out_of_range("no seas así");
  } else if (p_index == 0) {
    // push_front(data);
  } else if (p_index == m_size) {
    push_back(p_data);
  } else {
    Node* pNodeTemp = generateNode(p_data);
    Node* pList = getRootNode();
    while (p_index > 1) {
      pList = pList->m_pNext;
      p_index--;
    }
    pNodeTemp->m_pNext = pList->m_pNext;
    pList->m_pNext = pNodeTemp;
    m_size++;
  }
}

/**
 *
 *
 */
template <class T>
void LinkedList<T>::pop_front() {
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
void LinkedList<T>::pop_back() {
  if (!getRootNode()){
    return;
  } else if (getLastNode() == getRootNode()) {
    delete[] getRootNode();
    getRootNode() = nullptr;
    getLastNode() = nullptr;
  } else {
    Node* pNewLast = getRootNode();
    while (pNewLast->m_pNext != getLastNode()) {
      pNewLast = pNewLast->m_pNext;
    }
    delete[] getLastNode();
    pNewLast->m_pNext = nullptr;
    getLastNode() = pNewLast;
  }
  m_size--;
}

/**
 *
 *
 */
template <class T>
bool LinkedList<T>::find(T p_data) {
  Node* pNewLast = getRootNode();
  while(pNewLast) {
    if (pNewLast->m_data == p_data) {
      return true;
    }
    pNewLast = pNewLast->m_pNext;
  }
  return false;
}

/**
 * @brief elimina el primer nodo que contiene el dato indicado
 * @param p_data es el dato que buscamos
 */
template <class T>
void LinkedList<T>::remove(T p_data) {
  Node* pNewLast = getRootNode();
  // Lsita vacía
  if (!pNewLast) {
    return;
  }
  // El nodo a eliminar es el root
  if (pNewLast->m_data == p_data) {
    // Si sólo hay un nodo
    if (pNewLast == getLastNode()) {
      delete[] pNewLast;
      getRootNode() = nullptr;
      getLastNode() = nullptr;
      return;
    }
    // más de un nodo en la lista
    getRootNode() = pNewLast->m_pNext;
    delete[] pNewLast;
    return;
  }
  // Buscar el data en los nodos después del root
  while(pNewLast->m_pNext) {
    if (pNewLast->m_pNext->m_data == p_data) {
      // Se va a eliminar el último elemento de la lista
      if (pNewLast->m_pNext == getLastNode()) {
        delete[] getLastNode();
        getLastNode() = pNewLast;
        getLastNode()->m_pNext = nullptr;
      } else { // Se va a eliminar un nodo que no es el último
        Node* tmp = pNewLast->m_pNext;
        pNewLast->m_pNext = pNewLast->m_pNext->m_pNext;
        delete[] tmp;
      }
      return; 
    }
    pNewLast = pNewLast->m_pNext;
  }
}

/**
 * @brief elimina el primer nodo que contiene el dato indicado
 * @param p_data es el dato que buscamos
 */
template <class T>
void LinkedList<T>::removeAll(T p_data) {
  // Esto es ineficiente, porque find en el peor caso se repite
  // n veces, donde n es el tamaño de la lista
  //while(find(p_data)) {
    //remove(p_data);
  //}
  Node* pNewLast = getRootNode();
  // Lsita vacía
  if (!pNewLast) {
    return;
  }
  // El nodo a eliminar es el root
  if (pNewLast->m_data == p_data) {
    // Si sólo hay un nodo
    if (pNewLast == getLastNode()) {
      delete[] pNewLast;
      getRootNode() = nullptr;
      getLastNode() = nullptr;
      return;
    }
  }

  while (pNewLast->m_data == p_data) {
    getRootNode() = pNewLast->m_pNext;
    delete[] pNewLast;
    pNewLast = getRootNode();
  }

  // Buscar el data en los nodos después del root
  while (pNewLast->m_pNext) {
    if (pNewLast->m_pNext->m_data == p_data) {
      // Se va a eliminar el último elemento de la lista
      if (pNewLast->m_pNext == getLastNode()) {
        delete[] pNewLast->m_pNext;
        getLastNode() = pNewLast;
        getLastNode()->m_pNext = nullptr;
        return;
      }
      // Se va a eliminar un nodo que no es el último
      Node* tmp = pNewLast->m_pNext;
      pNewLast->m_pNext = tmp->m_pNext;
      delete[] tmp;
    }
    pNewLast = pNewLast->m_pNext;
  }
}

/**
 *
 *
 */
template <class T>
void LinkedList<T>::traverse() {
  Node* pNewLast = getRootNode();
  while(pNewLast) {
    cout << pNewLast->m_data << (pNewLast->m_pNext ? ", ": "");
    pNewLast = pNewLast->m_pNext;
  }
}
