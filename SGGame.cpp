#include <chrono>
#include <thread>
//#include <unistd.h>

#include "SGGame.h"

#include "SGField.h"
#include "SGPlayer.h"
#include "SGSettings.h"
#include "SGUI.h"

void Game::tick()
{
    int tick_delay_time = 500;

    while (true)
    {
        m_player.set_facing(m_ui.get_input());       
        update();
        std::this_thread::sleep_for(std::chrono::milliseconds(tick_delay_time));

    }
}

void Game::update()
{
    Point player_head = m_player.get(0);
   
    switch (m_field.get(player_head))
    {
    case Object::food:
    {
        m_field.set(player_head, Object::player);
        m_field.place_food();
        m_player.lengthen();
        break;
    }
    case Object::wall:
        throw GameEndDeath();
    default:
        break;
    }

    m_field.update_player(m_player);
    m_player.move(m_field.m_field_size);
    m_ui.update(m_player.length() - 1);
}

Game::Game(GameUI& p_ui) : m_ui(p_ui)
{
    //m_field = new Field();
    m_ui.set_field(m_field);

    //m_player = new Player();
}

Game::~Game()
{
    //delete m_field;
    //delete m_player;
}

void Game::start()
{
    if (Settings::enable_walls) 
    {
        m_field.add_walls();
    }

    m_field.place_food();

    m_ui.draw_static_elements();

    while (true)
    {
        try
        {
            tick();
        }
        catch (const GameEndQuit&)
        {
            // TODO: redraw the field when "No" is clicked
            if (UIUtils::dialogbox(std::string("Quit?"), std::vector<std::string> {std::string("No"), std::string("Yes")}) == 1) return;
            m_ui.draw_border();
            m_ui.draw_static_elements();
        }
        catch (const GameEndDeath&)
        {
            UIUtils::dialogbox(std::string("You died"), std::vector<std::string> {std::string("OK")});
            return;
        }
    }
}