#include "resource.h"

#include <cmath>
//#include <random>
#include <algorithm>

Resource::Resource(size_t size)
    : m_size(size)
{
    m_v.resize(m_size);
}

void Resource::generate()
{
//    std::random_device rnd;
//    std::default_random_engine rne(rnd());
//    std::uniform_real_distribution und(0.0, 1.0);

    std::for_each(m_v.begin(), m_v.end(), [/*&rne, &und*/](double &x){
        x = 0.01;//und(rne);
    });
}

size_t Resource::size() const
{
    return m_size;
}

double Resource::value(size_t index) const
{
    return (index < m_size ? m_v[index] : 0.0);
}
