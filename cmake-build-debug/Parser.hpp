// A Bison parser, made by GNU Bison 3.7.1.

// Skeleton interface for Bison LALR(1) parsers in C++

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


/**
 ** \file /home/parsab/dev/Quack-v2/cmake-build-debug/Parser.hpp
 ** Define the yy::parser class.
 */

// C++ LALR(1) parser skeleton written by Akim Demaille.

// DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
// especially those whose name start with YY_ or yy_.  They are
// private implementation details that can be changed or removed.

#ifndef YY_YY_HOME_PARSAB_DEV_QUACK_V2_CMAKE_BUILD_DEBUG_PARSER_HPP_INCLUDED
# define YY_YY_HOME_PARSAB_DEV_QUACK_V2_CMAKE_BUILD_DEBUG_PARSER_HPP_INCLUDED
// "%code requires" blocks.
#line 11 "/home/parsab/dev/Quack-v2/src/Parser.ypp"

  #include <string>
  #include <iostream>
  #include <memory>
  #include "AST.hpp"
  #include "Parser.hpp"

  namespace quack::parser
  {
    class ParserDriver;
  }

  using namespace quack::ast;

  // Some aliasing to improve code readability

  template <typename T> using ptr = std::unique_ptr<T>;

#line 68 "/home/parsab/dev/Quack-v2/cmake-build-debug/Parser.hpp"

# include <cassert>
# include <cstdlib> // std::abort
# include <iostream>
# include <stdexcept>
# include <string>
# include <vector>

#if defined __cplusplus
# define YY_CPLUSPLUS __cplusplus
#else
# define YY_CPLUSPLUS 199711L
#endif

// Support move semantics when possible.
#if 201103L <= YY_CPLUSPLUS
# define YY_MOVE           std::move
# define YY_MOVE_OR_COPY   move
# define YY_MOVE_REF(Type) Type&&
# define YY_RVREF(Type)    Type&&
# define YY_COPY(Type)     Type
#else
# define YY_MOVE
# define YY_MOVE_OR_COPY   copy
# define YY_MOVE_REF(Type) Type&
# define YY_RVREF(Type)    const Type&
# define YY_COPY(Type)     const Type&
#endif

// Support noexcept when possible.
#if 201103L <= YY_CPLUSPLUS
# define YY_NOEXCEPT noexcept
# define YY_NOTHROW
#else
# define YY_NOEXCEPT
# define YY_NOTHROW throw ()
#endif

// Support constexpr when possible.
#if 201703 <= YY_CPLUSPLUS
# define YY_CONSTEXPR constexpr
#else
# define YY_CONSTEXPR
#endif
# include "location.hh"
#include <typeinfo>
#ifndef YY_ASSERT
# include <cassert>
# define YY_ASSERT assert
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && ! defined __ICC && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                            \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif

namespace yy {
#line 202 "/home/parsab/dev/Quack-v2/cmake-build-debug/Parser.hpp"




  /// A Bison parser.
  class parser
  {
  public:
#ifndef YYSTYPE
  /// A buffer to store and retrieve objects.
  ///
  /// Sort of a variant, but does not keep track of the nature
  /// of the stored data, since that knowledge is available
  /// via the current parser state.
  class semantic_type
  {
  public:
    /// Type of *this.
    typedef semantic_type self_type;

    /// Empty construction.
    semantic_type () YY_NOEXCEPT
      : yybuffer_ ()
      , yytypeid_ (YY_NULLPTR)
    {}

    /// Construct and fill.
    template <typename T>
    semantic_type (YY_RVREF (T) t)
      : yytypeid_ (&typeid (T))
    {
      YY_ASSERT (sizeof (T) <= size);
      new (yyas_<T> ()) T (YY_MOVE (t));
    }

#if 201103L <= YY_CPLUSPLUS
    /// Non copyable.
    semantic_type (const self_type&) = delete;
    /// Non copyable.
    self_type& operator= (const self_type&) = delete;
#endif

    /// Destruction, allowed only if empty.
    ~semantic_type () YY_NOEXCEPT
    {
      YY_ASSERT (!yytypeid_);
    }

# if 201103L <= YY_CPLUSPLUS
    /// Instantiate a \a T in here from \a t.
    template <typename T, typename... U>
    T&
    emplace (U&&... u)
    {
      YY_ASSERT (!yytypeid_);
      YY_ASSERT (sizeof (T) <= size);
      yytypeid_ = & typeid (T);
      return *new (yyas_<T> ()) T (std::forward <U>(u)...);
    }
# else
    /// Instantiate an empty \a T in here.
    template <typename T>
    T&
    emplace ()
    {
      YY_ASSERT (!yytypeid_);
      YY_ASSERT (sizeof (T) <= size);
      yytypeid_ = & typeid (T);
      return *new (yyas_<T> ()) T ();
    }

    /// Instantiate a \a T in here from \a t.
    template <typename T>
    T&
    emplace (const T& t)
    {
      YY_ASSERT (!yytypeid_);
      YY_ASSERT (sizeof (T) <= size);
      yytypeid_ = & typeid (T);
      return *new (yyas_<T> ()) T (t);
    }
# endif

    /// Instantiate an empty \a T in here.
    /// Obsolete, use emplace.
    template <typename T>
    T&
    build ()
    {
      return emplace<T> ();
    }

    /// Instantiate a \a T in here from \a t.
    /// Obsolete, use emplace.
    template <typename T>
    T&
    build (const T& t)
    {
      return emplace<T> (t);
    }

    /// Accessor to a built \a T.
    template <typename T>
    T&
    as () YY_NOEXCEPT
    {
      YY_ASSERT (yytypeid_);
      YY_ASSERT (*yytypeid_ == typeid (T));
      YY_ASSERT (sizeof (T) <= size);
      return *yyas_<T> ();
    }

    /// Const accessor to a built \a T (for %printer).
    template <typename T>
    const T&
    as () const YY_NOEXCEPT
    {
      YY_ASSERT (yytypeid_);
      YY_ASSERT (*yytypeid_ == typeid (T));
      YY_ASSERT (sizeof (T) <= size);
      return *yyas_<T> ();
    }

    /// Swap the content with \a that, of same type.
    ///
    /// Both variants must be built beforehand, because swapping the actual
    /// data requires reading it (with as()), and this is not possible on
    /// unconstructed variants: it would require some dynamic testing, which
    /// should not be the variant's responsibility.
    /// Swapping between built and (possibly) non-built is done with
    /// self_type::move ().
    template <typename T>
    void
    swap (self_type& that) YY_NOEXCEPT
    {
      YY_ASSERT (yytypeid_);
      YY_ASSERT (*yytypeid_ == *that.yytypeid_);
      std::swap (as<T> (), that.as<T> ());
    }

    /// Move the content of \a that to this.
    ///
    /// Destroys \a that.
    template <typename T>
    void
    move (self_type& that)
    {
# if 201103L <= YY_CPLUSPLUS
      emplace<T> (std::move (that.as<T> ()));
# else
      emplace<T> ();
      swap<T> (that);
# endif
      that.destroy<T> ();
    }

# if 201103L <= YY_CPLUSPLUS
    /// Move the content of \a that to this.
    template <typename T>
    void
    move (self_type&& that)
    {
      emplace<T> (std::move (that.as<T> ()));
      that.destroy<T> ();
    }
#endif

    /// Copy the content of \a that to this.
    template <typename T>
    void
    copy (const self_type& that)
    {
      emplace<T> (that.as<T> ());
    }

    /// Destroy the stored \a T.
    template <typename T>
    void
    destroy ()
    {
      as<T> ().~T ();
      yytypeid_ = YY_NULLPTR;
    }

