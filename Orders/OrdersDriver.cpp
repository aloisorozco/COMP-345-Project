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
    orders.add(new Order());
    orders.add(new Deploy());
    orders.add(new Advance());
    orders.add(new Bomb());
    orders.add(new Blockade());
    orders.add(new Airlift());
    orders.add(new Negotiate());

    orders.add(new Advance());
    orders.add(new Bomb());
    orders.add(new Airlift());

    orders.remove(4);
    orders.remove();
    orders.remove();
    orders.remove(20);

    orders.move(2, 5);

    OrdersList orders2 = orders;

    orders2.executeAll();

    cout << "\n" << orders;

    return 0;
}