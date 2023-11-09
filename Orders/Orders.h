#ifndef ORDERS_H
#define ORDERS_H

#include <iostream>
#include <string>
#include <vector>
#include "../Map/Map.h"
#include "../GameEngine/GameEngine.h"

class Order {

    protected:
        int* playerIssuerID;
        string* description;

    public:
        Order() : playerIssuerID(nullptr), description(new string("This is a generic order description."))  {}
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
            os << "Description: " << order.getDescription() << ", PlayerIssuerID: " << order.playerIssuerID;
            return os;
        }

        virtual string getDescription() const {
            return *this->description;
        }

        virtual int getPlayerIssuerID() const {
            return *this->playerIssuerID;
        }
};

class Deploy : public Order{

    private:
        int* troops;
        Territory* target;

    public:
        Deploy() : Order() {
            *description = "This is a deploy order";
            troops = new int(0);
            target = nullptr;
        }

        Deploy(int playerID, const std::string& desc, int troops, Territory* source, Territory* target) : Order(playerID, desc), troops(new int(troops)), target(target) {}

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
            os << "Description: " << order.getDescription() << ", PlayerIssuerID: " << order.playerIssuerID << ", Type: Deploy";
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
        int* troops;
        Territory* source;
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
            os << "Description: " << order.getDescription() << ", PlayerIssuerID: " << order.playerIssuerID << ", Type: Advance";
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
            os << "Description: " << order.getDescription() << ", PlayerIssuerID: " << order.playerIssuerID << ", Type: Bomb";
            return os;
        }

        bool validate() override;
        int execute() override;

        Territory* getTarget() const { return target; }
        void setTarget(Territory* value) { target = value; }

};

class Blockade : public Order{

    private:
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
            os << "Description: " << order.getDescription() << ", PlayerIssuerID: " << order.playerIssuerID << ", Type: Blockade";
            return os;
        }

        bool validate() override;
        int execute() override;

        Territory* getTarget() const { return target; }
        void setTarget(Territory* value) { target = value; }
};

class Airlift : public Order{

    private:
        int* troops;
        Territory* source;
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
            os << "Description: " << order.getDescription() << ", PlayerIssuerID: " << order.playerIssuerID << ", Type: Airlift";
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
        int* targetPlayerID;

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
            os << "Description: " << order.getDescription() << ", PlayerIssuerID: " << order.playerIssuerID << ", Type: Negotiate";
            return os;
        }

        bool validate() override;
        int execute() override;

        int getPlayerTargetID() const { return *targetPlayerID; }
        void setPlayerTargetID(int value) { *targetPlayerID = value; }

};

class OrdersList {

    private:
        std::vector<Order> orders;

        void copyOrders(const OrdersList& other);

    public:

        OrdersList() = default;
        OrdersList(const OrdersList& other);

        OrdersList& operator=(const OrdersList& other);

        int add(Order order);
        int move(int index1, int index2);
        int remove();
        int remove(int index);
        int executeAll();

        Order* get(int index) {
            return &orders[index];
        }

        vector<Order> getOrders() {
            return orders;
        }

        void setOrder(vector<Order> ordersVector) {
            orders = ordersVector;
        }

        friend std::ostream& operator<<(std::ostream& os, const OrdersList& ordersList);
};

int testOrdersLists();

#endif