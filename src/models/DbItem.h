#ifndef STL_DBITEM_H
#define STL_DBITEM_H

#include <string>

class DbItem
{
public:
    DbItem();
    ~DbItem();
    [[nodiscard]] int id() const;
    void setId(int id);
    [[nodiscard]] int age() const;
    void setAge(int age);
    [[nodiscard]] std::string name() const;
    void setName(std::string_view name);
    [[nodiscard]] double weight() const;
    void setWeight(double weight);

private:
    int m_id;
    int m_age;
    std::string m_name;
    double m_weight;
};


#endif //STL_DBITEM_H
