

#include <thread>
#include <chrono>
#include <functional>
#include <atomic>
#pragma once

// Function to mimic JavaScript's setInterval
void setInterval(std::function<void()> func, int interval_ms) {
    std::thread([func, interval_ms]() {
        while(true){
            std::this_thread::sleep_for(std::chrono::milliseconds(interval_ms));
            func();
        }

        
    }).detach();
}
#include <random>


// Function to generate a random integer in a given range [min, max]
int getRandomInt(int min, int max) {
    // Random number generator
    std::random_device rd;  // Seed generator
    std::mt19937 gen(rd()); // Mersenne Twister engine initialized with seed

    // Create a distribution in the range [min, max]
    std::uniform_int_distribution<> distr(min, max);

    // Return the generated random number
    return distr(gen);
}