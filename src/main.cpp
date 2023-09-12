#include <iostream>
#include <fstream>
#include <chrono>
#include <memory>
#include <thread>
#include "Input/Algorithms.h"
#include "Input/CLIParser.h"
#include "MT-FSM/MT_FSMEvaluation.h"
#include "DynamicProgramming/Dynamic.h"
#include "BTT-FSM/BTT_FSMCreation.h"
#include "Rewriting/RewriteVisitor.h"
#include "MT-FSM/MT_FSMCreation.h"
#include "Utils/Timer.h"
#include "MT-FSM/MT_FSM.h"
#include "BTT-FSM/BTT_FSM.h"

#include "BTT-FSM/BTT_FSMEvaluation.h"
#include "Parser/Parser.h"
#include "Utils/Utils.h"
#include "EventConsuming/EventConsuming.h"
#include "env_model/auxiliaryDefs/structs.h"
#include "env_model/interfaces/commonroad/xml_reader.h"
#include "env_model/interfaces/standalone/command_line_input.h"
#include "env_model/roadNetwork/road_network.h"
#include "env_model/predicates/position_predicates.h"

/**
 * Lines for .csv.
 */
struct lineInfo {
    Algorithm algorithm;
    size_t vehicleA;
    size_t vehicleB;
    size_t traceLength;
    bool verdict;
    long creation;
    long evaluation;
    bool past;
    bool lazy;
    size_t run;
    size_t delay;
    std::map<std::string, size_t> predEvaluations;
    long traceCreation;

    /**
     * Header for a .csv.
     * @return
     */
    [[nodiscard]] std::string getHeader() const {
        std::stringstream header;
        header << "algorithm,ego,other,traceLength,verdict,creation,evaluation,past,lazy,run,delay,traceCreation,";
        header << Utils::iterableToString(predEvaluations,
                                          [](auto &pair) {
                                              return pair.first;
                                          }, {"", ""}, ",");
        return header.str();
    }

    friend std::ostream &operator<<(std::ostream &os, const lineInfo &info) {
        os << std::boolalpha
           << info.algorithm << ","
           << static_cast<char>(info.vehicleA - 1000 + 'A') << ","
           << static_cast<char>(info.vehicleB - 1000 + 'A') << ","
           << info.traceLength << ","
           << info.verdict << ","
           << info.creation << ","
           << info.evaluation << ","
           << info.past << ","
           << info.lazy << ","
           << info.run << ","
           << info.delay << ","
           << info.traceCreation << ","
           << Utils::iterableToString(info.predEvaluations,
                                      [](auto &pair) {
                                          return std::to_string(pair.second);
                                      }, {"", ""}, ",")
           << "\n";
        return os;
    }
};

std::vector<lineInfo> csv;

/**
 * Creates a (non-) lazy trace from given atomics and functions.
 * @param lazy True if trace should be lazy.
 * @param length Length of the trace.
 * @param atomicsAndFunctions Predicates mapped to their evaluation functions.
 * @return Trace.
 */
Trace createTrace(bool lazy, size_t length,
                  const std::map<std::string, std::function<bool(int)>> &atomicsAndFunctions) {
    if (lazy) {
        return Utils::createLazyTrace(atomicsAndFunctions, length);
    }

    // Else not lazy.
    std::vector<std::vector<std::string>> trueAtomics(length);

    // Evaluate all predicates at every event.
    for (size_t i = 0; i < length; ++i) {
        for (const auto &[atomic, function] : atomicsAndFunctions) {
            if (function(i)) {
                trueAtomics[i].push_back(atomic);
            }
        }
    }

    // Collect all predicate names.
    std::set<std::string> predicates;
    for (const auto &[atomic, _] : atomicsAndFunctions) {
        predicates.emplace(atomic);
    }

    auto trace = Utils::createTrace(predicates, trueAtomics);
    return trace;
}

std::unique_ptr<MT_FSM> mtFSM;
std::unique_ptr<BTT_FSM> bttFSM;

/**
 * Executes algorithm on a given trace and with given parameters.
 * @param formula Formula.
 * @param algorithm Monitoring algorithm.
 * @param trace Trace.
 * @param past True if formula is in PLTLf.
 * @param consoleOutput True if console output is desired.
 */
