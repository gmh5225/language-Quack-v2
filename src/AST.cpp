//
// Created by Parsa Bagheri on 9/2/20.
//

#include "AST.hpp"

namespace quack::ast {

const std::map<BinaryOperator::Operator, const char *> BinaryOperator::OpCodeStringLookUp{
    {BinaryOperator::Operator::Plus, "+"},
    {BinaryOperator::Operator::Minus, "-"},
    {BinaryOperator::Operator::Divide, "/"},
    {BinaryOperator::Operator::Times, "*"},
    {BinaryOperator::Operator::Equals, "=="},
    {BinaryOperator::Operator::Greater, ">"},
    {BinaryOperator::Operator::GreaterEqual, ">="},
    {BinaryOperator::Operator::Less, "<"},
    {BinaryOperator::Operator::LessEqual, "<="}};

}