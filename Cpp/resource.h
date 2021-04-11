#ifndef RESOURCE_H
#define RESOURCE_H

#include <vector>

class Resource
{
    friend class Controller;
public:
    double value(size_t index) const;

private:
    Resource(size_t size);
    size_t size() const;
    void generate();

private:
    size_t m_size;
    std::vector<double> m_v;

};

#endif // RESOURCE_H
