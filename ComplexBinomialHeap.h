//
// Created by Artem on 26.04.2022.
//

#ifndef COMPLEXBINOMIALHEAP_H
#define COMPLEXBINOMIALHEAP_H

#include "Complex.h"

class ComplexBinomialHeap
{
    struct HeapNode
    {
        Complex key;
        HeapNode* p; //parent
        HeapNode* child; //left child
        HeapNode* sibling; //right sibling
        size_t degree;

        HeapNode() : key(0), p(nullptr), child(nullptr), sibling(nullptr), degree(0) {};
        HeapNode(const Complex& key, HeapNode* p, HeapNode* child, HeapNode* sibling, size_t degree)
            : key(key), p(p), child(child), sibling(sibling), degree(degree) {};
        explicit HeapNode(const Complex& key) : key(key), p(nullptr), child(nullptr), sibling(nullptr), degree(0) {};
        void clearNodeTree();
    };
    HeapNode* head;

    static ComplexBinomialHeap connect(ComplexBinomialHeap& first, ComplexBinomialHeap& second);
    static void linkNodes(HeapNode& first, HeapNode& second);
public:
    ComplexBinomialHeap() : head(nullptr) {}; //створення порожньої біноміальної піраміди
    ~ComplexBinomialHeap();
    bool empty() const;
    void clear();
    Complex min() const; //пошук мінімального ключа
    static ComplexBinomialHeap merge(ComplexBinomialHeap& first, ComplexBinomialHeap& second); //злиття двох біноміальних пірамід
    //void insert(const Complex& k); //вставка вузла
    //Complex extractMin(); //вилучення мінімального вузла
    //bool decrease(const Complex& old, const Complex& current); //зменшення ключа
    //bool remove(const Complex& k); //видалення ключа
};


#endif
