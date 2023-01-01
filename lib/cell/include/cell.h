#ifndef LIFE_CELL_H
#define LIFE_CELL_H

#include <iostream>

struct Cell
{
    int m_x = 0;
    int m_y = 0;
    int m_neighbours = 0;

    template<typename CharT, typename Traits>
    friend std::basic_ostream<CharT, Traits> & operator<<(std::basic_ostream<CharT, Traits> & os,
                                                          const Cell cell);
    template<typename CharT, typename Traits>
    friend std::basic_istream<CharT, Traits> & operator>>(std::basic_istream<CharT, Traits> & is,
                                                          Cell & cell);
};

template<typename CharT, typename Traits>
std::basic_ostream<CharT, Traits> & operator<<(std::basic_ostream<CharT, Traits> & os,
                                               const Cell cell)
{
    os << cell.m_x << " " << cell.m_y;
    return os;
}

template<typename CharT, typename Traits>
std::basic_istream<CharT, Traits> & operator>>(std::basic_istream<CharT, Traits> & is,
                                               Cell & cell)
{
    is >> cell.m_x;
    is >> cell.m_y;
    return is;
}

#endif // LIFE_CELL_H