  private:
#if YY_CPLUSPLUS < 201103L
    /// Non copyable.
    semantic_type (const self_type&);
    /// Non copyable.
    self_type& operator= (const self_type&);
#endif

    /// Accessor to raw memory as \a T.
    template <typename T>
    T*
    yyas_ () YY_NOEXCEPT
    {
      void *yyp = yybuffer_.yyraw;
      return static_cast<T*> (yyp);
     }

    /// Const accessor to raw memory as \a T.
    template <typename T>
    const T*
    yyas_ () const YY_NOEXCEPT
    {
      const void *yyp = yybuffer_.yyraw;
      return static_cast<const T*> (yyp);
     }

    /// An auxiliary type to compute the largest semantic type.
    union union_type
    {
      // binaryOperator
      char dummy1[sizeof (BinaryOperator::Operator)];

      // unaryOperator
      char dummy2[sizeof (UnaryOperator::Operator)];

      // BOOL
      char dummy3[sizeof (bool)];

      // FLOAT
      char dummy4[sizeof (double)];

      // INT
      char dummy5[sizeof (long)];

      // args
      // argsNonEmpty
      char dummy6[sizeof (ptr<Arguments>)];

      // assignment
      char dummy7[sizeof (ptr<Assignment>)];

      // call
      char dummy8[sizeof (ptr<Call>)];

      // class
      char dummy9[sizeof (ptr<Class>)];

      // classes
      // classesNonEmpty
      char dummy10[sizeof (ptr<Classes>)];

      // compoundStmt
      // optElseIf
      char dummy11[sizeof (ptr<CompoundStmt>)];

      // expression
      char dummy12[sizeof (ptr<Expression>)];

      // identifier
      char dummy13[sizeof (ptr<Identifier>)];

      // ifStmt
      char dummy14[sizeof (ptr<If>)];

      // memberAccess
      char dummy15[sizeof (ptr<MemberAccess>)];

      // method
      char dummy16[sizeof (ptr<Method>)];

      // methods
      // methodsNonEmpty
      char dummy17[sizeof (ptr<Methods>)];

      // params
      // paramsNonEmpty
      char dummy18[sizeof (ptr<Parameters>)];

      // returnStmt
      char dummy19[sizeof (ptr<Return>)];

      // statement
      char dummy20[sizeof (ptr<Statement>)];

      // staticAssignment
      char dummy21[sizeof (ptr<StaticAssignment>)];

      // memberDecl
      char dummy22[sizeof (ptr<StaticMemberDecl>)];

      // translationUnit
      char dummy23[sizeof (ptr<TranslationUnit>)];

      // varDecl
      char dummy24[sizeof (ptr<VarDecl>)];

      // whileStmt
      char dummy25[sizeof (ptr<While>)];

      // STRING_LIT
      // THIS
      // IDENT
      // WEAK
      // CLASS
      // EXTENDS
      // DEF
      // RETURN
      // IF
      // ELIF
      // ELSE
      // WHILE
      char dummy26[sizeof (std::string)];
    };

    /// The size of the largest semantic type.
    enum { size = sizeof (union_type) };

    /// A buffer to store semantic values.
    union
    {
      /// Strongest alignment constraints.
      long double yyalign_me;
      /// A buffer large enough to store any of the semantic values.
      char yyraw[size];
    } yybuffer_;

    /// Whether the content is built: if defined, the name of the stored type.
    const std::type_info *yytypeid_;
  };

#else
    typedef YYSTYPE semantic_type;
#endif
    /// Symbol locations.
    typedef location location_type;

    /// Syntax errors thrown from user actions.
    struct syntax_error : std::runtime_error
    {
      syntax_error (const location_type& l, const std::string& m)
        : std::runtime_error (m)
        , location (l)
      {}

      syntax_error (const syntax_error& s)
        : std::runtime_error (s.what ())
        , location (s.location)
      {}

      ~syntax_error () YY_NOEXCEPT YY_NOTHROW;

      location_type location;
    };

    /// Token kinds.
    struct token
    {
      enum token_kind_type
      {
        TOK_YYEMPTY = -2,
    TOK_YYEOF = 0,                 // "end of file"
    TOK_YYerror = 1,               // error
    TOK_YYUNDEF = 2,               // "invalid token"
    TOK_ASSIGN = 3,                // "="
    TOK_MINUS = 4,                 // "-"
    TOK_PLUS = 5,                  // "+"
    TOK_STAR = 6,                  // "*"
    TOK_SLASH = 7,                 // "/"
    TOK_MOD = 8,                   // "%"
    TOK_LESS = 9,                  // "<"
    TOK_MORE = 10,                 // ">"
    TOK_LESSEQ = 11,               // "<="
    TOK_MOREEQ = 12,               // ">="
    TOK_EQUAL = 13,                // "=="
    TOK_NEG = 14,                  // "!"
    TOK_COLON = 15,                // ":"
    TOK_DOT = 16,                  // "."
    TOK_SEMICOLON = 17,            // ";"
    TOK_LPAREN = 18,               // "("
    TOK_RPAREN = 19,               // ")"
    TOK_LBRACK = 20,               // "{"
    TOK_RBRACK = 21,               // "}"
    TOK_INT = 22,                  // INT
    TOK_FLOAT = 23,                // FLOAT
    TOK_BOOL = 24,                 // BOOL
    TOK_STRING_LIT = 25,           // STRING_LIT
    TOK_THIS = 26,                 // THIS
    TOK_IDENT = 27,                // IDENT
    TOK_WEAK = 28,                 // WEAK
    TOK_CLASS = 29,                // CLASS
    TOK_EXTENDS = 30,              // EXTENDS
    TOK_DEF = 31,                  // DEF
    TOK_RETURN = 32,               // RETURN
    TOK_IF = 33,                   // IF
    TOK_ELIF = 34,                 // ELIF
    TOK_ELSE = 35,                 // ELSE
    TOK_WHILE = 36,                // WHILE
    TOK_UMINUS = 37                // UMINUS
      };
      /// Backward compatibility alias (Bison 3.6).
      typedef token_kind_type yytokentype;
    };

    /// Token kind, as returned by yylex.
    typedef token::yytokentype token_kind_type;

    /// Backward compatibility alias (Bison 3.6).
    typedef token_kind_type token_type;

