#ifndef HEAPPRIO_H
#define HEAPPRIO_H

#include "Estructura.h"
#include <queue>

template<class T>
class HeapPrio: public Estructura<T>{
public:
  HeapPrio(){}
  ~HeapPrio(){}
  void pop();
  T top();
  void push(T);
  bool empty();
private:
  //list<proceso*> cola;
  priority_queue<proceso*, vector<proceso*>, comparePrio> cola;
};


template<class T>
void HeapPrio<T>::pop(){
  cola.pop();
}

template<class T>
T HeapPrio<T>::top(){
  return cola.top();
}

template<class T>
void HeapPrio<T>::push(T d){
  cola.push(d);
}

template<class T>
bool HeapPrio<T>::empty(){
  return cola.empty();
}

#endif
