#include <iostream>
#include <vector>
#include <string>
#include "Orders.h"
#include "../Observer/LoggingObserver.h"
using namespace std;

bool Order::validate(){
    //To be implemented
    return true;
}

bool Deploy::validate(){
    //To be implemented
    return true;
}

bool Advance::validate(){
    //To be implemented
    return true;
}

bool Bomb::validate(){
    //To be implemented
    return true;
}

bool Blockade::validate(){
    //To be implemented
    return true;
}

bool Airlift::validate(){
    //To be implemented
    return true;
}

bool Negotiate::validate(){
    //To be implemented
    return true;
}
string Order::stringToLog() {
    string out = "Executed the Order:" + description;
    return out;
}
int Order::execute(){
    if(validate()){
        cout << description + "\n";
        Notify(this);
        return 0;
    }
    return -1;
}



int Deploy::execute(){

    if(validate()){
        cout << description + "\n";
        Notify(this);
        return 0;
    }

    return -1;
}

int Advance::execute(){
    
    if(validate()){
        cout << description + "\n";
        Notify(this);
        return 0;
    }

    return -1;
}

int Bomb::execute(){
    
    if(validate()){
        cout << description + "\n";
        Notify(this);
        return 0;
    }

    return -1;
}

int Blockade::execute(){
    
    if(validate()){
        cout << description + "\n";
        Notify(this);
        return 0;
    }

    return -1;
}

int Airlift::execute(){
    
    if(validate()){
        cout << description + "\n";
        Notify(this);
        return 0;
    }

    return -1;
}

int Negotiate::execute(){
    
    if(validate()){
        cout << description + "\n";
        Notify(this);
        return 0;
    }

    return -1;
}

int OrdersList::add(Order order){

    this->orders.push_back(order);
    Notify(this);
    return 0;
}

int OrdersList::remove(int index){

    if (index >= 0 && index < orders.size()) {

        orders.erase(orders.begin() + index);
        return 0;
    }

    else{

        cout << "Invalid index: " << (index) << " \n";
        return -1;
    }
}

int OrdersList::remove(){

    return remove(orders.size() - 1);
}

int OrdersList::move(int index1, int index2){

    if (index1 >= 0 && index1 < orders.size() && index2 >= 0 && index2 < orders.size() && index1 != index2) {

        Order ordermove = orders[index1];
        orders.erase(orders.begin() + index1);

        orders.insert(orders.begin() + index2, ordermove);
        return 0;
    }

    else{
        cout << "Invalid index(es)" << index1 << ", " << index2 << "\n";
        return -1;
    }
}

int OrdersList::executeAll(){

    for(Order order : orders){

        if(order.execute() != 0){
            return -1;
        }
    }

    return 0;
}

void OrdersList::copyOrders(const OrdersList& other) {
    orders.reserve(other.orders.size());
    for (Order order : other.orders) {
        orders.push_back(Order(order));
    }
}

OrdersList::OrdersList(const OrdersList& other) {

    copyOrders(other);
}

OrdersList& OrdersList::operator=(const OrdersList& other) {

    if (this != &other) {
        orders.clear();

        if (!other.orders.empty()) {
            copyOrders(other);
        }
    }
    return *this;
}

std::ostream& operator<<(std::ostream& os, const OrdersList& ordersList) {
    
    for (const Order order : ordersList.orders) {
        os << order << "\n";
    }
    return os;
}

string OrdersList::stringToLog() {
//when any order is put in a player’s OrderList using OrderList::add()
// the order should be output to the log file using the Observer notification mechanism.
// Later, when any order gets executed, its effect (as stored in the order itself)
// should be output to the log file, again using the Observer’s notification mechanism.

//get last order added.
Order o = orders.back();
string out = "Issued the Order:" + o.getDescription();
return out;
}