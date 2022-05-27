//
// Created by Artem on 26.05.2022.
//

#ifndef COMPLEXINTERVALTREE_H
#define COMPLEXINTERVALTREE_H

#include "Complex.h"
#include <cstring>

class Interval
{
public:
    Complex low;
    Complex high;

    Interval(Complex low, Complex high);
};

class ComplexIntervalTree
{
    enum Color
    {
        BLACK, RED
    };
    class TreeNode
    {
    public:
        Interval data;
        Complex max;
        Color color;
        TreeNode* p; //parent
        TreeNode *left, *right;

        explicit TreeNode(Interval interval) : data(interval), max(0), color(RED), p(nullptr), left(nullptr), right(nullptr) {};
        explicit TreeNode(Color color) : data(Complex(0), Complex(0)), max(0), color(color), p(nullptr), left(nullptr), right(nullptr) {};
        Complex key() const;
    };

    TreeNode* head;
    TreeNode* nil;

    void print_help(TreeNode* node, std::string indent, bool isLast) const;
    void maxFix(TreeNode* x);
    void maxFixAllUp(TreeNode* x);
    void leftRotate(TreeNode* x);
    void rightRotate(TreeNode* x);
    void insertFix(TreeNode* z);
    TreeNode* successor(TreeNode* z) const;
    void removeFix(TreeNode* x);
public:
    ComplexIntervalTree();
    void print() const;
    void insert(const Interval& toInsert);
    bool remove(const Interval& toRemove);
    Interval searchIntersect(const Interval& toSearch) const;
};

#endif
