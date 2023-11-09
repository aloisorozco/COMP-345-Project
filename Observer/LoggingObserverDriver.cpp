#include "../Observer/LoggingObserver.h"
#include <string>
#include <map>
#include <vector>
using namespace std;


int testLoggingObserver(){
    //Typically, a pointer variable to an abstract class type is declared,
    //then is instantiated with an object of one of the subtypes.
    Observer* observer = new LogObserver();

}
