#include "zadatak.h"
#include <iostream>
#include <algorithm>
#include <iterator>
#include <stdexcept>
#include <fstream>
#include <cmath>
#include <cassert>

// Ubaciti potrebne include datoteke

using namespace std;

std::vector<int> zadatak1(std::string const & file_name){
  // Implementacija zadatka 1
    ifstream in(file_name);
    if(!in)
        throw runtime_error("Otvaranje nije uspjelo");

    istream_iterator<int> isi(in);
    istream_iterator<int> isi_end;

    vector<int> vec(isi, isi_end);

    replace(vec.begin(),vec.end(),0,9);
    return vec;
}

void zadatak2(std::string const & file_name){
  // Implementacija zadatka 2
    ifstream in(file_name);
    if(!in)
        throw runtime_error("Otvaranje nije uspjelo");

    istream_iterator<float> isi(in);
    istream_iterator<float> isi_end;

    vector<float> vi;
    copy(isi, isi_end, back_inserter(vi));

    ofstream file("3cols.txt");
    if(!file)
        throw runtime_error("Nije uspjelo");
    for(size_t i=0; i<vi.size(); i++){
        file << scientific << showpos << vi[i] << " "<< showpos << sin(vi[i]) << " "<< showpos << exp(vi[i]) << endl;
    }
    file.close();
}

std::list<int> zadatak3(){
  // Implementacija zadatka 3
    list<int> la{1,2,3,4,5,6,7,8,9};
    list<int> lb{1,2,3,4,5,6,7,8,9};

    while(*(la.begin())!=5)
        next_permutation(la.begin(),la.end());
    while(*(lb.begin())!=9)
        next_permutation(lb.begin(),lb.end());

    auto it4= find(lb.begin(),lb.end(),4);
    assert(it4!=lb.end());
    auto it7= find(lb.begin(),lb.end(),7);
    assert(it7!=lb.end());
    auto it3= find(la.begin(),la.end(),3);
    assert(it3!=la.end());

    la.splice(it3, lb, it4, it7);

    return la;
}

