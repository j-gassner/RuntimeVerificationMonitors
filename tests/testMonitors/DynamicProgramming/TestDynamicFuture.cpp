#include "TestDynamicFuture.h"
#include "Parser/Parser.h"
#include "Trace/Trace.h"
#include "Utils/Utils.h"
#include "DynamicProgramming/DynamicFuture.h"

TEST(TestDynamicFuture, violated1) {
    Trace trace1 = Utils::createTrace({"a", "b", "c", "g", "f"}, {
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
    Formula formula = Parser::parse("G(a -> Fb)");

    EXPECT_FALSE(DynamicFuture::checkTraceDynamically(formula, trace1));
}


TEST(TestDynamicFuture, satisfied2) {
    Formula formula = Parser::parse("G(b -> Fc)");
    Trace trace2 = Utils::createTrace({"a", "b", "c", "g", "f", "h"}, {
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

    EXPECT_TRUE(DynamicFuture::checkTraceDynamically(formula, trace2));
}

TEST(TestDynamicFuture, violated2) {
    Trace trace2 = Utils::createTrace({"a", "b", "c", "g", "f", "h"}, {
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
    Formula formula = Parser::parse("F(!(G(b -> Fc)))");

    EXPECT_FALSE(DynamicFuture::checkTraceDynamically(formula, trace2));
}

TEST(TestDynamicFuture, violatedEnd) {
    Trace trace = Utils::createTrace({"green", "yellow", "red"}, {
            {"green"},
            {"yellow"},
            {"red"},
            {"green"},
            {"yellow"},
            {"green"},
            {"red"}});
    Formula formula = Parser::parse("G(green -> !red U yellow)");
    EXPECT_FALSE(DynamicFuture::checkTraceDynamically(formula, trace));
}

TEST(TestDynamicFuture, violatedBeginning) {
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
    EXPECT_FALSE(DynamicFuture::checkTraceDynamically(formula, trace));
}

TEST(TestDynamicFuture, satisfied) {
    Trace trace = Utils::createTrace({"green", "yellow", "red"}, {
            {"green"},
            {"yellow"},
            {"red"},
            {"yellow"},
            {"red"},
            {"green"},
            {"yellow"}});
    Formula formula = Parser::parse("G(green -> !red U yellow)");
    EXPECT_TRUE(DynamicFuture::checkTraceDynamically(formula, trace));
}

TEST(TestDynamicFuture, strongNext) {
Trace trace = Utils::createTrace({"a", "b"}, {
        {"b"},
        {"a"},
        {"b"}});
Formula formula = Parser::parse("G(b -> (X(a)))");

EXPECT_FALSE(DynamicFuture::checkTraceDynamically(formula, trace));
}

TEST(TestDynamicFuture, until) {
Trace trace = Utils::createTrace({"a", "b", "c"}, {
        {"b"},
        {"a"},
        {"b"}});
Formula formula = Parser::parse("a U b");
EXPECT_TRUE(DynamicFuture::checkTraceDynamically(formula, trace));
}