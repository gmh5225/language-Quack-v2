#ifndef AST_HPP
#define AST_HPP

#include "Location.hpp"
#include <iostream>
#include <map>
#include <memory>
#include <string>
#include <utility>
#include <vector>

namespace quack::ast {
/// Abstract node class, the base for every other AST node
class ASTNode {
  const Location _loc;

protected:
  explicit ASTNode(Location loc) : _loc(std::move(loc)) {}

public:
  const Location &getLocation() const { return _loc; }

  virtual ~ASTNode() = default;
};

class CompoundStmt; /// Forward ref
class Classes;

/// A TranslationUnit is the root of an AST, represents a file
class TranslationUnit : public ASTNode {
  std::unique_ptr<Classes> _classes;
  std::unique_ptr<CompoundStmt> _compoundStmt;

public:
  explicit TranslationUnit(Location loc, std::unique_ptr<Classes> classes,
                           std::unique_ptr<CompoundStmt> compoundStmt)
      : ASTNode(std::move(loc)), _classes(std::move(classes)),
        _compoundStmt(std::move(compoundStmt)) {}

  const CompoundStmt &getCompoundStmt() const { return *_compoundStmt; }
  const Classes &getClasses() const { return *_classes; }
};

/// Abstract Sequence type
template <typename Kind> class Sequence : public ASTNode {
  class Iterator {
  private:
    unsigned _index;
    const std::vector<std::unique_ptr<Kind>> &_vector;

  public:
    /// Iterator for Sequence type
    Iterator(const std::vector<std::unique_ptr<Kind>> &vector, unsigned index)
        : _vector(vector), _index(index) {}

    Iterator &operator++() {
      _index++;
      return *this;
    }

    Iterator operator++(int) {
      Iterator it = *this;
      ++(*this);
      return it;
    }

    Iterator &operator--() {
      _index--;
      return *this;
    }

    Iterator operator--(int) {
      Iterator it = *this;
      --(*this);
      return it;
    }

    Kind &operator*() { return *(_vector[_index]); }

    Kind *operator->() { return _vector[_index].get(); }

    bool operator==(const Iterator &other) const {
      return _index == other._index;
    }

    bool operator!=(const Iterator &other) const { return !(*this == other); }
  }; // Iterator

protected:
  std::vector<std::unique_ptr<Kind>> _sequence;

  explicit Sequence(const Location &loc) : ASTNode(loc), _sequence() {}

public:
  using SeqType = Kind;

  const auto &getSequence() const { return _sequence; }

  const bool isEmpty() const { return _sequence.size() == 0; }

  void append(std::unique_ptr<Kind> element) {
    _sequence.emplace_back(std::move(element));
  }

  /// Setting up an iterator
  /// Returns an iterator of vector of type T
  Iterator begin() const { return Iterator(_sequence, 0); }

  Iterator end() const { return Iterator(_sequence, _sequence.size()); }
};

/// Abstract Statement type, DeclStmt, IfStmt, WhileStmt, etc. are the concrete
/// types
class Statement : public ASTNode {
public:
  enum class Kind { ValueStmt, Assignment, Return, If, While, Print };

  Kind getKind() const { return _kind; }

protected:
  Statement(Location loc, Kind kind) : ASTNode(std::move(loc)), _kind(kind) {}

private:
  Kind _kind;
};

/// A block of statements
class CompoundStmt : public Sequence<Statement> {
public:
  explicit CompoundStmt(const Location &loc) : Sequence<Statement>(loc) {}
};

/// An Expression is either and LValue (has storage) or RValue (no storage)
/// If RValue, it can be primitive literal, or binary operator

class Expression : public ASTNode {
public:
  enum class Kind {
    Call,
    BinaryOperator,
    UnaryOperator,
    Identifier,
    LValue,
    IntegerLiteral,
    FloatLiteral,
    BoolLiteral,
    StringLiteral
  };

  Kind getKind() const { return _kind; }

  bool isLValue() const {
    return _kind == Kind::LValue || _kind == Kind::Identifier ||
           _kind == Kind::Call;
  }

protected:
  explicit Expression(Location loc, Kind kind)
      : ASTNode(std::move(loc)), _kind(kind) {}

private:
  Kind _kind;
};

/// Statements that could hold a value
class ValueStmt : public Statement {
  std::unique_ptr<Expression> _expr;

public:
  explicit ValueStmt(Location loc, std::unique_ptr<Expression> expr)
      : Statement(std::move(loc), Statement::Kind::ValueStmt),
        _expr(std::move(expr)) {}

