#ifndef _ISORT_H_ 
#define _ISORT_H_ 

#include<iostream>
#include<vector>
#include<algorithm>


// Verzija s indeksima
template <typename Record>
void insertion_sort_ind(std::vector<Record> & vec)
{
    for(size_t j = 1; j < vec.size(); ++j)
     {
         Record a = vec[j];
         int i = j-1;

         while(i >= 0 && vec[i] > a){
                vec[i+1] = vec[i];
                i--;
        }
        vec[i+1] = a;
     }
}


// Verzija koja uzima iterator range -- koristiti samo std::next i std::prev
template <typename Iter>
void insertion_sort(Iter first, Iter last) {
    for(auto it = std::next(first); it != last; ++it)
     {
         auto a = *it;
         auto i = std::prev(it), i_next = it;

         for (; i_next != first && *i > a; --i, --i_next) {
                *i_next=*i;
         }
         *i_next=a;
     }
}

// verzija sa algoritmima std::rotate i std::upper_bound
template <typename Iter>
void insertion_sort1(Iter first, Iter last) {
    for(auto it = first; it != last; ++it)
     {
         auto const i = std::upper_bound(first, it, *it);
         std::rotate(i, it, it+1);
     }
}


#endif
