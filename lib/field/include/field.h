#ifndef LIFE_FIELD_H
#define LIFE_FIELD_H

#include <stdexcept>
#include <vector>

class Field
{
public:
    Field() = default;
    Field(int width, int height);
    std::vector<bool> & operator[](int index);

private:
    std::vector<std::vector<bool>> m_field;
};

// Errors

class FieldError : public std::runtime_error
{
public:
    FieldError();
};

#endif //LIFE_FIELD_H
