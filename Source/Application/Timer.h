#pragma once
#include <chrono>

using TimePoint = std::chrono::time_point<std::chrono::steady_clock>;

class Timer {
public:
    void start();
    void stop();
    void pause();

    float getTime_Nano();
    float getTime_Micro();
    float getTime_Milli();
    float getTime_Seconds();

    bool isRunning();
    bool isPaused();
    bool isStopped();

    

private:
    
    TimePoint startTime;
    TimePoint endTime;
    bool running = false;
    bool paused = false;
};

