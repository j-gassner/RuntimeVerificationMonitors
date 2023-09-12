#include <stdexcept>
#include "Timer.h"

using namespace std::chrono;

Timer::Timer() : startTime{} {}

Timer::~Timer() = default;

void Timer::start() {
    if (currentlyRunning) {
        throw std::runtime_error("Timer::start() Timer is already running.");
    }
    currentlyRunning = true;
    startTime = high_resolution_clock::now();
}

long Timer::stop() {
    const auto time(high_resolution_clock::now());

    if (not currentlyRunning) {
        throw std::runtime_error("Timer::stop() Timer did not even start.");
    }
    currentlyRunning = false;

    const auto diff = duration_cast<nanoseconds>(time - startTime).count();

    totalTime += diff;

    return diff;
}

void Timer::addTime(long nanoseconds) {
    totalTime += nanoseconds; }