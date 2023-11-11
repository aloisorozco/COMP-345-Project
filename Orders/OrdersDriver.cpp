#include <iostream>
#include <vector>
#include <string>
#include "Orders.h"
#include "../Player/Player.h"

using namespace std;

int testOrdersLists(){
    int any;

    Player p1 = Player();
    Player p2 = Player();
    Player p3 = Player();
    Player p4 = Player();

    Territory* t1 = new Territory("try 1", "Trial World");
    Territory* t2 = new Territory("try 2", "Trial World");
    Territory* t3 = new Territory("try 3", "Trial World");
    Territory* t4 = new Territory("try 4", "Trial World");
    Territory* t5 = new Territory("try 5", "Trial World");
    Territory* t6 = new Territory("try 6", "Trial World");

    t1->addNeighbor(t2);

    t1->setArmy(6);
    t2->setArmy(6);
    t3->setArmy(6);
    t4->setArmy(6);
    t5->setArmy(6);
    t6->setArmy(6);

    t1->setPlayer(p1.getPlayerID());
    t2->setPlayer(p2.getPlayerID());
    t3->setPlayer(p3.getPlayerID());
    t4->setPlayer(p3.getPlayerID());
    t5->setPlayer(p4.getPlayerID());
    t6->setPlayer(p4.getPlayerID());

    p1.getOrdersList()->add(new Order());
    p1.getOrdersList()->add(new Deploy(p1.getPlayerID(), "p1 deploy", 4, t1));
    p1.getOrdersList()->add(new Advance(p1.getPlayerID(), "p1 advance", 3, t1, t2));
    p1.getOrdersList()->add(new Bomb(p1.getPlayerID(), "p1 bomb", t3));
    p4.getOrdersList()->add(new Blockade(p4.getPlayerID(), "p4 blockade", t5));
    p2.getOrdersList()->add(new Airlift(p1.getPlayerID(), "p2 airlift invalid", 4, t5, t6));
    p2.getOrdersList()->add(new Negotiate(p2.getPlayerID(), "p2 negotiates p1", p1.getPlayerID()));
    p2.getOrdersList()->add(new Bomb(p2.getPlayerID(), "p2 bomb", t1));

    p1.getOrdersList()->executeAll();
    p2.getOrdersList()->executeAll();
    p3.getOrdersList()->executeAll();
    p4.getOrdersList()->executeAll();

    cout << "Enter any character to end : ";
    cin >> any;
    return 0;
}