    /// Symbol kinds.
    struct symbol_kind
    {
      enum symbol_kind_type
      {
        YYNTOKENS = 39, ///< Number of tokens.
        S_YYEMPTY = -2,
        S_YYEOF = 0,                             // "end of file"
        S_YYerror = 1,                           // error
        S_YYUNDEF = 2,                           // "invalid token"
        S_ASSIGN = 3,                            // "="
        S_MINUS = 4,                             // "-"
        S_PLUS = 5,                              // "+"
        S_STAR = 6,                              // "*"
        S_SLASH = 7,                             // "/"
        S_MOD = 8,                               // "%"
        S_LESS = 9,                              // "<"
        S_MORE = 10,                             // ">"
        S_LESSEQ = 11,                           // "<="
        S_MOREEQ = 12,                           // ">="
        S_EQUAL = 13,                            // "=="
        S_NEG = 14,                              // "!"
        S_COLON = 15,                            // ":"
        S_DOT = 16,                              // "."
        S_SEMICOLON = 17,                        // ";"
        S_LPAREN = 18,                           // "("
        S_RPAREN = 19,                           // ")"
        S_LBRACK = 20,                           // "{"
        S_RBRACK = 21,                           // "}"
        S_INT = 22,                              // INT
        S_FLOAT = 23,                            // FLOAT
        S_BOOL = 24,                             // BOOL
        S_STRING_LIT = 25,                       // STRING_LIT
        S_THIS = 26,                             // THIS
        S_IDENT = 27,                            // IDENT
        S_WEAK = 28,                             // WEAK
        S_CLASS = 29,                            // CLASS
        S_EXTENDS = 30,                          // EXTENDS
        S_DEF = 31,                              // DEF
        S_RETURN = 32,                           // RETURN
        S_IF = 33,                               // IF
        S_ELIF = 34,                             // ELIF
        S_ELSE = 35,                             // ELSE
        S_WHILE = 36,                            // WHILE
        S_UMINUS = 37,                           // UMINUS
        S_38_ = 38,                              // ","
        S_YYACCEPT = 39,                         // $accept
        S_translationUnit = 40,                  // translationUnit
        S_compoundStmt = 41,                     // compoundStmt
        S_identifier = 42,                       // identifier
        S_memberAccess = 43,                     // memberAccess
        S_varDecl = 44,                          // varDecl
        S_memberDecl = 45,                       // memberDecl
        S_staticAssignment = 46,                 // staticAssignment
        S_assignment = 47,                       // assignment
        S_returnStmt = 48,                       // returnStmt
        S_ifStmt = 49,                           // ifStmt
        S_optElseIf = 50,                        // optElseIf
        S_whileStmt = 51,                        // whileStmt
        S_statement = 52,                        // statement
        S_binaryOperator = 53,                   // binaryOperator
        S_unaryOperator = 54,                    // unaryOperator
        S_call = 55,                             // call
        S_args = 56,                             // args
        S_argsNonEmpty = 57,                     // argsNonEmpty
        S_params = 58,                           // params
        S_paramsNonEmpty = 59,                   // paramsNonEmpty
        S_method = 60,                           // method
        S_methods = 61,                          // methods
        S_methodsNonEmpty = 62,                  // methodsNonEmpty
        S_class = 63,                            // class
        S_classes = 64,                          // classes
        S_classesNonEmpty = 65,                  // classesNonEmpty
        S_expression = 66                        // expression
      };
    };

    /// (Internal) symbol kind.
    typedef symbol_kind::symbol_kind_type symbol_kind_type;

    /// The number of tokens.
    static const symbol_kind_type YYNTOKENS = symbol_kind::YYNTOKENS;

    /// A complete symbol.
    ///
    /// Expects its Base type to provide access to the symbol kind
    /// via kind ().
    ///
    /// Provide access to semantic value and location.
    template <typename Base>
    struct basic_symbol : Base
    {
      /// Alias to Base.
      typedef Base super_type;

      /// Default constructor.
      basic_symbol ()
        : value ()
        , location ()
      {}

#if 201103L <= YY_CPLUSPLUS
      /// Move constructor.
      basic_symbol (basic_symbol&& that)
        : Base (std::move (that))
        , value ()
        , location (std::move (that.location))
      {
        switch (this->kind ())
    {
      case symbol_kind::S_binaryOperator: // binaryOperator
        value.move< BinaryOperator::Operator > (std::move (that.value));
        break;

      case symbol_kind::S_unaryOperator: // unaryOperator
        value.move< UnaryOperator::Operator > (std::move (that.value));
        break;

      case symbol_kind::S_BOOL: // BOOL
        value.move< bool > (std::move (that.value));
        break;

      case symbol_kind::S_FLOAT: // FLOAT
        value.move< double > (std::move (that.value));
        break;

      case symbol_kind::S_INT: // INT
        value.move< long > (std::move (that.value));
        break;

      case symbol_kind::S_args: // args
      case symbol_kind::S_argsNonEmpty: // argsNonEmpty
        value.move< ptr<Arguments> > (std::move (that.value));
        break;

      case symbol_kind::S_assignment: // assignment
        value.move< ptr<Assignment> > (std::move (that.value));
        break;

      case symbol_kind::S_call: // call
        value.move< ptr<Call> > (std::move (that.value));
        break;

      case symbol_kind::S_class: // class
        value.move< ptr<Class> > (std::move (that.value));
        break;

      case symbol_kind::S_classes: // classes
      case symbol_kind::S_classesNonEmpty: // classesNonEmpty
        value.move< ptr<Classes> > (std::move (that.value));
        break;

      case symbol_kind::S_compoundStmt: // compoundStmt
      case symbol_kind::S_optElseIf: // optElseIf
        value.move< ptr<CompoundStmt> > (std::move (that.value));
        break;

      case symbol_kind::S_expression: // expression
        value.move< ptr<Expression> > (std::move (that.value));
        break;

      case symbol_kind::S_identifier: // identifier
        value.move< ptr<Identifier> > (std::move (that.value));
        break;

      case symbol_kind::S_ifStmt: // ifStmt
        value.move< ptr<If> > (std::move (that.value));
        break;

      case symbol_kind::S_memberAccess: // memberAccess
        value.move< ptr<MemberAccess> > (std::move (that.value));
        break;

      case symbol_kind::S_method: // method
        value.move< ptr<Method> > (std::move (that.value));
        break;

      case symbol_kind::S_methods: // methods
      case symbol_kind::S_methodsNonEmpty: // methodsNonEmpty
        value.move< ptr<Methods> > (std::move (that.value));
        break;

      case symbol_kind::S_params: // params
      case symbol_kind::S_paramsNonEmpty: // paramsNonEmpty
        value.move< ptr<Parameters> > (std::move (that.value));
        break;

      case symbol_kind::S_returnStmt: // returnStmt
        value.move< ptr<Return> > (std::move (that.value));
        break;

      case symbol_kind::S_statement: // statement
        value.move< ptr<Statement> > (std::move (that.value));
        break;

      case symbol_kind::S_staticAssignment: // staticAssignment
        value.move< ptr<StaticAssignment> > (std::move (that.value));
        break;

      case symbol_kind::S_memberDecl: // memberDecl
        value.move< ptr<StaticMemberDecl> > (std::move (that.value));
        break;

      case symbol_kind::S_translationUnit: // translationUnit
        value.move< ptr<TranslationUnit> > (std::move (that.value));
        break;

      case symbol_kind::S_varDecl: // varDecl
        value.move< ptr<VarDecl> > (std::move (that.value));
        break;

      case symbol_kind::S_whileStmt: // whileStmt
        value.move< ptr<While> > (std::move (that.value));
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
        value.move< std::string > (std::move (that.value));
        break;

      default:
        break;
    }

      }
#endif

      /// Copy constructor.
      basic_symbol (const basic_symbol& that);

      /// Constructor for valueless symbols, and symbols from each type.
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, location_type&& l)
        : Base (t)
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const location_type& l)
        : Base (t)
        , location (l)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, BinaryOperator::Operator&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const BinaryOperator::Operator& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, UnaryOperator::Operator&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const UnaryOperator::Operator& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, bool&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const bool& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, double&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const double& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, long&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const long& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, ptr<Arguments>&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const ptr<Arguments>& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, ptr<Assignment>&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const ptr<Assignment>& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, ptr<Call>&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const ptr<Call>& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, ptr<Class>&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const ptr<Class>& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, ptr<Classes>&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const ptr<Classes>& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, ptr<CompoundStmt>&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const ptr<CompoundStmt>& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, ptr<Expression>&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const ptr<Expression>& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, ptr<Identifier>&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const ptr<Identifier>& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, ptr<If>&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const ptr<If>& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, ptr<MemberAccess>&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const ptr<MemberAccess>& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, ptr<Method>&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const ptr<Method>& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, ptr<Methods>&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const ptr<Methods>& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, ptr<Parameters>&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const ptr<Parameters>& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, ptr<Return>&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const ptr<Return>& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, ptr<Statement>&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const ptr<Statement>& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, ptr<StaticAssignment>&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const ptr<StaticAssignment>& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, ptr<StaticMemberDecl>&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const ptr<StaticMemberDecl>& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, ptr<TranslationUnit>&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const ptr<TranslationUnit>& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, ptr<VarDecl>&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const ptr<VarDecl>& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, ptr<While>&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const ptr<While>& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, std::string&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const std::string& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

