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
    };
};


#endif
