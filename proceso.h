#include <iostream>


using namespace std;

class proceso{
public:
    proceso(){}
    proceso(string nom, int pr){
      nombre = nom;
      prioridad = pr;
    }
    ~proceso(){}


    string nombre;
    int prioridad = 0;
friend class compareProceso;
friend class heap;

};

class compareProceso
{
public:
  bool operator()(proceso& t1, proceso& t2) // Returns true if t1 is earlier than t2
  {
     if (t1.prioridad < t2.prioridad)
      return true;
     return false;
  }
};
