#pragma once

#include <ostream>

enum Algorithm {
    dynamic,
    eventconsuming,
    mt_fsm,
    btt_fsm,
};

/**
 * Easier output for algorithms.
 * @param os
 * @param algorithm
 * @return osstream for algorithm.
 */
std::ostream &operator<<(std::ostream &os, const Algorithm &algorithm) {
    switch (algorithm) {
        case dynamic:
            os << "DynamicProgramming";
            break;
        case eventconsuming:
            os << "EventConsuming";
            break;
        case mt_fsm:
            os << "MT-FSM*";
            break;
        case btt_fsm:
            os << "BTT-FSM*";
            break;
    }
    return os;
}

/**
 * Converts a string into the corresponding algorithm.
 * @param algorithmString
 * @return
 */
Algorithm stringToAlgorithm(const std::string &algorithmString){
    if(algorithmString == "dynamicprogramming"){
        return dynamic;
    }
    else if(algorithmString == "eventconsuming"){
        return eventconsuming;
    }
    else if(algorithmString == "mt-fsm*"){
        return mt_fsm;
    }
    else if(algorithmString == "btt-fsm*"){
        return btt_fsm;
    }
    else{
        throw std::runtime_error("Algorithm::stringToAlgorithm Command line argument " + algorithmString + " is not a valid algorithm.\n"
                                                                                                           "Options are: dynamicprogramming, eventconsuming, mt-fsm*, btt-fsm*");
    }
}