void
verify(const Formula &formula, const Algorithm algorithm,
       Trace trace, bool past, bool consoleOutput) {

    if (algorithm > btt_fsm) {
        throw std::runtime_error(
                "main::verify() No valid argument for algorithm given. Try MT_FSM, BTT_FSM, DYNAMIC, or EVENTCONSUMING.)");
    }
    auto predicates = Utils::getAtomics(formula);

    Timer creationTimer, evaluationTimer;

    bool verdict = false;

    constexpr size_t textwidth = 15;
    if (consoleOutput) {
        std::cout << std::setw(textwidth) << std::left << "Algorithm" << ": " << algorithm << std::endl;
    }

    switch (algorithm) {
        case mt_fsm: {
            if (not mtFSM) {
                creationTimer.start();
                // Avoid creating the MT-FSM multiple times
                mtFSM = std::make_unique<MT_FSM>(MT_FSMCreation::formulaToMT_FSM(formula, past));
                creationTimer.stop();
            }

            evaluationTimer.start();
            verdict = MT_FSMEvaluation::evaluateMT_FSM(*mtFSM, trace, past);
            evaluationTimer.stop();
            break;
        }
        case btt_fsm: {
            if (not bttFSM) {
                creationTimer.start();
                // Avoid creating the BTT-FSM multiple times
                bttFSM = std::make_unique<BTT_FSM>(BTT_FSMCreation::formulaToBTT_FSM(formula, past));
                creationTimer.stop();
            }

            evaluationTimer.start();
            verdict = BTT_FSMEvaluation::evaluateBTT_FSM(*bttFSM, trace, past);
            evaluationTimer.stop();
            break;
        }
        case dynamic: {
            evaluationTimer.start();
            verdict = Dynamic::dynamic(formula, trace, past);
            evaluationTimer.stop();
            break;
        }
        case eventconsuming: {
            evaluationTimer.start();
            verdict = EventConsuming::eventConsuming(formula, trace, past);
            evaluationTimer.stop();
            break;
        }
    }

    csv.back().traceLength = trace.getLength();
    csv.back().verdict = verdict;
    csv.back().creation = creationTimer.getTotalTime();
    csv.back().evaluation = evaluationTimer.getTotalTime();
    if (consoleOutput) {
        std::cout << std::setw(textwidth) << std::left << "Trace length" << ": " << trace.getLength() << std::endl;
        std::cout << std::setw(textwidth) << std::left << "Verdict" << ": " << std::boolalpha << verdict << std::endl;
        std::cout << std::setw(textwidth) << std::left << "Creation took" << ": " << creationTimer.getTotalTime() / 1e6l
                  << " ms" << std::endl;
        std::cout << std::setw(textwidth) << std::left << "Evaluation took" << ": "
                  << evaluationTimer.getTotalTime() / 1e6l
                  << " ms"
                  << std::endl;
    }
}

/**
 * Loads and sets up CR scenario.
 * @param argc
 * @param argv
 * @return Tuple of obstacles and roadNetwork.
 */
auto getDataFromCommonRoad(int argc, char **argv) {
    int num_threads;
    std::string xmlFilePath;
    int error_code = CommandLine::readCommandLineValues(argc, argv, num_threads, xmlFilePath);
    if (error_code != 0) {
        throw std::runtime_error(
                "CommonRoad stuff crashed at reading cli values error code: " + std::to_string(error_code));
    }

    // Read and parse CommonRoad scenario file
    std::vector<std::shared_ptr<TrafficSign>> trafficSigns = XMLReader::createTrafficSignFromXML(xmlFilePath);
    std::vector<std::shared_ptr<TrafficLight>> trafficLights = XMLReader::createTrafficLightFromXML(xmlFilePath);
    std::vector<std::shared_ptr<Lanelet>> lanelets = XMLReader::createLaneletFromXML(xmlFilePath, trafficSigns,
                                                                                     trafficLights);
    std::vector<std::shared_ptr<Obstacle>> obstacles = XMLReader::createObstacleFromXML(xmlFilePath);
    std::vector<std::shared_ptr<Intersection>> intersections = XMLReader::createIntersectionFromXML(xmlFilePath,
                                                                                                    lanelets);

    std::shared_ptr<RoadNetwork> roadNetwork{std::make_shared<RoadNetwork>(RoadNetwork(lanelets))};


    for (const auto &obs : obstacles) {
        for (size_t i = 0; i < obs->getTrajectoryLength(); ++i) {
            obs->setLane(roadNetwork->getLanes(), i);
        }
    }

    return std::make_tuple(obstacles, roadNetwork);
}

