// A Bison parser, made by GNU Bison 3.7.1.

// Skeleton implementation for Bison LALR(1) parsers in C++

// Copyright (C) 2002-2015, 2018-2020 Free Software Foundation, Inc.

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

// As a special exception, you may create a larger work that contains
// part or all of the Bison parser skeleton and distribute that work
// under terms of your choice, so long as that work isn't itself a
// parser generator using the skeleton or a modified version thereof
// as a parser skeleton.  Alternatively, if you modify or redistribute
// the parser skeleton itself, you may (at your option) remove this
// special exception, which will cause the skeleton and the resulting
// Bison output files to be licensed under the GNU General Public
// License without this special exception.

// This special exception was added by the Free Software Foundation in
// version 2.2 of Bison.

// DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
// especially those whose name start with YY_ or yy_.  They are
// private implementation details that can be changed or removed.





#include "Parser.hpp"


// Unqualified %code blocks.
#line 38 "/home/parsab/dev/Quack-v2/src/Parser.ypp"

  #include "ParserDriver.hpp"

  // Creates a location object
  #define loc(BEGIN_TOK, END_TOK) \
    Location(BEGIN_TOK.begin.line, BEGIN_TOK.begin.column, END_TOK.end.line, END_TOK.end.column, BEGIN_TOK.begin.filename)

#line 54 "/home/parsab/dev/Quack-v2/cmake-build-debug/Parser.cpp"


#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> // FIXME: INFRINGES ON USER NAME SPACE.
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif


// Whether we are compiled with exception support.
#ifndef YY_EXCEPTIONS
# if defined __GNUC__ && !defined __EXCEPTIONS
#  define YY_EXCEPTIONS 0
# else
#  define YY_EXCEPTIONS 1
# endif
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K].location)
/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

# ifndef YYLLOC_DEFAULT
#  define YYLLOC_DEFAULT(Current, Rhs, N)                               \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).begin  = YYRHSLOC (Rhs, 1).begin;                   \
          (Current).end    = YYRHSLOC (Rhs, N).end;                     \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).begin = (Current).end = YYRHSLOC (Rhs, 0).end;      \
        }                                                               \
    while (false)
# endif


// Enable debugging if requested.
#if YYDEBUG

// A pseudo ostream that takes yydebug_ into account.
# define YYCDEBUG if (yydebug_) (*yycdebug_)

# define YY_SYMBOL_PRINT(Title, Symbol)         \
  do {                                          \
    if (yydebug_)                               \
    {                                           \
      *yycdebug_ << Title << ' ';               \
      yy_print_ (*yycdebug_, Symbol);           \
      *yycdebug_ << '\n';                       \
    }                                           \
  } while (false)

# define YY_REDUCE_PRINT(Rule)          \
  do {                                  \
    if (yydebug_)                       \
      yy_reduce_print_ (Rule);          \
  } while (false)

# define YY_STACK_PRINT()               \
  do {                                  \
    if (yydebug_)                       \
      yy_stack_print_ ();                \
  } while (false)

#else // !YYDEBUG

# define YYCDEBUG if (false) std::cerr
# define YY_SYMBOL_PRINT(Title, Symbol)  YYUSE (Symbol)
# define YY_REDUCE_PRINT(Rule)           static_cast<void> (0)
# define YY_STACK_PRINT()                static_cast<void> (0)

#endif // !YYDEBUG

#define yyerrok         (yyerrstatus_ = 0)
#define yyclearin       (yyla.clear ())

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYRECOVERING()  (!!yyerrstatus_)

namespace yy {
#line 146 "/home/parsab/dev/Quack-v2/cmake-build-debug/Parser.cpp"

  /// Build a parser object.
  parser::parser (quack::parser::ParserDriver& drv_yyarg)
#if YYDEBUG
    : yydebug_ (false),
      yycdebug_ (&std::cerr),
#else
    :
#endif
      yy_lac_established_ (false),
      drv (drv_yyarg)
  {}

  parser::~parser ()
  {}

  parser::syntax_error::~syntax_error () YY_NOEXCEPT YY_NOTHROW
  {}

  /*---------------.
  | symbol kinds.  |
  `---------------*/



  // by_state.
  parser::by_state::by_state () YY_NOEXCEPT
    : state (empty_state)
  {}

  parser::by_state::by_state (const by_state& that) YY_NOEXCEPT
    : state (that.state)
  {}

  void
  parser::by_state::clear () YY_NOEXCEPT
  {
    state = empty_state;
  }

  void
  parser::by_state::move (by_state& that)
  {
    state = that.state;
    that.clear ();
  }

  parser::by_state::by_state (state_type s) YY_NOEXCEPT
    : state (s)
  {}

  parser::symbol_kind_type
  parser::by_state::kind () const YY_NOEXCEPT
  {
    if (state == empty_state)
      return symbol_kind::S_YYEMPTY;
    else
      return YY_CAST (symbol_kind_type, yystos_[+state]);
  }

  parser::stack_symbol_type::stack_symbol_type ()
  {}

  parser::stack_symbol_type::stack_symbol_type (YY_RVREF (stack_symbol_type) that)
    : super_type (YY_MOVE (that.state), YY_MOVE (that.location))
  {
    switch (that.kind ())
    {
      case symbol_kind::S_binaryOperator: // binaryOperator
        value.YY_MOVE_OR_COPY< BinaryOperator::Operator > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_unaryOperator: // unaryOperator
        value.YY_MOVE_OR_COPY< UnaryOperator::Operator > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_BOOL: // BOOL
        value.YY_MOVE_OR_COPY< bool > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_FLOAT: // FLOAT
        value.YY_MOVE_OR_COPY< double > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_INT: // INT
        value.YY_MOVE_OR_COPY< long > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_args: // args
      case symbol_kind::S_argsNonEmpty: // argsNonEmpty
        value.YY_MOVE_OR_COPY< ptr<Arguments> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_assignment: // assignment
        value.YY_MOVE_OR_COPY< ptr<Assignment> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_call: // call
        value.YY_MOVE_OR_COPY< ptr<Call> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_class: // class
        value.YY_MOVE_OR_COPY< ptr<Class> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_classes: // classes
      case symbol_kind::S_classesNonEmpty: // classesNonEmpty
        value.YY_MOVE_OR_COPY< ptr<Classes> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_compoundStmt: // compoundStmt
      case symbol_kind::S_optElseIf: // optElseIf
        value.YY_MOVE_OR_COPY< ptr<CompoundStmt> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expression: // expression
        value.YY_MOVE_OR_COPY< ptr<Expression> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_identifier: // identifier
        value.YY_MOVE_OR_COPY< ptr<Identifier> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_ifStmt: // ifStmt
        value.YY_MOVE_OR_COPY< ptr<If> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_memberAccess: // memberAccess
        value.YY_MOVE_OR_COPY< ptr<MemberAccess> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_method: // method
        value.YY_MOVE_OR_COPY< ptr<Method> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_methods: // methods
      case symbol_kind::S_methodsNonEmpty: // methodsNonEmpty
        value.YY_MOVE_OR_COPY< ptr<Methods> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_params: // params
      case symbol_kind::S_paramsNonEmpty: // paramsNonEmpty
        value.YY_MOVE_OR_COPY< ptr<Parameters> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_returnStmt: // returnStmt
        value.YY_MOVE_OR_COPY< ptr<Return> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_statement: // statement
        value.YY_MOVE_OR_COPY< ptr<Statement> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_staticAssignment: // staticAssignment
        value.YY_MOVE_OR_COPY< ptr<StaticAssignment> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_memberDecl: // memberDecl
        value.YY_MOVE_OR_COPY< ptr<StaticMemberDecl> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_translationUnit: // translationUnit
        value.YY_MOVE_OR_COPY< ptr<TranslationUnit> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_varDecl: // varDecl
        value.YY_MOVE_OR_COPY< ptr<VarDecl> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_whileStmt: // whileStmt
        value.YY_MOVE_OR_COPY< ptr<While> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_STRING_LIT: // STRING_LIT
      case symbol_kind::S_THIS: // THIS
      case symbol_kind::S_IDENT: // IDENT
      case symbol_kind::S_WEAK: // WEAK
      case symbol_kind::S_CLASS: // CLASS
      case symbol_kind::S_EXTENDS: // EXTENDS
      case symbol_kind::S_DEF: // DEF
      case symbol_kind::S_RETURN: // RETURN
      case symbol_kind::S_IF: // IF
      case symbol_kind::S_ELIF: // ELIF
      case symbol_kind::S_ELSE: // ELSE
      case symbol_kind::S_WHILE: // WHILE
        value.YY_MOVE_OR_COPY< std::string > (YY_MOVE (that.value));
        break;

      default:
        break;
    }

#if 201103L <= YY_CPLUSPLUS
    // that is emptied.
    that.state = empty_state;
#endif
  }

