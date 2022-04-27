//
// Created by Artem on 26.04.2022.
//

#include <cassert>
#include "ComplexBinomialHeap.h"

void ComplexBinomialHeap::HeapNode::clear()
{
    if(child) child->clear();
    if(sibling) sibling->clear();
    //std::cout<<key<<std::endl;
    delete this;
}

ComplexBinomialHeap::~ComplexBinomialHeap()
{
    if(!empty()) head->clear();
}

bool ComplexBinomialHeap::empty() const
{
    return !head;
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