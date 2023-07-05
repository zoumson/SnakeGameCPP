#include <stdexcept>
#include "SGPlayer.h"
#include <iostream>



Player::Player()
{
    m_position = { {15, 10} };
    m_length = 1;
    Facing m_facing = Facing::right;
}
Player::~Player()
{

}
Player::Player(const Player& t)
{
    m_position = t.m_position;
    m_length = t.m_length;
    m_facing = t.m_facing;    
}

Player::Player(Player&& t)
{
    m_position = t.m_position;
    m_length = t.m_length;
    m_facing = t.m_facing;

    t.m_position = {};
    t.m_length = 0;
    t.m_facing = Facing::null;
}

Player& Player::operator=(const Player& t)
{
    m_position = t.m_position;
    m_length = t.m_length;
    m_facing = t.m_facing;
    return *this;
}

Player& Player::operator=(Player&& t)
{
    m_position = t.m_position;
    m_length = t.m_length;
    m_facing = t.m_facing;

    t.m_position = {};
    t.m_length = 0;
    t.m_facing = Facing::null;
    return *this;
}

void Player::lengthen()
{
    ++m_length;
}

Point Player::get(unsigned int p_at)
{
    return m_position.at(p_at);
}

Facing Player::get_facing()
{
    return m_facing;
}

int Player::size()
{
    return m_position.size();
}

unsigned int Player::length()
{
    return m_length; 
}

void Player::move(const Point& p_field_size)
{
    int player_curr_x = m_position.front().x;
    int player_curr_y = m_position.front().y;


    //move to a given direction 
    auto mv_to_dir = [&](Facing mv_dir)
    {
        //mask the previous location of the player with "space"
        //mvaddch(player_curr_y, player_curr_x, player_back_footprint);

        //step to the advance the player
        switch (mv_dir)
        {

        case Facing::left:
            --player_curr_x;
            break;

        case Facing::right:
            ++player_curr_x;
            break;


        case Facing::up:
            --player_curr_y;
            break;


        case Facing::down:
            ++player_curr_y;
            break;

        default:
            break;
        };

        //show the current location of the player on the screen
        //mvaddch(player_curr_y, player_curr_x, player_label);

    };

    //hit or pass throught the side borders when reached 
    auto pass_through_wall = [&](const Facing& wall_side, const int& wall_height, const int& wall_width, const bool& enable)
    {
        //allow to pass throught the walls/borders
        if (enable)
        {
            //mask the previous location of the player with "space"
            //mvaddch(player_curr_y, player_curr_x, player_back_footprint);

            //algo to pass throught the borders
            switch (wall_side)
            {

            case Facing::left:
                player_curr_x = wall_width - 1;
                break;

            case Facing::right:
                player_curr_x = 0;
                break;


            case Facing::up:
                player_curr_y = wall_height - 1;
                break;


            case Facing::down:
                player_curr_y = 0;
                break;

            default:
                break;
            }

            //show the current location of the player on the screen
            //mvaddch(player_curr_y, player_curr_x, player_label);
        }
        else
        {
            //hit the wall and wait there
        }
    };

    //display player current position after the later has hit a key
    auto displ_player_curr_pos = [&](const Facing& player_input_loc, const int& wall_height_loc, const int& wall_width_loc)
    {
        switch (player_input_loc)
        {
            //move to the left 
        case Facing::left:
            //when reach left border of the screen pass throught  or hit
            if (player_curr_x == 0)
            {
                pass_through_wall(Facing::left, wall_height_loc, wall_width_loc, false);
            }
            else
            {
                mv_to_dir(Facing::left);
            }

            break;
            //move to the right
        case Facing::right:
            //when reach right border of the screen pass throught  or hit
            if (player_curr_x >= wall_width_loc - 1)
            {
                pass_through_wall(Facing::right, wall_height_loc, wall_width_loc, true);
            }
            else
            {
                mv_to_dir(Facing::right);
            }

            break;
            //move up
        case Facing::up:

            //when reach upper border of the screen pass throught  or hit
            if (player_curr_y <= 0)
            {
                pass_through_wall(Facing::up, wall_height_loc, wall_width_loc, false);
            }
            else
            {
                mv_to_dir(Facing::up);
            }
            break;

            //move down
        case Facing::down:
            //when reach lower border of the screen pass throught  or hit
            if (player_curr_y == wall_height_loc - 1)
            {
                pass_through_wall(Facing::down, wall_height_loc, wall_width_loc, true);
            }
            else
            {
                mv_to_dir(Facing::down);
            }
            break;

        default:
            break;
        }
    };

    displ_player_curr_pos(m_facing, p_field_size.y, p_field_size.x);


    Point next_pos = { player_curr_y, player_curr_x };

    //m_position.insert(m_position.begin(), next_pos);
    m_position.push_front(next_pos);
    {
        if (m_position.size() > m_length) m_position.pop_back();
    }


}

void Player::set_facing(const Facing& p_facing)
{
    //m_facing = p_facing;
    
    switch (p_facing)
    {
    case Facing::right:
        if (m_facing == Facing::left)
        {
            //back turn not allowed
        }
        else
        {
            m_facing = p_facing;
        }
            
                      
        break;
    case Facing::left:
        if (m_facing == Facing::right)
        {
            //back turn not allowed
        }
        else
        {
            m_facing = p_facing;
        }

        break;
    case Facing::down:
        if (m_facing == Facing::up)
        {
            //back turn not allowed
        }
        else
        {
            m_facing = p_facing;
        }
        break;
    case Facing::up:
        if (m_facing == Facing::down)
        {
            //back turn not allowed
        }
        else
        {
            m_facing = p_facing;
        }
        break;
    default:
        break;
    }
    
}