  const Expression &getExpr() const { return *_expr; }
};

class UnaryOperator : public Expression {
public:
  enum class Operator { Print, Negate };

private:
  Operator _opCode;
  std::unique_ptr<Expression> _operand;

public:
  UnaryOperator(Location loc, Operator opCode,
                std::unique_ptr<Expression> operand)
      : Expression(std::move(loc), Expression::Kind::UnaryOperator),
        _opCode(opCode), _operand(std::move(operand)) {}

  const Expression &getOperand() { return *_operand; }
  const Operator getOpCode() { return _opCode; }
};

/// Binary operations:
///  a = b, a + b, a - b, etc.
/// comprised of two Expressions and an OpCode
class BinaryOperator : public Expression {
public:
  enum class Operator {
    Plus,
    Minus,
    Times,
    Divide,
    Modulo,
    Equals,
    Greater,
    GreaterEqual,
    Less,
    LessEqual
  };

private:
  Operator _opCode;
  std::unique_ptr<Expression> _leftHandSide;
  std::unique_ptr<Expression> _rightHandSide;
  const static std::map<Operator, const char *> OpCodeStringLookUp;

public:
  BinaryOperator(Location loc, Operator opCode,
                 std::unique_ptr<Expression> leftHandSide,
                 std::unique_ptr<Expression> rightHandSide)
      : Expression(std::move(loc), Expression::Kind::BinaryOperator),
        _opCode(opCode), _leftHandSide(std::move(leftHandSide)),
        _rightHandSide(std::move(rightHandSide)) {}

  bool isCompare() const {
    return _opCode == Operator::Equals || _opCode == Operator::Greater ||
           _opCode == Operator::GreaterEqual || _opCode == Operator::Less ||
           _opCode == Operator::LessEqual;
  }

  Operator getOpCode() const { return _opCode; }

  const char *getOpCodeString() const { return OpCodeStringLookUp.at(_opCode); }

  static const std::map<Operator, const char *> &getOperators() {
    return OpCodeStringLookUp;
  }

  const Expression &getLHS() const { return *_leftHandSide; }

  const Expression &getRHS() const { return *_rightHandSide; }
};

/// An Identifier token, such as type name, variable name, etc.
/// It's essentially an l-value reference
class Identifier final : public Expression {
public:
  Identifier(Location loc, const std::string &name)
      : Expression(std::move(loc), Expression::Kind::Identifier), _name(name){};

  Identifier(Location loc, std::string *name)
      : Expression(std::move(loc), Expression::Kind::Identifier),
        _name(*name){};

  const std::string &getName() const { return _name; }

private:
  const std::string _name;
};

class LValue : public Expression {
public:
  enum class Kind { VarDecl, LValueIdent, MemberAccess };

protected:
  Kind _kind;

  LValue(Location loc, Kind kind)
      : Expression(std::move(loc), Expression::Kind::LValue), _kind(kind) {}

public:
  Kind getKind() const { return _kind; }

  virtual const std::string &getSymbol() const = 0;
};

class MemberAccess final : public LValue {
  friend class StaticMemberDecl;
  std::unique_ptr<Identifier> _member;
  std::unique_ptr<Expression> _expr;
  std::string _symbol;

public:
  MemberAccess(const Location loc, std::unique_ptr<Identifier> member,
               std::unique_ptr<Expression> object)
      : LValue(loc, LValue::Kind::MemberAccess), _member(std::move(member)),
        _expr(std::move(object)), _symbol(_member->getName()) {}

  const Identifier &getMember() const { return *_member; }
  const std::string &getSymbol() const override { return _symbol; }
  const Expression &getExpression() const { return *_expr; }
};

class LValueIdent final : public LValue {
  std::unique_ptr<Identifier> _var;
  bool _isWeak;

public:
  LValueIdent(Location loc, std::unique_ptr<Identifier> var,
              bool isWeak = false)
      : LValue(std::move(loc), LValue::Kind::LValueIdent), _var(std::move(var)),
        _isWeak(isWeak) {}

