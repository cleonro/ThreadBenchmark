#include "controller.h"
#include "resource.h"

#include <chrono>
#include <thread>

Controller::Controller()
    : m_duration(0)
    , m_result(0.0)
{

}

void Controller::init(size_t resourceSize, size_t threadCount)
{
    m_resource.reset(new Resource(resourceSize));
    m_resource->generate();

    m_workers.clear();

    if(resourceSize == 0 || threadCount == 0)
    {
        return;
    }

    const size_t load = m_resource->size() / threadCount;
    size_t loadRemaining = m_resource->m_size % threadCount;
    m_workers.reserve(threadCount);
    size_t pos = 0;
    for(size_t count = 0; count < threadCount; ++count)
    {        
        size_t workerLoad = loadRemaining > 0 && loadRemaining-- ? load + 1 : load;
        m_workers.emplace_back(new Worker(m_resource, pos, pos + workerLoad));
        pos += workerLoad;
    }
}

void Controller::run()
{
    m_duration = 0;
    auto clockStart = std::chrono::high_resolution_clock::now();

    doWork();

    auto clockEnd = std::chrono::high_resolution_clock::now();
    auto clockDuration = std::chrono::duration_cast<std::chrono::microseconds>(clockEnd - clockStart);
    m_duration = clockDuration.count();
}

long Controller::duration() const
{
    return m_duration;
}

double Controller::result() const
{
    return m_result;
}

size_t Controller::resourceSize() const
{
    return (m_resource != nullptr ? m_resource->size() : 0);
}

size_t Controller::workersCount() const
{
    return m_workers.size();
}

void Controller::doWork()
{
    m_result = 0.0;
    if(m_resource == nullptr || m_resource->size() == 0 || m_workers.size() == 0)
    {
        return;
    }

    std::vector<std::thread> threads;
    threads.reserve(m_workers.size());

    for(auto &worker : m_workers)
    {
        threads.emplace_back(&Worker::run, worker.get());
    }
    for(std::thread &t : threads)
    {
        t.join();
    }

    for(auto &worker : m_workers)
    {
        m_result += worker->result();
    }
}
