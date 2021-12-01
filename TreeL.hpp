//#include "LinkedList.hpp"
#include "Queue.hpp"
#include "Stack.hpp"
#include <list>

template <class T>
class TreeL {
  private:
    class NodeTL {
      private:
        T m_data;
        //NodeTL* m_parent;
        std::list<NodeTL*> m_children;
      friend class TreeL;
    };
    
    /**
     * Genera un nodo con almacenanto un dato
     * @param p_data es el dato a almacenar en el nodo
     */
    NodeTL* generateNodeTL(T p_data /*, parent*/) {
      NodeTL* newNodeTL = new NodeTL;
      newNodeTL->m_data = p_data;
      return newNodeTL;
    }

    NodeTL*& getRootNodeTL() {
      return m_pRoot;
    }

    NodeTL* pBFS(T p_data) {
      Queue<NodeTL*> q;
      q.enqueue(getRootNodeTL());
      while(q.peek()) {
        //traverseBFS();
        if (q.peek()->m_data == p_data) {
          return q.peek();
        }/*
        for (int i = 0; i < q.peek()->m_children.size(); i++) {
          q.enqueue(q.peek()->m_children.at(i));
        }*/
        for (auto it = q.peek()->m_children.begin(); it != q.peek()->m_children.end(); it++) {
          q.enqueue(*it);
        }
        q.dequeue();
      }
      return nullptr;
    }

    static NodeTL* m_pRoot;
    //size_t m_size;

    public:
    /*TreeL<T>() noexcept {
      m_pRoot = nullptr;
    }*/
    TreeL<T>(T p_data) noexcept {
      NodeTL* pNewNodeTL = generateNodeTL(p_data);
      m_pRoot = pNewNodeTL;
    }
    void insert(T p_parent, T p_data);
    bool BFS(T p_data);
    /*void remove(T p_data);
    void removeAll(T p_data);
    void removeAt(size_t p_index);*/
    void traverseBFS();
    void traverseDFS();
    void printRoot();
};


/**
 *
 *
 */
template <class T>
typename TreeL<T>::NodeTL* TreeL<T>::m_pRoot = nullptr;

/**
 *
 *
 */
template <class T>
void TreeL<T>::insert(T p_parent, T p_data) {
  NodeTL* pParent = pBFS(p_parent);
  cout << "parent: " << pParent->m_data << "\n" ;
  if ( pParent && !BFS(p_data) ) {
    NodeTL* pNewNodeTL = generateNodeTL(p_data);
    pParent->m_children.push_back(pNewNodeTL);
    //cout << "new child: " << pParent->m_children.at(0)->m_data << "\n";
  }
  //pParent->m_children.traverse();
}

template <class T>
void TreeL<T>::printRoot() {
  cout << "root &: " << getRootNodeTL() << " data: " << getRootNodeTL()->m_children.size() << &getRootNodeTL()->m_children << ": [";/*
  for (int i = 0; i < getRootNodeTL()->m_children.size(); i++ ) {
    cout << getRootNodeTL()->m_children[i] << "," ;
  }*/
  //getRootNodeTL()->m_children.traverse(); 
  cout << "]\n";
}

/**
 *
 *
 */
template <class T>
bool TreeL<T>::BFS(T p_data) {
  Queue<NodeTL*> q;
  q.enqueue(getRootNodeTL());
  while(q.peek()) {
    if (q.peek()->m_data == p_data) {
      return true;
    }
    /*for (int i = 0; i < q.peek()->m_children.size(); i++) {
      q.enqueue(q.peek()->m_children.at(i));
    }*/
    for (auto it = q.peek()->m_children.begin(); it != q.peek()->m_children.end(); it++) {
      q.enqueue(*it);
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
void TreeL<T>::traverseBFS() {
  Queue<NodeTL*> q;
  q.enqueue(getRootNodeTL());
  while(q.peek()) {
    cout << q.peek()->m_data << " size(" << q.peek()->m_children.size() << ")->[";
    /*for (int i = 0; i < q.peek()->m_children.size(); i++) {
      q.enqueue(q.peek()->m_children.at(i));
      cout << q.peek()->m_children.at(i)->m_data << (i == q.peek()->m_children.size() - 1 ? "":",");
    }*/
    for (auto it = q.peek()->m_children.begin(); it != q.peek()->m_children.end(); it++) {
      q.enqueue(*it);
      cout << *it << ", ";
    }
    cout << "]\n";
    q.dequeue();
  }
}