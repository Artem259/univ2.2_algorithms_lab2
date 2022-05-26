//
// Created by Artem on 26.05.2022.
//

#include "ComplexIntervalTree.h"

Complex ComplexIntervalTree::TreeNode::key() const
{
    return data.low;
}

ComplexIntervalTree::ComplexIntervalTree()
{
    nil = new TreeNode(BLACK);
    head = nil;
}

void ComplexIntervalTree::insert(const Interval& toInsert)
{
    auto z = new TreeNode(toInsert);
    auto y = nil;
    auto x = head;
    while(x != nil)
    {
        y = x;
        if(z->key() < x->key()) x = x->left;
        else x = x->right;
    }
    z->p = y;
    if(y == nil) head = z;
    else if(x->key() < y->key()) y->left = z;
    else y->right = z;
    z->left = nil;
    z->right = nil;
    z->color = RED;
    insertFix(z);
}