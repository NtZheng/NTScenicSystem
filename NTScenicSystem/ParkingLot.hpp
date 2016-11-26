//
//  ParkingLot.hpp
//  NTScenicSystem
//
//  Created by nineteen on 11/26/16.
//  Copyright © 2016 Nineteen. All rights reserved.
//

#ifndef ParkingLot_hpp
#define ParkingLot_hpp

#include <stdio.h>
#include <stack>
#include <queue>
#include <chrono>
#include <string>

using namespace std;

struct car {
    string license;
    chrono::system_clock::time_point startTime;
    car(string license, chrono::system_clock::time_point startTime) : license(license), startTime(startTime){};
};

class parkingLot {
public:
    void management(); // 总入口
    parkingLot(unsigned s = 5) : capacity(s) {};
private:
    unsigned capacity;
    stack<shared_ptr<car>> carStack;
    queue<shared_ptr<car>> carQueue;
    void goIntoCarStack();
    void goOutCarStack();
    void printWelcomeWords();
    unsigned long long parkingCost(long long);
    void pushBackCarIntoStack(shared_ptr<car>);
    bool popBackCarOutFromStack(const string&);
};



#endif /* ParkingLot_hpp */
