//
//  main.cpp
//  NTScenicSystem
//
//  Created by Nineteen on 11/18/16.
//  Copyright © 2016 Nineteen. All rights reserved.
//

#include <iostream>

#include "ListUDG.hpp"

using namespace std;


void printWelcomeWords();

int main(int argc, const char * argv[]) {
    printWelcomeWords();
    shared_ptr<ListUDG> listUDG = make_shared<ListUDG>();
    while (true) {
        int command;
        cin >> command;
        cout << endl;
        switch (command) {
            case 1:
                listUDG->creatGraph();
                break;
            case 2:
                listUDG->outputGraph();
                break;
            case 3:
                listUDG->outputTourGuideLine();
                break;
            case 4:
                
                break;
            case 5:
                
                break;
            case 6:
                
                break;
            case 7:
                
                break;
            case 8:
                
                break;
            case 9:
                
                break;
            case 0:
                
                cout << "成功退出系统" << endl;
                return 0;
            default:
                cout << "无法识别该指令，请重新输入:" << endl;
                break;
        }
    }
    
    return 0;
}

void printWelcomeWords() {
    cout << "================================\n";
    cout << "     欢迎使用景区信息管理系统\n";
    cout << "         ***请选择菜单***\n";
    cout << "================================\n";
    cout << "1、创建景区景点分布图。\n";
    cout << "2、输出景区景点分布图。\n";
    cout << "3、输出导游线路图。\n";
    cout << "4、输出导游线路图中的回路。\n";
    cout << "5、求两个景点间的最短路径和最短距离。\n";
    cout << "6、输出道路修建规划图。\n";
    cout << "7、按景点欢迎度进行排序并输出。\n";
    cout << "8、根据用户输入的关键字进行景点的查找。\n";
    cout << "9、停车场车辆进出记录信息。\n";
    cout << "0、退出系统。\n";
    cout << "请输入您要选择的菜单项：" << endl;
}
