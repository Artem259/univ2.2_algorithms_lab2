//
// Created by Artem on 26.04.2022.
//

#include <cassert>
#include "ComplexBinomialHeap.h"

ComplexBinomialHeap::HeapNode::~HeapNode()
{
    delete child;
    delete sibling;
}

bool ComplexBinomialHeap::empty() const
{
    return head;
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