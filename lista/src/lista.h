#ifndef LISTA_H
#define LISTA_H 

#include <cstddef>  // za std::size_t
#include <stdexcept>
#include <cassert>
#include <iostream>

using namespace std;

template <typename> class ListTest;

// Paramtrizirana struktura koja predstavlja čvor u listi.
// Sadrži vrijednost (value) i pokazivače na prethodni i sljedeći
// element u listi.
template <typename T>
struct Node{
	T value{};
	Node * previous = nullptr;
	Node * next = nullptr;
};

/**
 * Dvostruko povezana lista s elementima indeksiranim cjelobrojnim indeksima.
 * Indeksi elemenata počinju s nulom. Sve metode koje uzimaju indeks provjeravaju
 * da li je unutar granica i u suprotnom izbacuju std::runtime_error.  
 **/
template <typename T>
class List{
    friend class ListTest<T>;
	public:
		// Konstruktor
		List() :  mSize(0), mPositionIdx(0), mStart(nullptr), mPosition(nullptr) {}

		// Destruktor
		~List() { clear(); }

		// Obriši (dealociraj) sve elemente liste. 
		void clear();

		// Da li je lista prazna?
		bool empty() const;

		// Broj elemenata u listi. 
		std::size_t size() const;

        // Ubaci element "t" na poziciju "i" u listi. Pozicija "i" mora biti važeća
		// i tada se element ubacuje na to mjesto, a prijašnji "i"-ti element postaje 
		// "i"+1-vi element. Pozicija "i" može biti jednaka size()  i tada se element ubacuje na kraj liste. 
		// Metoda mora ispravno ubacivati i u praznu listu. Metoda pozicionira listu na novom
		// i-tom elementu (pozivom metode setPosition()). 
        // Novi element se alocira dinamički pomoću new operatora.
		void insert(std::size_t i, T const & t);

		// Izbaciti element iz liste i dealocirati ga pomoću delete. Trenutna pozicija
		// nakon izbacivanja pokazuje na prethodni element ako postoji; kada se izabacuje prvi element
		// onda pokazuje na novi prvi element ili lista ostaje prazna. 
		void remove(std::size_t i);

		// Postaviti trenutnu poziciju na i-to mjesto. Dozvoljeni "i" ide od 0 do 
		// size()-1. Inače izbaci izuzetak std::runtime_error.
		void setPosition(std::size_t i) const;

		// Vrati selektirani element. Konstantan verzija.
        T const & current() const;

		// Vrati selektirani element. Nekonstantna verzija.
        T & current();

        // Dodaje element na kraj liste. Listu pozicionira na novom elementu.
		void push_back(T const & t);

        // Sortira listu pomoću operatora <. Implementirati "insertion sort".
        void sort();
	private:
	   std::size_t mSize;
       mutable std::size_t mPositionIdx;  //index trenutne pozicije u listi
       Node<T> * mStart;
       mutable Node<T> * mPosition; //pokazivač na trenutnu poziciju u listi

	   // Vrati pokazivač na selektirani node.
	   Node<T> * currentNode() { return mPosition; }
};


template <typename T>
bool List<T>::empty() const { 
  // Implementacija
    if(mSize==0) return 1;
    return 0;
}

template <typename T>
std::size_t List<T>::size() const { return mSize; }

template <typename T>
T const & List<T>::current() const {
 // Implementacija
    const T val=mPosition->value;
    return val;
}

template <typename T>
T & List<T>::current() {
 // Implementacija
    return mPosition->value;
}

template <typename T>
void List<T>::setPosition(std::size_t i) const{
 // Implementacija
    if(i<0 || i>size()-1)
        throw runtime_error("Index nije u rasponu1.");
    mPositionIdx=i;
    auto it=mStart;
    size_t j=0;
    while(j<i && it->next!=nullptr){
        it=it->next;
        j++;
    }
    mPosition=it;
    return;
}


template <typename T>
void List<T>::insert(std::size_t i, T const & t){
 // Implementacija
    if(i<0 || i>size())
        throw runtime_error("Index nije u rasponu2.");
    Node<T> *N;
    N=new Node<T>;
    if(empty()){
        N->value=t;
        N->next=nullptr;
        N->previous=nullptr;
        mStart=N;
    }
    else if(i==0){
        setPosition(i);
        N->value=t;
        N->next=mPosition;
        N->previous=nullptr;
        mPosition->previous=N;
        mStart=N;
    }
    else if(i==size())
    {
        setPosition(i-1);
        N->value=t;
        N->next=nullptr;
        N->previous=mPosition;
        mPosition->next=N;
    }
    else
    {
        setPosition(i);
        N->value=t;
        N->next=mPosition;
        N->previous=mPosition->previous;
        mPosition->previous=N;
        setPosition(i-1);
        mPosition->next=N;
    }
    mSize++;
    setPosition(i);
}

template <typename T>
void List<T>::remove(std::size_t i){
 // Implementacija
    setPosition(i);
    if(i==0)
    {
        Node<T> *N = mStart;
        auto it=N->next;
        if(it==nullptr)
        {
            mSize--;
            mStart=nullptr;
            delete N;
            setPosition(0);
            return;
        }
        it->previous= nullptr;
        mStart=it;
        setPosition(0);
        delete N;
        mSize--;
        return;
    }
    else if(i!=size()-1){
        Node<T> *N = mPosition;
        auto ip=N->previous;
        auto in=N->next;
        ip->next=in;
        in->previous=ip;
        setPosition(i-1);
        delete N;
        mSize--;
        return;
    }
    else{
        Node<T> *N = mPosition;
        auto ip=N->previous;
        ip->next=nullptr;
        setPosition(i-1);
        delete N;
        mSize--;
        return;
    }

}

template <typename T>
void List<T>::clear(){
 // Implementacija
    while(mSize)
    {
        remove(0);
    }
}

template <typename T>
void List<T>::push_back(T const & t) {
 // Implementacija
    insert(size(),t);
}

template <typename T>
void List<T>::sort() {
 // Implementacija
    for(size_t j = 1; j < size(); ++j)
         {
             setPosition(j);
             T a = mPosition->value;
             int i = j-1;
             setPosition(i);
             while(i >= 0 && mPosition->value > a){
                    mPosition->next->value = mPosition->value;
                    i--;
                    if(i>=0) setPosition(i);
            }
            if(i<0)
            {
                setPosition(0);
                mPosition->value = a;
            }
            else mPosition->next->value = a;
         }
}

#endif /* LISTA_H */
