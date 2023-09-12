#include "TestRewriteVisitor.h"
#include "Parser/Parser.h"
#include "Rewriting/RewriteVisitor.h"

TEST(TestRewriteVisitor, absorption) {
    auto absorption = Parser::parse("a & (b | a)");
    RewriteVisitor rw;
    rw.rewrite(absorption);
    EXPECT_EQ(absorption.to_string(), "a");
}

TEST(TestRewriteVisitor, absorption1) {
    auto testNot = Parser::parse("(a & b & c) | (a & b & c & d) | (a & b & c & e)");
    RewriteVisitor rw;
    rw.rewrite(testNot);
    EXPECT_EQ(testNot.to_string(), "(a & b & c)");
}

TEST(TestRewriteVisitor, absorption2) {
    auto absorption = Parser::parse("a & c & (c | d)");
    RewriteVisitor rw;
    rw.rewrite(absorption);
    EXPECT_EQ(absorption.to_string(), "(a & c)");
}

TEST(TestRewriteVisitor, absorption3) {
    auto absorption = Parser::parse("a & b & c & (a|b) & (a|c)");
    RewriteVisitor rw;
    rw.rewrite(absorption);
    EXPECT_EQ(absorption.to_string(), "(a & b & c)");
}

TEST(TestRewriteVisitor, absorption4) {
    auto absorption = Parser::parse("a & (a | b) & (a | c)");
    RewriteVisitor rw;
    rw.rewrite(absorption);
    EXPECT_EQ(absorption.to_string(), "a");
}

//TEST(TestRewriteVisitor, distr) {
//    auto absorption = Parser::parse("(a | b) & (a | c)");
//    RewriteVisitor rw;
//    rw.rewrite(absorption);
//    EXPECT_EQ(absorption.to_string(), "a & (b | c)");
//}
//
//TEST(TestRewriteVisitor, distr1) {
//    auto absorption = Parser::parse("(a | b | c) & (a | c | d)");
//    RewriteVisitor rw;
//    rw.rewrite(absorption);
//    EXPECT_EQ(absorption.to_string(), "((b & d) | a | c)");
//}
//
//TEST(TestRewriteVisitor, distr2) {
//    auto absorption = Parser::parse("(a & b) | (a & c)");
//    RewriteVisitor rw;
//    rw.rewrite(absorption);
//    EXPECT_EQ(absorption.to_string(), "((b | c) & a)");
//}
//
//TEST(TestRewriteVisitor, distr3) {
//    auto absorption = Parser::parse("(a & b & c) | (a & c & d)");
//    RewriteVisitor rw;
//    rw.rewrite(absorption);
//    EXPECT_EQ(absorption.to_string(), "((b | d) & a & c)");
//}

TEST(TestRewriteVisitor, reduceXor) {
    auto xorFormula = Parser::parse("a ^ b ^ c ^ (a | b)");
    RewriteVisitor rw;
    rw.rewrite(xorFormula);
    EXPECT_EQ(xorFormula.to_string(), "((a & b) ^ c)");
}

TEST(TestRewriteVisitor, moveNary) {
    auto xorFormula = Parser::parse("a & b & (c & d)");
    RewriteVisitor rw;
    rw.rewrite(xorFormula);
    EXPECT_EQ(xorFormula.to_string(), "(a & b & c & d)");
}

TEST(TestRewriteVisitor, testNot) {
    auto testNot = Parser::parse("a | b | !a | c");
    RewriteVisitor rw;
    rw.rewrite(testNot);
    EXPECT_EQ(testNot.to_string(), "true");
}

TEST(TestRewriteVisitor, trafficLight) {
    auto trafficLight = Parser::parse("G(green -> !red U yellow)");
    RewriteVisitor rw;
    rw.rewrite(trafficLight);
    EXPECT_EQ(trafficLight.to_string(), "G(((((red ^ true) U yellow) & green) ^ green ^ true))");
}