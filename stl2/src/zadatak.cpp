#include "zadatak.h"
// Ubaciti potrebne include datoteke
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

using namespace std;


// Zadan je raspon iteratora unutar stringa. Pročitati i vratiti prvu riječ iz stringa.
// Postaviti iterator it na prvu interpunkciju/bjelinu iza pročitane riječi ili na itend
// (end-iterator) ako takve nema.
// Riječi su cjeline međusobno odvojene bjelinama i/ili interpunkcijama: ,.!?:;()
// Bjeline su  \n\t\v.
std::string procitaj_rijec(std::string::const_iterator & it, std::string::const_iterator itend)
{
  // implementacija
    string str="", s;
    auto i = it;
    while((ispunct(*i) || isspace(*i)) && i!=itend)
        ++i;
    while(!ispunct(*i) && !isspace(*i) && i!=itend)
    {
        str += *i;
        ++i;
    }
    if(str=="") {
        it = itend;
        return s;
    }
    it = i;
    return str;
}

// Otvoriti datoteku file_name za čitanje, učitati tekst (npr. liniju po liniju)
// i smjestiti riječi u mapu. Riječ je ključ, a vrijednost je broj pnavljanja riječi.
// Riječ se učitava pomoću rutine ucitaj_rijec.
void procitaj_datoteku(std::string file_name, std::map<std::string,int> & word_list){
  // implementacija
    ifstream in(file_name);
    if(!in)
        throw runtime_error("Otvaranje neuspjelo");
    string l;
    while(getline(in, l))
    {
        string::const_iterator it=l.begin();
        while(it != l.end())
        {
            string rijec = procitaj_rijec(it, l.end());
            if(rijec=="") continue;
            auto mi = word_list.find(rijec);
            if(mi!=word_list.end())
                mi->second++;
            else word_list[rijec]=1;
        }
    }

}

// Vrati listu riječi koje se najčešće pojavljuju u mapi (std::list) i broj ponavljanja (int).
std::pair<std::list<std::string>, int> naj(std::map<std::string,int> const & word_list){
  // implementacija
    pair< list<string>, int> par;
    list<string> lista;
    int max=0;
    for(auto x : word_list)
    {
        if(x.second>max) max=x.second;
    }
    for(auto x : word_list)
    {
        if(x.second==max) lista.insert(lista.end(),x.first);
    }
    par.first = lista;
    par.second = max;
    return par;
}

// Argument grupe sadrži grupe riječi (ključ je ime grupe, a vrijednosti
// su riječi koje pripadaju grupi).
// Funkcija treba za svaku grupu riječi sumirati broj pojavljivanja svih riječi
// iz grupe u tekstu te vratiti vrijednosti u vektoru. Na i-tom mjestu u povratnom vektoru
// je broj pojavljivanja riječi iz i-te grupe (prema uređaju u multimap varijabli).
// Argument word_list je std::map svih riječi s brojem njihovih pojavljivanja.
std::vector<int>
broj_iz_grupe(std::map<std::string,int> const & word_list,
              std::multimap<std::string, std::string> const & grupe){

  // implementacija
    vector<int> vektor;
    map<string, int> mapa;
    int i;
    for(auto x:grupe)
    {
        string rijec=x.second;
        auto mi = word_list.find(rijec);
        if(mi==word_list.end()) i=0;
        else i=mi->second;

        auto mit = mapa.find(x.first);
        if(mit==mapa.end()) mapa[x.first]=i;
        else mit->second+=i;
    }

    for(auto x:mapa)
    {
        vektor.insert(vektor.end(),x.second);
    }
    return vektor;
}
