#include "vect.h"

using namespace std;

int main()
{
    // Vaši testovi dolaze ovdje.
    Vect<double> a;  // prazan vektor

    cout <<"Prazan vektor "; cout << a << endl;

    a.push_back(1.0);
    cout<< a << endl;
    a.push_back(2.0);
    a.push_back(3.0);
    cout<< a << endl;


    Vect<int> b(4,2);
    cout << b << endl;

    cout << b.two_norm()<<endl;
    b*=2;
    cout << b << endl;

    return 0;
}
