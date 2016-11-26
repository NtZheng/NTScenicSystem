//
//  ParkingLot.cpp
//  NTScenicSystem
//
//  Created by nineteen on 11/26/16.
//  Copyright © 2016 Nineteen. All rights reserved.
//

#include "ParkingLot.hpp"

#include <iostream>
#include <time.h>

using namespace std;

void ParkingLot::management() {
    while (true) {
        printWelcomeWords();
        char select;
        cin >> select;
        if (select == 'A') {
            this->goIntoCarStack();
        } else if (select == 'D') {
            this->goOutCarStack();
        } else if (select == 'E') {
            cout << endl << "请继续选择操作：" << endl;
            break;
        } else {
            cout << "无法识别输入的指令，请重新输入：" << endl;
        }
    }
}

inline void ParkingLot::printWelcomeWords() {
    cout << "\t\t\t\t\t** 停车场管理程序 **\n";
    cout << "============================================================\n";
    cout << "A --- 汽车 进 车场\tD --- 汽车 出 车场\tE --- 退出 程序\n";
    cout << "============================================================" << endl;
    cout << " 请选择：<A,D,E>:";
}

void ParkingLot::goOutCarStack() {
    if (carStack.empty()) {
        cout << "停车场是空的" << endl;
        return;
    }
    string license;
    cout << "出场车牌号：";
    cin >> license;
    
    // 如果便道上有车的情况
    if (popBackCarOutFromStack(license) && !carQueue.empty()) {
        shared_ptr<car> tempCar = carQueue.front();
        tempCar->startTime = time(nullptr);
        carQueue.pop();
        cout << "进场车牌为：" << tempCar->license << endl;
        pushBackCarIntoStack(tempCar);
    }
}

bool ParkingLot::popBackCarOutFromStack(const string& license) {
    stack<shared_ptr<car>> tempCarStack;
    shared_ptr<car> tempCar = nullptr;
    unsigned size = (unsigned)carStack.size();
    for (unsigned i = 0; i < size; i++) {
        shared_ptr<car> topCar = carStack.top();
        if (topCar->license == license) {
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
    
    time_t endTime = time(nullptr); // 出去的时间
    time_t durationTime = endTime - tempCar->startTime; // 停车时长
    
    cout << "下面是离开停车场的车辆信息：" << endl;
    cout << "车辆牌号：" << tempCar->license << endl;
    cout << "出场的时刻：" << asctime(localtime(&endTime));
    cout << "停车时长：" <<  durationTime << " 秒" << endl;
    cout << "停车花费：" << this->parkingCost(durationTime) << endl;
    return true;
}

void ParkingLot::goIntoCarStack() {
    string license;
    cout << "进入车牌为：";
    cin >> license;
    time_t t = time(nullptr);
    shared_ptr<car> tempCar(new car(license, t));
    pushBackCarIntoStack(tempCar);
}

void ParkingLot::pushBackCarIntoStack(shared_ptr<car> car) {
    if (carStack.size() < capacity) {
        carStack.push(car);
        
        cout << "进场的时刻：" << asctime(localtime(&car->startTime));
        cout << "该车已进入停车场，位于：" << carStack.size() << "号车道" << endl;
    } else {
        carQueue.push(car);
        cout << "停车场已满，该车停在便道上" << endl;
    }
}

inline unsigned long long ParkingLot::parkingCost(long long parkingTime) {
    return (unsigned long long)parkingTime * 2;
}

