#include "Parser/Parser.h"
#include "QMC/QMC.h"
#include "TestQMC.h"

// Test cases taken from https://github.com/pfpacket/Quine-McCluskey/tree/master/sample

TEST(TestQMC, formula0) {
    Formula formula0 = Parser::parse("a & (a|b)");
    auto minimizedFormula = QMC::reduceBoolFormula(formula0);
    EXPECT_EQ(minimizedFormula.to_string(), "a");
}

TEST(TestQMC, formula1) {
    auto formula1 = Parser::parse("(!a & b & !c) | (a & !b & !c) | (a & b & !c & !d) | (a & !b & c & !d) | "
                                  "(b & c & !d) | (!a & b & c & d) | (a & !b & c & d) | (!a & !b & d)");
    auto minimizedFormula = QMC::reduceBoolFormula(formula1);
    EXPECT_EQ(minimizedFormula.to_string(), "((!(a) & d) | (!(b) & a) | (!(d) & b))");
}
TEST(TestQMC, formula2) {
    auto formula2 = Parser::parse(
            "(!a & !b & !c & !d & !e&!f )| (!a & !b & !c & !d & e & !f) | (!a & !b & !c & d & e & !f) "
            "| (!a & !b & !c & d & e & !f) | (!a & !b & !c & d & e & f) | (!a & !b & c & d & e & !f) "
            "| (!a & !b & c & !d & !e & !f) | (a & !b & c & !d & !e & f) | (!a & !b & c & d & !e & !f) "
            "| (!a & !b & c & d & e & f) | (!a & !b & c & !d & e & !f)");
    auto minimizedFormula = QMC::reduceBoolFormula(formula2);
    EXPECT_EQ(minimizedFormula.to_string(), "((!(a) & !(b) & !(d) & !(f)) | (!(a) & !(b) & !(f) & c) | (!(a) & !(b) & d & e) | (!(b) & !(d) & !(e) & a & c & f))");
}

TEST(TestQMC, formula3) {
    auto formula3 = Parser::parse(
            "((!a & !b & !d) | (!a & !b & c) | (!a & !c & !d) | (!a & !c & b) | (!a & c & d) | (b & d))");
    auto minimizedFormula = QMC::reduceBoolFormula(formula3);
    EXPECT_EQ(minimizedFormula.to_string(), "((!(a) & !(b) & c) | (!(a) & !(c) & !(d)) | (b & d))");
}

TEST(TestQMC, formula4) {
    auto formula4 = Parser::parse("(!a & !b & !c & !d & !e) | (!a & !b & !c & d & !e) | (!a & !b & !c & d & e)"
                                  " | (!a & !b & c & !d & !e) | (!a & !b & c & d & !e) | (!a & !b & c & d & e)"
                                  " | (!a & b & c & !d & e) | (a & !b & c & !d & !e) | (a & !b & c & d & !e) | (a & !b & c & d & e)");
    auto minimizedFormula = QMC::reduceBoolFormula(formula4);
    EXPECT_EQ(minimizedFormula.to_string(), "((!(a) & !(b) & !(e)) | (!(a) & !(b) & d) | (!(a) & !(d) & b & c & e) | (!(b) & !(e) & c) | (!(b) & c & d))");
}

TEST(TestQMC, formula5) {
    auto formula5 = Parser::parse("(!a & !b & !c & d & !e) | (!a & !b & c & d & e) | (a & b & c & !d & !e) | (!a & b & c & d & !e) "
                                  "| (a & b & !c & !d & e) | (a & !b & !c & d & e) | (a & !b & c & d & e) | (!a & b & !c & d & !e) "
                                  "| (a & b & !c & !d & !e) | (!a & !b & c & d & !e) | (!a & !b & !c & d & e) | (a & b & c & !d & e)");
    auto minimizedFormula = QMC::reduceBoolFormula(formula5);
    EXPECT_EQ(minimizedFormula.to_string(), "((!(a) & !(e) & d) | (!(b) & d & e) | (!(d) & a & b))");
}

TEST(TestQMC, formula6) {
    auto formula5 = Parser::parse("(w & x & !y & !z) | (w & !x & !y & !z) | (!w & !x & !y & z) | (!w & x & !y & z) | (w & x & !y & z)"
                                  "| (w & !x & !y & z) | (!w & !x & y & !z) | (!w & x & y & !z) | (!w & x & y & z)");
    auto minimizedFormula = QMC::reduceBoolFormula(formula5);
    EXPECT_EQ(minimizedFormula.to_string(), "((!(w) & !(z) & y) | (!(w) & x & z) | (!(y) & w) | (!(y) & z))");
}




