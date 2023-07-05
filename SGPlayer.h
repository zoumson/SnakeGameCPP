#pragma once

#include <vector>
#include <deque>
#include "SGPoint.h"

enum class Facing { right, down, left, up, null };

class Player
{
private:
    std::deque<Point> m_position;
    unsigned int m_length;
    Facing m_facing;

public:

    Player();
    ~Player();
    Player(const Player& t);
    Player(Player&& t);
    Player& operator=(const Player& t);
    Player& operator=(Player&& t);
    void move(const Point& p_field_size);
    void lengthen();
    Point get(unsigned int p_at = 0);

    Facing get_facing();
    void set_facing(const Facing& p_facing);

    // returns the amount of Points the player occupies (costly!)
    int size();

    // returns the player's length. size() may have not been updated to it yet
    unsigned int length();
};