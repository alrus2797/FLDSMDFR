#include "proceso.h"
#include <queue>
using namespace std;




class cola_procesos{
public:
  cola_procesos(){}
  ~cola_procesos(){}
  priority_queue<proceso, vector<proceso>, compareProceso> heap_procesos;
  void add_proceso(proceso p){
    heap_procesos.push(p);
  }

  proceso get_proceso(){
    proceso res = heap_procesos.top();
    heap_procesos.pop();
    return res;
  }


};