  parser::stack_symbol_type::stack_symbol_type (state_type s, YY_MOVE_REF (symbol_type) that)
    : super_type (s, YY_MOVE (that.location))
  {
    switch (that.kind ())
    {
      case symbol_kind::S_binaryOperator: // binaryOperator
        value.move< BinaryOperator::Operator > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_unaryOperator: // unaryOperator
        value.move< UnaryOperator::Operator > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_BOOL: // BOOL
        value.move< bool > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_FLOAT: // FLOAT
        value.move< double > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_INT: // INT
        value.move< long > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_args: // args
      case symbol_kind::S_argsNonEmpty: // argsNonEmpty
        value.move< ptr<Arguments> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_assignment: // assignment
        value.move< ptr<Assignment> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_call: // call
        value.move< ptr<Call> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_class: // class
        value.move< ptr<Class> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_classes: // classes
      case symbol_kind::S_classesNonEmpty: // classesNonEmpty
        value.move< ptr<Classes> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_compoundStmt: // compoundStmt
      case symbol_kind::S_optElseIf: // optElseIf
        value.move< ptr<CompoundStmt> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expression: // expression
        value.move< ptr<Expression> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_identifier: // identifier
        value.move< ptr<Identifier> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_ifStmt: // ifStmt
        value.move< ptr<If> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_memberAccess: // memberAccess
        value.move< ptr<MemberAccess> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_method: // method
        value.move< ptr<Method> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_methods: // methods
      case symbol_kind::S_methodsNonEmpty: // methodsNonEmpty
        value.move< ptr<Methods> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_params: // params
      case symbol_kind::S_paramsNonEmpty: // paramsNonEmpty
        value.move< ptr<Parameters> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_returnStmt: // returnStmt
        value.move< ptr<Return> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_statement: // statement
        value.move< ptr<Statement> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_staticAssignment: // staticAssignment
        value.move< ptr<StaticAssignment> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_memberDecl: // memberDecl
        value.move< ptr<StaticMemberDecl> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_translationUnit: // translationUnit
        value.move< ptr<TranslationUnit> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_varDecl: // varDecl
        value.move< ptr<VarDecl> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_whileStmt: // whileStmt
        value.move< ptr<While> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_STRING_LIT: // STRING_LIT
      case symbol_kind::S_THIS: // THIS
      case symbol_kind::S_IDENT: // IDENT
      case symbol_kind::S_WEAK: // WEAK
      case symbol_kind::S_CLASS: // CLASS
      case symbol_kind::S_EXTENDS: // EXTENDS
      case symbol_kind::S_DEF: // DEF
      case symbol_kind::S_RETURN: // RETURN
      case symbol_kind::S_IF: // IF
      case symbol_kind::S_ELIF: // ELIF
      case symbol_kind::S_ELSE: // ELSE
      case symbol_kind::S_WHILE: // WHILE
        value.move< std::string > (YY_MOVE (that.value));
        break;

      default:
        break;
    }

    // that is emptied.
    that.kind_ = symbol_kind::S_YYEMPTY;
  }

#if YY_CPLUSPLUS < 201103L
  parser::stack_symbol_type&
  parser::stack_symbol_type::operator= (const stack_symbol_type& that)
  {
    state = that.state;
    switch (that.kind ())
    {
      case symbol_kind::S_binaryOperator: // binaryOperator
        value.copy< BinaryOperator::Operator > (that.value);
        break;

      case symbol_kind::S_unaryOperator: // unaryOperator
        value.copy< UnaryOperator::Operator > (that.value);
        break;

      case symbol_kind::S_BOOL: // BOOL
        value.copy< bool > (that.value);
        break;

      case symbol_kind::S_FLOAT: // FLOAT
        value.copy< double > (that.value);
        break;

      case symbol_kind::S_INT: // INT
        value.copy< long > (that.value);
        break;

      case symbol_kind::S_args: // args
      case symbol_kind::S_argsNonEmpty: // argsNonEmpty
        value.copy< ptr<Arguments> > (that.value);
        break;

      case symbol_kind::S_assignment: // assignment
        value.copy< ptr<Assignment> > (that.value);
        break;

      case symbol_kind::S_call: // call
        value.copy< ptr<Call> > (that.value);
        break;

      case symbol_kind::S_class: // class
        value.copy< ptr<Class> > (that.value);
        break;

      case symbol_kind::S_classes: // classes
      case symbol_kind::S_classesNonEmpty: // classesNonEmpty
        value.copy< ptr<Classes> > (that.value);
        break;

      case symbol_kind::S_compoundStmt: // compoundStmt
      case symbol_kind::S_optElseIf: // optElseIf
        value.copy< ptr<CompoundStmt> > (that.value);
        break;

      case symbol_kind::S_expression: // expression
        value.copy< ptr<Expression> > (that.value);
        break;

      case symbol_kind::S_identifier: // identifier
        value.copy< ptr<Identifier> > (that.value);
        break;

      case symbol_kind::S_ifStmt: // ifStmt
        value.copy< ptr<If> > (that.value);
        break;

      case symbol_kind::S_memberAccess: // memberAccess
        value.copy< ptr<MemberAccess> > (that.value);
        break;

      case symbol_kind::S_method: // method
        value.copy< ptr<Method> > (that.value);
        break;

      case symbol_kind::S_methods: // methods
      case symbol_kind::S_methodsNonEmpty: // methodsNonEmpty
        value.copy< ptr<Methods> > (that.value);
        break;

      case symbol_kind::S_params: // params
      case symbol_kind::S_paramsNonEmpty: // paramsNonEmpty
        value.copy< ptr<Parameters> > (that.value);
        break;

      case symbol_kind::S_returnStmt: // returnStmt
        value.copy< ptr<Return> > (that.value);
        break;

      case symbol_kind::S_statement: // statement
        value.copy< ptr<Statement> > (that.value);
        break;

      case symbol_kind::S_staticAssignment: // staticAssignment
        value.copy< ptr<StaticAssignment> > (that.value);
        break;

      case symbol_kind::S_memberDecl: // memberDecl
        value.copy< ptr<StaticMemberDecl> > (that.value);
        break;

      case symbol_kind::S_translationUnit: // translationUnit
        value.copy< ptr<TranslationUnit> > (that.value);
        break;

      case symbol_kind::S_varDecl: // varDecl
        value.copy< ptr<VarDecl> > (that.value);
        break;

      case symbol_kind::S_whileStmt: // whileStmt
        value.copy< ptr<While> > (that.value);
        break;

      case symbol_kind::S_STRING_LIT: // STRING_LIT
      case symbol_kind::S_THIS: // THIS
      case symbol_kind::S_IDENT: // IDENT
      case symbol_kind::S_WEAK: // WEAK
      case symbol_kind::S_CLASS: // CLASS
      case symbol_kind::S_EXTENDS: // EXTENDS
      case symbol_kind::S_DEF: // DEF
      case symbol_kind::S_RETURN: // RETURN
      case symbol_kind::S_IF: // IF
      case symbol_kind::S_ELIF: // ELIF
      case symbol_kind::S_ELSE: // ELSE
      case symbol_kind::S_WHILE: // WHILE
        value.copy< std::string > (that.value);
        break;

      default:
        break;
    }

    location = that.location;
    return *this;
  }

  parser::stack_symbol_type&
  parser::stack_symbol_type::operator= (stack_symbol_type& that)
  {
    state = that.state;
    switch (that.kind ())
    {
      case symbol_kind::S_binaryOperator: // binaryOperator
        value.move< BinaryOperator::Operator > (that.value);
        break;

      case symbol_kind::S_unaryOperator: // unaryOperator
        value.move< UnaryOperator::Operator > (that.value);
        break;

      case symbol_kind::S_BOOL: // BOOL
        value.move< bool > (that.value);
        break;

      case symbol_kind::S_FLOAT: // FLOAT
        value.move< double > (that.value);
        break;

      case symbol_kind::S_INT: // INT
        value.move< long > (that.value);
        break;

      case symbol_kind::S_args: // args
      case symbol_kind::S_argsNonEmpty: // argsNonEmpty
        value.move< ptr<Arguments> > (that.value);
        break;

      case symbol_kind::S_assignment: // assignment
        value.move< ptr<Assignment> > (that.value);
        break;

      case symbol_kind::S_call: // call
        value.move< ptr<Call> > (that.value);
        break;

      case symbol_kind::S_class: // class
        value.move< ptr<Class> > (that.value);
        break;

      case symbol_kind::S_classes: // classes
      case symbol_kind::S_classesNonEmpty: // classesNonEmpty
        value.move< ptr<Classes> > (that.value);
        break;

      case symbol_kind::S_compoundStmt: // compoundStmt
      case symbol_kind::S_optElseIf: // optElseIf
        value.move< ptr<CompoundStmt> > (that.value);
        break;

      case symbol_kind::S_expression: // expression
        value.move< ptr<Expression> > (that.value);
        break;

      case symbol_kind::S_identifier: // identifier
        value.move< ptr<Identifier> > (that.value);
        break;

      case symbol_kind::S_ifStmt: // ifStmt
        value.move< ptr<If> > (that.value);
        break;

      case symbol_kind::S_memberAccess: // memberAccess
        value.move< ptr<MemberAccess> > (that.value);
        break;

      case symbol_kind::S_method: // method
        value.move< ptr<Method> > (that.value);
        break;

      case symbol_kind::S_methods: // methods
      case symbol_kind::S_methodsNonEmpty: // methodsNonEmpty
        value.move< ptr<Methods> > (that.value);
        break;

      case symbol_kind::S_params: // params
      case symbol_kind::S_paramsNonEmpty: // paramsNonEmpty
        value.move< ptr<Parameters> > (that.value);
        break;

      case symbol_kind::S_returnStmt: // returnStmt
        value.move< ptr<Return> > (that.value);
        break;

      case symbol_kind::S_statement: // statement
        value.move< ptr<Statement> > (that.value);
        break;

      case symbol_kind::S_staticAssignment: // staticAssignment
        value.move< ptr<StaticAssignment> > (that.value);
        break;

      case symbol_kind::S_memberDecl: // memberDecl
        value.move< ptr<StaticMemberDecl> > (that.value);
        break;

      case symbol_kind::S_translationUnit: // translationUnit
        value.move< ptr<TranslationUnit> > (that.value);
        break;

      case symbol_kind::S_varDecl: // varDecl
        value.move< ptr<VarDecl> > (that.value);
        break;

      case symbol_kind::S_whileStmt: // whileStmt
        value.move< ptr<While> > (that.value);
        break;

      case symbol_kind::S_STRING_LIT: // STRING_LIT
      case symbol_kind::S_THIS: // THIS
      case symbol_kind::S_IDENT: // IDENT
      case symbol_kind::S_WEAK: // WEAK
      case symbol_kind::S_CLASS: // CLASS
      case symbol_kind::S_EXTENDS: // EXTENDS
      case symbol_kind::S_DEF: // DEF
      case symbol_kind::S_RETURN: // RETURN
      case symbol_kind::S_IF: // IF
      case symbol_kind::S_ELIF: // ELIF
      case symbol_kind::S_ELSE: // ELSE
      case symbol_kind::S_WHILE: // WHILE
        value.move< std::string > (that.value);
        break;

      default:
        break;
    }

    location = that.location;
    // that is emptied.
    that.state = empty_state;
    return *this;
  }
#endif

  template <typename Base>
  void
  parser::yy_destroy_ (const char* yymsg, basic_symbol<Base>& yysym) const
  {
    if (yymsg)
      YY_SYMBOL_PRINT (yymsg, yysym);
  }

#if YYDEBUG
  template <typename Base>
  void
  parser::yy_print_ (std::ostream& yyo, const basic_symbol<Base>& yysym) const
  {
    std::ostream& yyoutput = yyo;
    YYUSE (yyoutput);
    if (yysym.empty ())
      yyo << "empty symbol";
    else
      {
        symbol_kind_type yykind = yysym.kind ();
        yyo << (yykind < YYNTOKENS ? "token" : "nterm")
            << ' ' << yysym.name () << " ("
            << yysym.location << ": ";
        YYUSE (yykind);
        yyo << ')';
      }
  }
#endif

  void
  parser::yypush_ (const char* m, YY_MOVE_REF (stack_symbol_type) sym)
  {
    if (m)
      YY_SYMBOL_PRINT (m, sym);
    yystack_.push (YY_MOVE (sym));
  }

  void
  parser::yypush_ (const char* m, state_type s, YY_MOVE_REF (symbol_type) sym)
  {
#if 201103L <= YY_CPLUSPLUS
    yypush_ (m, stack_symbol_type (s, std::move (sym)));
#else
    stack_symbol_type ss (s, sym);
    yypush_ (m, ss);
#endif
  }

  void
  parser::yypop_ (int n)
  {
    yystack_.pop (n);
  }

#if YYDEBUG
  std::ostream&
  parser::debug_stream () const
  {
    return *yycdebug_;
  }

  void
  parser::set_debug_stream (std::ostream& o)
  {
    yycdebug_ = &o;
  }


  parser::debug_level_type
  parser::debug_level () const
  {
    return yydebug_;
  }

  void
  parser::set_debug_level (debug_level_type l)
  {
    yydebug_ = l;
  }
#endif // YYDEBUG

  parser::state_type
  parser::yy_lr_goto_state_ (state_type yystate, int yysym)
  {
    int yyr = yypgoto_[yysym - YYNTOKENS] + yystate;
    if (0 <= yyr && yyr <= yylast_ && yycheck_[yyr] == yystate)
      return yytable_[yyr];
    else
      return yydefgoto_[yysym - YYNTOKENS];
  }

  bool
  parser::yy_pact_value_is_default_ (int yyvalue)
  {
    return yyvalue == yypact_ninf_;
  }

  bool
  parser::yy_table_value_is_error_ (int yyvalue)
  {
    return yyvalue == yytable_ninf_;
  }

  int
  parser::operator() ()
  {
    return parse ();
  }

