#include "Parser/Parser.h"
#include "Trace/Trace.h"
#include "Utils/Utils.h"
#include "DynamicProgramming/DynamicPast.h"
#include "TestDynamicPast.h"

TEST(TestDynamicPast, violatedEnd) {
    Trace trace = Utils::createTrace({"green", "yellow", "red"}, {
            {"green"},
            {"red"},
            {"yellow"},
            {"green"},
            {"red"},
            {"green"}});
    Formula formula = Parser::parse("G(green -> P(yellow))");
    EXPECT_FALSE(DynamicPast::checkTraceDynamically(formula, trace));
}

TEST(TestDynamicPast, violatedBeginning) {
    Trace trace = Utils::createTrace({"green", "yellow", "red"}, {
            {"red"},
            {"green"},
            {"red"},
            {"yellow"},
            {"red"},
            {"green"},
            {"yellow"}});
    Formula formula = Parser::parse("G(green -> P(yellow))");
    EXPECT_FALSE(DynamicPast::checkTraceDynamically(formula, trace));
}

TEST(TestDynamicPast, satisfied) {
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
    EXPECT_TRUE(DynamicPast::checkTraceDynamically(formula, trace));
}