#include "TestBTT_FSMEvaluationFuture.h"
#include "BTT-FSM/BTT_FSMCreation.h"
#include "BTT-FSM/BTT_FSMEvaluation.h"
#include "Utils/Utils.h"
#include "Parser/Parser.h"
#include "Trace/Trace.h"

TEST(TestBTT_FSMEvaluation, violated1) {
    Trace trace = Utils::createTrace({"a", "b", "c", "g", "f"}, {
            {"a"},
            {"b"},
            {"a"},
            {"b"},
            {"a"},
            {"c"},
            {"a"},
            {"a"},
            {"b"},
            {"g"},
            {"f"},
            {"h"},
            {"c"},
            {"b"},
            {"a"}});
    Formula formula = Parser::parse("G(a -> F(b))");
    auto btt = BTT_FSMCreation::formulaToBTT_FSM(formula, false);
    EXPECT_FALSE(BTT_FSMEvaluation::evaluateBTT_FSM(btt, trace, false));
}

TEST(TestBTT_FSMEvaluation, satisfied1) {
    Trace trace = Utils::createTrace({"a", "b", "c", "g", "f"}, {
            {"a"},
            {"b"},
            {"a"},
            {"b"},
            {"a"},
            {"c"},
            {"a"},
            {"a"},
            {"b"},
            {"g"},
            {"f"},
            {"h"},
            {"c"},
            {"b"},
            {"a"}});
    Formula formula = Parser::parse("F(!G(b -> Fc))");
    auto btt = BTT_FSMCreation::formulaToBTT_FSM(formula, false);

    EXPECT_TRUE(BTT_FSMEvaluation::evaluateBTT_FSM(btt, trace, false));
}

TEST(TestBTT_FSMEvaluation, satisfied2) {
    Formula formula = Parser::parse("G(b -> Fc)");
    Trace trace = Utils::createTrace({"a", "b", "c", "g", "f", "h"}, {
            {"a"},
            {"b"},
            {"a"},
            {"b"},
            {"a"},
            {"c"},
            {"a"},
            {"a"},
            {"b"},
            {"g"},
            {"f"},
            {"h"},
            {"c"},
            {"b"},
            {"c"}});

    auto btt = BTT_FSMCreation::formulaToBTT_FSM(formula, false);
    EXPECT_TRUE(BTT_FSMEvaluation::evaluateBTT_FSM(btt, trace, false));
}

TEST(TestBTT_FSMEvaluation, violated2) {
    Trace trace = Utils::createTrace({"a", "b", "c", "g", "f", "h"}, {
            {"a"},
            {"b"},
            {"a"},
            {"b"},
            {"a"},
            {"c"},
            {"a"},
            {"a"},
            {"b"},
            {"g"},
            {"f"},
            {"h"},
            {"c"},
            {"b"},
            {"c"}});
    Formula formula = Parser::parse("F(!G(b -> Fc))");
    auto btt = BTT_FSMCreation::formulaToBTT_FSM(formula, false);

    EXPECT_FALSE(BTT_FSMEvaluation::evaluateBTT_FSM(btt, trace, false));
}

TEST(TestBTT_FSMEvaluation, satisfied3) {
    Trace trace = Utils::createTrace({"a", "b", "c", "d", "e"}, {
            {"a"},
            {"b"},
            {"a"},
            {"b"},
            {"a"},
            {"c"},
            {"a"},
            {"a"},
            {"b"},
            {"e"},
            {"d"},
            {"e"},
            {"c"},
            {"b"},
            {"c"}});
    Formula formula = Parser::parse("G((a & b & c & F(d)) -> (!(!(e) & F(e))))");
    auto btt = BTT_FSMCreation::formulaToBTT_FSM(formula, false);

    EXPECT_TRUE(BTT_FSMEvaluation::evaluateBTT_FSM(btt, trace, false));
}

TEST(TestBTT_FSMEvaluation, violatedEnd) {
    Trace trace = Utils::createTrace({"green", "yellow", "red"}, {
            {"green"},
            {"red"},
            {"yellow"},
            {"red"},
            {"green"},
            {"yellow"},
            {"green"},
            {"red"}});
    Formula formula = Parser::parse("G(green -> !red U yellow)");
    auto btt = BTT_FSMCreation::formulaToBTT_FSM(formula, false);

    EXPECT_FALSE(BTT_FSMEvaluation::evaluateBTT_FSM(btt, trace, false));
}

TEST(TestBTT_FSMEvaluation, violatedBeginning) {
    Trace trace = Utils::createTrace({"green", "yellow", "red"}, {
            {"green"},
            {"red"},
            {"yellow"},
            {"red"},
            {"yellow"},
            {"red"},
            {"green"},
            {"yellow"}});
    Formula formula = Parser::parse("G(green -> !red U yellow)");
    auto btt = BTT_FSMCreation::formulaToBTT_FSM(formula, false);

    EXPECT_FALSE(BTT_FSMEvaluation::evaluateBTT_FSM(btt, trace, false));
}

TEST(TestBTT_FSMEvaluation, satisfied) {
    Trace trace = Utils::createTrace({"green", "yellow", "red"}, {
            {"green"},
            {"yellow"},
            {"red"},
            {"green"},
            {"yellow"},
            {"red"},
            {"red"}});
    Formula formula = Parser::parse("G(green -> !red U yellow)");
    auto btt = BTT_FSMCreation::formulaToBTT_FSM(formula, false);

    EXPECT_TRUE(BTT_FSMEvaluation::evaluateBTT_FSM(btt, trace, false));
}

