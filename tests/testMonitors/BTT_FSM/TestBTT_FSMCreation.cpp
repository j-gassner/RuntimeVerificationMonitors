#include "Formula/Formula.h"
#include "Parser/Parser.h"
#include "BTT-FSM/BTT_FSMCreation.h"
#include "TestBTT_FSMCreation.h"

//TODO Set ordering is not deterministic due to pointers
//TEST(TestBTT_FSMCreation, correctTree) {
//    Formula formula = Parser::parse("G((a & b & c & F(d)) -> (!(!(e) & F(e))))");
//    auto generatedTree = BTT_FSMCreation::formulaToBTT_FSM(formula, false);
//    std::string expectedTree = "BTT-FSM for G(((F(d) & a & b & c) -> !((!(e) & F(e)))))"
//                               "\nfalse\ntrue\nId: 2\nNon-terminal: (a ? (b ? (c ? (e ? 2 : (d ? 5 : 3)) : 2) : 2) : 2)"
//                               "\nTerminal: (true ? true : true)\nId: 3\nNon-terminal: (e ? (d ? false : 4) : (d ? 5 : 3))"
//                               "\nTerminal: (e ? (d ? false : true) : true)\nId: 4\nNon-terminal: (d ? false : 4)"
//                               "\nTerminal: (d ? false : true)\nId: 5\nNon-terminal: (e ? false : 5)\nTerminal: (e ? false : true)\n";
//    EXPECT_EQ(expectedTree, generatedTree.to_string());
//}