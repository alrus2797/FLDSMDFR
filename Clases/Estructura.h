#ifndef ESTRUCTURA_H
#define ESTRUCTURA_H


#include <iostream>
#include <vector>

using namespace std;


template<class T>
class Estructura{
public:
  Estructura(){}
  ~Estructura(){}
  virtual void push(T d){}
  virtual T top(){}
  virtual void pop(){}
  virtual bool empty(){}



private:

};



#endif