  int
  parser::parse ()
  {
    int yyn;
    /// Length of the RHS of the rule being reduced.
    int yylen = 0;

    // Error handling.
    int yynerrs_ = 0;
    int yyerrstatus_ = 0;

    /// The lookahead symbol.
    symbol_type yyla;

    /// The locations where the error started and ended.
    stack_symbol_type yyerror_range[3];

    /// The return value of parse ().
    int yyresult;

    /// Discard the LAC context in case there still is one left from a
    /// previous invocation.
    yy_lac_discard_ ("init");

#if YY_EXCEPTIONS
    try
#endif // YY_EXCEPTIONS
      {
    YYCDEBUG << "Starting parse\n";


    /* Initialize the stack.  The initial state will be set in
       yynewstate, since the latter expects the semantical and the
       location values to have been already stored, initialize these
       stacks with a primary value.  */
    yystack_.clear ();
    yypush_ (YY_NULLPTR, 0, YY_MOVE (yyla));

  /*-----------------------------------------------.
  | yynewstate -- push a new symbol on the stack.  |
  `-----------------------------------------------*/
  yynewstate:
    YYCDEBUG << "Entering state " << int (yystack_[0].state) << '\n';
    YY_STACK_PRINT ();

    // Accept?
    if (yystack_[0].state == yyfinal_)
      YYACCEPT;

    goto yybackup;


  /*-----------.
  | yybackup.  |
  `-----------*/
  yybackup:
    // Try to take a decision without lookahead.
    yyn = yypact_[+yystack_[0].state];
    if (yy_pact_value_is_default_ (yyn))
      goto yydefault;

    // Read a lookahead token.
    if (yyla.empty ())
      {
        YYCDEBUG << "Reading a token\n";
#if YY_EXCEPTIONS
        try
#endif // YY_EXCEPTIONS
          {
            symbol_type yylookahead (yylex (drv));
            yyla.move (yylookahead);
          }
#if YY_EXCEPTIONS
        catch (const syntax_error& yyexc)
          {
            YYCDEBUG << "Caught exception: " << yyexc.what() << '\n';
            error (yyexc);
            goto yyerrlab1;
          }
#endif // YY_EXCEPTIONS
      }
    YY_SYMBOL_PRINT ("Next token is", yyla);

    if (yyla.kind () == symbol_kind::S_YYerror)
    {
      // The scanner already issued an error message, process directly
      // to error recovery.  But do not keep the error token as
      // lookahead, it is too special and may lead us to an endless
      // loop in error recovery. */
      yyla.kind_ = symbol_kind::S_YYUNDEF;
      goto yyerrlab1;
    }

    /* If the proper action on seeing token YYLA.TYPE is to reduce or
       to detect an error, take that action.  */
    yyn += yyla.kind ();
    if (yyn < 0 || yylast_ < yyn || yycheck_[yyn] != yyla.kind ())
      {
        if (!yy_lac_establish_ (yyla.kind ()))
           goto yyerrlab;
        goto yydefault;
      }

    // Reduce or error.
    yyn = yytable_[yyn];
    if (yyn <= 0)
      {
        if (yy_table_value_is_error_ (yyn))
          goto yyerrlab;
        if (!yy_lac_establish_ (yyla.kind ()))
           goto yyerrlab;

        yyn = -yyn;
        goto yyreduce;
      }

    // Count tokens shifted since error; after three, turn off error status.
    if (yyerrstatus_)
      --yyerrstatus_;

    // Shift the lookahead token.
    yypush_ ("Shifting", state_type (yyn), YY_MOVE (yyla));
    yy_lac_discard_ ("shift");
    goto yynewstate;


  /*-----------------------------------------------------------.
  | yydefault -- do the default action for the current state.  |
  `-----------------------------------------------------------*/
  yydefault:
    yyn = yydefact_[+yystack_[0].state];
    if (yyn == 0)
      goto yyerrlab;
    goto yyreduce;


  /*-----------------------------.
  | yyreduce -- do a reduction.  |
  `-----------------------------*/
  yyreduce:
    yylen = yyr2_[yyn];
    {
      stack_symbol_type yylhs;
      yylhs.state = yy_lr_goto_state_ (yystack_[yylen].state, yyr1_[yyn]);
      /* Variants are always initialized to an empty instance of the
         correct type. The default '$$ = $1' action is NOT applied
         when using variants.  */
      switch (yyr1_[yyn])
    {
      case symbol_kind::S_binaryOperator: // binaryOperator
        yylhs.value.emplace< BinaryOperator::Operator > ();
        break;

      case symbol_kind::S_unaryOperator: // unaryOperator
        yylhs.value.emplace< UnaryOperator::Operator > ();
        break;

      case symbol_kind::S_BOOL: // BOOL
        yylhs.value.emplace< bool > ();
        break;

      case symbol_kind::S_FLOAT: // FLOAT
        yylhs.value.emplace< double > ();
        break;

      case symbol_kind::S_INT: // INT
        yylhs.value.emplace< long > ();
        break;

      case symbol_kind::S_args: // args
      case symbol_kind::S_argsNonEmpty: // argsNonEmpty
        yylhs.value.emplace< ptr<Arguments> > ();
        break;

      case symbol_kind::S_assignment: // assignment
        yylhs.value.emplace< ptr<Assignment> > ();
        break;

      case symbol_kind::S_call: // call
        yylhs.value.emplace< ptr<Call> > ();
        break;

      case symbol_kind::S_class: // class
        yylhs.value.emplace< ptr<Class> > ();
        break;

      case symbol_kind::S_classes: // classes
      case symbol_kind::S_classesNonEmpty: // classesNonEmpty
        yylhs.value.emplace< ptr<Classes> > ();
        break;

      case symbol_kind::S_compoundStmt: // compoundStmt
      case symbol_kind::S_optElseIf: // optElseIf
        yylhs.value.emplace< ptr<CompoundStmt> > ();
        break;

      case symbol_kind::S_expression: // expression
        yylhs.value.emplace< ptr<Expression> > ();
        break;

      case symbol_kind::S_identifier: // identifier
        yylhs.value.emplace< ptr<Identifier> > ();
        break;

      case symbol_kind::S_ifStmt: // ifStmt
        yylhs.value.emplace< ptr<If> > ();
        break;

      case symbol_kind::S_memberAccess: // memberAccess
        yylhs.value.emplace< ptr<MemberAccess> > ();
        break;

      case symbol_kind::S_method: // method
        yylhs.value.emplace< ptr<Method> > ();
        break;

      case symbol_kind::S_methods: // methods
      case symbol_kind::S_methodsNonEmpty: // methodsNonEmpty
        yylhs.value.emplace< ptr<Methods> > ();
        break;

      case symbol_kind::S_params: // params
      case symbol_kind::S_paramsNonEmpty: // paramsNonEmpty
        yylhs.value.emplace< ptr<Parameters> > ();
        break;

      case symbol_kind::S_returnStmt: // returnStmt
        yylhs.value.emplace< ptr<Return> > ();
        break;

      case symbol_kind::S_statement: // statement
        yylhs.value.emplace< ptr<Statement> > ();
        break;

      case symbol_kind::S_staticAssignment: // staticAssignment
        yylhs.value.emplace< ptr<StaticAssignment> > ();
        break;

      case symbol_kind::S_memberDecl: // memberDecl
        yylhs.value.emplace< ptr<StaticMemberDecl> > ();
        break;

      case symbol_kind::S_translationUnit: // translationUnit
        yylhs.value.emplace< ptr<TranslationUnit> > ();
        break;

      case symbol_kind::S_varDecl: // varDecl
        yylhs.value.emplace< ptr<VarDecl> > ();
        break;

      case symbol_kind::S_whileStmt: // whileStmt
        yylhs.value.emplace< ptr<While> > ();
        break;

      case symbol_kind::S_STRING_LIT: // STRING_LIT
      case symbol_kind::S_THIS: // THIS
      case symbol_kind::S_IDENT: // IDENT
      case symbol_kind::S_WEAK: // WEAK
      case symbol_kind::S_CLASS: // CLASS
      case symbol_kind::S_EXTENDS: // EXTENDS
      case symbol_kind::S_DEF: // DEF
      case symbol_kind::S_RETURN: // RETURN
      case symbol_kind::S_IF: // IF
      case symbol_kind::S_ELIF: // ELIF
      case symbol_kind::S_ELSE: // ELSE
      case symbol_kind::S_WHILE: // WHILE
        yylhs.value.emplace< std::string > ();
        break;

      default:
        break;
    }


      // Default location.
      {
        stack_type::slice range (yystack_, yylen);
        YYLLOC_DEFAULT (yylhs.location, range, yylen);
        yyerror_range[1].location = yylhs.location;
      }

      // Perform the reduction.
      YY_REDUCE_PRINT (yyn);
#if YY_EXCEPTIONS
      try
#endif // YY_EXCEPTIONS
        {
          switch (yyn)
            {
  case 2: // translationUnit: classes compoundStmt
#line 129 "/home/parsab/dev/Quack-v2/src/Parser.ypp"
{
  yylhs.value.as < ptr<TranslationUnit> > () = std::make_unique<TranslationUnit>(loc(yystack_[1].location, yystack_[1].location), std::move(yystack_[1].value.as < ptr<Classes> > ()), std::move(yystack_[0].value.as < ptr<CompoundStmt> > ()));
  drv.setRoot(std::move(yylhs.value.as < ptr<TranslationUnit> > ()));
}
#line 1154 "/home/parsab/dev/Quack-v2/cmake-build-debug/Parser.cpp"
    break;

  case 3: // compoundStmt: %empty
#line 135 "/home/parsab/dev/Quack-v2/src/Parser.ypp"
                                      { yylhs.value.as < ptr<CompoundStmt> > () = std::make_unique<CompoundStmt>(loc(yylhs.location, yylhs.location)); }
#line 1160 "/home/parsab/dev/Quack-v2/cmake-build-debug/Parser.cpp"
    break;

  case 4: // compoundStmt: compoundStmt statement
#line 136 "/home/parsab/dev/Quack-v2/src/Parser.ypp"
                                      { yylhs.value.as < ptr<CompoundStmt> > () = std::move(yystack_[1].value.as < ptr<CompoundStmt> > ());
                                        if (yystack_[0].value.as < ptr<Statement> > ()) // can be null (empty stmt ";")
                                            yylhs.value.as < ptr<CompoundStmt> > ()->push_back(std::move(yystack_[0].value.as < ptr<Statement> > ()));
                                      }
#line 1169 "/home/parsab/dev/Quack-v2/cmake-build-debug/Parser.cpp"
    break;

  case 5: // identifier: IDENT
#line 142 "/home/parsab/dev/Quack-v2/src/Parser.ypp"
                                    { yylhs.value.as < ptr<Identifier> > () = std::make_unique<Identifier>(loc(yystack_[0].location, yystack_[0].location), yystack_[0].value.as < std::string > ()); }
#line 1175 "/home/parsab/dev/Quack-v2/cmake-build-debug/Parser.cpp"
    break;

  case 6: // memberAccess: expression "." identifier
#line 146 "/home/parsab/dev/Quack-v2/src/Parser.ypp"
                                    { yylhs.value.as < ptr<MemberAccess> > () = std::make_unique<MemberAccess>(loc(yystack_[2].location, yystack_[0].location), std::move(yystack_[0].value.as < ptr<Identifier> > ()), std::move(yystack_[2].value.as < ptr<Expression> > ())); }
#line 1181 "/home/parsab/dev/Quack-v2/cmake-build-debug/Parser.cpp"
    break;

  case 7: // varDecl: identifier ":" identifier
#line 150 "/home/parsab/dev/Quack-v2/src/Parser.ypp"
                                    { yylhs.value.as < ptr<VarDecl> > () = std::make_unique<VarDecl>(loc(yystack_[2].location, yystack_[0].location), std::move(yystack_[2].value.as < ptr<Identifier> > ()), std::move(yystack_[0].value.as < ptr<Identifier> > ())); }
#line 1187 "/home/parsab/dev/Quack-v2/cmake-build-debug/Parser.cpp"
    break;

  case 8: // memberDecl: memberAccess ":" identifier
#line 154 "/home/parsab/dev/Quack-v2/src/Parser.ypp"
                                    { yylhs.value.as < ptr<StaticMemberDecl> > () = std::make_unique<StaticMemberDecl>(loc(yystack_[2].location, yystack_[0].location), std::move(yystack_[2].value.as < ptr<MemberAccess> > ()), std::move(yystack_[0].value.as < ptr<Identifier> > ())); }
#line 1193 "/home/parsab/dev/Quack-v2/cmake-build-debug/Parser.cpp"
    break;

  case 9: // staticAssignment: varDecl "=" expression
#line 157 "/home/parsab/dev/Quack-v2/src/Parser.ypp"
                                          { yylhs.value.as < ptr<StaticAssignment> > () = std::make_unique<StaticAssignment>(loc(yystack_[2].location, yystack_[0].location), std::move(yystack_[2].value.as < ptr<VarDecl> > ()), std::move(yystack_[0].value.as < ptr<Expression> > ())); }
#line 1199 "/home/parsab/dev/Quack-v2/cmake-build-debug/Parser.cpp"
    break;

  case 10: // staticAssignment: memberDecl "=" expression
#line 158 "/home/parsab/dev/Quack-v2/src/Parser.ypp"
                                          { yylhs.value.as < ptr<StaticAssignment> > () = std::make_unique<StaticAssignment>(loc(yystack_[2].location, yystack_[0].location), std::move(yystack_[2].value.as < ptr<StaticMemberDecl> > ()), std::move(yystack_[0].value.as < ptr<Expression> > ())); }
#line 1205 "/home/parsab/dev/Quack-v2/cmake-build-debug/Parser.cpp"
    break;

  case 11: // assignment: memberAccess "=" expression
#line 161 "/home/parsab/dev/Quack-v2/src/Parser.ypp"
                                          { yylhs.value.as < ptr<Assignment> > () = std::make_unique<Assignment>(loc(yystack_[2].location, yystack_[0].location),std::move(yystack_[2].value.as < ptr<MemberAccess> > ()), std::move(yystack_[0].value.as < ptr<Expression> > ())); }
#line 1211 "/home/parsab/dev/Quack-v2/cmake-build-debug/Parser.cpp"
    break;

  case 12: // assignment: identifier "=" expression
#line 162 "/home/parsab/dev/Quack-v2/src/Parser.ypp"
                                 { auto lValueIdent = std::make_unique<LValueIdent>(loc(yystack_[2].location, yystack_[2].location), std::move(yystack_[2].value.as < ptr<Identifier> > ()));
                                   yylhs.value.as < ptr<Assignment> > () = std::make_unique<Assignment>(loc(yystack_[2].location, yystack_[0].location),std::move(lValueIdent), std::move(yystack_[0].value.as < ptr<Expression> > ())); }
#line 1218 "/home/parsab/dev/Quack-v2/cmake-build-debug/Parser.cpp"
    break;

  case 13: // returnStmt: RETURN expression
#line 166 "/home/parsab/dev/Quack-v2/src/Parser.ypp"
                               { yylhs.value.as < ptr<Return> > () = std::make_unique<Return>(loc(yystack_[1].location, yystack_[0].location), std::move(yystack_[0].value.as < ptr<Expression> > ())); }
#line 1224 "/home/parsab/dev/Quack-v2/cmake-build-debug/Parser.cpp"
    break;

  case 14: // returnStmt: RETURN
#line 167 "/home/parsab/dev/Quack-v2/src/Parser.ypp"
                                { yylhs.value.as < ptr<Return> > () = std::make_unique<Return>(loc(yystack_[0].location, yystack_[0].location), nullptr); }
#line 1230 "/home/parsab/dev/Quack-v2/cmake-build-debug/Parser.cpp"
    break;

  case 15: // ifStmt: IF expression "{" compoundStmt "}" optElseIf
#line 171 "/home/parsab/dev/Quack-v2/src/Parser.ypp"
    { yylhs.value.as < ptr<If> > () = std::make_unique<If>(loc(yystack_[5].location, yystack_[0].location), std::move(yystack_[4].value.as < ptr<Expression> > ()), std::move(yystack_[2].value.as < ptr<CompoundStmt> > ()), std::move(yystack_[0].value.as < ptr<CompoundStmt> > ())); }
#line 1236 "/home/parsab/dev/Quack-v2/cmake-build-debug/Parser.cpp"
    break;

  case 16: // optElseIf: ELIF expression "{" compoundStmt "}" optElseIf
#line 175 "/home/parsab/dev/Quack-v2/src/Parser.ypp"
    {
      yylhs.value.as < ptr<CompoundStmt> > () = std::make_unique<CompoundStmt>(loc(yystack_[5].location, yystack_[0].location));
      auto IfStmt = std::make_unique<If>(loc(yystack_[5].location, yystack_[0].location), std::move(yystack_[4].value.as < ptr<Expression> > ()), std::move(yystack_[2].value.as < ptr<CompoundStmt> > ()), std::move(yystack_[0].value.as < ptr<CompoundStmt> > ()));
      yylhs.value.as < ptr<CompoundStmt> > ()->push_back(std::move(IfStmt));
    }
#line 1246 "/home/parsab/dev/Quack-v2/cmake-build-debug/Parser.cpp"
    break;

  case 17: // optElseIf: ELSE "{" compoundStmt "}"
#line 180 "/home/parsab/dev/Quack-v2/src/Parser.ypp"
                                    { yylhs.value.as < ptr<CompoundStmt> > () = std::move(yystack_[1].value.as < ptr<CompoundStmt> > ()); }
#line 1252 "/home/parsab/dev/Quack-v2/cmake-build-debug/Parser.cpp"
    break;

  case 18: // optElseIf: %empty
#line 181 "/home/parsab/dev/Quack-v2/src/Parser.ypp"
                                    { yylhs.value.as < ptr<CompoundStmt> > () = nullptr; }
#line 1258 "/home/parsab/dev/Quack-v2/cmake-build-debug/Parser.cpp"
    break;

  case 19: // whileStmt: WHILE expression "{" compoundStmt "}"
#line 185 "/home/parsab/dev/Quack-v2/src/Parser.ypp"
    { yylhs.value.as < ptr<While> > () = std::make_unique<While>(loc(yystack_[4].location, yystack_[0].location), std::move(yystack_[3].value.as < ptr<Expression> > ()), std::move(yystack_[1].value.as < ptr<CompoundStmt> > ())); }
#line 1264 "/home/parsab/dev/Quack-v2/cmake-build-debug/Parser.cpp"
    break;

  case 20: // statement: ";"
#line 188 "/home/parsab/dev/Quack-v2/src/Parser.ypp"
                                    { ; }
#line 1270 "/home/parsab/dev/Quack-v2/cmake-build-debug/Parser.cpp"
    break;

  case 21: // statement: expression ";"
#line 189 "/home/parsab/dev/Quack-v2/src/Parser.ypp"
                                    { yylhs.value.as < ptr<Statement> > () = std::make_unique<ValueStmt>(loc(yystack_[1].location, yystack_[0].location), std::move(yystack_[1].value.as < ptr<Expression> > ())); }
#line 1276 "/home/parsab/dev/Quack-v2/cmake-build-debug/Parser.cpp"
    break;

  case 22: // statement: assignment ";"
#line 190 "/home/parsab/dev/Quack-v2/src/Parser.ypp"
                                    { yylhs.value.as < ptr<Statement> > () = std::move(yystack_[1].value.as < ptr<Assignment> > ()); }
#line 1282 "/home/parsab/dev/Quack-v2/cmake-build-debug/Parser.cpp"
    break;

  case 23: // statement: staticAssignment ";"
#line 191 "/home/parsab/dev/Quack-v2/src/Parser.ypp"
                                    { yylhs.value.as < ptr<Statement> > () = std::move(yystack_[1].value.as < ptr<StaticAssignment> > ()); }
#line 1288 "/home/parsab/dev/Quack-v2/cmake-build-debug/Parser.cpp"
    break;

  case 24: // statement: returnStmt ";"
#line 192 "/home/parsab/dev/Quack-v2/src/Parser.ypp"
                                    { yylhs.value.as < ptr<Statement> > () = std::move(yystack_[1].value.as < ptr<Return> > ()); }
#line 1294 "/home/parsab/dev/Quack-v2/cmake-build-debug/Parser.cpp"
    break;

  case 25: // statement: ifStmt
#line 193 "/home/parsab/dev/Quack-v2/src/Parser.ypp"
                                    { yylhs.value.as < ptr<Statement> > () = std::move(yystack_[0].value.as < ptr<If> > ()); }
#line 1300 "/home/parsab/dev/Quack-v2/cmake-build-debug/Parser.cpp"
    break;

  case 26: // statement: whileStmt
#line 194 "/home/parsab/dev/Quack-v2/src/Parser.ypp"
                                    { yylhs.value.as < ptr<Statement> > () = std::move(yystack_[0].value.as < ptr<While> > ()); }
#line 1306 "/home/parsab/dev/Quack-v2/cmake-build-debug/Parser.cpp"
    break;

  case 27: // binaryOperator: "+"
#line 197 "/home/parsab/dev/Quack-v2/src/Parser.ypp"
                                    { yylhs.value.as < BinaryOperator::Operator > () = BinaryOperator::Operator::Plus; }
#line 1312 "/home/parsab/dev/Quack-v2/cmake-build-debug/Parser.cpp"
    break;

  case 28: // binaryOperator: "-"
#line 198 "/home/parsab/dev/Quack-v2/src/Parser.ypp"
                                    { yylhs.value.as < BinaryOperator::Operator > () = BinaryOperator::Operator::Minus; }
#line 1318 "/home/parsab/dev/Quack-v2/cmake-build-debug/Parser.cpp"
    break;

  case 29: // binaryOperator: "*"
#line 199 "/home/parsab/dev/Quack-v2/src/Parser.ypp"
                                    { yylhs.value.as < BinaryOperator::Operator > () = BinaryOperator::Operator::Times; }
#line 1324 "/home/parsab/dev/Quack-v2/cmake-build-debug/Parser.cpp"
    break;

  case 30: // binaryOperator: "/"
#line 200 "/home/parsab/dev/Quack-v2/src/Parser.ypp"
                                    { yylhs.value.as < BinaryOperator::Operator > () = BinaryOperator::Operator::Divide; }
#line 1330 "/home/parsab/dev/Quack-v2/cmake-build-debug/Parser.cpp"
    break;

  case 31: // binaryOperator: "%"
#line 201 "/home/parsab/dev/Quack-v2/src/Parser.ypp"
                                    { yylhs.value.as < BinaryOperator::Operator > () = BinaryOperator::Operator::Modulo; }
#line 1336 "/home/parsab/dev/Quack-v2/cmake-build-debug/Parser.cpp"
    break;

  case 32: // binaryOperator: "<"
#line 202 "/home/parsab/dev/Quack-v2/src/Parser.ypp"
                                    { yylhs.value.as < BinaryOperator::Operator > () = BinaryOperator::Operator::Less; }
#line 1342 "/home/parsab/dev/Quack-v2/cmake-build-debug/Parser.cpp"
    break;

  case 33: // binaryOperator: ">"
#line 203 "/home/parsab/dev/Quack-v2/src/Parser.ypp"
                                    { yylhs.value.as < BinaryOperator::Operator > () = BinaryOperator::Operator::Greater; }
#line 1348 "/home/parsab/dev/Quack-v2/cmake-build-debug/Parser.cpp"
    break;

  case 34: // binaryOperator: "<="
#line 204 "/home/parsab/dev/Quack-v2/src/Parser.ypp"
                                    { yylhs.value.as < BinaryOperator::Operator > () = BinaryOperator::Operator::LessEqual; }
#line 1354 "/home/parsab/dev/Quack-v2/cmake-build-debug/Parser.cpp"
    break;

  case 35: // binaryOperator: ">="
#line 205 "/home/parsab/dev/Quack-v2/src/Parser.ypp"
                                    { yylhs.value.as < BinaryOperator::Operator > () = BinaryOperator::Operator::GreaterEqual; }
#line 1360 "/home/parsab/dev/Quack-v2/cmake-build-debug/Parser.cpp"
    break;

  case 36: // binaryOperator: "=="
#line 206 "/home/parsab/dev/Quack-v2/src/Parser.ypp"
                                    { yylhs.value.as < BinaryOperator::Operator > () = BinaryOperator::Operator::Equals; }
#line 1366 "/home/parsab/dev/Quack-v2/cmake-build-debug/Parser.cpp"
    break;

  case 37: // unaryOperator: "!"
#line 209 "/home/parsab/dev/Quack-v2/src/Parser.ypp"
                                    { yylhs.value.as < UnaryOperator::Operator > () = UnaryOperator::Operator::Not; }
#line 1372 "/home/parsab/dev/Quack-v2/cmake-build-debug/Parser.cpp"
    break;

  case 38: // unaryOperator: "-"
#line 210 "/home/parsab/dev/Quack-v2/src/Parser.ypp"
                                    { yylhs.value.as < UnaryOperator::Operator > () = UnaryOperator::Operator::Neg; }
#line 1378 "/home/parsab/dev/Quack-v2/cmake-build-debug/Parser.cpp"
    break;

  case 39: // call: expression "." identifier "(" args ")"
#line 213 "/home/parsab/dev/Quack-v2/src/Parser.ypp"
                                             { yylhs.value.as < ptr<Call> > () = std::make_unique<Call>(loc(yystack_[5].location, yystack_[0].location), std::move(yystack_[5].value.as < ptr<Expression> > ()), std::move(yystack_[3].value.as < ptr<Identifier> > ()),
                                                          std::move(yystack_[1].value.as < ptr<Arguments> > ())); }
#line 1385 "/home/parsab/dev/Quack-v2/cmake-build-debug/Parser.cpp"
    break;

  case 40: // args: argsNonEmpty
#line 217 "/home/parsab/dev/Quack-v2/src/Parser.ypp"
                                           { yylhs.value.as < ptr<Arguments> > () = std::move(yystack_[0].value.as < ptr<Arguments> > ()); }
#line 1391 "/home/parsab/dev/Quack-v2/cmake-build-debug/Parser.cpp"
    break;

  case 41: // args: %empty
#line 218 "/home/parsab/dev/Quack-v2/src/Parser.ypp"
                                           { yylhs.value.as < ptr<Arguments> > () = std::make_unique<Arguments>(loc(yylhs.location, yylhs.location)); }
#line 1397 "/home/parsab/dev/Quack-v2/cmake-build-debug/Parser.cpp"
    break;

  case 42: // argsNonEmpty: expression
#line 221 "/home/parsab/dev/Quack-v2/src/Parser.ypp"
                                           { yylhs.value.as < ptr<Arguments> > () = std::make_unique<Arguments>(loc(yystack_[0].location, yystack_[0].location));
                                             yylhs.value.as < ptr<Arguments> > ()->push_back(std::move(yystack_[0].value.as < ptr<Expression> > ())); }
#line 1404 "/home/parsab/dev/Quack-v2/cmake-build-debug/Parser.cpp"
    break;

  case 43: // argsNonEmpty: argsNonEmpty "," expression
#line 223 "/home/parsab/dev/Quack-v2/src/Parser.ypp"
                                           { yystack_[2].value.as < ptr<Arguments> > ()->push_back(std::move(yystack_[0].value.as < ptr<Expression> > ())); yylhs.value.as < ptr<Arguments> > () = std::move(yystack_[2].value.as < ptr<Arguments> > ()); }
#line 1410 "/home/parsab/dev/Quack-v2/cmake-build-debug/Parser.cpp"
    break;

  case 44: // params: paramsNonEmpty
#line 226 "/home/parsab/dev/Quack-v2/src/Parser.ypp"
                                           { yylhs.value.as < ptr<Parameters> > () = std::move(yystack_[0].value.as < ptr<Parameters> > ()); }
#line 1416 "/home/parsab/dev/Quack-v2/cmake-build-debug/Parser.cpp"
    break;

  case 45: // params: %empty
#line 227 "/home/parsab/dev/Quack-v2/src/Parser.ypp"
                                           { yylhs.value.as < ptr<Parameters> > () = std::make_unique<Parameters>(loc(yylhs.location, yylhs.location)); }
#line 1422 "/home/parsab/dev/Quack-v2/cmake-build-debug/Parser.cpp"
    break;

  case 46: // paramsNonEmpty: varDecl
#line 230 "/home/parsab/dev/Quack-v2/src/Parser.ypp"
                                           { yylhs.value.as < ptr<Parameters> > () = std::make_unique<Parameters>(loc(yystack_[0].location, yystack_[0].location));
                                             yylhs.value.as < ptr<Parameters> > ()->push_back(std::move(yystack_[0].value.as < ptr<VarDecl> > ())); }
#line 1429 "/home/parsab/dev/Quack-v2/cmake-build-debug/Parser.cpp"
    break;

  case 47: // paramsNonEmpty: paramsNonEmpty "," varDecl
#line 232 "/home/parsab/dev/Quack-v2/src/Parser.ypp"
                                           { yystack_[2].value.as < ptr<Parameters> > ()->push_back(std::move(yystack_[0].value.as < ptr<VarDecl> > ())); yylhs.value.as < ptr<Parameters> > () = std::move(yystack_[2].value.as < ptr<Parameters> > ()); }
#line 1435 "/home/parsab/dev/Quack-v2/cmake-build-debug/Parser.cpp"
    break;

  case 48: // method: DEF identifier "(" params ")" ":" identifier "{" compoundStmt "}"
#line 236 "/home/parsab/dev/Quack-v2/src/Parser.ypp"
                                           { yylhs.value.as < ptr<Method> > () = std::make_unique<Method>(
                                                loc(yystack_[9].location, yystack_[0].location), std::move(yystack_[6].value.as < ptr<Parameters> > ()), std::move(yystack_[8].value.as < ptr<Identifier> > ()), std::move(yystack_[3].value.as < ptr<Identifier> > ()),
                                                std::move(yystack_[1].value.as < ptr<CompoundStmt> > ()));
                                           }
#line 1444 "/home/parsab/dev/Quack-v2/cmake-build-debug/Parser.cpp"
    break;

  case 49: // method: DEF identifier "(" params ")" "{" compoundStmt "}"
#line 241 "/home/parsab/dev/Quack-v2/src/Parser.ypp"
                                           { yylhs.value.as < ptr<Method> > () = std::make_unique<Method>(
                                                loc(yystack_[7].location, yystack_[0].location), std::move(yystack_[4].value.as < ptr<Parameters> > ()), std::move(yystack_[6].value.as < ptr<Identifier> > ()),
                                                std::make_unique<Identifier>(loc(yystack_[7].location, yystack_[7].location), "Nothing"),
                                                std::move(yystack_[1].value.as < ptr<CompoundStmt> > ()));
                                           }
#line 1454 "/home/parsab/dev/Quack-v2/cmake-build-debug/Parser.cpp"
    break;

  case 50: // methods: methodsNonEmpty
#line 248 "/home/parsab/dev/Quack-v2/src/Parser.ypp"
                                           { yylhs.value.as < ptr<Methods> > () = std::move(yystack_[0].value.as < ptr<Methods> > ()); }
#line 1460 "/home/parsab/dev/Quack-v2/cmake-build-debug/Parser.cpp"
    break;

  case 51: // methods: %empty
#line 249 "/home/parsab/dev/Quack-v2/src/Parser.ypp"
                                           { yylhs.value.as < ptr<Methods> > () = std::make_unique<Methods>(loc(yylhs.location, yylhs.location)); }
#line 1466 "/home/parsab/dev/Quack-v2/cmake-build-debug/Parser.cpp"
    break;

  case 52: // methodsNonEmpty: method
#line 252 "/home/parsab/dev/Quack-v2/src/Parser.ypp"
                                           { yylhs.value.as < ptr<Methods> > () = std::make_unique<Methods>(loc(yystack_[0].location, yystack_[0].location));
                                             yylhs.value.as < ptr<Methods> > ()->push_back(std::move(yystack_[0].value.as < ptr<Method> > ())); }
#line 1473 "/home/parsab/dev/Quack-v2/cmake-build-debug/Parser.cpp"
    break;

  case 53: // methodsNonEmpty: methodsNonEmpty "," method
#line 254 "/home/parsab/dev/Quack-v2/src/Parser.ypp"
                                           { yystack_[2].value.as < ptr<Methods> > ()->push_back(std::move(yystack_[0].value.as < ptr<Method> > ())); yylhs.value.as < ptr<Methods> > () = std::move(yystack_[2].value.as < ptr<Methods> > ()); }
#line 1479 "/home/parsab/dev/Quack-v2/cmake-build-debug/Parser.cpp"
    break;

  case 54: // class: CLASS identifier "(" params ")" "{" compoundStmt methods "}"
#line 258 "/home/parsab/dev/Quack-v2/src/Parser.ypp"
                                           {
                                             yylhs.value.as < ptr<Class> > () = std::make_unique<Class>(loc(yystack_[8].location, yystack_[0].location), std::move(yystack_[1].value.as < ptr<Methods> > ()),
                                                  std::make_unique<Identifier>(loc(yystack_[7].location, yystack_[7].location), yystack_[7].value.as < ptr<Identifier> > ()->getName()),
                                                  std::make_unique<Method>(loc(yystack_[8].location, yystack_[0].location), std::move(yystack_[5].value.as < ptr<Parameters> > ()),
                                                  std::make_unique<Identifier>(loc(yystack_[7].location, yystack_[7].location), yystack_[7].value.as < ptr<Identifier> > ()->getName()),
                                                  std::move(yystack_[7].value.as < ptr<Identifier> > ()), std::move(yystack_[2].value.as < ptr<CompoundStmt> > ())));
                                           }
#line 1491 "/home/parsab/dev/Quack-v2/cmake-build-debug/Parser.cpp"
    break;

  case 55: // class: CLASS identifier "(" params ")" EXTENDS identifier "{" compoundStmt methods "}"
#line 266 "/home/parsab/dev/Quack-v2/src/Parser.ypp"
                                           {
                                            yylhs.value.as < ptr<Class> > () = std::make_unique<Class>(loc(yystack_[10].location, yystack_[0].location), std::move(yystack_[1].value.as < ptr<Methods> > ()),
                                                std::make_unique<Identifier>(loc(yystack_[9].location, yystack_[9].location), yystack_[9].value.as < ptr<Identifier> > ()->getName()),
                                                std::make_unique<Method>(loc(yystack_[10].location, yystack_[0].location), std::move(yystack_[7].value.as < ptr<Parameters> > ()),
                                                std::make_unique<Identifier>(loc(yystack_[9].location, yystack_[9].location), yystack_[9].value.as < ptr<Identifier> > ()->getName()),
                                                std::move(yystack_[9].value.as < ptr<Identifier> > ()), std::move(yystack_[2].value.as < ptr<CompoundStmt> > ())), std::move(yystack_[4].value.as < ptr<Identifier> > ())
                                              );
                                           }
#line 1504 "/home/parsab/dev/Quack-v2/cmake-build-debug/Parser.cpp"
    break;

  case 56: // classes: classesNonEmpty
#line 276 "/home/parsab/dev/Quack-v2/src/Parser.ypp"
                                           { yylhs.value.as < ptr<Classes> > () = std::move(yystack_[0].value.as < ptr<Classes> > ()); }
#line 1510 "/home/parsab/dev/Quack-v2/cmake-build-debug/Parser.cpp"
    break;

  case 57: // classes: %empty
#line 277 "/home/parsab/dev/Quack-v2/src/Parser.ypp"
                                           { yylhs.value.as < ptr<Classes> > () = std::make_unique<Classes>(loc(yylhs.location, yylhs.location)); }
#line 1516 "/home/parsab/dev/Quack-v2/cmake-build-debug/Parser.cpp"
    break;

  case 58: // classesNonEmpty: class
#line 280 "/home/parsab/dev/Quack-v2/src/Parser.ypp"
                                          { yylhs.value.as < ptr<Classes> > () = std::make_unique<Classes>(loc(yystack_[0].location, yystack_[0].location));
                                            yylhs.value.as < ptr<Classes> > ()->push_back(std::move(yystack_[0].value.as < ptr<Class> > ())); }
#line 1523 "/home/parsab/dev/Quack-v2/cmake-build-debug/Parser.cpp"
    break;

  case 59: // classesNonEmpty: classesNonEmpty "," class
#line 282 "/home/parsab/dev/Quack-v2/src/Parser.ypp"
                                          { yystack_[2].value.as < ptr<Classes> > ()->push_back(std::move(yystack_[0].value.as < ptr<Class> > ())); yylhs.value.as < ptr<Classes> > () = std::move(yystack_[2].value.as < ptr<Classes> > ()); }
#line 1529 "/home/parsab/dev/Quack-v2/cmake-build-debug/Parser.cpp"
    break;

  case 60: // expression: INT
#line 286 "/home/parsab/dev/Quack-v2/src/Parser.ypp"
                                           { yylhs.value.as < ptr<Expression> > () = std::make_unique<IntegerLiteral>(loc(yystack_[0].location, yystack_[0].location), yystack_[0].value.as < long > ()); }
#line 1535 "/home/parsab/dev/Quack-v2/cmake-build-debug/Parser.cpp"
    break;

  case 61: // expression: FLOAT
#line 287 "/home/parsab/dev/Quack-v2/src/Parser.ypp"
                                           { yylhs.value.as < ptr<Expression> > () = std::make_unique<FloatLiteral>(loc(yystack_[0].location, yystack_[0].location), yystack_[0].value.as < double > ()); }
#line 1541 "/home/parsab/dev/Quack-v2/cmake-build-debug/Parser.cpp"
    break;

  case 62: // expression: BOOL
#line 288 "/home/parsab/dev/Quack-v2/src/Parser.ypp"
                                           { yylhs.value.as < ptr<Expression> > () = std::make_unique<BoolLiteral>(loc(yystack_[0].location, yystack_[0].location), yystack_[0].value.as < bool > ()); }
#line 1547 "/home/parsab/dev/Quack-v2/cmake-build-debug/Parser.cpp"
    break;

  case 63: // expression: STRING_LIT
#line 289 "/home/parsab/dev/Quack-v2/src/Parser.ypp"
                                           { yylhs.value.as < ptr<Expression> > () = std::make_unique<StringLiteral>(loc(yystack_[0].location, yystack_[0].location), yystack_[0].value.as < std::string > ()); }
#line 1553 "/home/parsab/dev/Quack-v2/cmake-build-debug/Parser.cpp"
    break;

  case 64: // expression: THIS
#line 290 "/home/parsab/dev/Quack-v2/src/Parser.ypp"
                                           { yylhs.value.as < ptr<Expression> > () = std::make_unique<LValueIdent>(loc(yystack_[0].location, yystack_[0].location), std::make_unique<Identifier>(loc(yystack_[0].location, yystack_[0].location), "this")); }
#line 1559 "/home/parsab/dev/Quack-v2/cmake-build-debug/Parser.cpp"
    break;

  case 65: // expression: identifier
#line 291 "/home/parsab/dev/Quack-v2/src/Parser.ypp"
                                           { yylhs.value.as < ptr<Expression> > () = std::make_unique<LValueIdent>(loc(yystack_[0].location, yystack_[0].location), std::move(yystack_[0].value.as < ptr<Identifier> > ())); }
#line 1565 "/home/parsab/dev/Quack-v2/cmake-build-debug/Parser.cpp"
    break;

  case 66: // expression: "(" expression ")"
#line 292 "/home/parsab/dev/Quack-v2/src/Parser.ypp"
                                           { yylhs.value.as < ptr<Expression> > () = std::move(yystack_[1].value.as < ptr<Expression> > ()); }
#line 1571 "/home/parsab/dev/Quack-v2/cmake-build-debug/Parser.cpp"
    break;

  case 67: // expression: call
#line 293 "/home/parsab/dev/Quack-v2/src/Parser.ypp"
                                           { yylhs.value.as < ptr<Expression> > () = std::move(yystack_[0].value.as < ptr<Call> > ()); }
#line 1577 "/home/parsab/dev/Quack-v2/cmake-build-debug/Parser.cpp"
    break;

  case 68: // expression: memberAccess
#line 294 "/home/parsab/dev/Quack-v2/src/Parser.ypp"
                                           { yylhs.value.as < ptr<Expression> > () = std::move(yystack_[0].value.as < ptr<MemberAccess> > ()); }
#line 1583 "/home/parsab/dev/Quack-v2/cmake-build-debug/Parser.cpp"
    break;

  case 69: // expression: unaryOperator expression
#line 295 "/home/parsab/dev/Quack-v2/src/Parser.ypp"
                                            { yylhs.value.as < ptr<Expression> > () = std::make_unique<UnaryOperator>(loc(yystack_[1].location, yystack_[0].location), yystack_[1].value.as < UnaryOperator::Operator > (), std::move(yystack_[0].value.as < ptr<Expression> > ())); }
#line 1589 "/home/parsab/dev/Quack-v2/cmake-build-debug/Parser.cpp"
    break;

  case 70: // expression: expression binaryOperator expression
#line 296 "/home/parsab/dev/Quack-v2/src/Parser.ypp"
                                           { yylhs.value.as < ptr<Expression> > () = std::make_unique<BinaryOperator>(loc(yystack_[2].location, yystack_[0].location), yystack_[1].value.as < BinaryOperator::Operator > (), std::move(yystack_[2].value.as < ptr<Expression> > ()),
                                                          std::move(yystack_[0].value.as < ptr<Expression> > ())); }
#line 1596 "/home/parsab/dev/Quack-v2/cmake-build-debug/Parser.cpp"
    break;


#line 1600 "/home/parsab/dev/Quack-v2/cmake-build-debug/Parser.cpp"

            default:
              break;
            }
        }
#if YY_EXCEPTIONS
      catch (const syntax_error& yyexc)
        {
          YYCDEBUG << "Caught exception: " << yyexc.what() << '\n';
          error (yyexc);
          YYERROR;
        }
#endif // YY_EXCEPTIONS
      YY_SYMBOL_PRINT ("-> $$ =", yylhs);
      yypop_ (yylen);
      yylen = 0;

      // Shift the result of the reduction.
      yypush_ (YY_NULLPTR, YY_MOVE (yylhs));
    }
    goto yynewstate;


  /*--------------------------------------.
  | yyerrlab -- here on detecting error.  |
  `--------------------------------------*/
  yyerrlab:
    // If not already recovering from an error, report this error.
    if (!yyerrstatus_)
      {
        ++yynerrs_;
        context yyctx (*this, yyla);
        std::string msg = yysyntax_error_ (yyctx);
        error (yyla.location, YY_MOVE (msg));
      }


    yyerror_range[1].location = yyla.location;
    if (yyerrstatus_ == 3)
      {
        /* If just tried and failed to reuse lookahead token after an
           error, discard it.  */

        // Return failure if at end of input.
        if (yyla.kind () == symbol_kind::S_YYEOF)
          YYABORT;
        else if (!yyla.empty ())
          {
            yy_destroy_ ("Error: discarding", yyla);
            yyla.clear ();
          }
      }

    // Else will try to reuse lookahead token after shifting the error token.
    goto yyerrlab1;


  /*---------------------------------------------------.
  | yyerrorlab -- error raised explicitly by YYERROR.  |
  `---------------------------------------------------*/
  yyerrorlab:
    /* Pacify compilers when the user code never invokes YYERROR and
       the label yyerrorlab therefore never appears in user code.  */
    if (false)
      YYERROR;

    /* Do not reclaim the symbols of the rule whose action triggered
       this YYERROR.  */
    yypop_ (yylen);
    yylen = 0;
    YY_STACK_PRINT ();
    goto yyerrlab1;


  /*-------------------------------------------------------------.
  | yyerrlab1 -- common code for both syntax error and YYERROR.  |
  `-------------------------------------------------------------*/
  yyerrlab1:
    yyerrstatus_ = 3;   // Each real token shifted decrements this.
    // Pop stack until we find a state that shifts the error token.
    for (;;)
      {
        yyn = yypact_[+yystack_[0].state];
        if (!yy_pact_value_is_default_ (yyn))
          {
            yyn += symbol_kind::S_YYerror;
            if (0 <= yyn && yyn <= yylast_
                && yycheck_[yyn] == symbol_kind::S_YYerror)
              {
                yyn = yytable_[yyn];
                if (0 < yyn)
                  break;
              }
          }

        // Pop the current state because it cannot handle the error token.
        if (yystack_.size () == 1)
          YYABORT;

        yyerror_range[1].location = yystack_[0].location;
        yy_destroy_ ("Error: popping", yystack_[0]);
        yypop_ ();
        YY_STACK_PRINT ();
      }
    {
      stack_symbol_type error_token;

      yyerror_range[2].location = yyla.location;
      YYLLOC_DEFAULT (error_token.location, yyerror_range, 2);

      // Shift the error token.
      yy_lac_discard_ ("error recovery");
      error_token.state = state_type (yyn);
      yypush_ ("Shifting", YY_MOVE (error_token));
    }
    goto yynewstate;


  /*-------------------------------------.
  | yyacceptlab -- YYACCEPT comes here.  |
  `-------------------------------------*/
  yyacceptlab:
    yyresult = 0;
    goto yyreturn;


  /*-----------------------------------.
  | yyabortlab -- YYABORT comes here.  |
  `-----------------------------------*/
  yyabortlab:
    yyresult = 1;
    goto yyreturn;


  /*-----------------------------------------------------.
  | yyreturn -- parsing is finished, return the result.  |
  `-----------------------------------------------------*/
  yyreturn:
    if (!yyla.empty ())
      yy_destroy_ ("Cleanup: discarding lookahead", yyla);

    /* Do not reclaim the symbols of the rule whose action triggered
       this YYABORT or YYACCEPT.  */
    yypop_ (yylen);
    YY_STACK_PRINT ();
    while (1 < yystack_.size ())
      {
        yy_destroy_ ("Cleanup: popping", yystack_[0]);
        yypop_ ();
      }

    return yyresult;
  }
#if YY_EXCEPTIONS
    catch (...)
      {
        YYCDEBUG << "Exception caught: cleaning lookahead and stack\n";
        // Do not try to display the values of the reclaimed symbols,
        // as their printers might throw an exception.
        if (!yyla.empty ())
          yy_destroy_ (YY_NULLPTR, yyla);

        while (1 < yystack_.size ())
          {
            yy_destroy_ (YY_NULLPTR, yystack_[0]);
            yypop_ ();
          }
        throw;
      }
#endif // YY_EXCEPTIONS
  }

