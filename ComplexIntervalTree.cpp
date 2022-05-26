//
// Created by Artem on 26.05.2022.
//

#include <iostream>
#include <cassert>
#include "ComplexIntervalTree.h"

Interval::Interval(Complex low, Complex high) : low(low), high(high)
{
    assert(low <= high);
}

Complex ComplexIntervalTree::TreeNode::key() const
{
    return data.low;
}

void ComplexIntervalTree::print_help(TreeNode* node, std::string indent, bool isLast) const
{
    if(node == nil) return;
    std::cout << indent;
    if(isLast)
    {
        if(node != head)
        {
            std::cout << "L----";
            indent += "      ";
        }
        else
        {
            indent += " ";
        }
    }
    else
    {
        std::cout << "R----";
        indent += "|     ";
    }
    std::string color = node->color == RED ? "RED" : "BLACK";
    std::cout << "(" << node->key() << ") [" << color << "]" << std::endl;
    print_help(node->right, indent, false);
    print_help(node->left, indent, true);
}

void ComplexIntervalTree::maxFix(TreeNode* x)
{
    x->max = std::max(x->data.high, std::max(x->left->max, x->right->max));
}

void ComplexIntervalTree::leftRotate(TreeNode* x)
{
    auto y = x->right;
    x->right = y->left;
    if(y->left != nil) y->left->p = x;
    y->p = x->p;
    if(x->p == nil) head = y;
    else if(x == x->p->left) x->p->left = y;
    else x->p->right = y;
    y->left = x;
    x->p = y;
    maxFix(x);
    maxFix(y);
}

void ComplexIntervalTree::rightRotate(TreeNode* x)
{
    auto y = x->left;
    x->left = y->right;
    if(y->right != nil) y->right->p = x;
    y->p = x->p;
    if(x->p == nil) head = y;
    else if(x == x->p->right) x->p->right = y;
    else x->p->left = y;
    y->right = x;
    x->p = y;
    maxFix(x);
    maxFix(y);
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
                maxFix(z);
                maxFix(z->p);
                z = z->p->p;
            }
            else
            {
                if(z == z->p->right)
                {
                    maxFix(z);
                    z = z->p;
                    leftRotate(z);
                }
                z->p->color = BLACK;
                z->p->p->color = RED;
                rightRotate(z->p->p);
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
                maxFix(z);
                maxFix(z->p);
                z = z->p->p;
            }
            else
            {
                if(z == z->p->left)
                {
                    maxFix(z);
                    z = z->p;
                    rightRotate(z);
                }
                z->p->color = BLACK;
                z->p->p->color = RED;
                leftRotate(z->p->p);
            }
        }
    }
    head->color = BLACK;
    while(z != nil)
    {
        maxFix(z);
        z = z->p;
    }
}

ComplexIntervalTree::ComplexIntervalTree()
{
    nil = new TreeNode(BLACK);
    head = nil;
}

void ComplexIntervalTree::print() const
{
    print_help(head, "", true);
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
    else if(z->key() < y->key()) y->left = z;
    else y->right = z;
    z->left = nil;
    z->right = nil;
    z->color = RED;
    z->max = z->data.high;
    insertFix(z);
}