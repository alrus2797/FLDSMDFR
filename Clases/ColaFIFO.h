#ifndef COLAFIFO_H
#define COLAFIFO_H

#include "Estructura.h"

template<class T>
class ColaFIFO: public Estructura<T>{
public:
  ColaFIFO(){}
  ~ColaFIFO(){}
  void pop();
  T top();
  void push(T);
  bool empty();
private:
  list<proceso*> cola;
};


template<class T>
void ColaFIFO<T>::pop(){
  cola.pop_front();
}

template<class T>
T ColaFIFO<T>::top(){
  return cola.front();
}

template<class T>
void ColaFIFO<T>::push(T d){
  cola.push_back(d);
}

template<class T>
bool ColaFIFO<T>::empty(){
  return cola.empty();
}

#endif
