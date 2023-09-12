#include "Parser.h"
#include <ANTLRInputStream.h>
#include "Parser/gen/FormulaLexer.h"
#include "Parser/gen/FormulaParser.h"
#include "Visitor.h"

Formula Parser::parse(const std::string &formula) {

    antlr4::ANTLRInputStream input(formula);
    FormulaLexer lexer(&input);
    antlr4::CommonTokenStream tokens(&lexer);
    tokens.fill();
    FormulaParser parser(&tokens);
    antlr4::tree::ParseTree *treePointer = parser.formula();
    Visitor visitor;
    return visitor.visit(treePointer).as<Formula>();
}
