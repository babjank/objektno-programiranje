#ifndef _VECT_H_IS_INCLUDED_
#define _VECT_H_IS_INCLUDED_

#include <iostream>
#include <string>
#include <memory>

// deklaracija potrebna za testiranje
template <typename> class VectTest;

template <typename T>
class Vect
{
    friend class VectTest<T>;  // da testovi mogu dohvatiti privatne varijable
public:
    explicit Vect(size_t n = 0, T v= {});  // Ctor
    // Kontrola kopiranja dolazi ovdje
    Vect(const Vect& v);                            // CCtor
    Vect(Vect && v) noexcept;                       // MCtor

    Vect& operator=(const Vect & v);                 // OP
    Vect& operator=(Vect && v) noexcept;            // MOP
    ~Vect(){ free(); }// DTOR

    // dohvat elemenata (operator [])
    T  operator[](size_t i) const { return mdata[i]; }
    T& operator[](size_t i)       { return mdata[i]; }

    // push_back metoda
    void push_back(T v);

     // info rutine size() i capacity()
     size_t size() const { return mfirst_free-mdata; }
     size_t capacity() const { return mend-mdata; }

     // operatori +=, -=, *=
     Vect& operator+=(const Vect & v);
     Vect& operator-=(const Vect & v);
     Vect& operator*=(T const & v);


     // euklidska norma vraća double !
     double two_norm() const;
private:
        T *mdata;       // pokazivač na prvi element
        T *mfirst_free; // pokazivač na prvo slobodno mjesto
        T *mend;        // pokazivač na kraj alociranog prostora
                             // (jedno mjesto iza posljednjeg)
  
        // Oslobodi zauzeti prostor (pomoću alokatora)
        void free();

      	// realociraj na novu lokaciju. Povećaj dimenziju vektora 2 puta; ako je 
        // vektor prazan alociraj jedan element. 
        void reallocate();

        // dodati vlastite privatne metode.
        bool slobodno() {if(size()==capacity()) return false; return true;}
	
        // alokator ne mora imati pristup varijablama članicama klase pa ga činimo 
        // statičkim. Ne zaboraviti definirati ga.
        static std::allocator<T> alloc;
};

// Deklaracija operator +, - i <<
template <typename T>
Vect<T> operator+(Vect<T> const & v1, Vect<T> const & v2);

template <typename T>
Vect<T> operator-(Vect<T> const & v1, Vect<T> const & v2);

template <typename T>
std::ostream & operator<<(std::ostream & out, Vect<T> const & v);

// Implementacija je u posebnoj .h datoteci
#include "vect_impl.h"

#endif
