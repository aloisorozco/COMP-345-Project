#include <iostream>
#include <vector>
#include <string>
#include "Orders.h"

using namespace std;

int testOrdersLists();

int main(){

    return testOrdersLists();
}

int testOrdersLists(){

    OrdersList orders = OrdersList();
    orders.add(Order());
    orders.add(Deploy());
    orders.add(Advance());
    orders.add(Bomb());
    orders.add(Blockade());
    orders.add(Airlift());
    orders.add(Negotiate());

    orders.add(Advance());
    orders.add(Bomb());
    orders.add(Airlift());

    orders.remove(4);
    orders.remove();
    orders.remove();
    orders.remove(20);

    orders.move(2, 5);

    return orders.executeAll();
}