  void
  parser::error (const syntax_error& yyexc)
  {
    error (yyexc.location, yyexc.what ());
  }

  const char *
  parser::symbol_name (symbol_kind_type yysymbol)
  {
    static const char *const yy_sname[] =
    {
    "end of file", "error", "invalid token", "=", "-", "+", "*", "/", "%",
  "<", ">", "<=", ">=", "==", "!", ":", ".", ";", "(", ")", "{", "}",
  "INT", "FLOAT", "BOOL", "STRING_LIT", "THIS", "IDENT", "WEAK", "CLASS",
  "EXTENDS", "DEF", "RETURN", "IF", "ELIF", "ELSE", "WHILE", "UMINUS", ",",
  "$accept", "translationUnit", "compoundStmt", "identifier",
  "memberAccess", "varDecl", "memberDecl", "staticAssignment",
  "assignment", "returnStmt", "ifStmt", "optElseIf", "whileStmt",
  "statement", "binaryOperator", "unaryOperator", "call", "args",
  "argsNonEmpty", "params", "paramsNonEmpty", "method", "methods",
  "methodsNonEmpty", "class", "classes", "classesNonEmpty", "expression", YY_NULLPTR
    };
    return yy_sname[yysymbol];
  }



  // parser::context.
  parser::context::context (const parser& yyparser, const symbol_type& yyla)
    : yyparser_ (yyparser)
    , yyla_ (yyla)
  {}

