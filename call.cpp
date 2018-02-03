#include <iostream>
#include <string>
#include <sstream>
#include "dlist.h"

using namespace std;

int statusFind(string status);

const string priorityName[] = {"platinum", "gold", "silver", "regular"};

class Customer
{
private:
    int timestamp;
    string name;
    string status;
    int statusnumber;
    unsigned int waiting;
    unsigned int duration;
    int order;

public:
    Customer(int customer_timestamp = 0, const string customer_name = "",
             string customer_status = 0, unsigned int customer_waiting = 0, unsigned int customer_duration = 0) {
            timestamp = customer_timestamp;
            name = customer_name;
            status = customer_status;
            statusnumber = statusFind(customer_status);
            waiting = customer_waiting;
            duration = customer_duration;
            order = -1;
    }

    void adaptOrder(int tick) {
        order = tick;
    }

    int readTimestamp() {
        return timestamp;
    }

    string readName() {
        return name;
    }

    string readStatus() {
        return status;
    }

    int readStatusnumber() {
        return statusnumber;
    }

    int readWaiting() {
        return waiting;
    }

    int readDuration() {
        return duration;
    }

    int readOrder() {
        return order;
    }
};

int statusFind(string status) {
    int i;
    for (i = 0; i < 4; i++){
        if (status == priorityName[i]){
            return i;
        }
    }
    return 4;
}

int main() {
    Dlist<Customer> queue[4];
    Dlist<Customer> queueAll;
    Dlist<Customer> agent;

    int number, timestamp, waiting, duration;
    int i;
    int tick = 0;
    string name, status;
    Customer *caller;
    cin >> number;

    for (i = 0; i < number; i++) {
        cin >> timestamp >> name >> status >> waiting >> duration;
        Customer *customer=new Customer(timestamp, name, status, waiting, duration);
        queueAll.insertFront(customer);
    }

    while (!queue[0].isEmpty() || !queue[1].isEmpty() || !queue[2].isEmpty()
           || !queue[3].isEmpty() || !queueAll.isEmpty() || !agent.isEmpty()) {
        cout << "Starting tick #" << tick << endl;

        for (i = 0; i < 4; i++) {
            if (!queue[i].isEmpty()) {
                Dlist<Customer> tempList;
                while (!queue[i].isEmpty()) {
                    Customer *temp = queue[i].removeBack();

                    if (temp->readWaiting() + temp->readTimestamp() <= tick) {
                        cout << temp->readName() << " hangs up" << endl;
                        delete temp;
                    }
                    else {
                        tempList.insertFront(temp);
                    }

                }

                queue[i] = tempList;
                while (!tempList.isEmpty()) {
                    Customer *op = tempList.removeFront();
                    delete op;
                }
            }
        }

        while (!queueAll.isEmpty()) {
            caller = queueAll.removeBack();
            if (caller->readTimestamp() == tick) {
                cout << "Call from " << caller->readName() << " a "
                     << priorityName[caller->readStatusnumber()] << " member" << endl;

                queue[caller->readStatusnumber()].insertFront(caller);
            }
            else {
                queueAll.insertBack(caller);
                break;
            }
        }

        if (!agent.isEmpty()) {
            Customer *temp = agent.removeBack();
            if (temp->readOrder() + temp->readDuration() <= tick) {
                delete temp;
            }
            else {
                agent.insertFront(temp);
            }
        }

        if (agent.isEmpty()) {
            for (i = 0; i < 4; i++){
                if (!queue[i].isEmpty()){
                    caller = queue[i].removeBack();
                    caller->adaptOrder(tick);

                    cout << "Answering call from " << caller->readName() << endl;
                    agent.insertFront(caller);
                    break;
                }
            }
        }
        tick++;
    }
}
