#include <iostream>
#include <climits>
#include "Point.h"

extern int read_file(char ** const buff, const unsigned int spec, const char * const filename);

int startPointNum = 12;//xiaoqu geshu
int normalPointNum = 28;//zhongzhuanzhan geshu
int roadNum = 45;
int serverprice;

vector<vector<int> > startmap(startPointNum,vector<int>(2,0));//first:point,second:capacity

vector<vector<int> > pricemap(normalPointNum,vector<int>(normalPointNum,0));
vector<vector<int> > capacitymap(normalPointNum,vector<int>(normalPointNum,0));
vector<vector<int> > flowmap(normalPointNum,vector<int>(normalPointNum,0));

Point ** startPoint = new Point*[startPointNum];
Point ** normalPoint = new Point*[normalPointNum];

void readdata(){
    char ** buffer = new char*[200];
    for (int i = 0; i < 200; ++i) {
        buffer[i] = new char[50]();
    }
    int x = read_file(buffer,100,"case");

    auto firstline(readArraybyLine(buffer,0));
    auto secondline(readArraybyLine(buffer,2));
    normalPointNum = firstline[0];
    roadNum = firstline[1];
    startPointNum = firstline[2];
    serverprice = secondline[0];

    for (int j = 4; j < 4+roadNum; ++j) {
        auto line(readArraybyLine(buffer,j));
        capacitymap[line[0]][line[1]] = line[2];
        capacitymap[line[1]][line[0]] = line[2];
        pricemap[line[0]][line[1]] = line[3];
    }

    for (int j = 4+roadNum+1; j < x; ++j) {
        auto line(readArraybyLine(buffer,j));
        startmap[line[0]][0] = line[1];
        startmap[line[0]][1] = line[2];
    }
}

void init(){
    for (int i = 0; i < normalPointNum; ++i) {
        normalPoint[i] = new Point(0,0,i);
    }
    for (int i = 0; i < startPointNum; ++i) {
        startPoint[i] = new Point(startPointNum,startmap[i][1],i);
        startPoint[i]->push_into_neighborList(normalPoint[startmap[i][0]]);
    }
    for (int i = 0; i < normalPointNum; ++i) {
        for (int j = 0; j < normalPointNum; ++j) {
            if (capacitymap[i][j] != 0) {
                normalPoint[i]->push_into_neighborList(normalPoint[j]);
            }
            if (capacitymap[j][i] != 0) {
                normalPoint[i]->push_into_neighborList(normalPoint[j]);
            }
        }
    }
}

void first_run(){
    for (int i = 0; i < startPointNum; ++i) {
        startPoint[i]->INITIALISE();
    }
};

void run(){
    for(int x = 0; x < 1000; x++){
        for (int i = 0; i < normalPointNum; ++i) {
            normalPoint[i]->DISCHARGE();
            int count = 0;
            for (int j = 0; j < normalPointNum; ++j) {
                if(normalPoint[j]->overflow == 0) count++;
            }
            cout << count << endl;
            print_mat(flowmap);
        }
    }

}

int main(){
    readdata();
    init();

    first_run();
    print_info();

    run();
    print_info();
	return 0;
}