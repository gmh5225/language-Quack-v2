//
// Created by Parsa Bagheri on 9/2/20.
//

#ifndef QUACK_LOCATION_HPP
#define QUACK_LOCATION_HPP

#include <sstream>
#include <string>

namespace quick::frontend {

struct Location {
  unsigned l_from, l_to, c_from, c_to, pos, len;
  Location(unsigned lineFrom, unsigned columnFrom, unsigned lineTo,
           unsigned columnTo, unsigned pos = 0, unsigned len = 0)
      : l_from(lineFrom), l_to(lineTo), c_from(columnFrom), c_to(columnTo),
        pos(pos), len(len) {}
  Location() : l_from(0), l_to(0), c_from(0), c_to(0), pos(0), len(0) {}
  bool operator==(const Location &o) const {
    return (l_from == o.l_from && l_to == o.l_to && c_from == o.c_from &&
            c_to == o.c_to && pos == o.pos && len == o.len);
  }
  bool operator!=(const Location &o) const {
    return !(*this == o);
  }
  //    const std::string& getFileName() const    { return _fileName; };
  std::string toString() const {
    std::stringstream ss;
    ss << l_from << "." << c_from << "-" << l_to << "." << c_to;
    return ss.str();
  }
};

} // namespace quick::frontend
#endif // QUACK_LOCATION_HPP
