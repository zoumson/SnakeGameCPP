#pragma once

#include "SGPoint.h"
#include "SGPlayer.h"


enum class Object { empty, player, food, wall, head_up, head_down, head_left, head_right, tail_h, tail_v };

class Field
{
private:

    std::vector<std::vector<Object>> m_field;
public:
    Field();
    ~Field();
    Field(const Field& t);
    Field& operator=(const Field& t);
    Field(Field&& t);
    Field& operator=(Field&& t);

    Point m_field_size;

    const Object& get(const Point& p_point);

    void set(Point& p_point, Object p_object);
    void place_food();
    void add_walls();
    void update_player(Player& p_player);
};