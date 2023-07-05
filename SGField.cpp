#include <random>
#include "SGField.h"
#include "SGPlayer.h"
#include "SGSettings.h"

Field::Field() : m_field_size(Settings::field_size)
{
    m_field.resize(m_field_size.y, std::vector<Object>(m_field_size.x, Object::empty));

}

Field::~Field()
{
}

Field::Field(const Field& t)
{
    m_field_size = t.m_field_size;

    m_field.resize(m_field_size.y, std::vector<Object>(m_field_size.x, Object::empty));

    for (int y = 0; y < m_field_size.y; ++y)
    {
        for (int x = 0; x < m_field_size.x; ++x)
        {
            m_field[y][x] = t.m_field[y][x];
        }
    }
}

Field& Field::operator=(const Field& t)
{
    m_field_size = t.m_field_size;

    m_field.resize(m_field_size.y, std::vector<Object>(m_field_size.x, Object::empty));


    for (int y = 0; y < m_field_size.y; ++y)
    {
        for (int x = 0; x < m_field_size.x; ++x)
        {
            m_field[y][x] = t.m_field[y][x];
        }
    }

    return *this;
}

Field::Field(Field&& t)
{
    m_field_size = t.m_field_size;

    m_field.resize(m_field_size.y, std::vector<Object>(m_field_size.x, Object::empty));

    for (int y = 0; y < m_field_size.y; ++y)
    {
        for (int x = 0; x < m_field_size.x; ++x)
        {
            m_field[y][x] = t.m_field[y][x];
        }
    }

    t.m_field_size = {};
    t.m_field = {};
}

Field& Field::operator=(Field&& t)
{
    m_field_size = t.m_field_size;

    m_field.resize(m_field_size.y, std::vector<Object>(m_field_size.x, Object::empty));

    for (int y = 0; y < m_field_size.y; ++y)
    {
        for (int x = 0; x < m_field_size.x; ++x)
        {
            m_field[y][x] = t.m_field[y][x];
        }
    }

    t.m_field_size = {};
    t.m_field = {};

    return *this;
}

const Object& Field::get(const Point& p_point) 
{
    return m_field[p_point.y][p_point.x];
}

void Field::set(Point& p_point, Object p_object)
{
    m_field[p_point.y][p_point.x] = p_object;
}

void Field::place_food()
{

        static std::mt19937 rng(std::random_device{}());

        std::uniform_int_distribution<int> disty(0, m_field_size.y - 1);
        std::uniform_int_distribution<int> distx(0, m_field_size.x - 1);

        Point location{ disty(rng), distx(rng) };
        while (get(location) != Object::empty)
        {
            location = Point{ disty(rng), distx(rng) };
        }
        set(location, Object::food);

}

void Field::add_walls()
{

    for (int y = 0; y < m_field_size.y; ++y)
    {
        m_field[y][0] = Object::wall;
        m_field[y][m_field_size.x - 1] = Object::wall;
    }

    for (int x = 0; x < m_field_size.x; ++x)
    {
        m_field[0][x] = Object::wall;
        m_field[m_field_size.y - 1][x] = Object::wall;
    }
}

void Field::update_player(Player& p_player)
{
    //mask player previous footprint
    for (int row = 0; row < m_field_size.y; ++row)
    {
        for (int col = 0; col < m_field_size.x; ++col)
        {
            //if (m_field[row][col] == Object::player)
            if (m_field[row][col] == Object::player || m_field[row][col] == Object::head_right ||
                m_field[row][col] == Object::head_left || m_field[row][col] == Object::head_up || 
                m_field[row][col] == Object::head_down ||
                m_field[row][col] == Object::tail_h ||
                m_field[row][col] == Object::tail_v)
            {
                m_field[row][col] = Object::empty;
            }
        }
    }

    Object curr_facing;

    switch (p_player.get_facing())
    {
    case Facing::right:
    {
        curr_facing = Object::tail_h;
        break;
    }
    case Facing::left:
    {
        curr_facing = Object::tail_h;
        break;
    }
    case Facing::up:
    {
        curr_facing = Object::tail_v;
        break;
    }
    case Facing::down:
    {
        curr_facing = Object::tail_v;
        break;
    }
    default:
        break;
    }

     


    //player current path
    for (int i = 0; i < p_player.size(); ++i)
    {
        Point player_point = p_player.get(i);

        //m_field[player_point.y][player_point.x] = Object::player;
        m_field[player_point.y][player_point.x] = curr_facing;
    }

    Point player_point = p_player.get(0);
    

    switch (p_player.get_facing())
    {
    case Facing::right:
    {
        curr_facing = Object::head_right;
        break;
    }    
    case Facing::left:
    {
        curr_facing = Object::head_left;
        break;
    }    
    case Facing::up:
    {
        curr_facing = Object::head_up;
        break;
    }    
    case Facing::down:
    {
        curr_facing = Object::head_down;
        break;
    }
    default:
        break;
    }
    m_field[player_point.y][player_point.x] = curr_facing;

}