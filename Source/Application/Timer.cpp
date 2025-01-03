#include "Timer.h"

void Timer::start() {
    if (!paused) {
        startTime = std::chrono::steady_clock::now();
    }
    running = true;
    paused = false;
}

void Timer::stop() {
    endTime = std::chrono::steady_clock::now();
    running = false;
}

void Timer::pause() {
    paused = true;
    stop();
}

float Timer::getTime_Nano() {
    std::chrono::time_point<std::chrono::steady_clock> currentTime;

    
    if (running) {//if the timer isn't stopped, get the current time
        currentTime = std::chrono::steady_clock::now();
    }
    else {//otherwise the current time is the time right before the timer stopped
        currentTime = endTime;
    }

    //return the difference from the time started to the current time
    return std::chrono::duration_cast<std::chrono::nanoseconds>(currentTime - startTime).count();
}

float Timer::getTime_Micro() {
    return getTime_Nano() / 1000.0;
}

float Timer::getTime_Milli() {
    return getTime_Nano() / 1000000.0;
}

float Timer::getTime_Seconds() {
    return getTime_Nano() / 1000000000.0;
}

bool Timer::isRunning() {
    return running;
}
bool Timer::isPaused() {
    return paused;
}
bool Timer::isStopped() {
    return !isRunning() && !isPaused();
}