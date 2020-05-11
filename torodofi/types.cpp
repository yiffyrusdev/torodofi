#include "types.hpp"
#include "logic.hpp"

using namespace std;

namespace toro {
namespace types {

// class date

date::date() {}

date::date(string yyyymmdd) {
  unsigned short yyyy;
  unsigned short mm;
  unsigned short dd;
  vector<string> parsed;
  bool passed;

  parsed = logic::splitString(yyyymmdd, "-");
  if (parsed.size() == 3) {
    yyyy = atoi(parsed[0].c_str());
    mm = atoi(parsed[1].c_str());
    dd = atoi(parsed[2].c_str());
    passed = _validate_and_pass(yyyy, mm, dd);
    if (passed) {
      _gnudate = logic::joinString(parsed, "-");
    } else {
      printf("unsigned short yyyy, mm, dd: %d %d %d\n", yyyy, mm, dd);
      throw std::invalid_argument("Date must be a valid GNU date!");
    }
  } else {
    printf("string yyyymmdd: %s", yyyymmdd.c_str());
    throw std::invalid_argument("Date must contain 3 fields");
  }
}

bool date::_validate_and_pass(unsigned short yyyy, unsigned short mm,
                              unsigned short dd) {
  bool passed = true;
  int days_in;

  passed = passed && (yyyy < 3000);
  switch (mm) {
  case 1:
    days_in = 31;
    break;
  case 2:
    days_in = 29;
    break;
  case 3:
    days_in = 31;
    break;
  case 4:
    days_in = 30;
    break;
  case 5:
    days_in = 31;
    break;
  case 6:
    days_in = 30;
    break;
  case 7:
    days_in = 31;
    break;
  case 8:
    days_in = 30;
    break;
  case 9:
    days_in = 31;
    break;
  case 10:
    days_in = 30;
    break;
  case 11:
    days_in = 31;
    break;
  case 12:
    days_in = 30;
    break;
  default:
    passed = false;
    break;
  }
  passed = passed && (dd > 0 && dd <= days_in);

  if (passed) {
    _year = yyyy;
    _month = mm;
    _day = dd;
    return true;
  } else {
    return false;
  }
}

string date::toString() { return _gnudate; }

const char *date::c_str() const { return _gnudate.c_str(); }

// getters
unsigned short date::getYear() { return _year; }
unsigned short date::getMonth() { return _month; }
unsigned short date::getDay() { return _day; }

// Operators
bool date::operator==(date &other) { return _gnudate == other.toString(); }

bool date::operator!=(date &other) { return _gnudate != other.toString(); }

bool date::operator>(date &other) {
  bool isgreater = false;

  if (_year > other.getYear()) {
    isgreater = true;
  } else {
    if (_year == other.getYear()) {
      if (_month > other.getMonth()) {
        isgreater = true;
      } else {
        if (_month == other.getMonth()) {
          if (_day > other.getDay()) {
            isgreater = true;
          }
        }
      }
    }
  }

  return isgreater;
}

bool date::operator<(date &other) {
  return ((*this) != other) && (!((*this) > other));
}
bool date::operator>=(date &other) {
  return ((*this) > other) || ((*this) == other);
}
bool date::operator<=(date &other) {
  return ((*this) < other) || ((*this) == other);
}

} // namespace types
} // namespace toro
