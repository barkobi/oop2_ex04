#pragma once
#include "iostream"
#include "Consts.h"
#include "vector"
#include "iostream"
#include "Consts.h"
#include "MosaicNode.h"

template<typename T>
class Mosaic {
private:
    std::vector<MosaicNode<T>*> data;
public:
    ~Mosaic() = default;
    // Add element to the data structure
    void add(T *element) {
        data.push_back(element);
    }

    // Get element at index
    T &operator[](int index) {
        return data[index];
    }

    // Iterator class
    class iterator {
    private:
        T *ptr;
    public:
        explicit iterator(T *p) : ptr(p) {}
        ~iterator() = default;

        iterator &operator++() {
            if (ptr) {
                ptr++;
            }
            return *this;
        }
        iterator operator++(int) {
            iterator tmp = *this;
            ++(*this);
            return tmp;
        }

        T &operator*() {
            return *ptr;
        }

        bool operator==(const iterator &other) const { return ptr == other.ptr; }

        bool operator!=(const iterator &other) const { return ptr != other.ptr; }
    };

    // Begin iterator
    iterator begin() {
        return iterator(&data[0]);
    }

    // End iterator
    iterator end() {
        return iterator(&data[data.size()]);
    }
};
