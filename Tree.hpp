#include "Vector.hpp"
#include "Queue.hpp"
#include "Stack.hpp"

template <class T>
class Tree {
  private:
    class Node {
      private:
        T m_data;
        size_t m_childreSize;
        Node* m_parent;
        Vector<Node*> m_children;
      friend class Tree;
    };
    
    /**
     * Genera un nodo con almacenanto un dato
     * @param p_data es el dato a almacenar en el nodo
     */
    Node* generateNode(T p_data /*, parent*/) {
      Node* newNode = new Node;
      newNode->m_data = p_data;
      //newNode->m_parent = parent;
      //newNode->m_children = nullptr;
      return newNode;
    }

    /**
     * Genera un nodo con almacenanto un dato
     * @param p_data es el dato a almacenar en el nodo
     */
    Node* generateNode(T p_data, size_t p_chldnSize) {
      Node* newNode = new Node;
      newNode->m_data = p_data;
      newNode->m_childreSize = p_chldnSize;
      return newNode;
    }

    Node*& getRootNode() {
      return m_pRoot;
    }

    Node* pBFS(T p_data) {
      Queue<Node*> q;
      q.enqueue(getRootNode());
      while(q.peek()) {
        if (q.peek()->m_data == p_data) {
          return q.peek();
        }
        for (int i = 0; i < q.peek()->m_children.size(); i++) {
          q.enqueue(q.peek()->m_children[i]);
        }
        q.dequeue();
      }
      return nullptr;
    }

    static Node* m_pRoot;
    //size_t m_size;

    public:
    /*Tree<T>() noexcept {
      m_pRoot = nullptr;
    }*/
    Tree<T>(T data) noexcept {
      Node* pNewNode = generateNode(data);
      m_pRoot = pNewNode;
    }
    void insert(T p_parent, T p_data);
    bool BFS(T p_data);
    /*void remove(T p_data);
    void removeAll(T p_data);
    void removeAt(size_t p_index);*/
    void traverseBFS();
    void traverseDFS();
};


/**
 *
 *
 */
template <class T>
typename Tree<T>::Node* Tree<T>::m_pRoot = nullptr;

/**
 *
 *
 */
template <class T>
void Tree<T>::insert(T p_parent, T p_data) {
  Node* pParent = pBFS(p_parent);
  if ( pParent && !BFS(p_data) ) {
    // vefiricar que el nodo todavía puede agregar otro child
    Node* pNewNode = generateNode(p_data);
    pParent->m_children.push_back(pNewNode);
  }
}

/**
 *
 *
 */
template <class T>
bool Tree<T>::BFS(T p_data) {
  Queue<Node*> q;
  q.enqueue(getRootNode());
  while(q.peek()) {
    if (q.peek()->m_data == p_data) {
      return true;
    }
    for (int i = 0; i < q.peek()->m_children.size(); i++) {
      q.enqueue(q.peek()->m_children[i]);
    }
    q.dequeue();
  }
  return false;
}


/**
 *
 *
 */
template <class T>
void Tree<T>::traverseBFS() {
  Queue<Node*> q;
  q.enqueue(getRootNode());
  while(q.peek()) {
    cout << q.peek()->m_data << "->[";
    for (int i = 0; i < q.peek()->m_children.size(); i++) {
      q.enqueue(q.peek()->m_children[i]);
      cout << q.peek()->m_children[i]->m_data << (i == q.peek()->m_children.size() - 1 ? "":",");
    }
    cout << "]\n";
    q.dequeue();
  }
}