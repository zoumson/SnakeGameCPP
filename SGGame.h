#pragma once

#include <exception>
#include "SGPlayer.h"
#include "SGField.h"
#include "SGUI.h"
//
//class Field;
//class GameUI;
//class Player;

struct GameEndDeath : std::exception {};
struct GameEndQuit : std::exception {};


//Facade Design Pattern
class Game
{
private:
    GameUI m_ui;
    Field m_field;
    Player m_player;

    void tick();
    void update();
public:
    Game(GameUI& p_ui);
    ~Game();
    void start();
};