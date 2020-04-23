#pragma once

#include <string>

class StatisticLogger {
public:
    StatisticLogger(const StatisticLogger&) = delete;
    StatisticLogger& operator=(const StatisticLogger&) = delete;
    StatisticLogger(StatisticLogger&&) = delete;
    StatisticLogger& operator=(StatisticLogger&&) = delete;

    void init();
    void finish();
    void log();
    void dump();

    static StatisticLogger& getInstance() {
        static StatisticLogger slInst;
        return slInst;
    }
private:
    StatisticLogger() = default;
    ~StatisticLogger() = default;

    void dumpStr(std::string);
    std::string textDump();

private:
    unsigned int count = 0;

    unsigned int intervalSec = 30;
};