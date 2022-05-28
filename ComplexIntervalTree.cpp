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

std::ostream& operator <<(std::ostream& ofs, const Interval& interval)
{
    ofs << "[" << interval.low << ";" << interval.high << "]";
    return ofs;
}

Complex ComplexIntervalTree::TreeNode::key() const
{
    return data.low;
}

void ComplexIntervalTree::clear_help(TreeNode* node)
{
    if(node == nil) return;
    clear_help(node->left);
    clear_help(node->right);
    delete node;
}

void ComplexIntervalTree::print_help(std::ostream& ofs, TreeNode* node, std::string indent, bool isLast) const
{
    if(node == nil) return;
    ofs << indent;
    if(isLast)
    {
        if(node != head)
        {
            ofs << "L----";
            indent += "      ";
        }
        else
        {
            indent += " ";
        }
    }
    else
    {
        ofs << "R----";
        indent += "|     ";
    }
    std::string color = node->color == RED ? "RED" : "BLACK";
    ofs << node->data << " (" << node->max << ") [" << color << "]" << std::endl;
    print_help(ofs, node->right, indent, false);
    print_help(ofs, node->left, indent, true);
}

void ComplexIntervalTree::maxFix(TreeNode* x)
{
    if(x == nil) return;
    x->max = std::max(x->data.high, std::max(x->left->max, x->right->max));
}

void ComplexIntervalTree::maxFixAllUp(TreeNode* x)
{
    while(x != nil)
    {
        maxFix(x);
        x = x->p;
    }
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
    maxFixAllUp(z);
}

ComplexIntervalTree::TreeNode* ComplexIntervalTree::successor(TreeNode* z) const
{
    auto x = z->right;
    while(x->left != nil)
    {
        x = x->left;
    }
    return x;
}

void ComplexIntervalTree::removeFix(TreeNode* x)
{
    while(x!=head && x->color==BLACK)
    {
        if(x == x->p->left)
        {
            auto w = x->p->right;
            if(w->color == RED)
            {
                w->color = BLACK;
                x->p->color = RED;
                leftRotate(x->p);
                w = x->p->right;
            }
            if(w->left->color==BLACK && w->right->color==BLACK)
            {
                w->color = RED;
                maxFix(x);
                x = x->p;
            }
            else
            {
                if(w->right->color == BLACK)
                {
                    w->left->color = BLACK;
                    w->color = RED;
                    rightRotate(w);
                    w = x->p->right;
                }
                w->color = x->p->color;
                x->p->color = BLACK;
                w->right->color = BLACK;
                leftRotate(x->p);
                maxFixAllUp(x);
                x = head;
            }
        }
        else
        {
            auto w = x->p->left;
            if(w->color == RED)
            {
                w->color = BLACK;
                x->p->color = RED;
                rightRotate(x->p);
                w = x->p->left;
            }
            if(w->right->color==BLACK && w->left->color==BLACK)
            {
                w->color = RED;
                maxFix(x);
                x = x->p;
            }
            else
            {
                if(w->left->color == BLACK)
                {
                    w->right->color = BLACK;
                    w->color = RED;
                    leftRotate(w);
                    w = x->p->left;
                }
                w->color = x->p->color;
                x->p->color = BLACK;
                w->left->color = BLACK;
                rightRotate(x->p);
                maxFixAllUp(x);
                x = head;
            }
        }
    }
    x->color = BLACK;
    maxFixAllUp(x);
}

bool ComplexIntervalTree::isOverlaps(Interval x, Interval z)
{
    return (x.low<=z.high && z.low<=x.high);
}

ComplexIntervalTree::ComplexIntervalTree()
{
    nil = new TreeNode(BLACK);
    head = nil;
    error = false;
}

ComplexIntervalTree::~ComplexIntervalTree()
{
    clear();
    delete nil;
}

void ComplexIntervalTree::clear()
{
    clear_help(head);
    head = nil;
    error = false;
}

bool ComplexIntervalTree::errorState() const
{
    return error;
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

bool ComplexIntervalTree::remove(const Interval& toRemove)
{
    auto x = head;
    while(x != nil)
    {
        if(toRemove.low < x->key())
        {
            x = x->left;
        }
        else if(toRemove.low > x->key())
        {
            x = x->right;
        }
        else
        {
            if(toRemove.high == x->data.high) break;
            else x = x->right;
        }
    }
    if(x == nil) return false;

    auto z = x;
    TreeNode* y;
    if(z->left==nil || z->right==nil) y = z;
    else y = successor(z);
    if(y->left != nil) x = y->left;
    else x = y->right;
    x->p = y->p;
    if(y->p == nil) head = x;
    else if(y == y->p->left) y->p->left = x;
    else y->p->right = x;
    if(y != z)
    {
        z->data = y->data;
    }
    if(y->color == BLACK) removeFix(x);
    else maxFixAllUp(x->p);
    delete y;
    return true;
}

bool ComplexIntervalTree::search(const Interval& toSearch) const
{
    auto x = head;
    while(x != nil)
    {
        if(toSearch.low < x->key())
        {
            x = x->left;
        }
        else if(toSearch.low > x->key())
        {
            x = x->right;
        }
        else
        {
            if(toSearch.high == x->data.high) break;
            else x = x->right;
        }
    }
    if(x == nil) return false;
    return true;
}

Interval ComplexIntervalTree::searchIntersect(const Interval& toSearch)
{
    auto x = head;
    while(x != nil && !isOverlaps(toSearch, x->data))
    {
        if(x->left!=nil && x->left->max>=toSearch.low) x = x->left;
        else x = x->right;
    }
    if(x == nil)
    {
        error = true;
        return {Complex{0}, Complex{0}};
    }
    return x->data;
}

std::ostream& operator <<(std::ostream& ofs, const ComplexIntervalTree& toOut)
{
    toOut.print_help(ofs, toOut.head, "", true);
    return ofs;
}