/**
 * Test algorithms with different configurations.
 * @param formula Formula.
 * @param past True if formula is in PLTLf.
 * @param runs Number of desired runs.
 * @param delays Desired delays that are added to evaluation functions.
 * @param lazyModes Lazy, non-lazy, or both.
 * @param algorithms Algorithms to be tested.
 * @param rebuildFSMsEveryRun True if MT-FSM* or BTT-FSM* should be rebuilt in every run.
 * @param consoleOutput True if console output is desired.
 * @param roadNetwork RoadNetwork.
 * @param obstacles Obstacles.
 */
void testRunner(const Formula &formula,
                bool past,
                size_t runs,
                const std::vector<size_t> &delays,
                const std::vector<bool> &lazyModes,
                const std::vector<Algorithm> &algorithms,
                bool rebuildFSMsEveryRun,
                bool consoleOutput,
                const std::shared_ptr<RoadNetwork> &roadNetwork,
                const std::vector<std::shared_ptr<Obstacle>> &obstacles) {

    csv.reserve(obstacles.size() * obstacles.size() * algorithms.size() * lazyModes.size() * delays.size() * runs);

    if (consoleOutput) {
        std::cout << "Formula        : " << formula << std::endl;
    }

    for (size_t run = 0; run < runs; ++run) {

        // Always print this as a progress counter.
        std::cout << "Run " << run << std::endl;
        if (rebuildFSMsEveryRun) {
            mtFSM = nullptr;
            bttFSM = nullptr;
        }

        for (const size_t sleeptime : delays) {
            for (const auto &lazy : lazyModes) {
                for (const auto &algorithm : algorithms) {

                    PositionPredicates posPred{PositionPredicates(roadNetwork)};
                    for (const auto &ego : obstacles) {
                        for (const auto &other : obstacles) {
                            if (ego->getId() == other->getId()) {
                                continue;
                            }
                            auto egoCopy = std::make_shared<Obstacle>(**std::find_if(
                                    obstacles.begin(),
                                    obstacles.end(),
                                    [&](const auto &o) {
                                        return o->getId() == ego->getId();
                                    }));

                            auto otherCopy = std::make_shared<Obstacle>(**std::find_if(
                                    obstacles.begin(),
                                    obstacles.end(),
                                    [&](const auto &o) {
                                        return o->getId() == other->getId();
                                    }));


                            csv.emplace_back(lineInfo());
                            if (consoleOutput) {
                                std::cout << "Vehicle pair   : " << ego->getId() << ", " << other->getId() << std::endl;
                            }
                            csv.back().vehicleA = ego->getId();
                            csv.back().vehicleB = other->getId();
                            csv.back().algorithm = algorithm;
                            csv.back().past = past;
                            csv.back().lazy = lazy;
                            csv.back().run = run;
                            csv.back().delay = sleeptime;

                            std::map<std::string, std::map<size_t, size_t>> lazyEvaluationTracker;
                            lazyEvaluationTracker["onmaincarriageway_ego"] = {};
                            lazyEvaluationTracker["onmaincarriageway_other"] = {};
                            lazyEvaluationTracker["infrontof"] = {};
                            lazyEvaluationTracker["onaccessramp"] = {};
                            lazyEvaluationTracker["onmaincarriagewayrightlane"] = {};

                            std::map<std::string, std::function<bool(int)>> atomicsAndFunctions;
                            atomicsAndFunctions.emplace("onmaincarriageway_ego",
                                                        [&](int i) {
                                                            ++lazyEvaluationTracker["onmaincarriageway_ego"][i];
                                                            std::this_thread::sleep_for(
                                                                    std::chrono::microseconds(sleeptime));
                                                            return posPred.onMainCarriageWay(i, egoCopy);
                                                        });
                            atomicsAndFunctions.emplace("onmaincarriageway_other",
                                                        [&](int i) {
                                                            ++lazyEvaluationTracker["onmaincarriageway_other"][i];
                                                            std::this_thread::sleep_for(
                                                                    std::chrono::microseconds(sleeptime));
                                                            return posPred.onMainCarriageWay(i, egoCopy);
                                                        });
                            atomicsAndFunctions.emplace("infrontof",
                                                        [&](int i) {
                                                            ++lazyEvaluationTracker["infrontof"][i];
                                                            std::this_thread::sleep_for(
                                                                    std::chrono::microseconds(sleeptime));
                                                            return PositionPredicates::inFrontOf(i, egoCopy, otherCopy);
                                                        });
                            atomicsAndFunctions.emplace("onaccessramp",
                                                        [&](int i) {
                                                            ++lazyEvaluationTracker["onaccessramp"][i];
                                                            std::this_thread::sleep_for(
                                                                    std::chrono::microseconds(sleeptime));
                                                            return posPred.onAccessRamp(i, otherCopy);
                                                        });
                            atomicsAndFunctions.emplace("onmaincarriagewayrightlane",
                                                        [&](int i) {
                                                            ++lazyEvaluationTracker["onmaincarriagewayrightlane"][i];
                                                            std::this_thread::sleep_for(
                                                                    std::chrono::microseconds(sleeptime));
                                                            return posPred.onMainCarriageWayRightLane(i, egoCopy);
                                                        });

                            Timer traceTimer;
                            traceTimer.start();

                            auto trace = createTrace(lazy, egoCopy->getTrajectoryLength(), atomicsAndFunctions);
                            traceTimer.stop();

                            if (consoleOutput) {
                                std::cout << "Lazy           : " << std::boolalpha << lazy << std::endl;
                                std::cout << "Delay          : " << sleeptime / 1e3l << " ms" << std::endl;
                                std::cout << "Trace creation : " << traceTimer.getTotalTime() / 1e6l << " ms"
                                          << std::endl;
                            }
                            csv.back().traceCreation = traceTimer.getTotalTime();
                            verify(formula, algorithm, trace, past, consoleOutput);

                            // Sum up the number of function calls per atomic
                            std::map<std::string, size_t> totalCalls;
                            for (const auto &[atomic, mapICalls]: lazyEvaluationTracker) {
                                totalCalls[atomic] = std::accumulate(mapICalls.begin(),
                                                                     mapICalls.end(),
                                                                     0,
                                                                     [](auto &acc,
                                                                        auto &pair) {
                                                                         return acc + pair.second;
                                                                     });
                            }
                            csv.back().predEvaluations = totalCalls;
                            if (consoleOutput) {
                                std::cout << Utils::iterableToString(totalCalls,
                                                                     [](auto &pair) {
                                                                         return pair.first + ": " +
                                                                                std::to_string(pair.second);
                                                                     }, {"", ""}) << std::endl << std::endl;
                            }
                        }
                    }
                }
            }
        }
    }
}

