#ifndef Orders
#define Orders

#include <iostream>
#include <string>
#include <vector>

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

class Deploy : public Order{

    public:
        Deploy(){
            description = "This is a deploy order";
        }

        bool validate() override;
        int execute() override;

};

class Advance : public Order{

    public:
        Advance(){
            description = "This is an Advance order";
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
        std::vector<Order*> orders;

        void copyOrders(const OrdersList& other);

    public:

        OrdersList() = default;
        OrdersList(const OrdersList& other);

        OrdersList& operator=(const OrdersList& other);

        int add(Order* order);
        int move(int index1, int index2);
        int remove();
        int remove(int index);
        int executeAll();

        friend std::ostream& operator<<(std::ostream& os, const OrdersList& ordersList);
};

#endif