  int
  parser::context::expected_tokens (symbol_kind_type yyarg[], int yyargn) const
  {
    // Actual number of expected tokens
    int yycount = 0;

#if YYDEBUG
    // Execute LAC once. We don't care if it is successful, we
    // only do it for the sake of debugging output.
    if (!yyparser_.yy_lac_established_)
      yyparser_.yy_lac_check_ (yyla_.kind ());
#endif

    for (int yyx = 0; yyx < YYNTOKENS; ++yyx)
      {
        symbol_kind_type yysym = YY_CAST (symbol_kind_type, yyx);
        if (yysym != symbol_kind::S_YYerror
            && yysym != symbol_kind::S_YYUNDEF
            && yyparser_.yy_lac_check_ (yysym))
          {
            if (!yyarg)
              ++yycount;
            else if (yycount == yyargn)
              return 0;
            else
              yyarg[yycount++] = yysym;
          }
      }
    if (yyarg && yycount == 0 && 0 < yyargn)
      yyarg[0] = symbol_kind::S_YYEMPTY;
    return yycount;
  }


  bool
  parser::yy_lac_check_ (symbol_kind_type yytoken) const
  {
    // Logically, the yylac_stack's lifetime is confined to this function.
    // Clear it, to get rid of potential left-overs from previous call.
    yylac_stack_.clear ();
    // Reduce until we encounter a shift and thereby accept the token.
#if YYDEBUG
    YYCDEBUG << "LAC: checking lookahead " << symbol_name (yytoken) << ':';
#endif
    std::ptrdiff_t lac_top = 0;
    while (true)
      {
        state_type top_state = (yylac_stack_.empty ()
                                ? yystack_[lac_top].state
                                : yylac_stack_.back ());
        int yyrule = yypact_[+top_state];
        if (yy_pact_value_is_default_ (yyrule)
            || (yyrule += yytoken) < 0 || yylast_ < yyrule
            || yycheck_[yyrule] != yytoken)
          {
            // Use the default action.
            yyrule = yydefact_[+top_state];
            if (yyrule == 0)
              {
                YYCDEBUG << " Err\n";
                return false;
              }
          }
        else
          {
            // Use the action from yytable.
            yyrule = yytable_[yyrule];
            if (yy_table_value_is_error_ (yyrule))
              {
                YYCDEBUG << " Err\n";
                return false;
              }
            if (0 < yyrule)
              {
                YYCDEBUG << " S" << yyrule << '\n';
                return true;
              }
            yyrule = -yyrule;
          }
        // By now we know we have to simulate a reduce.
        YYCDEBUG << " R" << yyrule - 1;
        // Pop the corresponding number of values from the stack.
        {
          std::ptrdiff_t yylen = yyr2_[yyrule];
          // First pop from the LAC stack as many tokens as possible.
          std::ptrdiff_t lac_size = std::ptrdiff_t (yylac_stack_.size ());
          if (yylen < lac_size)
            {
              yylac_stack_.resize (std::size_t (lac_size - yylen));
              yylen = 0;
            }
          else if (lac_size)
            {
              yylac_stack_.clear ();
              yylen -= lac_size;
            }
          // Only afterwards look at the main stack.
          // We simulate popping elements by incrementing lac_top.
          lac_top += yylen;
        }
        // Keep top_state in sync with the updated stack.
        top_state = (yylac_stack_.empty ()
                     ? yystack_[lac_top].state
                     : yylac_stack_.back ());
        // Push the resulting state of the reduction.
        state_type state = yy_lr_goto_state_ (top_state, yyr1_[yyrule]);
        YYCDEBUG << " G" << int (state);
        yylac_stack_.push_back (state);
      }
  }

