#ifndef LOGGINGOBSERVER_H
#define LOGGINGOBSERVER_H

// #include "../CommandProcessor/CommandProcessing.h"
//#include "../Orders/Orders.h"
//#include "../GameEngine/GameEngine.h"
#include <string>
#include <list>
#include <vector>
using namespace std;
//Forward Declare everything
class ILoggable;
class Observer;
class Subject;
class OrdersList;
class GameEngine;
class LogObserver;
class Command;
class CommandProcessor;
class ConsoleCommandProcessor;
class FileCommandProcessorAdapter;

//abstract class, with method stringToLog(). all classes inherit this to log data.
class ILoggable{
    public:
        ~ILoggable();
        ILoggable();
        ILoggable(const ILoggable&); // copy constructor
        ILoggable& operator = (const ILoggable&);
        friend ostream& operator<<(ostream&,const ILoggable&);//3.stream insertion operator for output
        // pure virtual, create and return string for output into log file gamelog.txt
        virtual string stringToLog()=0;
    private:
};
//Observer class in the Observer Pattern
class Observer{
    public:
        ~Observer();
        Observer();
        Observer(const Observer&); // copy constructor
        Observer& operator = (const Observer&);
        friend ostream &operator<<(ostream &os, const Observer &observer);
        //Pure virtual update used by our concreteObserver LogObserver
        virtual void Update(ILoggable* iLoggable)=0;
};
/*
 * writes every game command read by a CommandProcessor object (or a FileCommandProcessorAdapter object)
game log observer should be notified by the CommandProcessor::saveCommand(), as well as the and Command::saveEffect()
 This should result in all the current game’s commands and their effects to be logged into a “gamelog.txt”
file.
 *///our ConcreteObserver (View class)
class LogObserver : public Observer{
    public:
        //A constructor for every subject we wish to observee
        LogObserver();
        ~LogObserver();
        LogObserver(const LogObserver&); // copy constructor
        LogObserver& operator = (const LogObserver&);
        friend ostream& operator<<(ostream&,const LogObserver&);//3.stream insertion operator for output
        void AddSubject(Subject* subject);
        //explicit LogObserver(OrdersList* ordersList);
        //explicit LogObserver(GameEngine* gameEngine);
        //LogObserver(CommandProcessor *commandProcessor);
        //LogObserver(FileCommandProcessorAdapter *fileCommandProcessorAdapter);
        void Update(ILoggable* iLoggable) override;
        const vector<Subject *> &getSubject() const;
private:
        vector<Subject*> _subject;
        //OrdersList *_ordersList_subject;
        //GameEngine *_gameEngine_subject;
        //CommandProcessor* _commandProcessor_subject{};
        //FileCommandProcessorAdapter* _fileCommandProcessorAdapter_subject{};
};
//Subject class in the observer pattern
class Subject{
public:
    virtual void Attach(Observer* o);
    virtual void Detach(Observer* o);
    virtual void Notify(ILoggable *);
    Subject();
    ~Subject();

    Subject(const Subject&); // copy constructor
    Subject& operator = (const Subject&); // unused
    friend ostream& operator<<(ostream&,const Subject&);//3.stream insertion operator for output

    //used to check if Notify was called.
    bool NotifyCalled() const {
        return notified;
    }
private:
    list<Observer*> *_observers;
    bool notified = false;
};
void CheckNotifyStatus(Subject& subject);
bool isInLog(string s);
void testLoggingObserver();

#endif //LOGGINGOBSERVER_H
