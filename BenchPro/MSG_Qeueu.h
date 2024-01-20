#pragma once
#include <iostream>       // std::cout
#include <queue>          // std::queue
using namespace std;

class MSG_Queue {
private:
    queue<char*> msgQueue;
public:
    //MSG_Queue();
    void addMsg(char* msg) {
        msgQueue.push(msg);
        //cout << "message is added" << endl;
    }
    char* readMsg() {
        if (!msgQueue.empty()) {
            char* msg;
            msg = msgQueue.front();
            msgQueue.pop();
            return msg;
        }
        return "";
    }

    void printMSG() {
        //cout << "qeuee contents" << endl;
        while (!msgQueue.empty()) {
            cout << readMsg() << endl;
        }
    }
    bool isEmty() {
        if (msgQueue.empty())
            return true;
        else
            return false;
    }
};
//int main()
//{
//    MSG_Queue* mq = new MSG_Queue();
//
//    for (int i = 0; i < 5; ++i)
//        mq->addMsg("hello");
//
//    mq->printMSG();
//
//    return 1;
//}


