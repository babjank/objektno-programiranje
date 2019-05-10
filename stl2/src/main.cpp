#include <iostream>
#include <set>
#include <map>
#include <vector>
#include <string>
#include <algorithm>
#include <iterator>
#include <utility>
#include <cassert>
#include <cctype>
#include <fstream>
#include "zadatak.h"

using namespace std;

int main()
{
    // Ovdje napisati svoje vlastite testove!
    const string s = "    a, b, b, b, c, \n c c c ";
    auto it = s.begin();
    string rijec = procitaj_rijec(it, s.end());
    cout << rijec << endl;
    rijec = procitaj_rijec(it, s.end());
    cout << rijec << endl;
    rijec = procitaj_rijec(it, s.end());
    cout << rijec << endl;
    rijec = procitaj_rijec(it, s.end());
    cout << rijec << endl;
    rijec = procitaj_rijec(it, s.end());
    cout << rijec << endl;
    rijec = procitaj_rijec(it, s.end());
    cout << rijec << endl;


    map<string, int> word_list;

    procitaj_datoteku("1.txt", word_list);

    for(auto x : word_list)
    {
        cout << "Rijec: " <<x.first <<" ponavljanje: " <<x.second<<endl;
    }

    pair< list<string>, int> p;
    list<string> l;
    p = naj(word_list);
    l = p.first;
    for(auto x : l)
    {
        cout << "Rijec: " << x <<" ";
    }
    cout<<"Broj ponavljanja: "<<p.second<<endl;

    multimap< string,  string> grupe;
    pair<string, string> pp;
    pp.first = "grupa1";
    pp.second ="a";
    grupe.insert(pp);
    pp.first = "grupa1";
    pp.second ="b";
    grupe.insert(pp);
    pp.first = "grupa2";
    pp.second ="c";
    grupe.insert(pp);

    vector<int> v=broj_iz_grupe(word_list, grupe);
    int i=1;
    for(auto x : v)
    {
        cout << "Broj riječi grupe" << i <<": "<< x <<endl;
        i++;
    }
    return 0;
}
