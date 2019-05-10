// Vaša implementacija dolazi ovdje.
#include "vect.h"

#include <iostream>
#include <stdexcept>
#include <cmath>
#include <cassert>
#include <utility>
#include <string>

template <typename T>
std::allocator<T> Vect<T>::alloc;

template <typename T>
Vect<T>::Vect(size_t n, T v ):mdata(nullptr),mfirst_free(nullptr),mend(nullptr)
{
    if(n>0)
    {
        mdata = alloc.allocate(n);
        for(size_t i=0; i<n; ++i) alloc.construct(mdata+i, v);
        mfirst_free = mend = mdata+n;
    }
}


template <typename T>
Vect<T>::Vect(const Vect& v): mdata(nullptr),mfirst_free(nullptr),mend(nullptr)
{
    size_t n=v.size();
    if(n>0)
    {
        mdata = alloc.allocate(n);
        mfirst_free = mend = mdata + n;
        for(size_t i=0; i<n; ++i) alloc.construct(mdata+i, v[i]);
    }
}

template <typename T>
Vect<T>::Vect(Vect && v) noexcept : mdata(v.mdata),mfirst_free(v.mfirst_free),mend(v.mend)
{
    v.mdata=nullptr;
    v.mfirst_free=nullptr;
    v.mend=nullptr;
}


template <typename T>
Vect<T>& Vect<T>::operator=(const Vect& v)
{
    if(this->mdata != v.mdata)
    {
        size_t n=v.size();
        mdata = alloc.allocate(n);
        mfirst_free = mend = mdata + n;
        for(size_t i=0; i<n; ++i) alloc.construct(mdata+i, v[i]);
    }
    return *this;
}

template <typename T>
Vect<T>& Vect<T>::operator=(Vect && v) noexcept
{
    if(this != &v)
    {
        free();
        mdata = v.mdata;
        mend  = v.mend;
        mfirst_free = v.mfirst_free;

        v.mdata = nullptr;
        v.mfirst_free = nullptr;
        v.mend = nullptr;
    }
    return *this;
}

template <typename T>
void Vect<T>::free(){
    if(mdata!=nullptr){
        for(size_t i=size(); i>0; i--) alloc.destroy(mdata+i-1);
        alloc.deallocate(mdata,capacity());
    }
}

template <typename T>
void Vect<T>::reallocate(){
    size_t n;
    if(size()==0) n=1;
    else n=2*size();
    T * n_mdata=alloc.allocate(n);
    T * n_mfirst_free=n_mdata+size();
    T * n_mend=n_mdata+n;

    for(size_t i=0; i<size(); ++i) alloc.construct(n_mdata + i, std::move(mdata[i]));

    free();
    mdata=n_mdata;
    mfirst_free=n_mfirst_free;
    mend=n_mend;
}

template <typename T>
void Vect<T>::push_back(T v){
    if( !slobodno() )
        reallocate();
    alloc.construct(mfirst_free++, v);
}

template <typename T>
Vect<T>& Vect<T>::operator+=(const Vect & v){
    for(size_t i=0; i<size(); ++i) mdata[i]+=v.mdata[i];
    return *this;
}

template <typename T>
Vect<T>& Vect<T>::operator-=(const Vect & v)
{
    for(size_t i=0; i<size(); ++i)  mdata[i]-=v.mdata[i];
    return *this;
}

template <typename T>
Vect<T>& Vect<T>::operator*=(T const & s)
{
    for(size_t i=0; i<size(); ++i) mdata[i]*=s;
    return *this;
}

template <typename T>
double Vect<T>::two_norm() const {
    double norm = 0.0;
    for(size_t i=0; i < size(); ++i) norm += mdata[i]*mdata[i];
    return std::sqrt(norm);
}

template <typename T>
Vect<T> operator+(Vect<T> const & v1, Vect<T> const & v2){
    Vect<T> tmp;
    if(v1.size()>=v2.size()){
        size_t i=0;
        for(; i<v2.size(); ++i) tmp.push_back(v1[i]+v2[i]);
        for(; i<v1.size(); ++i) tmp.push_back(v1[i]);
    }
    else{
        size_t i=0;
        for(; i<v1.size(); ++i) tmp.push_back(v1[i]+v2[i]);
        for(; i<v2.size(); ++i) tmp.push_back(v2[i]);
    }

    return tmp;
}

template <typename T>
Vect<T> operator-(Vect<T> const & v1, Vect<T> const & v2){
    Vect<T> tmp;
    if(v1.size()>=v2.size()){
        size_t i=0;
        for(; i<v2.size(); ++i) tmp.push_back(v1[i]-v2[i]);
        for(; i<v1.size(); ++i) tmp.push_back(v1[i]);
    }
    else{
        size_t i=0;
        for(; i<v1.size(); ++i) tmp.push_back(v1[i]-v2[i]);
        for(; i<v2.size(); ++i) tmp.push_back(-v2[i]);
    }

    return tmp;
}

template <typename T>
std::ostream & operator<<(std::ostream & out, Vect<T> const & v){
        out <<"[";
        for(size_t i=0; i < v.size(); ++i) {
                out << v[i];
                if(i+1 < v.size()) out << ",";
            }
        out <<"]";
  return out;
}
