#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <vector>
#include <memory>

#include "worker.h"

class Resource;

class Controller
{
public:
    Controller();

    void init(size_t resourceSize, size_t threadCount);
    void run();

    long duration() const;
    double result() const;
    size_t resourceSize() const;
    size_t workersCount() const;

private:
    void doWork();

private:
    std::shared_ptr<Resource> m_resource;
    std::vector<std::unique_ptr<Worker>> m_workers;
    long m_duration;
    double m_result;
};

#endif // CONTROLLER_H
