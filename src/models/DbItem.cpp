#include "DbItem.h"

DbItem::DbItem() :
    m_id(0), m_age(0), m_name{std::string()}, m_weight(0)
{}

DbItem::~DbItem() = default;

int DbItem::id() const
{
    return this->m_id;
}

void DbItem::setId(int id)
{
    if (id >= 0)
        this->m_id = id;
    else
        id = 0;
}

int DbItem::age() const
{
    return this->m_age;
}

void DbItem::setAge(int age)
{
    if (age >= 0)
        this->m_age = age;
    else
        age = 0;
}

std::string DbItem::name() const
{
    return this->m_name;
}

void DbItem::setName(std::string_view name)
{
    if (!name.empty())
        this->m_name = name;
    else
        this->m_name = std::string();
}

double DbItem::weight() const
{
    return this->m_weight;
}

void DbItem::setWeight(double weight)
{
    if (weight >= 0)
        this->m_weight = weight;
    else
        this->m_weight = 0;
}
