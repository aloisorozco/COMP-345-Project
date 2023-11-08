#ifndef LOGGINGOBSERVER_H
#define LOGGINGOBSERVER_H
#include <string>
#include <list>
#include <vector>

using namespace std;

//Observer class in the Observer Pattern
class Observer{
public:
    ~Observer();
    virtual void Update()=0;
protected:
};

//Subject class in the observer pattern
class Subject{
public:
    //not sure if need to be pure virtual or not
    virtual void Attach(Observer* observer);
    virtual void Detach(Observer* observer);
    virtual void Notify(ILoggable)=0;
    Subject();
    ~Subject();
private:
list<Observer*> *_observers;
};

//abstract class, with method stringToLog(). all classes inherit this to log data.
class ILoggable{
    // create and return string for output into log file gamelog.txt
    virtual string stringToLog()=0;
};
//the observer class in our pattern

//our ConcreteObserver (View class)
class LogObserver : public Observer{
/*
 * writes every game command read by a CommandProcessor object (or a
FileCommandProcessorAdapter object) into a log file. The game log observer should be notified by the
CommandProcessor::saveCommand() method that saves the command into the collection of commands, as well
as the and Command::saveEffect() method that records the effect of the command into the command object.
This should result in all the current game’s commands and their effects to be logged into a “gamelog.txt”
file.
 */
public:
    LogObserver(CommandProcessor *commandProcessor);
    LogObserver();
    LogObserver();
    ~LogObserver();
    void Update(ILoggable);
private:
};

#endif //LOGGINGOBSERVER_H
