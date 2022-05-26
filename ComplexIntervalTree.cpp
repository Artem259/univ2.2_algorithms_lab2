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

void ComplexIntervalTree::insertFix(TreeNode* z)
{
    while(z->p->color == RED)
    {
        if(z->p == z->p->p->left)
        {
            auto y = z->p->p->right;
            if(y->color == RED)
            {
                z->p->color = BLACK;
                y->color = BLACK;
                z->p->p->color = RED;
                z = z->p->p;
            }
            else
            {
                if(z == z->p->right)
                {
                    z = z->p;
                    //!leftRotate(z);
                }
                z->p->color = BLACK;
                z->p->p->color = RED;
                //!rightRotate(z->p->p);
            }
        }
        else
        {
            auto y = z->p->p->left;
            if(y->color == RED)
            {
                z->p->color = BLACK;
                y->color = BLACK;
                z->p->p->color = RED;
                z = z->p->p;
            }
            else
            {
                if(z == z->p->left)
                {
                    z = z->p;
                    //!rightRotate(z);
                }
                z->p->color = BLACK;
                z->p->p->color = RED;
                //!leftRotate(z->p->p);
            }
        }
    }
    head->color = BLACK;
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