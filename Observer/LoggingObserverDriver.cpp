//#include "../Observer/LoggingObserver.h"

#include <string>
#include <map>
#include <vector>
using namespace std;


int testLoggingObserver(){
/*
 * You must deliver a driver as a free function named testLoggingObserver() that demonstrates that (1) The
Command, CommandProcessor (see Part 1), Order, OrderList, and GameEngine classes are all a subclass of the
Subject and ILoggable classes (2) the CommandProcessor::saveCommand(), Order::execute(),
Command::saveEffect(), OrderList::addOrder(), and GameEngine::transition() methods are effectively
using the Observer patterns’ Notify(Subject) method to trigger the writing of an entry in the log file (3) the
gamelog.txt file gets correctly written into when commands are entered on the console (4) when an order is
added to the order list of a player, the game log observer is notified which results in outputting the order to the log
file (5) when an order is executed, the game log observer is notified which results in outputting the effect of the
order to the log file (6) when the GameEngine changes its state, the new state is output to the log file. This driver
function must be in the LoggingObserverDriver.cpp file.
 */
}