  const Identifier &getVar() const { return *_var; }

  const std::string &getSymbol() const override { return _var->getName(); }

  bool isWeak() const { return _isWeak; }
};

/// Defines a variable declaration
/// Either declared with a value or without value
class VarDecl : public LValue {
protected:
  std::unique_ptr<Identifier> _type;
  std::unique_ptr<Identifier> _var;
  bool _isWeak;
  bool _isMemberDecl;

public:
  VarDecl(const Location &loc, std::unique_ptr<Identifier> var,
          std::unique_ptr<Identifier> type, bool isMemberDecl = false,
          bool isWeak = false)
      : LValue(std::move(loc), LValue::Kind::VarDecl), _var(std::move(var)),
        _type(std::move(type)), _isWeak(isWeak), _isMemberDecl(isMemberDecl) {}

  VarDecl(const Location &loc, std::unique_ptr<VarDecl> other)
      : LValue(std::move(loc), LValue::Kind::VarDecl),
        _var(std::move(other->_var)), _type(std::move(other->_type)) {}

  const Identifier &getType() const { return *_type; }

  const Identifier &getVar() const { return *_var; }

  const std::string &getSymbol() const override { return _var->getName(); }

  bool isWeak() const { return _isWeak; }

  bool isMemberDecl() const { return _isMemberDecl; }
};

class StaticMemberDecl final : public VarDecl {
  const std::string _symbol;
  std::unique_ptr<Expression> _object;

public:
  StaticMemberDecl(Location loc, std::unique_ptr<MemberAccess> var,
                   std::unique_ptr<Identifier> type, bool isWeak = false)
      : VarDecl(loc, std::move(var->_member), std::move(type), true, isWeak),
        _object(std::move(var->_expr)), _symbol(_var->getName()) {}

  const std::string &getSymbol() const override { return _symbol; }
  const Expression &getObject() const { return *_object; }
};

class Assignment : public Statement {
protected:
  std::unique_ptr<LValue> _lvalue;
  std::unique_ptr<Expression> _rvalue;

public:
  Assignment(Location loc, std::unique_ptr<LValue> lvalue,
             std::unique_ptr<Expression> rvalue)
      : Statement(std::move(loc), Statement::Kind::Assignment),
        _lvalue(std::move(lvalue)), _rvalue(std::move(rvalue)) {}

  const LValue &getLeftHandSide() const { return *_lvalue; }
  const Expression &getRightHandSide() const { return *_rvalue; }
};

/// Leaf of AST
/// An IntegerLiteral is an RValue Expression
/// It is stored as a long integer (8 bytes)
class IntegerLiteral final : public Expression {
private:
  long int _integer;

public:
  explicit IntegerLiteral(Location loc, long int integer)
      : Expression(std::move(loc), Expression::Kind::IntegerLiteral),
        _integer(integer) {}

  long int getInteger() const { return _integer; }
};

class FloatLiteral final : public Expression {
private:
  double _float;

public:
  explicit FloatLiteral(Location loc, double floatingpoint)
      : Expression(std::move(loc), Expression::Kind::FloatLiteral),
        _float(floatingpoint) {}

  double getFloat() const { return _float; }
};

class BoolLiteral final : public Expression {
private:
  bool _bool;

public:
  BoolLiteral(Location loc, bool boolean)
      : Expression(std::move(loc), Expression::Kind::BoolLiteral),
        _bool(boolean) {}
  bool getBool() const { return _bool; }
};

class StringLiteral final : public Expression {
  std::string _text;

public:
  StringLiteral(Location loc, const std::string &text)
      : Expression(std::move(loc), Expression::Kind::StringLiteral),
        _text(text) {}

  const std::string &getText() const { return _text; }
};

class Return final : public Statement {
  std::unique_ptr<Expression> _retVal;

public:
  explicit Return(Location loc, std::unique_ptr<Expression> retVal)
      : Statement(std::move(loc), Statement::Kind::Return),
        _retVal(std::move(retVal)) {}

