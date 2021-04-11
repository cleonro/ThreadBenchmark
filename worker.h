#ifndef WORKER_H
#define WORKER_H

#include <memory>

class Resource;

class Worker
{
public:
    Worker(std::shared_ptr<Resource> resource, size_t start, size_t end);

    double result() const;

    void run();

private:
    std::shared_ptr<Resource> m_resource;
    const size_t m_start;
    const size_t m_end;
    double m_result;
};

#endif // WORKER_H
