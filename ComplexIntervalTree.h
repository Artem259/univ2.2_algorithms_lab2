//
// Created by Artem on 26.05.2022.
//

#ifndef COMPLEXINTERVALTREE_H
#define COMPLEXINTERVALTREE_H

#include "Complex.h"

class Interval
{
public:
    Complex low;
    Complex high;

    Interval(Complex low, Complex high) : low(low), high(high) {};
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

    void insertFix(TreeNode* z);
public:
    ComplexIntervalTree();
    void insert(const Interval& toInsert);
    void remove(const Interval& toRemove);
    Interval searchIntersect(const Interval& toSearch) const;
};

#endif
