//
// Created by Artem on 26.04.2022.
//

#include <cassert>
#include "ComplexBinomialHeap.h"

void ComplexBinomialHeap::HeapNode::clearNodeTree()
{
    if(child) child->clearNodeTree();
    if(sibling) sibling->clearNodeTree();
    //std::cout<<key<<std::endl;
    delete this;
}

void ComplexBinomialHeap::HeapNode::linkTo(HeapNode& target)
{
    p = &target;
    sibling = target.child;
    target.child = this;
    target.degree++;
}

ComplexBinomialHeap::~ComplexBinomialHeap()
{
    clear();
}

bool ComplexBinomialHeap::empty() const
{
    return !head;
}

void ComplexBinomialHeap::clear()
{
    if(!empty()) head->clearNodeTree();
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

ComplexBinomialHeap ComplexBinomialHeap::connect(ComplexBinomialHeap& first, ComplexBinomialHeap& second)
{
    ComplexBinomialHeap res;
    if(!first.empty() && !second.empty())
    {
        HeapNode* a = first.head;
        HeapNode* b = second.head;
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
            if(!res.head)
            {
                res.head = curr;
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
    else if(first.empty())
    {
        res.head = second.head;
    }
    else
    {
        res.head = first.head;
    }
    first.head = nullptr;
    second.head = nullptr;
    return res;
}

ComplexBinomialHeap ComplexBinomialHeap::merge(ComplexBinomialHeap& first, ComplexBinomialHeap& second)
{
    ComplexBinomialHeap res = connect(first, second);
    if(res.empty()) return res;
    HeapNode* prev = nullptr;
    HeapNode* curr = res.head;
    HeapNode* next = res.head->sibling;
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
            next->linkTo(*curr);
        }
        else if(!prev)
        {
            res.head = next;
        }
        else
        {
            prev->sibling = next;
            curr->linkTo(*next);
            curr = next;
        }
        next = curr->sibling;
    }
    return res;
}

void ComplexBinomialHeap::insert(const Complex& k)
{
    ComplexBinomialHeap tempHeap;
    tempHeap.head = new HeapNode(k, nullptr, nullptr, nullptr, 0);
    *this = merge(*this, tempHeap);
}