  // Establish the initial context if no initial context currently exists.
  bool
  parser::yy_lac_establish_ (symbol_kind_type yytoken)
  {
    /* Establish the initial context for the current lookahead if no initial
       context is currently established.

       We define a context as a snapshot of the parser stacks.  We define
       the initial context for a lookahead as the context in which the
       parser initially examines that lookahead in order to select a
       syntactic action.  Thus, if the lookahead eventually proves
       syntactically unacceptable (possibly in a later context reached via a
       series of reductions), the initial context can be used to determine
       the exact set of tokens that would be syntactically acceptable in the
       lookahead's place.  Moreover, it is the context after which any
       further semantic actions would be erroneous because they would be
       determined by a syntactically unacceptable token.

       yy_lac_establish_ should be invoked when a reduction is about to be
       performed in an inconsistent state (which, for the purposes of LAC,
       includes consistent states that don't know they're consistent because
       their default reductions have been disabled).

       For parse.lac=full, the implementation of yy_lac_establish_ is as
       follows.  If no initial context is currently established for the
       current lookahead, then check if that lookahead can eventually be
       shifted if syntactic actions continue from the current context.  */
    if (!yy_lac_established_)
      {
#if YYDEBUG
        YYCDEBUG << "LAC: initial context established for "
                 << symbol_name (yytoken) << '\n';
#endif
        yy_lac_established_ = true;
        return yy_lac_check_ (yytoken);
      }
    return true;
  }

