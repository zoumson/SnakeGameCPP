#pragma once

#include <curses.h>
#include <string>
#include <vector>

#include "SGPoint.h"
#include "SGField.h"

class Field;
enum class Facing;

using menu_item_t = int;

struct MenuItem
{
    std::string label;
    Point pos;

    MenuItem(std::string _label, Point _pos) : label(_label), pos(_pos) {};
};

class MainMenu
{
private:
    template<typename Functor>
    void display_menu(std::vector<MenuItem>& p_menu_items, Functor p_selected_item_handler, bool p_quit_with_q, std::string p_title = "Snake");
    void new_game();
    void show_settings();
public:
    MainMenu();
    ~MainMenu();
    void show();
};

class GameUI
{
private:


    //Facade Design Pattern 
    WINDOW* m_border_win,  *m_field_win;
    Field* m_field;

    void update_field();
public:

    GameUI(WINDOW* p_border_win, WINDOW* p_field_win);


    GameUI() = delete;


    GameUI(const GameUI& t)
    {
        m_border_win = t.m_border_win;
        m_field_win = t.m_field_win;
        m_field = t.m_field;
    }

    

    GameUI& operator=(const GameUI& t)
    {
        m_border_win = t.m_border_win;
        m_field_win = t.m_field_win;
        m_field = t.m_field;

        return *this;
    }
    
    GameUI(GameUI&& t)
    {
        m_border_win = t.m_border_win;
        m_field_win = t.m_field_win;
        m_field = t.m_field;

        t.m_border_win = nullptr;
        t.m_field_win = nullptr;
        t.m_field = nullptr;
    }

    

    GameUI& operator=(GameUI&& t)
    {
        m_border_win = t.m_border_win;
        m_field_win = t.m_field_win;
        m_field = t.m_field;

        t.m_border_win = nullptr;
        t.m_field_win = nullptr;
        t.m_field = nullptr;

        return *this;
    }



    void set_field(Field& p_field) { m_field = &p_field; };
    void draw_border();
    void draw_static_elements();
    void update(int score);
    Facing get_input();

};

class UIUtils
{
private:
    UIUtils() {};
public:
    static menu_item_t dialogbox(std::string p_text, std::vector<std::string> p_buttons);
};