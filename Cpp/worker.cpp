#include "worker.h"
#include "resource.h"

Worker::Worker(std::shared_ptr<Resource> resource, size_t start, size_t end)
    : m_resource(resource)
    , m_start(start)
    , m_end(end)
    , m_result(0.0)
{

}

double Worker::result() const
{
    return m_result;
}

void Worker::run()
{
    m_result = 0.0;
    for(size_t index = m_start; index < m_end; ++index)
    {
        m_result += m_resource->value(index);
    }
}
