//
// Created by Artem on 26.04.2022.
//

#ifndef COMPLEXBINOMIALHEAP_H
#define COMPLEXBINOMIALHEAP_H

#include "Complex.h"

class HeapNode;
class ComplexBinomialHeap;

/*----------------------------------------------
 * - Initialization:
 * auto foo = new ComplexBinomialHeap();
 * - Then:
 * delete foo;
 *
 * - extractMin():
 * auto bar = foo->extractMin();
 * - Then:
 * delete bar;
 *
 * - insert(...):
 * auto bar = foo->insert(...);
 * - Then: DO NOT delete
 *----------------------------------------------*/

class HeapNode
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
    void linkTo(HeapNode* target);
    void isolate();

    friend class ComplexBinomialHeap;
    friend ComplexBinomialHeap* merge(ComplexBinomialHeap* first, ComplexBinomialHeap* second);
    friend void decrease(HeapNode** node, const Complex& newKey);
public:
    Complex getKey() const;
};

class ComplexBinomialHeap
{
    HeapNode* head;
    size_t sizeN;

    static ComplexBinomialHeap* connect(ComplexBinomialHeap* first, ComplexBinomialHeap* second);
    static void decreaseHelp(HeapNode** node, const Complex& newKey);
    void reset();

    friend class HeapNode;
    friend ComplexBinomialHeap* merge(ComplexBinomialHeap* first, ComplexBinomialHeap* second);
    friend void decrease(HeapNode** node, const Complex& newKey);
public:
    ComplexBinomialHeap() : head(nullptr), sizeN(0) {}; //створення порожньої біноміальної піраміди
    ~ComplexBinomialHeap();
    bool empty() const;
    bool size() const;
    void clear();
    Complex min() const; //пошук мінімального ключа
    HeapNode* insert(const Complex& k); //вставка вузла
    HeapNode* extractMin(); //вилучення мінімального вузла
    void remove(HeapNode** node); //видалення ключа
};

ComplexBinomialHeap* merge(ComplexBinomialHeap* first, ComplexBinomialHeap* second); //злиття двох біноміальних пірамід
void decrease(HeapNode** node, const Complex& newKey); //зменшення ключа

#endif
