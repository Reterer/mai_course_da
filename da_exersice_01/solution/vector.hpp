#pragma once
#include <stddef.h>

namespace NVector {

    template <class T>
    class TVector {
    public:
        // Создает вектор с нулевым размером
        TVector();
        // Создает вектор с размером size
        explicit TVector(size_t size);
        // Создает вектор с размером size и буфером размера cap
        explicit TVector(size_t size, size_t cap);
        ~TVector();

        // Меняет местами два вектора
        static void Swap(TVector<T> &a, TVector<T> &b);

        // Возвращает размер вектора
        size_t GetSize();
        // Добавляет элемент value в конец вектора
        void PushBack(T value);

        // Возвращает указатель на начало вектора
        T* begin();
        // Возвращает указатель на конец вектора
        T* end();
        // Возвращает i элемент вектора
        T& operator[] (size_t i);
    private:
        T* Buf;
        size_t Cap;
        size_t Size;
    };

    template <class T>
    TVector<T>::TVector() {
        Size = 0;
        Cap = 0;
        Buf = nullptr;
    }

    template <class T> 
    TVector<T>::TVector(size_t size) {
        Size = size;
        Cap  = size;
        Buf =  new T[size];
    }

    template <class T>
    TVector<T>::TVector(size_t size, size_t cap) {
        if(size > cap) {
            throw std::invalid_argument("size is greater than cap");
        }

        Size = size;
        Cap = cap;
        Buf =  new T[cap];
    }

    template <class T>
    TVector<T>::~TVector() {
        delete[] Buf;
    }

    template <class T>
    void LocalSwap(T &a, T &b) {
        T tmp = a;
        a = b;
        b = tmp;
    }

    template <class T>
    void TVector<T>::Swap(TVector<T> &a, TVector<T> &b) {
        LocalSwap(a.Cap, b.Cap);
        LocalSwap(a.Size, b.Size);
        LocalSwap(a.Buf, b.Buf);
    }

    template <class T>
    size_t TVector<T>::GetSize() {
        return Size;
    }

    template <class T>
    void TVector<T>::PushBack(T value) {
        if (Size == Cap) {     // Если нужно увеличить размер буффера
            if (Cap == 0) {
                Cap = 1;
            }
            else {
                Cap *= 2;
            }

            T *newBuf = new T[Cap];
            for(size_t i = 0; i < Size; ++i) {
                newBuf[i] = Buf[i];
            }

            delete[] Buf;
            Buf = newBuf;
        }

        Buf[Size++] = value;
    }

    template <class T>
    T* TVector<T>::begin() {
        return Buf;
    }

    template <class T>
    T* TVector<T>::end() {
        return Buf + Size;
    }

    template <class T>
    T& TVector<T>::operator[] (size_t i) {
        if (i >= Size) {
            throw std::out_of_range("idx is greater then size");
        }
        return Buf[i];
    } 
}
