//
// Created by Parsa Bagheri on 9/2/20.
//

#ifndef QUACK_LOCATION_HPP
#define QUACK_LOCATION_HPP

#include <sstream>
#include <string>

namespace quack::ast {

class Location {
private:
  unsigned _lineFrom, _lineTo;
  unsigned _columnFrom, _columnTo;
  const std::string _fileName;

public:
  Location(unsigned lineFrom, unsigned columnFrom, unsigned lineTo, unsigned columnTo, const std::string *filename)
      : _lineFrom(lineFrom), _lineTo(lineTo), _columnFrom(columnFrom),
        _columnTo(columnTo), _fileName(filename != nullptr ? *filename : "<filename>") {}

  Location()
      : _lineFrom(0), _lineTo(0), _columnFrom(0),
        _columnTo(0) {}

  unsigned getLineFrom() const { return _lineFrom; };
  unsigned getLineTo() const { return _lineTo; };
  unsigned getColumnFrom() const { return _columnFrom; };
  unsigned getColumnTo() const { return _columnTo; };
  //    const std::string& getFileName() const    { return _fileName; };
  std::string toString() const {
    std::stringstream ss;
    ss << _fileName << ":" << _lineFrom << "." << _columnFrom
       << "-" << _lineTo << "." << _columnTo;
    return ss.str();
  }
};

}// namespace quack::ast
#endif//QUACK_LOCATION_HPP