  // Discard any previous initial lookahead context.
  void
  parser::yy_lac_discard_ (const char* evt)
  {
   /* Discard any previous initial lookahead context because of Event,
      which may be a lookahead change or an invalidation of the currently
      established initial context for the current lookahead.

      The most common example of a lookahead change is a shift.  An example
      of both cases is syntax error recovery.  That is, a syntax error
      occurs when the lookahead is syntactically erroneous for the
      currently established initial context, so error recovery manipulates
      the parser stacks to try to find a new initial context in which the
      current lookahead is syntactically acceptable.  If it fails to find
      such a context, it discards the lookahead.  */
    if (yy_lac_established_)
      {
        YYCDEBUG << "LAC: initial context discarded due to "
                 << evt << '\n';
        yy_lac_established_ = false;
      }
  }

  int
  parser::yy_syntax_error_arguments_ (const context& yyctx,
                                                 symbol_kind_type yyarg[], int yyargn) const
  {
    /* There are many possibilities here to consider:
       - If this state is a consistent state with a default action, then
         the only way this function was invoked is if the default action
         is an error action.  In that case, don't check for expected
         tokens because there are none.
       - The only way there can be no lookahead present (in yyla) is
         if this state is a consistent state with a default action.
         Thus, detecting the absence of a lookahead is sufficient to
         determine that there is no unexpected or expected token to
         report.  In that case, just report a simple "syntax error".
       - Don't assume there isn't a lookahead just because this state is
         a consistent state with a default action.  There might have
         been a previous inconsistent state, consistent state with a
         non-default action, or user semantic action that manipulated
         yyla.  (However, yyla is currently not documented for users.)
         In the first two cases, it might appear that the current syntax
         error should have been detected in the previous state when
         yy_lac_check was invoked.  However, at that time, there might
         have been a different syntax error that discarded a different
         initial context during error recovery, leaving behind the
         current lookahead.
    */

    if (!yyctx.lookahead ().empty ())
      {
        if (yyarg)
          yyarg[0] = yyctx.token ();
        int yyn = yyctx.expected_tokens (yyarg ? yyarg + 1 : yyarg, yyargn - 1);
        return yyn + 1;
      }
    return 0;
  }

