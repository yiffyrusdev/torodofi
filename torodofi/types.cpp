#include "types.hpp"
#include "logic.hpp"

using namespace std;

namespace toro {
namespace types {

// class date

date::date() {
  date today = this->today();
  _validate_and_pass(today.getYear(), today.getMonth(), today.getDay());
}

date::date(string yyyymmdd) { _real_constructor(yyyymmdd); }

date::date(unsigned year, unsigned month, unsigned day) {
  bool passed;
  vector<string> parsed = {to_string(year), to_string(month), to_string(day)};

  passed = _validate_and_pass(year, month, day);
  if (!passed) {
    printf("unsigned short yyyy, mm, dd: %d %d %d\n", year, month, day);
    throw std::invalid_argument("Date must be a valid GNU date!");
  }
}

void date::_real_constructor(string yyyymmdd) {
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
    if (!passed) {
      printf("unsigned short yyyy, mm, dd: %d %d %d\n", yyyy, mm, dd);
      throw std::invalid_argument("Date must be a valid GNU date!");
    }
  } else {
    printf("string yyyymmdd: %s", yyyymmdd.c_str());
    throw std::invalid_argument("Date must contain 3 fields");
  }
}

bool date::_validate_and_pass(unsigned short year, unsigned short month,
                              unsigned short day) {
  bool passed = true;
  unsigned short days_in;
  string yyyy, mm, dd;

  passed = passed && (year < 4000);
  if ((year % 4 == 0) && (year % 100 != 0)) { // високосный year
    days_in = (month == 2) ? _days_in_months[0] : _days_in_months[month];
    _bissextile = true;
  } else {
    days_in = _days_in_months[month];
  }
  passed = passed && (month < 13);
  passed = passed && (day <= days_in);

  if (passed) {
    _year = year;
    _month = month;
    _day = day;

    yyyy = to_string(year);
    mm = to_string(month);
    dd = to_string(day);

    mm = (mm.length() < 2) ? "0" + mm : mm;
    dd = (dd.length() < 2) ? "0" + dd : dd;

    _gnudate = yyyy + "-" + mm + "-" + dd;

    return true;
  } else {
    return false;
  }
}

vector<date> date::vectorBefore(size_t acount) {
  vector<date> dates = {*this};

  for (; acount > 0; acount--) {
    dates.push_back(dates[dates.size() - 1] - 1);
  }

  return dates;
}

vector<date> date::vectorAfter(size_t acount) {
  vector<date> dates = {*this};

  for (size_t d = 0; d < acount; d++) {
    dates.push_back(dates[dates.size() - 1] + 1);
  }

  return dates;
}

date date::today() {
  time_t rawtime;
  struct tm *timeinfo;
  char buffer[80];
  string today_date;

  time(&rawtime);
  timeinfo = localtime(&rawtime);
  strftime(buffer, 80, "%Y-%m-%d", timeinfo);
  today_date = buffer;

  return date(today_date);
}

string date::toString() { return _gnudate; }

const char *date::c_str() const { return _gnudate.c_str(); }

// getters
unsigned short date::getYear() { return _year; }
unsigned short date::getMonth() { return _month; }
unsigned short date::getDay() { return _day; }

// Operators
date date::operator+(unsigned short adays) {
  unsigned short days, months, years, days_in;
  years = _year;
  months = _month;
  days = _day;

  days += adays;
  days_in = (_bissextile && months == 2) ? _days_in_months[0]
                                         : _days_in_months[months];
  months = (days > days_in) ? months + 1 : months;
  years = (_month > 12) ? years + 1 : years;

  days = (days > days_in) ? days - days_in : days;
  months = (months > 12) ? 1 : months;

  return date(years, months, days);
}

date date::operator-(unsigned short adays) {
  unsigned short days, months, years, days_in;
  years = _year;
  months = _month;
  days = _day;

  days -= adays;
  days_in = (_bissextile && months == 3) ? _days_in_months[0]
                                         : _days_in_months[months - 1];
  if (days < 1) {
    months--;
    days = days_in;
  }
  if (months < 1) {
    years--;
    months = 12;
  }

  return date(years, months, days);
}

bool date::operator==(date &other) {
  bool eq = _year == other.getYear();
  eq = eq && _month == other.getMonth();
  eq = eq && _day == other.getDay();
  return eq;
}

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

bool date::operator!=(date &other) { return !((*this) == other); }

bool date::operator<(date &other) {
  return ((*this) != other) && !((*this) > other);
}
bool date::operator>=(date &other) {
  return ((*this) > other) || ((*this) == other);
}
bool date::operator<=(date &other) {
  return ((*this) < other) || ((*this) == other);
}

date &date::operator=(string gnudate) {
  _real_constructor(gnudate);
  return *this;
}

} // namespace types
} // namespace toro
