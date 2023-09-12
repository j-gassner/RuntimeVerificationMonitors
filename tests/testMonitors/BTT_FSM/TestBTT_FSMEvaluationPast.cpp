#include "TestBTT_FSMEvaluationPast.h"
#include "BTT-FSM/BTT_FSMEvaluation.h"
#include "BTT-FSM/BTT_FSMCreation.h"
#include "Utils/Utils.h"
#include "Parser/Parser.h"
#include "Trace/Trace.h"

TEST(TestBTT_FSMPast, violatedEnd) {
Trace trace = Utils::createTrace({"green", "yellow", "red"}, {
        {"green"},
        {"red"},
        {"yellow"},
        {"green"},
        {"red"},
        {"green"}});
Formula formula = Parser::parse("G(green -> P(yellow))");
    auto btt = BTT_FSMCreation::formulaToBTT_FSM(formula, true);

EXPECT_FALSE(BTT_FSMEvaluation::evaluateBTT_FSM(btt, trace, true));
}

TEST(TestBTT_FSMPast, violatedBeginning) {
Trace trace = Utils::createTrace({"green", "yellow", "red"}, {
        {"red"},
        {"green"},
        {"red"},
        {"yellow"},
        {"red"},
        {"green"},
        {"yellow"}});
Formula formula = Parser::parse("G(green -> P(yellow))");
    auto btt = BTT_FSMCreation::formulaToBTT_FSM(formula, true);

EXPECT_FALSE(BTT_FSMEvaluation::evaluateBTT_FSM(btt, trace, true));
}

TEST(TestBTT_FSMPast, satisfied) {
Trace trace = Utils::createTrace({"green", "yellow", "red"}, {
        {"yellow"},
        {"green"},
        {"red"},
        {"yellow"},
        {"green"},
        {"red"},
        {"yellow"},
        {"green"}});
Formula formula = Parser::parse("G(green -> P(yellow))");
    auto btt = BTT_FSMCreation::formulaToBTT_FSM(formula, true);

EXPECT_TRUE(BTT_FSMEvaluation::evaluateBTT_FSM(btt, trace, true));
}