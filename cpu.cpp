#include "cpu.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <thread>
#include <chrono>

int Cpu::readfile() {
    {
        std::ifstream file("/proc/stat");
        std::string line;

        if (!std::getline(file, line)) {
            return 1;
        }
        parseline(line);
    }

    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    {
        std::ifstream file("/proc/stat");
        std::string line;
        if (!std::getline(file, line)) {
            return 1;
        }
        parseline(line);
    }
}


void Cpu::parseline(std::string &line) {
    std::istringstream iss(line);
    std::string tag;
    CpuTimes cur;


    iss >> tag
         >> cur.user >> cur.nice >> cur.system >> cur.idle
         >> cur.iowait >> cur.irq >> cur.softirq >> cur.steal;

    percent(tag, cur);
}

void Cpu::percent(const std::string &tag, const CpuTimes &cur) {
    if (tag != "cpu") {
        return;
    }

    if (!prev.valid) {
        prev = cur;
        prev.valid = true;
        return;
    }

    long long idle_prev = prev.idle + prev.iowait;
    long long idle_cur  = cur.idle  + cur.iowait;

    long long total_prev = prev.user + prev.nice + prev.system + prev.idle +
                           prev.iowait + prev.irq + prev.softirq + prev.steal;
    long long total_cur  = cur.user + cur.nice + cur.system + cur.idle +
                           cur.iowait + cur.irq + cur.softirq + cur.steal;

    long long delta_idle  = idle_cur  - idle_prev;
    long long delta_total = total_cur - total_prev;

    double usage = 0.0;
    if (delta_total > 0) {
        usage = 100.0 * (delta_total - delta_idle) / delta_total;
    }

    std::cout << usage << std::endl;

    prev = cur;
    prev.valid = true;
}