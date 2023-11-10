
#ifndef ORDERS_H
#define ORDERS_H

#include "../Observer/LoggingObserver.h"
#include <iostream>
#include <string>
#include <vector>
#include "../Map/Map.h"
using namespace std;

class Order : public Subject, public ILoggable{
    private:
        list<Observer *> *_observers;
    protected:
        //ID of the player Issuing the order
        int* playerIssuerID;

        //Description of the order
        string* description;

    public:
        Order() : playerIssuerID(nullptr), description(new string("This is a generic order"))  {}
        Order(int playerID, const std::string desc) : playerIssuerID(new int(playerID)), description(new string(desc)) {}
        Order(const Order& other) : playerIssuerID(new int(*other.playerIssuerID)), description(new string(*other.description)) {}

        Order& operator=(const Order& other) {

            if (this != &other) {
                delete playerIssuerID;
                delete description;

                this->description = new string(*other.description);
                this->playerIssuerID = new int(*other.playerIssuerID);
            }
            return *this;
        }

        ~Order(){

            delete playerIssuerID;
            delete description;
        }

        virtual bool validate();
        virtual int execute();

        friend ostream& operator<<(std::ostream& os, const Order& order) {
            os << *order.description + " executed by Player " << *order.playerIssuerID << ". Nothing happens. \n";
            return os;
        }

        virtual string getDescription() const {
            return *this->description;
        }

        virtual int getPlayerIssuerID() const {
            return *this->playerIssuerID;
        }

        string stringToLog() override;
};

class Deploy : public Order{

    private:
        //Number of troops to deploy
        int* troops;

        //Territory to send troops to
        Territory* target;

    public:
        Deploy() : Order() {
            *description = "This is a deploy order";
            troops = new int(0);
            target = nullptr;
        }

        Deploy(int playerID, const std::string& desc, int troops, Territory* target) : Order(playerID, desc), troops(new int(troops)), target(target) {}

        Deploy(const Deploy& other) : Order(other), troops(new int(*other.troops)), target(other.target) {}

        ~Deploy() {

            Order::~Order();
            delete troops;
        }

        Deploy& operator=(const Deploy& other) {
            if (this != &other) {
                Order::operator=(other);
                delete troops;
                this->troops = new int(*other.troops);
                this->target = other.target;
            }
            return *this;
        }

        friend ostream& operator<<(std::ostream& os, const Deploy& order) {
            os << *order.description + " executed by Player " << *order.playerIssuerID << ". " << *order.troops << " troops have been deployed to " << order.target->getName() << "\n";
            return os;
        }

        bool validate() override;
        int execute() override;

        int getTroops() const { return *troops; }
        void setTroops(int value) { *troops = value; }

        Territory* getTarget() const { return target; }
        void setTarget(Territory* value) { target = value; }

};

class Advance : public Order{

    private:

        //Number of troops to advance from source
        int* troops;

        //Source of the troops
        Territory* source;

        //Territory to send troops to
        Territory* target;

    public:
        Advance() : Order() {
            *description = "This is an advance order";
            troops = new int(0);
            source = nullptr;
            target = nullptr;
        }

        Advance(int playerID, const std::string& desc, int troops, Territory* source, Territory* target) : Order(playerID, desc), troops(new int(troops)), source(source), target(target) {}

        Advance(const Advance& other) : Order(other), troops(new int(*other.troops)), source(other.source), target(other.target) {}

        ~Advance() {
            Order::~Order();
            delete troops;
        }

        Advance& operator=(const Advance& other) {
            if (this != &other) {
                Order::operator=(other);
                delete troops;
                this->troops = new int(*other.troops);
                this->source = other.source;
                this->target = other.target;
            }
            return *this;
        }

        friend ostream& operator<<(std::ostream& os, const Advance& order) {
            os << *order.description + " executed by Player " << *order.playerIssuerID << ". " << *order.troops << " troops have been sent from " << order.source->getName() << " to " << order.target->getName() << "\n";
            return os;
        }

        bool validate() override;
        int execute() override;

        int getTroops() const { return *troops; }
        void setTroops(int value) { *troops = value; }

        Territory* getSource() const { return source; }
        void setSource(Territory* value) { source = value; }

        Territory* getTarget() const { return target; }
        void setTarget(Territory* value) { target = value; }

};

class Bomb : public Order{

    private:

        //Territory to send the bomb order to
        Territory* target;

    public:
        Bomb() : Order() {
            *description = "This is a bomb order";
            target = nullptr;
        }

        Bomb(int playerID, const std::string& desc, Territory* target) : Order(playerID, desc), target(target) {}

        Bomb(const Bomb& other) : Order(other), target(other.target) {}

        ~Bomb() {
            Order::~Order();
        }

        Bomb& operator=(const Bomb& other) {
            if (this != &other) {
                Order::operator=(other);
                this->target = other.target;
            }
            return *this;
        }

        friend ostream& operator<<(std::ostream& os, const Bomb& order) {
            os << *order.description + " executed by Player " << *order.playerIssuerID << ". " << order.target->getName() << " has been bombed, half of its army wiped out. Remaining army: " << order.target->getArmy() << "\n";
            return os;
        }

        bool validate() override;
        int execute() override;

        Territory* getTarget() const { return target; }
        void setTarget(Territory* value) { target = value; }

};

class Blockade : public Order{

