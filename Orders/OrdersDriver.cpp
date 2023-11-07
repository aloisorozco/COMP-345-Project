#include <iostream>
#include <vector>
#include <string>
#include "Orders.h"

using namespace std;

int testOrdersLists(){
    int any;

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

    OrdersList orders2 = orders;

    orders2.executeAll();

    cout << "\n" << orders;

    cout << "Enter any character to end : ";
    cin >> any;
    return 0;
}

/*int main(){
    testOrdersLists();
    return 0;
}*/