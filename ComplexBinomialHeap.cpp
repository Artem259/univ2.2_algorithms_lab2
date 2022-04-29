//
// Created by Artem on 26.04.2022.
//

#include <cassert>
#include "ComplexBinomialHeap.h"

void HeapNode::clearNodeTree()
{
    if(child) child->clearNodeTree();
    if(sibling) sibling->clearNodeTree();
    //std::cout<<"Deleted: "<<this<<" "<<key<<std::endl;
    delete this;
}

void HeapNode::linkTo(HeapNode* target)
{
    p = target;
    sibling = target->child;
    target->child = this;
    (target->degree)++;
}

void HeapNode::isolate()
{
    p = nullptr;
    child = nullptr;
    sibling = nullptr;
    degree = 0;
}

Complex HeapNode::getKey() const
{
    return key;
}

void ComplexBinomialHeap::reset()
{
    head = nullptr;
    sizeN = 0;
}

ComplexBinomialHeap::~ComplexBinomialHeap()
{
    clear();
}

bool ComplexBinomialHeap::empty() const
{
    return (head == nullptr);
}

bool ComplexBinomialHeap::size() const
{
    return sizeN;
}

void ComplexBinomialHeap::clear()
{
    if(!empty())
    {
        head->clearNodeTree();
    }
    reset();
}

Complex ComplexBinomialHeap::min() const
{
    assert(!empty());
    HeapNode* curr = head;
    Complex res = head->key;
    while(curr)
    {
        res = std::min(res, curr->key);
        curr = curr->sibling;
    }
    return res;
}

ComplexBinomialHeap* ComplexBinomialHeap::connect(ComplexBinomialHeap* first, ComplexBinomialHeap* second)
{
    auto res = new ComplexBinomialHeap();
    if(!first->empty() && !second->empty())
    {
        HeapNode* a = first->head;
        HeapNode* b = second->head;
        HeapNode *resLast, *curr;
        while(a && b)
        {
            if(a->degree < b->degree)
            {
                curr = a;
                a = a->sibling;
            }
            else
            {
                curr = b;
                b = b->sibling;
            }
            if(!res->head)
            {
                res->head = curr;
                resLast = curr;
            }
            else
            {
                resLast->sibling = curr;
                resLast = curr;
            }
        }
        HeapNode* end = a ? a : b;
        while(end)
        {
            resLast->sibling = end;
            resLast = end;
            end = end->sibling;
        }
    }
    else if(first->empty())
    {
        res->head = second->head;
    }
    else
    {
        res->head = first->head;
    }
    res->sizeN = first->sizeN + second->sizeN;
    first->reset();
    second->reset();
    return res;
}

void ComplexBinomialHeap::decreaseHelp(HeapNode** node, const Complex& newKey)
{
    assert(!(newKey > (*node)->key));
    (*node)->key = newKey;
    HeapNode* current = *node;
    HeapNode* parent = current->p;
    while(parent && (current->key < parent->key))
    {
        std::swap(current->key, parent->key);
        current = parent;
        parent = current->p;
    }
    *node = current;
}

HeapNode* ComplexBinomialHeap::insert(const Complex& k)
{
    assert(k != Complex(0));
    auto tempHeap = new ComplexBinomialHeap;
    auto newNode = new HeapNode(k, nullptr, nullptr, nullptr, 0);
    tempHeap->head = newNode;
    tempHeap->sizeN = 1;
    auto mergedHeap = merge(this, tempHeap);
    *this = *mergedHeap;
    tempHeap->reset();
    mergedHeap->reset();
    delete tempHeap;
    delete mergedHeap;
    return newNode;
}

HeapNode* ComplexBinomialHeap::extractMin()
{
    assert(!empty());
    size_t prevSize = sizeN;
    Complex min = this->min();
    HeapNode *prev(nullptr), *curr(head), *next;
    while(curr->key != min)
    {
        prev = curr;
        curr = curr->sibling;
    }
    if(!prev) head = curr->sibling;
    else prev->sibling = curr->sibling;
    auto res = curr;
    curr = curr->child;
    if(curr)
    {
        curr->p = nullptr;
        prev = nullptr;
        while(curr)
        {
            next = curr->sibling;
            curr->sibling = prev;
            prev = curr;
            curr->p = nullptr;
            curr = next;
        }
        auto tempHeap = new ComplexBinomialHeap;
        tempHeap->head = prev;
        auto mergedHeap = merge(this, tempHeap);
        this->head = mergedHeap->head;
        tempHeap->reset();
        mergedHeap->reset();
        delete tempHeap;
        delete mergedHeap;
    }
    sizeN = prevSize-1;
    res->isolate();
    return res;
}

void ComplexBinomialHeap::remove(HeapNode** node)
{
    decreaseHelp(node,Complex(0));
    auto removed = extractMin();
    assert(removed == *node);
    delete removed;
    *node = nullptr;
}

ComplexBinomialHeap* merge(ComplexBinomialHeap* first, ComplexBinomialHeap* second)
{
    ComplexBinomialHeap* res = ComplexBinomialHeap::connect(first, second);
    if(res->empty()) return res;
    HeapNode* prev = nullptr;
    HeapNode* curr = res->head;
    HeapNode* next = res->head->sibling;
    while(next)
    {
        if((curr->degree != next->degree) || (next->sibling && (curr->degree == next->sibling->degree)))
        {
            prev = curr;
            curr = next;
        }
        else if(curr->key <= next->key)
        {
            curr->sibling = next->sibling;
            next->linkTo(curr);
        }
        else
        {
            if(!prev)
            {
                res->head = next;
            }
            else
            {
                prev->sibling = next;
            }
            curr->linkTo(next);
            curr = next;
        }
        next = curr->sibling;
    }
    return res;
}

void decrease(HeapNode** node, const Complex& newKey)
{
    assert(newKey != Complex(0));
    ComplexBinomialHeap::decreaseHelp(node, newKey);
}