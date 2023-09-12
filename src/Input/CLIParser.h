#pragma once

#include "Settings.h"
#include <getopt.h>
#include <algorithm>
#include <cstring>

namespace CLIParser {
    /**
     * Prints help function to console.
     */
    void printHelp() {
        std::cout << "--help             Help.\n"
                     "--input-file       Path to input file.\n"
                     "--algorithms       dynamicprogramming, eventconsuming, mt-fsm*, btt-fsm*. You can pass more than one algorithm.\n"
                     "--past             true if formula is in PLTLf, false otherwise.\n"
                     "--runs             Number of runs for each algorithm.\n"
                     "--delays           Delay in microseconds in predicate evaluation functions. You can pass more than one delay.\n"
                     "--lazyModes        true for lazy evaluation, false for non-lazy, or both.\n"
                     "--rebuildFSMs      true if MT-FSM* and BTT-FSM* should be built again in each run.\n"
                     "--consoleOutput    true if output is desired for each run.\n"
                     "--outputFile       Name of the output file."
                  << std::endl;
    }

    /**
     * Checks if --help was passed.
     * @param argc
     * @param argv
     * @return
     */
    bool sendHelp(int argc, char **argv) {
        for (size_t i = 1; i < argc; ++i) {
            if (strcmp(argv[i], "--help") == 0) {
                printHelp();
                return true;
            }
        }
        return false;
    }

    /**
     * Splits a string into a vector of single words separated by ,; or space.
     * @param str
     * @return
     */
    std::vector<std::string> splitString(const std::string &str) {
        std::vector<std::string> ret;
        size_t begin = 0;
        size_t end = 0;
        while ((end = str.find_first_of(" ,;", begin)) != std::string::npos) {
            if (end > begin) {
                ret.push_back(str.substr(begin, end - begin));
            }
            begin = end + 1;
        }
        if (begin < str.length()) {
            ret.push_back(str.substr(begin, str.length() - begin));
        }
        return ret;
    }

    /**
     * Parses and allocates command line arguments.
     * @param argc
     * @param argv
     * @return
     */
    Settings parseCLI(int argc, char **argv) {
        Settings settings;
        const std::vector<struct option> options{
                {"help",          no_argument,       nullptr, 'h'},
                {"input-file",    required_argument, nullptr, 'i'},
                {"algorithms",    required_argument, nullptr, 'a'},
                {"past",          required_argument, nullptr, 'p'},
                {"runs",          required_argument, nullptr, 'r'},
                {"delays",        required_argument, nullptr, 'd'},
                {"lazyModes",     required_argument, nullptr, 'l'},
                {"rebuildFSMs",   required_argument, nullptr, 'b'},
                {"consoleOutput", required_argument, nullptr, 'c'},
                {"outputFile",    required_argument, nullptr, 'o'},
                {nullptr,         no_argument,       nullptr, 0}
        };
        for (int option = 0; (option = getopt_long(argc, argv, "", options.data(), nullptr)) != -1;) {
            std::string optargString;
            if (optarg) {
                optargString = optarg;
                std::transform(optargString.begin(), optargString.end(), optargString.begin(), tolower);
            }

            switch (option) {
                case 'h': {
                    printHelp();
                    break;
                }
                    // The other parser takes care of it
                case 'i': {
                    break;
                }
                case 'a': {
                    auto split = splitString(optargString);
                    settings.algorithms.clear();
                    std::transform(split.begin(), split.end(), std::back_inserter(settings.algorithms),
                                   stringToAlgorithm);
                    break;
                }
                case 'd': {
                    auto split = splitString(optargString);
                    settings.delays.clear();
                    std::transform(split.begin(), split.end(), std::back_inserter(settings.delays),
                                   [](const std::string &delayStr) { return std::stoul(delayStr); });
                    break;
                }
                case 'r': {
                    settings.runs = std::stoul(optargString);
                    break;
                }
                case 'p': {
                    if (optargString == "true") {
                        settings.past = true;
                    }
                    else if (optargString == "false") {
                        settings.past = false;
                    }
                    else {
                        throw std::runtime_error("CLIParser::parseCLI No valid option for past. Try true or false.");
                    }
                    break;
                }

                case 'b': {
                    if (optargString == "true") {
                        settings.rebuildFSMsEveryRun = true;
                    }
                    else if (optargString == "false") {
                        settings.rebuildFSMsEveryRun = false;
                    }
                    else {
                        throw std::runtime_error("CLIParser::parseCLI No valid option for rebuild. Try true or false.");
                    }
                    break;
                }

                case 'c': {
                    if (optargString == "true") {
                        settings.consoleOutput = true;
                    }
                    else if (optargString == "false") {
                        settings.consoleOutput = false;
                    }
                    else {
                        throw std::runtime_error(
                                "CLIParser::parseCLI No valid option for console output. Try true or false.");
                    }
                    break;
                }
                case 'o': {
                    settings.outputFile = optargString;
                    break;
                }
                case 'l': {
                    auto split = splitString(optargString);
                    settings.lazyModes.clear();
                    std::transform(split.begin(), split.end(), std::back_inserter(settings.lazyModes),
                                   [](const std::string &lazyStr) { return (lazyStr == "true"); });
                    break;

                }
                default:
                    throw std::runtime_error("CLIParser::parseCLI() Not a valid argument. Use --help for help.");

            }
        }
        return settings;
    }


}