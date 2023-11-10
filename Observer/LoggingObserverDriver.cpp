#include "LoggingObserver.h"
#include "../Orders/Orders.h"
#include "../GameEngine/GameEngine.h"
//using the testGameStates function.
//#include "../CommandProcessing/CommandProcessing.h"
#include <string>
#include <map>
#include <vector>
using namespace std;

void CheckNotifyStatus(Subject& subject) {
    cout << "Was it notified: " << (subject.NotifyCalled() ? "Yes" : "No") <<endl;
}
void testLoggingObserver(){
    //Observer* logObserver = new LogObserver();
    LogObserver* logObserver = new LogObserver();
    Subject* subject = new Subject();
    Order order = Order();
    OrdersList ordersList = OrdersList();
    GameEngine engine = gameInit();
    //Command command;
    //CommandProcessor commandprocessor;
    //Subject* order = new Order();
    //Subject* orderList = new OrdersList();
    //Subject* gameEngine = new GameEngine();
    //Subject* command = new Command();
    //Subject* commandprocessor = new CommandProcessor();

    //1)The Command, CommandProcessor, Order, OrderList, and GameEngine classes
    // are all a subclass of the Subject and ILoggable classes

    //bool is_command_child = is_base_of<Subject, Command >::value;
    //bool is_commandProcessor_child = is_base_of<Subject, CommandProcessor >::value;
    bool is_order_child = is_base_of<Subject, Order >::value;
    bool is_orderList_child = is_base_of<Subject, OrdersList >::value;
    bool is_gameEngine_child = is_base_of<Subject, GameEngine >::value;
    //True/False instead of 1/0
    cout << std::boolalpha;
    //cout <<"Is Command a subclass: "<<+is_command_child <<" .Is CommandProcessor a subclass: "<<+is_commandProcessor_child + endl;
    cout <<"Is Order a subclass: "<<+is_order_child <<" .Is OrderList a subclass: "<<+is_orderList_child <<" .Is GameEngine a subclass: "<<+is_gameEngine_child << endl;

    //2)the CommandProcessor::saveCommand(), Order::execute(), Command::saveEffect(), OrderList::addOrder(), and GameEngine::transition()
    // methods are effectively using the Observer patterns’ Notify(Subject) method to trigger the writing of an entry in the log file
    order.Attach(logObserver);
    order.execute();
    CheckNotifyStatus(order);

    ordersList.Attach(logObserver);
    ordersList.add(order);
    CheckNotifyStatus(ordersList);

    engine.Attach(logObserver);
    engine.processCommand("loadmap");
    CheckNotifyStatus(engine);

//    saveCommand
//    command.Attach(logObserver);
//    ordersList.saveEffect(order);
//    CheckNotifyStatus(command);
//    saveEffect
//    commandprocessor.Attach(logObserver);
//    commandprocessor.saveCommand(order);
//    CheckNotifyStatus(ordersList);

    //3) the gamelog.txt file gets correctly written into when commands are entered on the console

    //4) when an order is added to the order list of a player,
    // the game log observer is notified which results in outputting the order to the logfile

    //5)when an order is executed, the game log observer is notified which results
    // in outputting the effect of the order to the log file

    //6)when the GameEngine changes its state, the new state is output to the log file.



    delete subject;
    delete logObserver;
}
