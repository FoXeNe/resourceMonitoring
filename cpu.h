#ifndef RESOURCEMONITORING_PARSER_H
#define RESOURCEMONITORING_PARSER_H

#include <string>

class Cpu {
public:
    int readfile();

private:
    struct CpuTimes {
        long long user{}, nice{}, system{}, idle{}, iowait{}, irq{}, softirq{}, steal{};
        bool valid = false;
    };

    CpuTimes prev{};
    void parseline(std::string &line);
    void percent(const std::string &tag, const CpuTimes &cur);
};


#endif //RESOURCEMONITORING_PARSER_H