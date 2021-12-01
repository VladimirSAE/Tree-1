#include <iostream>
#include "Tree.hpp"
#include "TreeL.hpp"

int main() {
  Vector<int> v;
  v.push_back(3);
  v.push_back(4);
  v.push_back(6);
  Vector<int> v2(v);
  v2[0] = 1;
  std::cout << (v == v2) <<" !\n";
  v2 = v;
  std::cout << (v == v2) <<" !\n";
  /*LinkedList<int*> ll; int i = 0;
  int * pi = &i; 
  ll.push_back(pi);
  ll.push_back(pi);
  cout << ll[0] << "\n";
  cout << ll.at(1) << "\n";*/
  /*
  LinkedList<LinkedList<int*>> pll;
  pll.push_back(ll);
  LinkedList<int*> llt = pll[0];
  cout << *llt[0] << "\n";*/
  //cout << ll.at(3) << "\n";
  
  TreeL<int> t(0);
  t.insert(0, 10);
  //t.printRoot();
  //t.traverseBFS();
  t.insert(0, 11);
  //t.printRoot();
  //t.insert(0, 12);
  //t.printRoot();
  t.insert(0, 12);
  t.insert(10, 20);
  t.insert(11, 30);
  t.insert(12, 40);
  t.insert(0, 50);
  t.traverseBFS();
  //cout << std::boolalpha << t.BFS(10) << "\n"; 

  /*
  try {
    v[3] = 45;
    std::cout << v[2] <<" !\n";
  } catch(std::out_of_range e) {
    std::cout << e.what() << "\n"; 
  }
  */
}