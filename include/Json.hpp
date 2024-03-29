//
// Created by parsab on 6/11/22.
//

#ifndef QUACK_JSON_HPP
#define QUACK_JSON_HPP

#include "llvm/Support/raw_os_ostream.h"
#include "llvm/ADT/MapVector.h"
#include <map>

namespace json {
template <typename T, typename... Args> auto make(Args &&...args) {
  return std::make_unique<T>(std::forward<Args>(args)...);
}

class JSONNode {
public:
  struct PrintContext {
    llvm::raw_ostream &out = llvm::outs();
    int indentation = 0;
    void indent() { indentation += 2; }
    void dedent() { indentation -= 2; }
    void printIndent() {
      for (int i = 0; i < indentation; i++)
        out << ' ';
    }
    template <typename... Args> void print(Args &&...args) {
      ([this](const auto &arg) { out << arg; }(args), ...);
    }
    template <typename... Args> void println(Args &&...args) {
      print(std::forward<Args>(args)...);
      out << "\n";
    }
  };

  virtual void dump(PrintContext pctx = {llvm::outs(), 0}) const = 0;
  virtual ~JSONNode() = default;
};

class DictionaryNode : public JSONNode,
                       public llvm::MapVector<llvm::StringRef, std::unique_ptr<JSONNode>> {
public:
  void dump(PrintContext pctx) const override {
    pctx.println("{");
    pctx.indent();
    size_t i = 0;
    for (const auto &[key, val] : *this) {
      pctx.printIndent();
      pctx.print("\"", key, "\": ");
      val->dump(pctx);
      if (i == this->size() - 1)
        pctx.println();
      else
        pctx.println(",");
      i++;
    }
    pctx.dedent();
    pctx.printIndent();
    pctx.print("}");
  }
};

class ListNode : public JSONNode,
                 public std::vector<std::unique_ptr<JSONNode>> {
public:
  void dump(PrintContext pctx) const override {
    pctx.println("[");
    pctx.indent();
    size_t i = 0;
    for (const auto &val : *this) {
      pctx.printIndent();
      val->dump(pctx);
      if (i == this->size() - 1)
        pctx.println();
      else
        pctx.println(",");
      i++;
    }
    pctx.dedent();
    pctx.printIndent();
    pctx.print("]");
  }
};

class StringNode : public JSONNode, public std::string {
public:
  explicit StringNode(const std::string &str) : std::string(str) {}
  explicit StringNode(std::string &&str) : std::string(std::move(str)) {}
  explicit StringNode(int64_t num) : std::string(std::to_string(num)) {}
  void dump(PrintContext pctx) const override { pctx.print("\"", *this, "\""); }
};
} // namespace json
#endif // QUACK_JSON_HPP
