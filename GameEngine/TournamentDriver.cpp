// GameEngine.cpp
#include "GameEngine.h"
#include <iostream>
#include <map>
#include <chrono>
#include <thread>
#include <random>
#include <sstream>
#include <stdexcept>
#include <iomanip>

#include "../Player/Player.h"
#include "../PlayerStrategy/PlayerStrategy.h"
#include "../PlayerStrategy/HumanPlayerStrategy.h"
#include "../PlayerStrategy/NeutralPlayerStrategy.h"
#include "../PlayerStrategy/CheaterPlayerStrategy.h"
#include "../PlayerStrategy/AggressivePlayerStrategy.h"
#include "../PlayerStrategy/BenevolentPlayerStrategy.h"
#include "../Map/Map.h"
#include "../CommandProcessor/CommandProcessing.h"


void testTournament(){
    GameEngine* engine = new GameEngine();
    engine->startupPhase(*engine);
    delete engine;
}