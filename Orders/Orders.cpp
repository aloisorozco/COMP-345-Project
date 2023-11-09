#include <iostream>
#include <vector>
#include <string>
#include "Orders.h"

using namespace std;

bool Deploy::validate(){
    if(this->getPlayerIssuerID() != this->getTarget()->getPlayer()){return false;}
    else{return true;}
}

bool Advance::validate(){
    if(this->getPlayerIssuerID() != this->getSource()->getPlayer()){return false;}
    else if(!this->getTarget()->isNeighbor(this->getSource())){return false;}
    else if(Negotiate::isNegotiation(this->getSource()->getPlayer(), this->getTarget()->getPlayer())){return false;}
    else{return true;}
}

bool Bomb::validate(){
    if(this->getPlayerIssuerID() == this->getTarget()->getPlayer()){return false;}
    else if(Negotiate::isNegotiation(*this->playerIssuerID, this->getTarget()->getPlayer())){return false;}
    else {
        for(Territory* territory : this->getTarget()->getNeighbors()){if(territory->getPlayer() == this->getPlayerIssuerID()){return true;}}
        return false;
    }
}

bool Blockade::validate(){
    if(this->getTarget()->getPlayer() != 0){return false;}
    else{return true;}
}

bool Airlift::validate(){
    if(this->getPlayerIssuerID() != this->getSource()->getPlayer()){return false;}
    else if(this->getPlayerIssuerID() != this->getTarget()->getPlayer()){return false;}
    else{return true;}
}

bool Negotiate::validate(){
    if(this->getPlayerIssuerID() == this->getPlayerTargetID()){return false;}
    else if(Negotiate::isNegotiation(this->getPlayerIssuerID(), this->getPlayerTargetID())){return false;}
    else{return true;}
}

int Order::execute(){

    if(validate()){
        cout << "Generic order executed by player " << this->getPlayerIssuerID() << ". Nothing happens." << "\n";
        return 0;
    }

    return -1;
}

int Deploy::execute(){

    if(validate()){
        target->addTroops(*troops);
        cout << *this->troops << " troops have been deployed to " << this->target->getName();
        return 0;
    }

    return -1;
}

int Advance::execute(){
    
    if(validate()){
        this->source->transferTroops(this->target, *this->troops);
        cout << *this->troops << " troops have been sent from " << this->source->getName() << " to " << this->target->getName();
        return 0;
    }

    return -1;
}

int Bomb::execute(){
    
    if(validate()){
        if(target->getArmy() > 0){
            target->removeTroops((target->getArmy() / 2) + (target->getArmy() % 2));
            cout << this->target->getName() << " has been bombed, half of its army wiped out. Remaining army: " << target->getArmy();
        }

        else{
            cout << this->target->getName() << " has been bombed, but no one was there";
        }
            
        return 0;
    }

    return -1;
}

int Blockade::execute(){
    
    if(validate()){

        target->setPlayer(0);
        target->setArmy(target->getArmy() * 2);

        cout << this->target->getName() << " has been blockaded. Ownership is now neutral and the army size is now " << target->getArmy();

        return 0;
    }

    return -1;
}

int Airlift::execute(){
    
    if(validate()){
        this->source->transferTroops(this->target, *this->troops);
        cout << *this->troops << " troops have been airlifted from " << this->source->getName() << " to " << this->target->getName();
        return 0;
    }

    return -1;
}

int Negotiate::execute(){
    
    if(validate()){
        addNegotiation(*this->playerIssuerID, *this->targetPlayerID);
        cout << "Player " << *this->playerIssuerID << " has negotiated with Player " << *this->targetPlayerID << ". No attacks between them shall be launched.";
        return 0;
    }

    return -1;
}

int OrdersList::add(Order order){

    orders.push_back(order);
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