#include "heapP.h"

int main(){
  cola_procesos a;
  proceso p1("p1", 10);
  proceso p2("p2", 5);
  a.add_proceso(p1);
  a.add_proceso(p2);

  proceso p3 = a.get_proceso();
  cout<< p3.prioridad<<endl;

}