      /// Destroy the symbol.
      ~basic_symbol ()
      {
        clear ();
      }

      /// Destroy contents, and record that is empty.
      void clear ()
      {
        // User destructor.
        symbol_kind_type yykind = this->kind ();
        basic_symbol<Base>& yysym = *this;
        (void) yysym;
        switch (yykind)
        {
       default:
          break;
        }

        // Value type destructor.
switch (yykind)
    {
      case symbol_kind::S_binaryOperator: // binaryOperator
        value.template destroy< BinaryOperator::Operator > ();
        break;

      case symbol_kind::S_unaryOperator: // unaryOperator
        value.template destroy< UnaryOperator::Operator > ();
        break;

      case symbol_kind::S_BOOL: // BOOL
        value.template destroy< bool > ();
        break;

      case symbol_kind::S_FLOAT: // FLOAT
        value.template destroy< double > ();
        break;

      case symbol_kind::S_INT: // INT
        value.template destroy< long > ();
        break;

      case symbol_kind::S_args: // args
      case symbol_kind::S_argsNonEmpty: // argsNonEmpty
        value.template destroy< ptr<Arguments> > ();
        break;

      case symbol_kind::S_assignment: // assignment
        value.template destroy< ptr<Assignment> > ();
        break;

      case symbol_kind::S_call: // call
        value.template destroy< ptr<Call> > ();
        break;

      case symbol_kind::S_class: // class
        value.template destroy< ptr<Class> > ();
        break;

      case symbol_kind::S_classes: // classes
      case symbol_kind::S_classesNonEmpty: // classesNonEmpty
        value.template destroy< ptr<Classes> > ();
        break;

      case symbol_kind::S_compoundStmt: // compoundStmt
      case symbol_kind::S_optElseIf: // optElseIf
        value.template destroy< ptr<CompoundStmt> > ();
        break;

      case symbol_kind::S_expression: // expression
        value.template destroy< ptr<Expression> > ();
        break;

      case symbol_kind::S_identifier: // identifier
        value.template destroy< ptr<Identifier> > ();
        break;

      case symbol_kind::S_ifStmt: // ifStmt
        value.template destroy< ptr<If> > ();
        break;

      case symbol_kind::S_memberAccess: // memberAccess
        value.template destroy< ptr<MemberAccess> > ();
        break;

      case symbol_kind::S_method: // method
        value.template destroy< ptr<Method> > ();
        break;

      case symbol_kind::S_methods: // methods
      case symbol_kind::S_methodsNonEmpty: // methodsNonEmpty
        value.template destroy< ptr<Methods> > ();
        break;

      case symbol_kind::S_params: // params
      case symbol_kind::S_paramsNonEmpty: // paramsNonEmpty
        value.template destroy< ptr<Parameters> > ();
        break;

      case symbol_kind::S_returnStmt: // returnStmt
        value.template destroy< ptr<Return> > ();
        break;

      case symbol_kind::S_statement: // statement
        value.template destroy< ptr<Statement> > ();
        break;

      case symbol_kind::S_staticAssignment: // staticAssignment
        value.template destroy< ptr<StaticAssignment> > ();
        break;

      case symbol_kind::S_memberDecl: // memberDecl
        value.template destroy< ptr<StaticMemberDecl> > ();
        break;

      case symbol_kind::S_translationUnit: // translationUnit
        value.template destroy< ptr<TranslationUnit> > ();
        break;

      case symbol_kind::S_varDecl: // varDecl
        value.template destroy< ptr<VarDecl> > ();
        break;

      case symbol_kind::S_whileStmt: // whileStmt
        value.template destroy< ptr<While> > ();
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
        value.template destroy< std::string > ();
        break;

      default:
        break;
    }

        Base::clear ();
      }

      /// The user-facing name of this symbol.
      const char *name () const YY_NOEXCEPT
      {
        return parser::symbol_name (this->kind ());
      }

      /// Backward compatibility (Bison 3.6).
      symbol_kind_type type_get () const YY_NOEXCEPT;

      /// Whether empty.
      bool empty () const YY_NOEXCEPT;

      /// Destructive move, \a s is emptied into this.
      void move (basic_symbol& s);

      /// The semantic value.
      semantic_type value;

      /// The location.
      location_type location;

