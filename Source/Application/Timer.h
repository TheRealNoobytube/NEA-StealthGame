#pragma once
#include <chrono>


class Timer {
public:
    void start();
    void stop();
    void pause();

    float getTime_Nano();
    float getTime_Micro();
    float getTime_Milli();
    float getTime_Seconds();

private:
    std::chrono::time_point<std::chrono::steady_clock> startTime;
    std::chrono::time_point<std::chrono::steady_clock> endTime;
    bool running = false;
    bool paused = false;
};

