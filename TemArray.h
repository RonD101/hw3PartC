//
// Created by Ron Dahan on 20/06/2020.
//

#ifndef HW3PARTB_TEMARRAY_H
#define HW3PARTB_TEMARRAY_H

#include <iostream>
#include "Auxiliaries.h"
#include <string>

namespace mtm {
    template<class T>
    class TemArray {
        T *data;
        int length;
    public:
        class BadAccess;
        explicit TemArray(int size = 10);

        TemArray(const TemArray<T> &a);

        ~TemArray();

        TemArray &operator=(const TemArray<T> &a);

        int size() const;

        T &operator[](int index);

        const T &operator[](int index) const;
    };

    template<class T>
    TemArray<T>::TemArray(int size) {
        data = new T[size];
        length = size;
    }

    template<class T>
    TemArray<T>::TemArray(const TemArray<T> &a) {
        data = new T[a.size()];
        length = a.size();
        for (int i = 0; i < a.size(); ++i) {
            data[i] = a[i];
        }
    }

    template<class T>
    TemArray<T>::~TemArray() {
        delete[] data;
    }

    template<class T>
    TemArray<T>& TemArray<T>::operator=(const TemArray<T> &a) {
        if (this == &a) {
            return *this;
        }
        T *temp_array = new T[a.size()];
        delete[] data;
        for (int i = 0; i < a.size(); ++i) {
            try {
                temp_array[i] = a[i];
            }
            catch (const std::exception &e) {
                delete[] temp_array;
                throw e;
            }
        }
        data = temp_array;
        length = a.size();
        return *this;
    }

    template<class T>
    int TemArray<T>::size() const {
        return length;
    }

    template<class T>
    T &TemArray<T>::operator[](int index) {
        if (index < 0 || index >= this->size()) {
            throw TemArray::BadAccess();
        }
        return data[index];
    }

    template<class T>
    const T &TemArray<T>::operator[](int index) const {
        if (index < 0 || index >= this->size()) {
            throw TemArray::BadAccess();
        }
        return data[index];
    }

    template <class T>
    class TemArray<T>::BadAccess : public std::exception {
    public:
        const char* what() const noexcept override
        {
            return "Bad Access";
        }
    };
}

#endif //HW3PARTB_TEMARRAY_H
