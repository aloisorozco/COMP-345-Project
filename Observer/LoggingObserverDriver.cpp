#include "LoggingObserver.h"
#include "../Orders/Orders.h"
#include "../GameEngine/GameEngine.h"
//using the testGameStates function.
<<<<<<< Updated upstream
//#include "../CommandProcessing/CommandProcessing.h"
=======
#include "../CommandProcessor/CommandProcessing.h"
>>>>>>> Stashed changes
#include <string>
#include <map>
#include <vector>
#include <sstream>
#include <fstream>

using namespace std;

void CheckNotifyStatus(Subject& subject) {
    cout << "Was Notify() called: " << (subject.NotifyCalled() ? "Yes" : "No") <<endl;
}
string outputLog(){
    ifstream log("gamelog.txt");
    ostringstream buffer;
    buffer << log.rdbuf();
    log.close();
    return buffer.str();
}
bool isInLog(string s){
    string log = outputLog();
    return log.find(s) != string::npos;
}
void testLoggingObserver(){
    //Observer* logObserver = new LogObserver();
    LogObserver* logObserver = new LogObserver();
    Subject* subject = new Subject();
    Order *order = new Order();
    OrdersList *ordersList = new OrdersList();
<<<<<<< Updated upstream
    GameEngine engineInit = gameInit();
    GameEngine *engine = &engineInit;
    Command *command = new Command();
    CommandProcessor *commandProcessor = new CommandProcessor();

=======
    GameEngine *engine = new GameEngine();
    gameInit(*engine); //new gameInit
    Command *command = new Command();
    ConsoleCommandProcessor *consoleProcessor = new ConsoleCommandProcessor(engine);
>>>>>>> Stashed changes
    //1)The Command, CommandProcessor, Order, OrderList, and GameEngine classes
    // are all a subclass of the Subject and ILoggable classes
    bool is_command_child = is_base_of<Subject, Command >::value;
    bool is_commandProcessor_child = is_base_of<Subject, ConsoleCommandProcessor >::value;
    bool is_order_child = is_base_of<Subject, Order >::value;
    bool is_orderList_child = is_base_of<Subject, OrdersList >::value;
    bool is_gameEngine_child = is_base_of<Subject, GameEngine >::value;
    //True/False instead of 1/0
    cout << std::boolalpha;
<<<<<<< Updated upstream
    cout <<"\nIs Command a subclass: "<<+is_command_child <<" .Is CommandProcessor a subclass: "<<+is_commandProcessor_child + endl;
=======
    cout <<"\nIs Command a subclass: "<<is_command_child <<" .Is CommandProcessor a subclass: "<<is_commandProcessor_child <<endl;
>>>>>>> Stashed changes
    cout <<"\nIs Order a subclass: "<< is_order_child <<" .Is OrderList a subclass: "<< is_orderList_child <<" .Is GameEngine a subclass: "<< is_gameEngine_child << endl;

    //2)the CommandProcessor::saveCommand(), Order::execute(), Command::saveEffect(), OrderList::addOrder(), and GameEngine::transition()
    // methods are effectively using the Observer patterns’ Notify(Subject) method to trigger the writing of an entry in the log file
    //order->Attach(logObserver);
    logObserver->AddSubject(order);
    order->execute();
    CheckNotifyStatus(*order);

    //ordersList.Attach(logObserver);
    logObserver->AddSubject(ordersList);
    ordersList->add(order);
    CheckNotifyStatus(*ordersList);

    //engine.Attach(logObserver);
    logObserver->AddSubject(engine);
    engine->processCommand("loadmap");
    CheckNotifyStatus(*engine);

<<<<<<< Updated upstream
//    saveCommand
    logObserver->AddSubject(command);
    command->saveEffect(order);
    CheckNotifyStatus(command);

//    saveEffect
    logObserver->AddSubject(commandProcessor);
    commandProcessor.saveCommand(order);
    CheckNotifyStatus(commandProcessor);
=======
////    saveEffect
//    logObserver->AddSubject(consoleProcessor);
//    consoleProcessor->saveCommand(command->command);
//    CheckNotifyStatus(*consoleProcessor);
//    //    saveCommand
//    cout<<"Save Command"<<endl;
//    logObserver->AddSubject(consoleProcessor);
//    consoleProcessor->saveEffect(command->effect);
//    CheckNotifyStatus(*command);
>>>>>>> Stashed changes
//  part 3,4,5,6
    bool orderWritten = isInLog(order->stringToLog());
    bool orderListWritten = isInLog(ordersList->stringToLog());
    bool engineWritten = isInLog(engine->stringToLog());
//    bool commandWritten = isInLog(command->stringToLog());
//    bool commandProcessorWritten = isInLog(consoleProcessor->stringToLog());
    cout <<"\nIs Order written to logs: "<< orderWritten <<" .Is OrderList written to log: "<< orderListWritten <<" .Is GameEngine a subclass: "<<engineWritten << endl;
//    cout <<"\nIs Command written to logs: "<< commandWritten <<" .Is CommandProcessor written to log: "<< commandProcessorWritten << endl;

    delete subject;
    delete logObserver;
<<<<<<< Updated upstream
=======


>>>>>>> Stashed changes
}
