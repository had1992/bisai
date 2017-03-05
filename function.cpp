//
// Created by had on 3/5/17.
//

#include <climits>
#include "Point.h"

void Point::RELABEL() {
    int minheight = INT_MAX;
    auto it = neighborList.begin();
    for (;it!=neighborList.end();it++) {
        if(Cf(*it)>0){
            minheight = min(minheight,(*it)->height);
        }
    }
    height = minheight+1;
}

void Point::PUSH(Point * p) {
    int delt = min(overflow,Cf(p));
    if(isBelongtoE(p)){
        flowmap[num][p->num] += delt;
    } else {
        flowmap[p->num][num] -= delt;
    }
    overflow -= delt;
    p->overflow += delt;
}

void Point::DISCHARGE() {
    auto it = neighborList.begin();
    while(overflow > 0) {
        if (it == neighborList.end()) {
            RELABEL();
            it = neighborList.begin();
        } else
        if (height == (*it)->height+1 && Cf(*it) > 0) {
            PUSH(*it);
        } else {
            it++;
        }
//        print_info();
//        cin.get();
    }
}

void Point::INITIALISE() {
    Point * p = neighborList.front();
    int delt = startmap[num][1];
    overflow -= delt;
    p->overflow += delt;
}

void print_info(){
    cout << "start point:" << endl;
    for (int i = 0; i < startmap.size(); ++i) {
        cout << i << "\t" << startPoint[i]->height << "\t" << startPoint[i]->overflow << "\t" << endl;
    }
    cout << "normal point:" << endl;
    for (int i = 0; i < capacitymap.size(); ++i) {
        cout << i << "\t" << normalPoint[i]->height << "\t" << normalPoint[i]->overflow << "\t" << endl;
    }
}

int charstoint(char *p, int s, int e){
    int result = 0;
    int base = 1;
    for (int i = e-1; i >= s; --i) {
        result += base*(p[i]-'0');
        base *= 10;
    }
    return result;
}

vector<int> readArraybyLine(char **p, int line) {
    vector<int> result;
    int start = 0;
    int end = 0;
    while(p[line][end] != '\n'){
        while(p[line][end] == ' '){
            end++;
        }
        start = end;
        while(p[line][end] != ' ' && p[line][end] != '\n'){
            end++;
        }
        result.push_back(charstoint(p[line],start,end));
    }
    return result;
}

void print_mat(vector<vector<int> > x){
    for (int i = 0; i < x.size(); ++i) {
        for (int j = 0; j < x[0].size(); ++j) {
            cout << x[i][j] << " ";
        }
        cout << endl;
    }
}
