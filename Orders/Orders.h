#ifndef ORDERS_H
#define ORDERS_H

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Order {

    protected:
        std::string description;

    public:
        Order() : description("This is a generic order description."){}
        Order(const Order& other) : description(other.description) {}

        Order& operator=(const Order& other) {

            if (this != &other) {
                this->description = other.description;
            }
            return *this;
        }

        virtual bool validate();
        virtual int execute();

        friend std::ostream& operator<<(std::ostream& os, const Order& order) {
            os << order.getDescription();
            return os;
        }

        virtual std::string getDescription() const {
            return this->description;
        }
};

class Deploy : public Order {

    private:
        string* territoryName;
        int* troopsDeployed;

    public:
        Deploy(){
            description = "This is a deploy order";
            territoryName = new string();
            troopsDeployed = new int(0);
        }

        Deploy(string tName, int troops) : territoryName(new string(tName)), troopsDeployed(new int(troops)) {

        }

        bool validate() override;
        int execute() override;


};

class Advance : public Order {

    private:
        string* srcTerritoryName;
        string* dstTerritoryName;
        int* troopsToAdvance;

    public:
        Advance(){
            description = "This is an Advance order";
            srcTerritoryName = new string();
            dstTerritoryName = new string();
            troopsToAdvance = new int(0);
        }

        Advance(string src, string dst, int troops) : 
            srcTerritoryName(new string(src)), dstTerritoryName(new string(dst)), troopsToAdvance(new int (troops)) {

        }

        bool validate() override;
        int execute() override;



};

class Bomb : public Order{

    public:
        Bomb(){
            description = "This is a Bomb order";
        }

        bool validate() override;
        int execute() override;

};

class Blockade : public Order{

    public:
        Blockade(){
            description = "This is a Blockade order";
        }

        bool validate() override;
        int execute() override;
};

class Airlift : public Order{

    public:
        Airlift(){
            description = "This is an Airlift order";
        }

        bool validate() override;
        int execute() override;

};

class Negotiate : public Order{

    public:
        Negotiate(){
            description = "This is a Negotiate order";
        }

        bool validate() override;
        int execute() override;

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

        //keep this function returning a pointer!!!
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

// free function declaration
int testOrdersLists();

#endif