    private:
#if YY_CPLUSPLUS < 201103L
      /// Assignment operator.
      basic_symbol& operator= (const basic_symbol& that);
#endif
    };

    /// Type access provider for token (enum) based symbols.
    struct by_kind
    {
      /// Default constructor.
      by_kind ();

#if 201103L <= YY_CPLUSPLUS
      /// Move constructor.
      by_kind (by_kind&& that);
#endif

      /// Copy constructor.
      by_kind (const by_kind& that);

      /// The symbol kind as needed by the constructor.
      typedef token_kind_type kind_type;

      /// Constructor from (external) token numbers.
      by_kind (kind_type t);

      /// Record that this symbol is empty.
      void clear ();

      /// Steal the symbol kind from \a that.
      void move (by_kind& that);

      /// The (internal) type number (corresponding to \a type).
      /// \a empty when empty.
      symbol_kind_type kind () const YY_NOEXCEPT;

      /// Backward compatibility (Bison 3.6).
      symbol_kind_type type_get () const YY_NOEXCEPT;

      /// The symbol kind.
      /// \a S_YYEMPTY when empty.
      symbol_kind_type kind_;
    };

    /// Backward compatibility for a private implementation detail (Bison 3.6).
    typedef by_kind by_type;

    /// "External" symbols: returned by the scanner.
    struct symbol_type : basic_symbol<by_kind>
    {
      /// Superclass.
      typedef basic_symbol<by_kind> super_type;

      /// Empty symbol.
      symbol_type () {}

      /// Constructor for valueless symbols, and symbols from each type.
#if 201103L <= YY_CPLUSPLUS
      symbol_type (int tok, location_type l)
        : super_type(token_type (tok), std::move (l))
      {
        YY_ASSERT (tok == token::TOK_YYEOF || tok == token::TOK_YYerror || tok == token::TOK_YYUNDEF || tok == token::TOK_ASSIGN || tok == token::TOK_MINUS || tok == token::TOK_PLUS || tok == token::TOK_STAR || tok == token::TOK_SLASH || tok == token::TOK_MOD || tok == token::TOK_LESS || tok == token::TOK_MORE || tok == token::TOK_LESSEQ || tok == token::TOK_MOREEQ || tok == token::TOK_EQUAL || tok == token::TOK_NEG || tok == token::TOK_COLON || tok == token::TOK_DOT || tok == token::TOK_SEMICOLON || tok == token::TOK_LPAREN || tok == token::TOK_RPAREN || tok == token::TOK_LBRACK || tok == token::TOK_RBRACK || tok == token::TOK_UMINUS || tok == 293);
      }
#else
      symbol_type (int tok, const location_type& l)
        : super_type(token_type (tok), l)
      {
        YY_ASSERT (tok == token::TOK_YYEOF || tok == token::TOK_YYerror || tok == token::TOK_YYUNDEF || tok == token::TOK_ASSIGN || tok == token::TOK_MINUS || tok == token::TOK_PLUS || tok == token::TOK_STAR || tok == token::TOK_SLASH || tok == token::TOK_MOD || tok == token::TOK_LESS || tok == token::TOK_MORE || tok == token::TOK_LESSEQ || tok == token::TOK_MOREEQ || tok == token::TOK_EQUAL || tok == token::TOK_NEG || tok == token::TOK_COLON || tok == token::TOK_DOT || tok == token::TOK_SEMICOLON || tok == token::TOK_LPAREN || tok == token::TOK_RPAREN || tok == token::TOK_LBRACK || tok == token::TOK_RBRACK || tok == token::TOK_UMINUS || tok == 293);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      symbol_type (int tok, bool v, location_type l)
        : super_type(token_type (tok), std::move (v), std::move (l))
      {
        YY_ASSERT (tok == token::TOK_BOOL);
      }
#else
      symbol_type (int tok, const bool& v, const location_type& l)
        : super_type(token_type (tok), v, l)
      {
        YY_ASSERT (tok == token::TOK_BOOL);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      symbol_type (int tok, double v, location_type l)
        : super_type(token_type (tok), std::move (v), std::move (l))
      {
        YY_ASSERT (tok == token::TOK_FLOAT);
      }
#else
      symbol_type (int tok, const double& v, const location_type& l)
        : super_type(token_type (tok), v, l)
      {
        YY_ASSERT (tok == token::TOK_FLOAT);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      symbol_type (int tok, long v, location_type l)
        : super_type(token_type (tok), std::move (v), std::move (l))
      {
        YY_ASSERT (tok == token::TOK_INT);
      }
#else
      symbol_type (int tok, const long& v, const location_type& l)
        : super_type(token_type (tok), v, l)
      {
        YY_ASSERT (tok == token::TOK_INT);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      symbol_type (int tok, std::string v, location_type l)
        : super_type(token_type (tok), std::move (v), std::move (l))
      {
        YY_ASSERT (tok == token::TOK_STRING_LIT || tok == token::TOK_THIS || tok == token::TOK_IDENT || tok == token::TOK_WEAK || tok == token::TOK_CLASS || tok == token::TOK_EXTENDS || tok == token::TOK_DEF || tok == token::TOK_RETURN || tok == token::TOK_IF || tok == token::TOK_ELIF || tok == token::TOK_ELSE || tok == token::TOK_WHILE);
      }
#else
      symbol_type (int tok, const std::string& v, const location_type& l)
        : super_type(token_type (tok), v, l)
      {
        YY_ASSERT (tok == token::TOK_STRING_LIT || tok == token::TOK_THIS || tok == token::TOK_IDENT || tok == token::TOK_WEAK || tok == token::TOK_CLASS || tok == token::TOK_EXTENDS || tok == token::TOK_DEF || tok == token::TOK_RETURN || tok == token::TOK_IF || tok == token::TOK_ELIF || tok == token::TOK_ELSE || tok == token::TOK_WHILE);
      }
#endif
    };

    /// Build a parser object.
    parser (quack::parser::ParserDriver& drv_yyarg);
    virtual ~parser ();

#if 201103L <= YY_CPLUSPLUS
    /// Non copyable.
    parser (const parser&) = delete;
    /// Non copyable.
    parser& operator= (const parser&) = delete;
#endif

    /// Parse.  An alias for parse ().
    /// \returns  0 iff parsing succeeded.
    int operator() ();

    /// Parse.
    /// \returns  0 iff parsing succeeded.
    virtual int parse ();

#if YYDEBUG
    /// The current debugging stream.
    std::ostream& debug_stream () const YY_ATTRIBUTE_PURE;
    /// Set the current debugging stream.
    void set_debug_stream (std::ostream &);

    /// Type for debugging levels.
    typedef int debug_level_type;
    /// The current debugging level.
    debug_level_type debug_level () const YY_ATTRIBUTE_PURE;
    /// Set the current debugging level.
    void set_debug_level (debug_level_type l);
#endif

    /// Report a syntax error.
    /// \param loc    where the syntax error is found.
    /// \param msg    a description of the syntax error.
    virtual void error (const location_type& loc, const std::string& msg);

    /// Report a syntax error.
    void error (const syntax_error& err);

    /// The user-facing name of the symbol whose (internal) number is
    /// YYSYMBOL.  No bounds checking.
    static const char *symbol_name (symbol_kind_type yysymbol);

    // Implementation of make_symbol for each symbol type.
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_YYEOF (location_type l)
      {
        return symbol_type (token::TOK_YYEOF, std::move (l));
      }
#else
      static
      symbol_type
      make_YYEOF (const location_type& l)
      {
        return symbol_type (token::TOK_YYEOF, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_YYerror (location_type l)
      {
        return symbol_type (token::TOK_YYerror, std::move (l));
      }
#else
      static
      symbol_type
      make_YYerror (const location_type& l)
      {
        return symbol_type (token::TOK_YYerror, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_YYUNDEF (location_type l)
      {
        return symbol_type (token::TOK_YYUNDEF, std::move (l));
      }
#else
      static
      symbol_type
      make_YYUNDEF (const location_type& l)
      {
        return symbol_type (token::TOK_YYUNDEF, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_ASSIGN (location_type l)
      {
        return symbol_type (token::TOK_ASSIGN, std::move (l));
      }
#else
      static
      symbol_type
      make_ASSIGN (const location_type& l)
      {
        return symbol_type (token::TOK_ASSIGN, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_MINUS (location_type l)
      {
        return symbol_type (token::TOK_MINUS, std::move (l));
      }
#else
      static
      symbol_type
      make_MINUS (const location_type& l)
      {
        return symbol_type (token::TOK_MINUS, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_PLUS (location_type l)
      {
        return symbol_type (token::TOK_PLUS, std::move (l));
      }
#else
      static
      symbol_type
      make_PLUS (const location_type& l)
      {
        return symbol_type (token::TOK_PLUS, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_STAR (location_type l)
      {
        return symbol_type (token::TOK_STAR, std::move (l));
      }
#else
      static
      symbol_type
      make_STAR (const location_type& l)
      {
        return symbol_type (token::TOK_STAR, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_SLASH (location_type l)
      {
        return symbol_type (token::TOK_SLASH, std::move (l));
      }
#else
      static
      symbol_type
      make_SLASH (const location_type& l)
      {
        return symbol_type (token::TOK_SLASH, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_MOD (location_type l)
      {
        return symbol_type (token::TOK_MOD, std::move (l));
      }
#else
      static
      symbol_type
      make_MOD (const location_type& l)
      {
        return symbol_type (token::TOK_MOD, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_LESS (location_type l)
      {
        return symbol_type (token::TOK_LESS, std::move (l));
      }
#else
      static
      symbol_type
      make_LESS (const location_type& l)
      {
        return symbol_type (token::TOK_LESS, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_MORE (location_type l)
      {
        return symbol_type (token::TOK_MORE, std::move (l));
      }
#else
      static
      symbol_type
      make_MORE (const location_type& l)
      {
        return symbol_type (token::TOK_MORE, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_LESSEQ (location_type l)
      {
        return symbol_type (token::TOK_LESSEQ, std::move (l));
      }
#else
      static
      symbol_type
      make_LESSEQ (const location_type& l)
      {
        return symbol_type (token::TOK_LESSEQ, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_MOREEQ (location_type l)
      {
        return symbol_type (token::TOK_MOREEQ, std::move (l));
      }
#else
      static
      symbol_type
      make_MOREEQ (const location_type& l)
      {
        return symbol_type (token::TOK_MOREEQ, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_EQUAL (location_type l)
      {
        return symbol_type (token::TOK_EQUAL, std::move (l));
      }
#else
      static
      symbol_type
      make_EQUAL (const location_type& l)
      {
        return symbol_type (token::TOK_EQUAL, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_NEG (location_type l)
      {
        return symbol_type (token::TOK_NEG, std::move (l));
      }
#else
      static
      symbol_type
      make_NEG (const location_type& l)
      {
        return symbol_type (token::TOK_NEG, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_COLON (location_type l)
      {
        return symbol_type (token::TOK_COLON, std::move (l));
      }
#else
      static
      symbol_type
      make_COLON (const location_type& l)
      {
        return symbol_type (token::TOK_COLON, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_DOT (location_type l)
      {
        return symbol_type (token::TOK_DOT, std::move (l));
      }
#else
      static
      symbol_type
      make_DOT (const location_type& l)
      {
        return symbol_type (token::TOK_DOT, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_SEMICOLON (location_type l)
      {
        return symbol_type (token::TOK_SEMICOLON, std::move (l));
      }
#else
      static
      symbol_type
      make_SEMICOLON (const location_type& l)
      {
        return symbol_type (token::TOK_SEMICOLON, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_LPAREN (location_type l)
      {
        return symbol_type (token::TOK_LPAREN, std::move (l));
      }
#else
      static
      symbol_type
      make_LPAREN (const location_type& l)
      {
        return symbol_type (token::TOK_LPAREN, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_RPAREN (location_type l)
      {
        return symbol_type (token::TOK_RPAREN, std::move (l));
      }
#else
      static
      symbol_type
      make_RPAREN (const location_type& l)
      {
        return symbol_type (token::TOK_RPAREN, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_LBRACK (location_type l)
      {
        return symbol_type (token::TOK_LBRACK, std::move (l));
      }
#else
      static
      symbol_type
      make_LBRACK (const location_type& l)
      {
        return symbol_type (token::TOK_LBRACK, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_RBRACK (location_type l)
      {
        return symbol_type (token::TOK_RBRACK, std::move (l));
      }
#else
      static
      symbol_type
      make_RBRACK (const location_type& l)
      {
        return symbol_type (token::TOK_RBRACK, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_INT (long v, location_type l)
      {
        return symbol_type (token::TOK_INT, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_INT (const long& v, const location_type& l)
      {
        return symbol_type (token::TOK_INT, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_FLOAT (double v, location_type l)
      {
        return symbol_type (token::TOK_FLOAT, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_FLOAT (const double& v, const location_type& l)
      {
        return symbol_type (token::TOK_FLOAT, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_BOOL (bool v, location_type l)
      {
        return symbol_type (token::TOK_BOOL, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_BOOL (const bool& v, const location_type& l)
      {
        return symbol_type (token::TOK_BOOL, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_STRING_LIT (std::string v, location_type l)
      {
        return symbol_type (token::TOK_STRING_LIT, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_STRING_LIT (const std::string& v, const location_type& l)
      {
        return symbol_type (token::TOK_STRING_LIT, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_THIS (std::string v, location_type l)
      {
        return symbol_type (token::TOK_THIS, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_THIS (const std::string& v, const location_type& l)
      {
        return symbol_type (token::TOK_THIS, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_IDENT (std::string v, location_type l)
      {
        return symbol_type (token::TOK_IDENT, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_IDENT (const std::string& v, const location_type& l)
      {
        return symbol_type (token::TOK_IDENT, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_WEAK (std::string v, location_type l)
      {
        return symbol_type (token::TOK_WEAK, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_WEAK (const std::string& v, const location_type& l)
      {
        return symbol_type (token::TOK_WEAK, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_CLASS (std::string v, location_type l)
      {
        return symbol_type (token::TOK_CLASS, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_CLASS (const std::string& v, const location_type& l)
      {
        return symbol_type (token::TOK_CLASS, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_EXTENDS (std::string v, location_type l)
      {
        return symbol_type (token::TOK_EXTENDS, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_EXTENDS (const std::string& v, const location_type& l)
      {
        return symbol_type (token::TOK_EXTENDS, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_DEF (std::string v, location_type l)
      {
        return symbol_type (token::TOK_DEF, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_DEF (const std::string& v, const location_type& l)
      {
        return symbol_type (token::TOK_DEF, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_RETURN (std::string v, location_type l)
      {
        return symbol_type (token::TOK_RETURN, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_RETURN (const std::string& v, const location_type& l)
      {
        return symbol_type (token::TOK_RETURN, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_IF (std::string v, location_type l)
      {
        return symbol_type (token::TOK_IF, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_IF (const std::string& v, const location_type& l)
      {
        return symbol_type (token::TOK_IF, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_ELIF (std::string v, location_type l)
      {
        return symbol_type (token::TOK_ELIF, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_ELIF (const std::string& v, const location_type& l)
      {
        return symbol_type (token::TOK_ELIF, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_ELSE (std::string v, location_type l)
      {
        return symbol_type (token::TOK_ELSE, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_ELSE (const std::string& v, const location_type& l)
      {
        return symbol_type (token::TOK_ELSE, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_WHILE (std::string v, location_type l)
      {
        return symbol_type (token::TOK_WHILE, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_WHILE (const std::string& v, const location_type& l)
      {
        return symbol_type (token::TOK_WHILE, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_UMINUS (location_type l)
      {
        return symbol_type (token::TOK_UMINUS, std::move (l));
      }
#else
      static
      symbol_type
      make_UMINUS (const location_type& l)
      {
        return symbol_type (token::TOK_UMINUS, l);
      }
#endif


    class context
    {
    public:
      context (const parser& yyparser, const symbol_type& yyla);
      const symbol_type& lookahead () const { return yyla_; }
      symbol_kind_type token () const { return yyla_.kind (); }
      const location_type& location () const { return yyla_.location; }

      /// Put in YYARG at most YYARGN of the expected tokens, and return the
      /// number of tokens stored in YYARG.  If YYARG is null, return the
      /// number of expected tokens (guaranteed to be less than YYNTOKENS).
      int expected_tokens (symbol_kind_type yyarg[], int yyargn) const;

    private:
      const parser& yyparser_;
      const symbol_type& yyla_;
    };

  private:
#if YY_CPLUSPLUS < 201103L
    /// Non copyable.
    parser (const parser&);
    /// Non copyable.
    parser& operator= (const parser&);
#endif

    /// Check the lookahead yytoken.
    /// \returns  true iff the token will be eventually shifted.
    bool yy_lac_check_ (symbol_kind_type yytoken) const;
    /// Establish the initial context if no initial context currently exists.
    /// \returns  true iff the token will be eventually shifted.
    bool yy_lac_establish_ (symbol_kind_type yytoken);
    /// Discard any previous initial lookahead context because of event.
    /// \param event  the event which caused the lookahead to be discarded.
    ///               Only used for debbuging output.
    void yy_lac_discard_ (const char* event);

    /// Stored state numbers (used for stacks).
    typedef unsigned char state_type;

    /// The arguments of the error message.
    int yy_syntax_error_arguments_ (const context& yyctx,
                                    symbol_kind_type yyarg[], int yyargn) const;

    /// Generate an error message.
    /// \param yyctx     the context in which the error occurred.
    virtual std::string yysyntax_error_ (const context& yyctx) const;
    /// Compute post-reduction state.
    /// \param yystate   the current state
    /// \param yysym     the nonterminal to push on the stack
    static state_type yy_lr_goto_state_ (state_type yystate, int yysym);

    /// Whether the given \c yypact_ value indicates a defaulted state.
    /// \param yyvalue   the value to check
    static bool yy_pact_value_is_default_ (int yyvalue);

    /// Whether the given \c yytable_ value indicates a syntax error.
    /// \param yyvalue   the value to check
    static bool yy_table_value_is_error_ (int yyvalue);

    static const signed char yypact_ninf_;
    static const signed char yytable_ninf_;

    /// Convert a scanner token kind \a t to a symbol kind.
    /// In theory \a t should be a token_kind_type, but character literals
    /// are valid, yet not members of the token_type enum.
    static symbol_kind_type yytranslate_ (int t);



    // Tables.
    // YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
    // STATE-NUM.
    static const short yypact_[];

    // YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
    // Performed when YYTABLE does not specify something else to do.  Zero
    // means the default is an error.
    static const signed char yydefact_[];

    // YYPGOTO[NTERM-NUM].
    static const signed char yypgoto_[];

    // YYDEFGOTO[NTERM-NUM].
    static const signed char yydefgoto_[];

    // YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
    // positive, shift that token.  If negative, reduce the rule whose
    // number is the opposite.  If YYTABLE_NINF, syntax error.
    static const unsigned char yytable_[];

    static const short yycheck_[];

    // YYSTOS[STATE-NUM] -- The (internal number of the) accessing
    // symbol of state STATE-NUM.
    static const signed char yystos_[];

    // YYR1[YYN] -- Symbol number of symbol that rule YYN derives.
    static const signed char yyr1_[];

    // YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.
    static const signed char yyr2_[];


#if YYDEBUG
    // YYRLINE[YYN] -- Source line where rule number YYN was defined.
    static const short yyrline_[];
    /// Report on the debug stream that the rule \a r is going to be reduced.
    virtual void yy_reduce_print_ (int r) const;
    /// Print the state stack on the debug stream.
    virtual void yy_stack_print_ () const;

    /// Debugging level.
    int yydebug_;
    /// Debug stream.
    std::ostream* yycdebug_;

    /// \brief Display a symbol kind, value and location.
    /// \param yyo    The output stream.
    /// \param yysym  The symbol.
    template <typename Base>
    void yy_print_ (std::ostream& yyo, const basic_symbol<Base>& yysym) const;
#endif

    /// \brief Reclaim the memory associated to a symbol.
    /// \param yymsg     Why this token is reclaimed.
    ///                  If null, print nothing.
    /// \param yysym     The symbol.
    template <typename Base>
    void yy_destroy_ (const char* yymsg, basic_symbol<Base>& yysym) const;

  private:
    /// Type access provider for state based symbols.
    struct by_state
    {
      /// Default constructor.
      by_state () YY_NOEXCEPT;

      /// The symbol kind as needed by the constructor.
      typedef state_type kind_type;

      /// Constructor.
      by_state (kind_type s) YY_NOEXCEPT;

      /// Copy constructor.
      by_state (const by_state& that) YY_NOEXCEPT;

      /// Record that this symbol is empty.
      void clear () YY_NOEXCEPT;

      /// Steal the symbol kind from \a that.
      void move (by_state& that);

      /// The symbol kind (corresponding to \a state).
      /// \a symbol_kind::S_YYEMPTY when empty.
      symbol_kind_type kind () const YY_NOEXCEPT;

      /// The state number used to denote an empty symbol.
      /// We use the initial state, as it does not have a value.
      enum { empty_state = 0 };

      /// The state.
      /// \a empty when empty.
      state_type state;
    };

    /// "Internal" symbol: element of the stack.
    struct stack_symbol_type : basic_symbol<by_state>
    {
      /// Superclass.
      typedef basic_symbol<by_state> super_type;
      /// Construct an empty symbol.
      stack_symbol_type ();
      /// Move or copy construction.
      stack_symbol_type (YY_RVREF (stack_symbol_type) that);
      /// Steal the contents from \a sym to build this.
      stack_symbol_type (state_type s, YY_MOVE_REF (symbol_type) sym);
#if YY_CPLUSPLUS < 201103L
      /// Assignment, needed by push_back by some old implementations.
      /// Moves the contents of that.
      stack_symbol_type& operator= (stack_symbol_type& that);

      /// Assignment, needed by push_back by other implementations.
      /// Needed by some other old implementations.
      stack_symbol_type& operator= (const stack_symbol_type& that);
#endif
    };

    /// A stack with random access from its top.
    template <typename T, typename S = std::vector<T> >
    class stack
    {
    public:
      // Hide our reversed order.
      typedef typename S::iterator iterator;
      typedef typename S::const_iterator const_iterator;
      typedef typename S::size_type size_type;
      typedef typename std::ptrdiff_t index_type;

      stack (size_type n = 200)
        : seq_ (n)
      {}

#if 201103L <= YY_CPLUSPLUS
      /// Non copyable.
      stack (const stack&) = delete;
      /// Non copyable.
      stack& operator= (const stack&) = delete;
#endif

      /// Random access.
      ///
      /// Index 0 returns the topmost element.
      const T&
      operator[] (index_type i) const
      {
        return seq_[size_type (size () - 1 - i)];
      }

      /// Random access.
      ///
      /// Index 0 returns the topmost element.
      T&
      operator[] (index_type i)
      {
        return seq_[size_type (size () - 1 - i)];
      }

      /// Steal the contents of \a t.
      ///
      /// Close to move-semantics.
      void
      push (YY_MOVE_REF (T) t)
      {
        seq_.push_back (T ());
        operator[] (0).move (t);
      }

      /// Pop elements from the stack.
      void
      pop (std::ptrdiff_t n = 1) YY_NOEXCEPT
      {
        for (; 0 < n; --n)
          seq_.pop_back ();
      }

      /// Pop all elements from the stack.
      void
      clear () YY_NOEXCEPT
      {
        seq_.clear ();
      }

      /// Number of elements on the stack.
      index_type
      size () const YY_NOEXCEPT
      {
        return index_type (seq_.size ());
      }

      /// Iterator on top of the stack (going downwards).
      const_iterator
      begin () const YY_NOEXCEPT
      {
        return seq_.begin ();
      }

      /// Bottom of the stack.
      const_iterator
      end () const YY_NOEXCEPT
      {
        return seq_.end ();
      }

      /// Present a slice of the top of a stack.
      class slice
      {
      public:
        slice (const stack& stack, index_type range)
          : stack_ (stack)
          , range_ (range)
        {}

        const T&
        operator[] (index_type i) const
        {
          return stack_[range_ - i];
        }

      private:
        const stack& stack_;
        index_type range_;
      };

    private:
#if YY_CPLUSPLUS < 201103L
      /// Non copyable.
      stack (const stack&);
      /// Non copyable.
      stack& operator= (const stack&);
#endif
      /// The wrapped container.
      S seq_;
    };


    /// Stack type.
    typedef stack<stack_symbol_type> stack_type;

    /// The stack.
    stack_type yystack_;
    /// The stack for LAC.
    /// Logically, the yy_lac_stack's lifetime is confined to the function
    /// yy_lac_check_. We just store it as a member of this class to hold
    /// on to the memory and to avoid frequent reallocations.
    /// Since yy_lac_check_ is const, this member must be mutable.
    mutable std::vector<state_type> yylac_stack_;
    /// Whether an initial LAC context was established.
    bool yy_lac_established_;


    /// Push a new state on the stack.
    /// \param m    a debug message to display
    ///             if null, no trace is output.
    /// \param sym  the symbol
    /// \warning the contents of \a s.value is stolen.
    void yypush_ (const char* m, YY_MOVE_REF (stack_symbol_type) sym);

    /// Push a new look ahead token on the state on the stack.
    /// \param m    a debug message to display
    ///             if null, no trace is output.
    /// \param s    the state
    /// \param sym  the symbol (for its value and location).
    /// \warning the contents of \a sym.value is stolen.
    void yypush_ (const char* m, state_type s, YY_MOVE_REF (symbol_type) sym);

    /// Pop \a n symbols from the stack.
    void yypop_ (int n = 1);

    /// Constants.
    enum
    {
      yylast_ = 410,     ///< Last index in yytable_.
      yynnts_ = 28,  ///< Number of nonterminal symbols.
      yyfinal_ = 8 ///< Termination state number.
    };


    // User arguments.
    quack::parser::ParserDriver& drv;

  };

  inline
  parser::symbol_kind_type
  parser::yytranslate_ (int t)
  {
    return static_cast<symbol_kind_type> (t);
  }

  // basic_symbol.
  template <typename Base>
  parser::basic_symbol<Base>::basic_symbol (const basic_symbol& that)
    : Base (that)
    , value ()
    , location (that.location)
  {
    switch (this->kind ())
    {
      case symbol_kind::S_binaryOperator: // binaryOperator
        value.copy< BinaryOperator::Operator > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_unaryOperator: // unaryOperator
        value.copy< UnaryOperator::Operator > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_BOOL: // BOOL
        value.copy< bool > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_FLOAT: // FLOAT
        value.copy< double > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_INT: // INT
        value.copy< long > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_args: // args
      case symbol_kind::S_argsNonEmpty: // argsNonEmpty
        value.copy< ptr<Arguments> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_assignment: // assignment
        value.copy< ptr<Assignment> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_call: // call
        value.copy< ptr<Call> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_class: // class
        value.copy< ptr<Class> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_classes: // classes
      case symbol_kind::S_classesNonEmpty: // classesNonEmpty
        value.copy< ptr<Classes> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_compoundStmt: // compoundStmt
      case symbol_kind::S_optElseIf: // optElseIf
        value.copy< ptr<CompoundStmt> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expression: // expression
        value.copy< ptr<Expression> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_identifier: // identifier
        value.copy< ptr<Identifier> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_ifStmt: // ifStmt
        value.copy< ptr<If> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_memberAccess: // memberAccess
        value.copy< ptr<MemberAccess> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_method: // method
        value.copy< ptr<Method> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_methods: // methods
      case symbol_kind::S_methodsNonEmpty: // methodsNonEmpty
        value.copy< ptr<Methods> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_params: // params
      case symbol_kind::S_paramsNonEmpty: // paramsNonEmpty
        value.copy< ptr<Parameters> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_returnStmt: // returnStmt
        value.copy< ptr<Return> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_statement: // statement
        value.copy< ptr<Statement> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_staticAssignment: // staticAssignment
        value.copy< ptr<StaticAssignment> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_memberDecl: // memberDecl
        value.copy< ptr<StaticMemberDecl> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_translationUnit: // translationUnit
        value.copy< ptr<TranslationUnit> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_varDecl: // varDecl
        value.copy< ptr<VarDecl> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_whileStmt: // whileStmt
        value.copy< ptr<While> > (YY_MOVE (that.value));
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
        value.copy< std::string > (YY_MOVE (that.value));
        break;

      default:
        break;
    }

  }



  template <typename Base>
  parser::symbol_kind_type
  parser::basic_symbol<Base>::type_get () const YY_NOEXCEPT
  {
    return this->kind ();
  }

  template <typename Base>
  bool
  parser::basic_symbol<Base>::empty () const YY_NOEXCEPT
  {
    return this->kind () == symbol_kind::S_YYEMPTY;
  }

  template <typename Base>
  void
  parser::basic_symbol<Base>::move (basic_symbol& s)
  {
    super_type::move (s);
    switch (this->kind ())
    {
      case symbol_kind::S_binaryOperator: // binaryOperator
        value.move< BinaryOperator::Operator > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_unaryOperator: // unaryOperator
        value.move< UnaryOperator::Operator > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_BOOL: // BOOL
        value.move< bool > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_FLOAT: // FLOAT
        value.move< double > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_INT: // INT
        value.move< long > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_args: // args
      case symbol_kind::S_argsNonEmpty: // argsNonEmpty
        value.move< ptr<Arguments> > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_assignment: // assignment
        value.move< ptr<Assignment> > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_call: // call
        value.move< ptr<Call> > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_class: // class
        value.move< ptr<Class> > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_classes: // classes
      case symbol_kind::S_classesNonEmpty: // classesNonEmpty
        value.move< ptr<Classes> > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_compoundStmt: // compoundStmt
      case symbol_kind::S_optElseIf: // optElseIf
        value.move< ptr<CompoundStmt> > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_expression: // expression
        value.move< ptr<Expression> > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_identifier: // identifier
        value.move< ptr<Identifier> > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_ifStmt: // ifStmt
        value.move< ptr<If> > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_memberAccess: // memberAccess
        value.move< ptr<MemberAccess> > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_method: // method
        value.move< ptr<Method> > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_methods: // methods
      case symbol_kind::S_methodsNonEmpty: // methodsNonEmpty
        value.move< ptr<Methods> > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_params: // params
      case symbol_kind::S_paramsNonEmpty: // paramsNonEmpty
        value.move< ptr<Parameters> > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_returnStmt: // returnStmt
        value.move< ptr<Return> > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_statement: // statement
        value.move< ptr<Statement> > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_staticAssignment: // staticAssignment
        value.move< ptr<StaticAssignment> > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_memberDecl: // memberDecl
        value.move< ptr<StaticMemberDecl> > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_translationUnit: // translationUnit
        value.move< ptr<TranslationUnit> > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_varDecl: // varDecl
        value.move< ptr<VarDecl> > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_whileStmt: // whileStmt
        value.move< ptr<While> > (YY_MOVE (s.value));
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
        value.move< std::string > (YY_MOVE (s.value));
        break;

      default:
        break;
    }

    location = YY_MOVE (s.location);
  }

  // by_kind.
  inline
  parser::by_kind::by_kind ()
    : kind_ (symbol_kind::S_YYEMPTY)
  {}

#if 201103L <= YY_CPLUSPLUS
  inline
  parser::by_kind::by_kind (by_kind&& that)
    : kind_ (that.kind_)
  {
    that.clear ();
  }
#endif

  inline
  parser::by_kind::by_kind (const by_kind& that)
    : kind_ (that.kind_)
  {}

  inline
  parser::by_kind::by_kind (token_kind_type t)
    : kind_ (yytranslate_ (t))
  {}

  inline
  void
  parser::by_kind::clear ()
  {
    kind_ = symbol_kind::S_YYEMPTY;
  }

  inline
  void
  parser::by_kind::move (by_kind& that)
  {
    kind_ = that.kind_;
    that.clear ();
  }

  inline
  parser::symbol_kind_type
  parser::by_kind::kind () const YY_NOEXCEPT
  {
    return kind_;
  }

  inline
  parser::symbol_kind_type
  parser::by_kind::type_get () const YY_NOEXCEPT
  {
    return this->kind ();
  }

} // yy
#line 2810 "/home/parsab/dev/Quack-v2/cmake-build-debug/Parser.hpp"




#endif // !YY_YY_HOME_PARSAB_DEV_QUACK_V2_CMAKE_BUILD_DEBUG_PARSER_HPP_INCLUDED
