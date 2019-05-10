#include "isort.h"

#include<iostream>
#include<vector>
#include<algorithm>

template <typename T>
void print(std::vector<T> vec){
    for(T x :vec)
        std::cout << x << " ";
    std::cout<<std::endl;
}

int main()
{
    // Testirajte vaše algoritme na vektoru i listi. 
    std::vector<int> veca{2, 1, 5, 3, 7, 5, 4, 6};
        std::vector<std::string> vecb{"Bjana", "Matea", "Valen", "Monik", "Kreso"};
        std::vector<int> vecc{1, 1, 5, 3, 7, 5, 4, 6};

        insertion_sort_ind(veca);
        insertion_sort(vecc.begin(), vecc.end());
        insertion_sort1(vecb.begin(), vecb.end());

        print(veca);
        print(vecb);
        print(vecc);

    return 0;
}