  const Expression *getRetVal() const {
    return _retVal != nullptr ? _retVal.get() : nullptr;
  }
};

class Arguments final : public Sequence<Expression> {
public:
  explicit Arguments(const Location &loc) : Sequence<Expression>(loc) {}
};

class Parameters final : public Sequence<VarDecl> {
public:
  explicit Parameters(const Location &loc) : Sequence<VarDecl>(loc) {}
};

class Method final : public ASTNode {
  std::unique_ptr<Parameters> _params;
  std::unique_ptr<Identifier> _name;
  std::unique_ptr<Identifier> _returnType;
  std::unique_ptr<CompoundStmt> _body;

public:
  Method(const Location &loc, std::unique_ptr<Parameters> params,
         std::unique_ptr<Identifier> name,
         std::unique_ptr<Identifier> returnType,
         std::unique_ptr<CompoundStmt> body)
      : ASTNode(loc), _params(std::move(params)), _name(std::move(name)),
        _returnType(std::move(returnType)), _body(std::move(body)) {}

  const Parameters &getParams() const { return *_params; }
  const Identifier &getMethodIdent() const { return *_name; }
  const Identifier &getReturnType() const { return *_returnType; }
  const CompoundStmt &getBody() const { return *_body; }
};

class Methods final : public Sequence<Method> {
public:
  explicit Methods(const Location &loc) : Sequence<Method>(loc) {}
};

class Class final : public ASTNode {
  std::unique_ptr<Methods> _methods;
  std::unique_ptr<Identifier> _name;
  std::unique_ptr<Method> _constructor;
  std::unique_ptr<Identifier> _super;

public:
  Class(const Location &loc, std::unique_ptr<Methods> methods,
        std::unique_ptr<Identifier> name, std::unique_ptr<Method> constructor,
        std::unique_ptr<Identifier> super = nullptr)
      : ASTNode(loc), _methods(std::move(methods)), _name(std::move(name)),
        _constructor(std::move(constructor)), _super(std::move(super)) {}

  const Method &getConstructor() const { return *_constructor; }
  const Identifier &getClassIdent() const { return *_name; }
  const Identifier *getSuper() const {
    return _super.get(); /* could be null */
  }
  const Methods &getMethods() const { return *_methods; }
};

class Classes final : public Sequence<Class> {
public:
  explicit Classes(const Location &loc) : Sequence<Class>(loc) {}
};

class Call final : public Expression {
  std::unique_ptr<Expression> _caller;
  std::unique_ptr<Identifier> _callee;
  std::unique_ptr<Arguments> _args;

public:
  Call(const Location &loc, std::unique_ptr<Expression> caller,
       std::unique_ptr<Identifier> callee, std::unique_ptr<Arguments> args)
      : Expression(loc, Expression::Kind::Call), _caller(std::move(caller)),
        _callee(std::move(callee)), _args(std::move(args)) {}

  const Expression *getCaller() const {
    return _caller ? _caller.get() : nullptr;
  }
  const Identifier *getCallee() const { return _callee.get(); }
  const Arguments *getArgs() const { return _args.get(); }
  bool isConstructorCall() const { return _caller == nullptr; }
};

class If final : public Statement {
  std::unique_ptr<Expression> _cond;
  std::unique_ptr<CompoundStmt> _ifStmts;
  std::unique_ptr<CompoundStmt> _elseStmts;

public:
  If(Location loc, std::unique_ptr<Expression> cond,
     std::unique_ptr<CompoundStmt> ifStmts,
     std::unique_ptr<CompoundStmt> elseStmts)
      : Statement(std::move(loc), Statement::Kind::If), _cond(std::move(cond)),
        _ifStmts(std::move(ifStmts)), _elseStmts(std::move(elseStmts)) {}

  const Expression &getCond() const { return *_cond; }
  const CompoundStmt &getIfBlock() const { return *_ifStmts; }
  const CompoundStmt *getElseBlock() const { return _elseStmts.get(); }
};

class While final : public Statement {
  std::unique_ptr<Expression> _cond;
  std::unique_ptr<CompoundStmt> _block;

public:
  While(Location loc, std::unique_ptr<Expression> cond,
        std::unique_ptr<CompoundStmt> stmnts)
      : Statement(std::move(loc), Statement::Kind::While),
        _cond(std::move(cond)), _block(std::move(stmnts)) {}

  const Expression &getCond() const { return *_cond; }
  const CompoundStmt &getBlock() const { return *_block; }
};

} // namespace quack::ast

#endif // AST_HPP