    private:
        //Territory to blockade
        Territory* target;

    public:
        Blockade() : Order() {
            *description = "This is a bomb order";
            target = nullptr;
        }

        Blockade(int playerID, const std::string& desc, Territory* target) : Order(playerID, desc), target(target) {}

        Blockade(const Blockade& other) : Order(other), target(other.target) {}

        ~Blockade() {
            Order::~Order();
        }

        Blockade& operator=(const Blockade& other) {
            if (this != &other) {
                Order::operator=(other);
                this->target = other.target;
            }
            return *this;
        }

        friend ostream& operator<<(std::ostream& os, const Blockade& order) {
            os << *order.description + " executed by Player " << *order.playerIssuerID << ". " << order.target->getName() << " has been blockaded. Ownership is now neutral and the army size is now " << order.target->getArmy() << "\n";
            return os;
        }

        bool validate() override;
        int execute() override;

        Territory* getTarget() const { return target; }
        void setTarget(Territory* value) { target = value; }
};

class Airlift : public Order{

    private:

        //Number of troops to send
        int* troops;

        //Source territory
        Territory* source;

        //Target territory
        Territory* target;

    public:
        Airlift() : Order() {
            *description = "This is an advance order";
            troops = new int(0);
            source = nullptr;
            target = nullptr;
        }

        Airlift(int playerID, const std::string& desc, int troops, Territory* source, Territory* target) : Order(playerID, desc), troops(new int(troops)), source(source), target(target) {}

        Airlift(const Airlift& other) : Order(other), troops(new int(*other.troops)), source(other.source), target(other.target) {}

        ~Airlift() {
            Order::~Order();
            delete troops;
        }

        Airlift& operator=(const Airlift& other) {
            if (this != &other) {
                Order::operator=(other);
                delete troops;
                this->troops = new int(*other.troops);
                this->source = other.source;
                this->target = other.target;
            }
            return *this;
        }

        friend ostream& operator<<(std::ostream& os, const Airlift& order) {
            os << *order.description + " executed by Player " << *order.playerIssuerID << ". " << *order.troops << " troops have been airlifted from " << order.source->getName() << " to " << order.target->getName() << "\n";
            return os;
        }

        bool validate() override;
        int execute() override;

        int getTroops() const { return *troops; }
        void setTroops(int value) { *troops = value; }

        Territory* getSource() const { return source; }
        void setSource(Territory* value) { source = value; }

        Territory* getTarget() const { return target; }
        void setTarget(Territory* value) { target = value; }

};

class Negotiate : public Order{

    private:
        //Player ID to negotiate with
        int* targetPlayerID;

        //Array to store negotiations for the negotiations. To be cleared at the end of the turn.
        static std::vector<std::pair<int, int>> negotiations;

    public:
        Negotiate() : Order() {
            *description = "This is a Negotiate order";
            targetPlayerID = new int(0);
        }

        Negotiate(int playerID, const std::string& desc, int targetPlayerID) : Order(playerID, desc), targetPlayerID(new int(targetPlayerID)) {}

        Negotiate(const Negotiate& other) : Order(other), targetPlayerID(new int(*other.targetPlayerID)) {}

        ~Negotiate() {
            Order::~Order();
            delete targetPlayerID;
        }

        Negotiate& operator=(const Negotiate& other) {
            if (this != &other) {
                Order::operator=(other);
                delete targetPlayerID;
                this->targetPlayerID = new int(*other.targetPlayerID);
            }
            return *this;
        }

        friend ostream& operator<<(std::ostream& os, const Negotiate& order) {
            os << *order.description + " executed by Player " << *order.playerIssuerID << ". " << "Player " << *order.playerIssuerID << " has negotiated with Player " << *order.targetPlayerID << ". No attacks between them shall be launched." << "\n";
            return os;
        }

        static void addNegotiation(int player1, int player2){
            negotiations.push_back(std::make_pair(player1, player2));
        }

        static bool isNegotiation(int player1, int player2){
            for(std::pair pair : negotiations){
                if((pair.first == player1 || pair.second == player1) && (pair.first == player2 || pair.second == player2) && (player1 != player2))
                    return true;
            }

            return false;
        }

        static void emptyNegotiations(){
            negotiations.clear();
        }

        bool validate() override;
        int execute() override;

        int getPlayerTargetID() const { return *targetPlayerID; }
        void setPlayerTargetID(int value) { *targetPlayerID = value; }

};

class OrdersList : public ILoggable, public Subject{

    private:
      
        std::vector<Order*> orders;
        void copyOrders(const OrdersList& other);

    public:
        OrdersList() = default;
        OrdersList(const OrdersList& other);

        ~OrdersList() {
            for (Order* order : orders) {
                delete order;
            }

            orders.clear();
        }

        OrdersList& operator=(const OrdersList& other);

        int add(Order* order);
        int move(int index1, int index2);
        int remove();
        int remove(int index);
        int executeAll();

        Order* get(int index) {
            return orders[index];
        }

        vector<Order*> getOrders() {
            return orders;
        }

        void setOrder(vector<Order*> ordersVector) {
            orders = ordersVector;
        }

        friend std::ostream& operator<<(std::ostream& os, const OrdersList& ordersList);


        string stringToLog() override;

        void addOrders(const Order& o);
};

// free function declaration
int testOrdersLists();

#endif