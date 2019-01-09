
#include <string>


#include "boost/foreach.hpp"
#include "boost/unordered_map.hpp"

struct EnumHash {
  template <typename T>
  int operator()(T enumValue) const {
    return static_cast<int>(enumValue);
  }
};

struct StringHash {
  int operator()(const std::string &strToHash) const {
    if (strToHash.empty()) {
      return 0;
    }

    int hash = 0;
    BOOST_FOREACH (const char &charValue, strToHash) {
      hash = charValue + 31 * hash;
    }
    return hash;
  }
};

struct Color {
  enum Value {
    White = 0,
    Red = 1,
    Black = 2
  };
};

using std::string;
int main() {
  typedef boost::unordered_map<std::string, int> map;
  map x;
  x["one"] = 1;
  x["two"] = 2;
  x["three"] = 3;
  assert(x.at("one") == 1);

  boost::unordered_map<Color::Value, std::string, EnumHash> map1;
  map1[Color::White] = "white";
  map1[Color::Red] = "red";
  map1[Color::Black] = "black";
  assert(map1.at(Color::Black) == "black");

  static const char *const AP_1 = "ap1";
  static const char *const PEK_2 = "pek2";
  static const char *const PEK_3A = "pek3a";  // default zone
  boost::unordered_map<string, string, StringHash> mapZone;
  mapZone[AP_1] = "ap1.qingstor.com";
  mapZone[PEK_2] = "pek2.qingstor.com";
  mapZone[PEK_3A] = "pek3a.qingstor.com";
  assert(mapZone.at(AP_1) == "ap1.qingstor.com");
}
