//
//  ParkingLot.cpp
//  NTScenicSystem
//
//  Created by nineteen on 11/26/16.
//  Copyright © 2016 Nineteen. All rights reserved.
//

#include "ParkingLot.hpp"

#include <iostream>

using namespace std;

void parkingLot::management() {
    while (true) {
        printWelcomeWords();
        char select;
        cin >> select;
        if (select == 'A') {
            this->goIntoCarStack();
        } else if (select == 'D') {
            this->goOutCarStack();
        } else if (select == 'E') {
            break;
        } else {
            cout << "无法识别输入的指令，请重新输入：" << endl;
        }
    }
}

inline void parkingLot::printWelcomeWords() {
    cout << "\t\t** 停车场管理程序 **\n";
    cout << "============================================================\n";
    cout << "**\t\t\t\t\t\t\t**\n";
    cout << "**\tA --- 汽车 进 车场\tD --- 汽车 出 车场\t**\n";
    cout << "**\t\t\t\t\t\t\t**\n";
    cout << "**\t\t\tE --- 退出 程序\t\t\t**\n";
    cout << "============================================================" << endl;
    cout << " 请选择：<A,D,E>:";
}

void parkingLot::goOutCarStack() {
    if (carStack.empty()) {
        cout << "停车场是空的" << endl;
        return;
    }
    string license;
    cout << license;
    
    // 如果便道上有车的情况
    if (popBackCarOutFromStack(license) && !carQueue.empty()) {
        shared_ptr<car> tempCar = carQueue.front();
        tempCar->startTime = chrono::system_clock::now();
        carQueue.pop();
        cout << "进场车牌为：" << tempCar->license << endl;
        pushBackCarIntoStack(tempCar);
    }
}

bool parkingLot::popBackCarOutFromStack(const string& license) {
    stack<shared_ptr<car>> tempCarStack;
    shared_ptr<car> tempCar = nullptr;
    unsigned size = (unsigned)carStack.size();
    for (unsigned i = 0; i < size; i++) {
        shared_ptr<car> topCar = carStack.top();
        if (tempCar->license == license) {
            tempCar = topCar;
            carStack.pop();
            break;
        }
        tempCarStack.push(topCar);
        carStack.pop();
    }
    
    // 将让位的车辆都按次序放回停车场
    while (!tempCarStack.empty()) {
        carStack.push(tempCarStack.top());
        tempCarStack.pop();
    }
    
    // 没找到这辆车
    if (tempCar == nullptr) {
        return false;
    }
    
    //auto end = chrono::system_clock::now;
    
    cout << "下面是离开停车场的车辆信息：" << endl;
    cout << "车辆牌号：" << tempCar->license << endl;
    cout << "出场的时刻：" << endl;
    cout << "停车时长：" << endl;
    cout << "停车花费：" << endl;
    return true;
}

void parkingLot::goIntoCarStack() {
    string license;
    cout << "进入车牌为：";
    cin >> license;
    auto time = chrono::system_clock::now();
    shared_ptr<car> tempCar(new car(license, time));
    pushBackCarIntoStack(tempCar);
}

void parkingLot::pushBackCarIntoStack(shared_ptr<car> car) {
    if (carStack.size() < capacity) {
        carStack.push(car);
        
        cout << "进场的时刻：";
        cout << "该车已进入停车场，位于：" << carStack.size() << "号车道" << endl;
    } else {
        carQueue.push(car);
        cout << "停车场已满，该车停在便道上" << endl;
    }
}

inline unsigned long long parkingLot::parkingCost(long long parkingTime) {
    return (unsigned long long)parkingTime * 2;
}
