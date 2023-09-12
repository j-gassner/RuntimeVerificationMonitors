#pragma once
#include <chrono>
/**
 * Taken from https://github.com/AutoPas/AutoPas/blob/ecbf799e8c1f828eb51e3507b76275afe98a8cb2/src/autopas/utils/Timer.h
 */
class Timer {
public:
    Timer();

    virtual ~Timer();

    /**
     * Start the timer.
     */
    void start();

    /**
     * Stops the timer and returns the time elapsed in nanoseconds since the last call to start.
     * It also adds the duration to the total time.
     * @return elapsed time in nanoseconds
     */
    long stop();

    /**
     * Adds the given amount of nanoseconds to the total time.
     * @param nanoseconds
     */
    void addTime(long nanoseconds);

    /**
     * Get total accumulated time.
     * @return Total time in nano seconds.
     */
    [[nodiscard]] long getTotalTime() const { return totalTime; }

private:
    /**
     * Time point of last call of start().
     */
    std::chrono::high_resolution_clock::time_point startTime;

    /**
     * Accumulated total time.
     */
    long totalTime = 0;

    /**
     * Indicator if this timer currently is measuring.
     */
    bool currentlyRunning = false;
};





