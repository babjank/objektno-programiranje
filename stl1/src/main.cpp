#include "zadatak.h"
#include <iostream>

int main()
{
    std::vector<int> vec = zadatak1("../../src/brojevi.txt");
    zadatak2("../../src/fpbrojevi.txt");
    std::list<int> l = zadatak3();

    return 0;
}