  // Generate an error message.
  std::string
  parser::yysyntax_error_ (const context& yyctx) const
  {
    // Its maximum.
    enum { YYARGS_MAX = 5 };
    // Arguments of yyformat.
    symbol_kind_type yyarg[YYARGS_MAX];
    int yycount = yy_syntax_error_arguments_ (yyctx, yyarg, YYARGS_MAX);

    char const* yyformat = YY_NULLPTR;
    switch (yycount)
      {
#define YYCASE_(N, S)                         \
        case N:                               \
          yyformat = S;                       \
        break
      default: // Avoid compiler warnings.
        YYCASE_ (0, YY_("syntax error"));
        YYCASE_ (1, YY_("syntax error, unexpected %s"));
        YYCASE_ (2, YY_("syntax error, unexpected %s, expecting %s"));
        YYCASE_ (3, YY_("syntax error, unexpected %s, expecting %s or %s"));
        YYCASE_ (4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
        YYCASE_ (5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
#undef YYCASE_
      }

    std::string yyres;
    // Argument number.
    std::ptrdiff_t yyi = 0;
    for (char const* yyp = yyformat; *yyp; ++yyp)
      if (yyp[0] == '%' && yyp[1] == 's' && yyi < yycount)
        {
          yyres += symbol_name (yyarg[yyi++]);
          ++yyp;
        }
      else
        yyres += *yyp;
    return yyres;
  }


  const signed char parser::yypact_ninf_ = -72;

  const signed char parser::yytable_ninf_ = -1;

  const short
  parser::yypact_[] =
  {
     -20,    -5,    20,   -72,   -72,   -15,   -72,    11,   -72,   280,
     -20,    -5,   -72,   -72,   -72,    10,   -72,   -72,   -72,   -72,
     -72,    10,    10,    10,     2,     3,    28,    36,    23,    25,
      26,   -72,   -72,   -72,    10,   -72,   380,   -72,    29,   -72,
      30,     7,   -72,   -72,   364,   394,   313,   330,    10,    -5,
      10,    -5,    10,    10,   -72,   -72,   -72,   -72,   -72,   -72,
     -72,   -72,   -72,   -72,   -72,   -72,   -72,   -72,    -5,   -72,
      10,    -9,    -5,   -72,   -72,   -72,   394,   -72,   394,   -72,
     394,   394,    33,   394,   -72,    -5,   -72,   112,   136,    10,
     160,    27,   -19,   -72,    34,    22,   394,    -5,   -72,    37,
      31,   -72,    10,    41,   -72,   -72,    10,    45,   -72,    35,
     160,   347,   -72,   394,    -5,   -72,    43,   -72,   184,    46,
     -72,   208,   -72,    -8,   -19,    -5,   -72,   -72,    48,   232,
     -72,   -72,   256,   -72
  };

  const signed char
  parser::yydefact_[] =
  {
      57,     0,     0,    58,     3,    56,     5,     0,     1,     2,
       0,    45,    38,    37,    20,     0,    60,    61,    62,    63,
      64,    14,     0,     0,    65,    68,     0,     0,     0,     0,
       0,    25,    26,     4,     0,    67,     0,    59,     0,    46,
       0,    44,    65,    68,     0,    13,     0,     0,     0,     0,
       0,     0,     0,     0,    23,    22,    24,    69,    28,    27,
      29,    30,    31,    32,    33,    34,    35,    36,     0,    21,
       0,     0,     0,    66,     3,     3,    12,     7,    11,     8,
       9,    10,     6,    70,     3,     0,    47,     0,     0,    41,
      51,     0,    18,    19,     0,    40,    42,     0,    52,     0,
      50,     3,     0,     0,    15,    39,     0,     0,    54,     0,
      51,     0,     3,    43,    45,    53,     0,     3,     0,     0,
      55,     0,    17,     0,    18,     0,     3,    16,     0,     0,
       3,    49,     0,    48
  };

  const signed char
  parser::yypgoto_[] =
  {
     -72,   -72,   -71,    -1,    -7,   -10,   -72,   -72,   -72,   -72,
     -72,   -54,   -72,   -72,   -72,   -72,   -72,   -72,   -72,   -42,
     -72,   -36,   -35,   -72,    66,   -72,   -72,     4
  };

  const signed char
  parser::yydefgoto_[] =
  {
      -1,     2,     9,    42,    43,    26,    27,    28,    29,    30,
      31,   104,    32,    33,    70,    34,    35,    94,    95,    40,
      41,    98,    99,   100,     3,     4,     5,    36
  };

  const unsigned char
  parser::yytable_[] =
  {
       7,    39,    25,    87,    88,    48,    50,   125,    24,     1,
      38,    84,   126,    90,    12,   102,   103,    49,    51,    44,
       8,    85,     6,    10,    13,    45,    46,    47,    15,    11,
     110,    52,    16,    17,    18,    19,    20,     6,    57,    53,
      54,   118,    55,    56,    49,    72,   121,   101,    77,    71,
      79,    89,    76,   105,    78,   129,    80,    81,   108,   132,
     106,   112,    86,   114,   120,   123,    97,    82,   130,   109,
     127,    38,   119,   115,    83,   116,    37,     0,     0,     0,
      25,    25,     0,    25,    91,     0,    24,    24,     0,    24,
       0,     0,     0,    96,     0,     0,   107,     0,     0,     0,
       0,     0,     0,    25,    39,     0,   111,     0,     0,    24,
     113,    25,     0,    38,    25,     0,    12,    24,     0,     0,
      24,     0,    25,     0,   128,    25,    13,     0,    24,    14,
      15,    24,     0,    92,    16,    17,    18,    19,    20,     6,
      12,     0,     0,     0,    21,    22,     0,     0,    23,     0,
      13,     0,     0,    14,    15,     0,     0,    93,    16,    17,
      18,    19,    20,     6,    12,     0,     0,     0,    21,    22,
       0,     0,    23,     0,    13,     0,     0,    14,    15,     0,
       0,     0,    16,    17,    18,    19,    20,     6,    12,     0,
       0,    97,    21,    22,     0,     0,    23,     0,    13,     0,
       0,    14,    15,     0,     0,   122,    16,    17,    18,    19,
      20,     6,    12,     0,     0,     0,    21,    22,     0,     0,
      23,     0,    13,     0,     0,    14,    15,     0,     0,   124,
      16,    17,    18,    19,    20,     6,    12,     0,     0,     0,
      21,    22,     0,     0,    23,     0,    13,     0,     0,    14,
      15,     0,     0,   131,    16,    17,    18,    19,    20,     6,
      12,     0,     0,     0,    21,    22,     0,     0,    23,     0,
      13,     0,     0,    14,    15,     0,     0,   133,    16,    17,
      18,    19,    20,     6,    12,     0,     0,     0,    21,    22,
       0,     0,    23,     0,    13,     0,     0,    14,    15,     0,
       0,     0,    16,    17,    18,    19,    20,     6,     0,     0,
       0,     0,    21,    22,     0,     0,    23,    58,    59,    60,
      61,    62,    63,    64,    65,    66,    67,     0,     0,    68,
       0,     0,     0,    74,    58,    59,    60,    61,    62,    63,
      64,    65,    66,    67,     0,     0,    68,     0,     0,     0,
      75,    58,    59,    60,    61,    62,    63,    64,    65,    66,
      67,     0,     0,    68,     0,     0,     0,   117,    58,    59,
      60,    61,    62,    63,    64,    65,    66,    67,     0,     0,
      68,     0,     0,    73,    58,    59,    60,    61,    62,    63,
      64,    65,    66,    67,     0,     0,    68,    69,    58,    59,
      60,    61,    62,    63,    64,    65,    66,    67,     0,     0,
      68
  };

  const short
  parser::yycheck_[] =
  {
       1,    11,     9,    74,    75,     3,     3,    15,     9,    29,
      11,    20,    20,    84,     4,    34,    35,    15,    15,    15,
       0,    30,    27,    38,    14,    21,    22,    23,    18,    18,
     101,     3,    22,    23,    24,    25,    26,    27,    34,     3,
      17,   112,    17,    17,    15,    38,   117,    20,    49,    19,
      51,    18,    48,    19,    50,   126,    52,    53,    21,   130,
      38,    20,    72,    18,    21,    19,    31,    68,    20,    38,
     124,    72,   114,   109,    70,   110,    10,    -1,    -1,    -1,
      87,    88,    -1,    90,    85,    -1,    87,    88,    -1,    90,
      -1,    -1,    -1,    89,    -1,    -1,    97,    -1,    -1,    -1,
      -1,    -1,    -1,   110,   114,    -1,   102,    -1,    -1,   110,
     106,   118,    -1,   114,   121,    -1,     4,   118,    -1,    -1,
     121,    -1,   129,    -1,   125,   132,    14,    -1,   129,    17,
      18,   132,    -1,    21,    22,    23,    24,    25,    26,    27,
       4,    -1,    -1,    -1,    32,    33,    -1,    -1,    36,    -1,
      14,    -1,    -1,    17,    18,    -1,    -1,    21,    22,    23,
      24,    25,    26,    27,     4,    -1,    -1,    -1,    32,    33,
      -1,    -1,    36,    -1,    14,    -1,    -1,    17,    18,    -1,
      -1,    -1,    22,    23,    24,    25,    26,    27,     4,    -1,
      -1,    31,    32,    33,    -1,    -1,    36,    -1,    14,    -1,
      -1,    17,    18,    -1,    -1,    21,    22,    23,    24,    25,
      26,    27,     4,    -1,    -1,    -1,    32,    33,    -1,    -1,
      36,    -1,    14,    -1,    -1,    17,    18,    -1,    -1,    21,
      22,    23,    24,    25,    26,    27,     4,    -1,    -1,    -1,
      32,    33,    -1,    -1,    36,    -1,    14,    -1,    -1,    17,
      18,    -1,    -1,    21,    22,    23,    24,    25,    26,    27,
       4,    -1,    -1,    -1,    32,    33,    -1,    -1,    36,    -1,
      14,    -1,    -1,    17,    18,    -1,    -1,    21,    22,    23,
      24,    25,    26,    27,     4,    -1,    -1,    -1,    32,    33,
      -1,    -1,    36,    -1,    14,    -1,    -1,    17,    18,    -1,
      -1,    -1,    22,    23,    24,    25,    26,    27,    -1,    -1,
      -1,    -1,    32,    33,    -1,    -1,    36,     4,     5,     6,
       7,     8,     9,    10,    11,    12,    13,    -1,    -1,    16,
      -1,    -1,    -1,    20,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    13,    -1,    -1,    16,    -1,    -1,    -1,
      20,     4,     5,     6,     7,     8,     9,    10,    11,    12,
      13,    -1,    -1,    16,    -1,    -1,    -1,    20,     4,     5,
       6,     7,     8,     9,    10,    11,    12,    13,    -1,    -1,
      16,    -1,    -1,    19,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    13,    -1,    -1,    16,    17,     4,     5,
       6,     7,     8,     9,    10,    11,    12,    13,    -1,    -1,
      16
  };

  const signed char
  parser::yystos_[] =
  {
       0,    29,    40,    63,    64,    65,    27,    42,     0,    41,
      38,    18,     4,    14,    17,    18,    22,    23,    24,    25,
      26,    32,    33,    36,    42,    43,    44,    45,    46,    47,
      48,    49,    51,    52,    54,    55,    66,    63,    42,    44,
      58,    59,    42,    43,    66,    66,    66,    66,     3,    15,
       3,    15,     3,     3,    17,    17,    17,    66,     4,     5,
       6,     7,     8,     9,    10,    11,    12,    13,    16,    17,
      53,    19,    38,    19,    20,    20,    66,    42,    66,    42,
      66,    66,    42,    66,    20,    30,    44,    41,    41,    18,
      41,    42,    21,    21,    56,    57,    66,    31,    60,    61,
      62,    20,    34,    35,    50,    19,    38,    42,    21,    38,
      41,    66,    20,    66,    18,    60,    61,    20,    41,    58,
      21,    41,    21,    19,    21,    15,    20,    50,    42,    41,
      20,    21,    41,    21
  };

  const signed char
  parser::yyr1_[] =
  {
       0,    39,    40,    41,    41,    42,    43,    44,    45,    46,
      46,    47,    47,    48,    48,    49,    50,    50,    50,    51,
      52,    52,    52,    52,    52,    52,    52,    53,    53,    53,
      53,    53,    53,    53,    53,    53,    53,    54,    54,    55,
      56,    56,    57,    57,    58,    58,    59,    59,    60,    60,
      61,    61,    62,    62,    63,    63,    64,    64,    65,    65,
      66,    66,    66,    66,    66,    66,    66,    66,    66,    66,
      66
  };

  const signed char
  parser::yyr2_[] =
  {
       0,     2,     2,     0,     2,     1,     3,     3,     3,     3,
       3,     3,     3,     2,     1,     6,     6,     4,     0,     5,
       1,     2,     2,     2,     2,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     6,
       1,     0,     1,     3,     1,     0,     1,     3,    10,     8,
       1,     0,     1,     3,     9,    11,     1,     0,     1,     3,
       1,     1,     1,     1,     1,     1,     3,     1,     1,     2,
       3
  };




#if YYDEBUG
  const short
  parser::yyrline_[] =
  {
       0,   128,   128,   135,   136,   142,   145,   149,   153,   157,
     158,   161,   162,   166,   167,   170,   174,   180,   181,   184,
     188,   189,   190,   191,   192,   193,   194,   197,   198,   199,
     200,   201,   202,   203,   204,   205,   206,   209,   210,   213,
     217,   218,   221,   223,   226,   227,   230,   232,   235,   240,
     248,   249,   252,   254,   257,   265,   276,   277,   280,   282,
     286,   287,   288,   289,   290,   291,   292,   293,   294,   295,
     296
  };

  void
  parser::yy_stack_print_ () const
  {
    *yycdebug_ << "Stack now";
    for (stack_type::const_iterator
           i = yystack_.begin (),
           i_end = yystack_.end ();
         i != i_end; ++i)
      *yycdebug_ << ' ' << int (i->state);
    *yycdebug_ << '\n';
  }

  void
  parser::yy_reduce_print_ (int yyrule) const
  {
    int yylno = yyrline_[yyrule];
    int yynrhs = yyr2_[yyrule];
    // Print the symbols being reduced, and their result.
    *yycdebug_ << "Reducing stack by rule " << yyrule - 1
               << " (line " << yylno << "):\n";
    // The symbols being reduced.
    for (int yyi = 0; yyi < yynrhs; yyi++)
      YY_SYMBOL_PRINT ("   $" << yyi + 1 << " =",
                       yystack_[(yynrhs) - (yyi + 1)]);
  }
#endif // YYDEBUG


} // yy
#line 2301 "/home/parsab/dev/Quack-v2/cmake-build-debug/Parser.cpp"

#line 299 "/home/parsab/dev/Quack-v2/src/Parser.ypp"


void yy::parser::error (const location_type& l, const std::string& m) {
  std::cerr << "error @" << l << ": " << m << "\n\n";
}
