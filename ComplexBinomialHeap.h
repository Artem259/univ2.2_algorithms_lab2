//
// Created by Artem on 26.04.2022.
//

#ifndef COMPLEXBINOMIALHEAP_H
#define COMPLEXBINOMIALHEAP_H

#include <memory>
#include "Complex.h"

class ComplexBinomialHeap
{
    struct HeapNode
    {
        Complex key;
        std::shared_ptr<HeapNode> p; //parent
        std::shared_ptr<HeapNode> child; //left child
        std::shared_ptr<HeapNode> sibling; //right
        size_t degree;
        HeapNode() : key(0), p(nullptr), child(nullptr), sibling(nullptr), degree(0) {};
        explicit HeapNode(const Complex& key) : key(key), p(nullptr), child(nullptr), sibling(nullptr), degree(0) {};
    };
    std::shared_ptr<HeapNode> head;
public:
    ComplexBinomialHeap() : head(nullptr) {}; //створення порожньої біноміальної піраміди
    //Complex min() const; //пошук мінімального ключа
    //ComplexBinomialHeap merge(const ComplexBinomialHeap& first, const ComplexBinomialHeap& second); //злиття двох біноміальних пірамід
    //void insert(const Complex& k); //вставка вузла
    //Complex extractMin(); //вилучення мінімального вузла
    //bool decrease(const Complex& old, const Complex& current); //зменшення ключа
    //bool remove(const Complex& k); //видалення ключа
};


#endif
