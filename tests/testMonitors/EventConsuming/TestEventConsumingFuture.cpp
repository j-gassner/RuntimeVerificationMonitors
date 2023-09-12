#include "TestEventConsumingFuture.h"
#include "Utils/Utils.h"
#include "Parser/Parser.h"
#include "Trace/Trace.h"
#include "EventConsuming/EventConsuming.h"

TEST(TestECFuture, violated1) {
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

    EXPECT_EQ(EventConsuming::eventConsumingFuture(formula, trace).to_string(), "false");
}

TEST(TestECFuture, satisfied1) {
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

    EXPECT_EQ(EventConsuming::eventConsumingFuture(formula, trace).to_string(), "true");
}

TEST(TestECFuture, satisfied2) {
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

    EXPECT_EQ(EventConsuming::eventConsumingFuture(formula, trace).to_string(), "true");
}

TEST(TestECFuture, violated2) {
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

    EXPECT_EQ(EventConsuming::eventConsumingFuture(formula, trace).to_string(), "false");
}

TEST(TestECFuture, violatedEnd) {
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
    EXPECT_EQ(EventConsuming::eventConsumingFuture(formula, trace).to_string(), "false");
}

TEST(TestECFuture, violatedBeginning) {
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
    EXPECT_EQ(EventConsuming::eventConsumingFuture(formula, trace).to_string(), "false");
}

TEST(TestECFuture, satisfied) {
    Trace trace = Utils::createTrace({"green", "yellow", "red"}, {
            {"green"},
            {"yellow"},
            {"red"},
            {"green"},
            {"yellow"},
            {"red"},
            {"red"}});
    Formula formula = Parser::parse("G(green -> !red U yellow)");
    EXPECT_EQ(EventConsuming::eventConsumingFuture(formula, trace).to_string(), "true");
}

TEST(TestECFuture, strongNext) {
    Trace trace = Utils::createTrace({"a"}, {
            {"a"},
            {"a"},
            {"a"},
            {"a"}});
    Formula formula = Parser::parse("G(X(a))");

    EXPECT_EQ(EventConsuming::eventConsumingFuture(formula, trace).to_string(), "false");
}

TEST(TestECFuture, weakNext) {
    Trace trace = Utils::createTrace({"a"}, {
            {"a"},
            {"a"},
            {"a"},
            {"a"}});
    Formula formula = Parser::parse("G(W(a))");

    EXPECT_EQ(EventConsuming::eventConsumingFuture(formula, trace).to_string(), "true");
}

TEST(TestECFuture, atomic) {
    Trace trace = Utils::createTrace({"a", "b"}, {
            {"a"},
            {"a"},
            {"b"},
            {"a"}});
    Formula formula = Parser::parse("G(a)");

    EXPECT_EQ(EventConsuming::eventConsumingFuture(formula, trace).to_string(), "false");
}