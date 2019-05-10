#include "lista.h"


int main()
{
// Ovdje pišete vlastite testove klase.
    List<int> L;
    if(L.empty()==true) cout<<"Prazno!"<<endl;

    L.push_back(2);
    L.push_back(3);
    L.push_back(4);
    cout <<L.current()<<endl;
    cout <<L.size()<<endl;

    L.remove(1);
    cout <<L.current()<<endl;
    cout <<L.size()<<endl;
    L.remove(0);
    cout <<L.current()<<endl;
    cout <<L.size()<<endl;

    L.insert(0,28);
    L.insert(1,39);
    cout <<L.current()<<endl;
    cout <<L.size()<<endl;

    L.sort();
    L.setPosition(0);
    cout<<L.current()<<endl;

    L.insert(0,1);
    L.insert(0,2);
    L.insert(1,3);
    L.push_back(4);
    L.remove(1);
    L.remove(1);
    L.remove(1);
    L.remove(0);
    L.clear();
   
  return 0;
}
 