int main(int argc, char **argv) {
    if(CLIParser::sendHelp(argc, argv)){
        return 0;
    }
    //Read command line parameters; if none are provided, use default values (specified in read_command_line_values and Settings.h)
    const auto &[obstacles, roadNetwork] = getDataFromCommonRoad(3, argv);


    auto settings = CLIParser::parseCLI(argc, argv);
    // Initialize output file.
    std::stringstream outputFileName;
    outputFileName << settings.outputFile;
    std::ofstream outputFile(outputFileName.str());


    // Define the test
    Formula formula = Parser::parse("G((onmaincarriageway_ego & infrontof & "
                                    "onaccessramp & F(onmaincarriageway_other)) -> "
                                    "(!(!(onmaincarriagewayrightlane) "
                                    "& F(onmaincarriagewayrightlane))))");
    testRunner(formula,
               settings.past,
               settings.runs,
               settings.delays,
               settings.lazyModes,
               settings.algorithms,
               settings.rebuildFSMsEveryRun,
               settings.consoleOutput,
               roadNetwork,
               obstacles);


    // Print the output file.
    outputFile << csv.front().getHeader() << "\n";
    outputFile << Utils::iterableToString(csv,
                                          [](const auto &x) {
                                              return x;
                                          }, {"", ""}, "") << std::endl;
    outputFile.close();

}
