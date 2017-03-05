//
// Created by had on 3/5/17.
//
#include <list>
#include <vector>
#include <iostream>

#ifndef BISAI_POINT_H
#define BISAI_POINT_H
using namespace std;

class Point;

extern vector<vector<int> > startmap;
extern vector<vector<int> > capacitymap;
extern vector<vector<int> > flowmap;
extern vector<vector<int> > pricemap;

extern Point ** startPoint;
extern Point ** normalPoint;

class Point{
public:
    int height;
    int overflow;
    int num;
    list<Point*> neighborList;//邻接链表

    Point(int x, int y, int n):height(x),overflow(y),num(n){}
    inline void push_into_neighborList(Point * p){
        neighborList.push_back(p);
    }
    void DISCHARGE();

    void INITIALISE();

private:
    void RELABEL();
    void PUSH(Point * p);


    inline int Cf(Point* p){
        return capacitymap[num][p->num]-flowmap[num][p->num];
    }

    inline bool isBelongtoE(Point * p){
        return true;
    };
};

extern void print_info();

extern int charstoint(char *p, int s, int e);

extern vector<int> readArraybyLine(char ** p, int line);

extern void print_mat(vector<vector<int> > x);



#endif //BISAI_POINT_H
