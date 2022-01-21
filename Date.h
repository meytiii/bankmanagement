#ifndef DATE_H
#define DATE_H
#include <iostream>
#include <cstdlib>
#include <string>

using namespace std;
class Date {
public:
    Date(int d, int m, int y);
    Date();
    void set_date(int d, int m, int y);
    void print_date();
    bool equals(Date d);

    int get_day() { return day; }
    int get_month() { return month; }
    int get_year() { return year; }
    void inc_one_day();
    static bool is_leap_year(int);
    static int max_day_for_month(int, int);
    static int days_between(Date, Date);
    static Date str_to_date(string);
private:
    int day;
    int month;
    int year;
};

Date::Date(int d, int m, int y)
{
    //constructor
    set_date(d, m, y);
}
Date::Date()
{
    //default constructor
    set_date(1, 1, 1390);
}


bool Date::is_leap_year(int year)
{
    int r = year % 33;
    return r==1 || r==5 || r==9 || r==13 || r==17 || r==22 || r==26 || r==30;
}

int Date::max_day_for_month(int m, int y)
{
    if (m < 7)
        return 31;
    else if (m < 12)
        return 30;
    else if (m == 12)
        return is_leap_year(y) ? 30 : 29;
    else
        abort();
}

void Date::inc_one_day()
{
    day++;
    if (day > max_day_for_month(month, year)) {
        day = 1;
        month++;
        if (month > 12) {
            month = 1;
            year++;
        }
    }
}

void Date::set_date(int d, int m, int y)
{
    if (y < 0 || m < 1 || m > 12 || d < 1 || d > max_day_for_month(m, y))
        abort();

    day = d;
    month = m;
    year = y;
}

void Date::print_date()
{
    //baraye chape tarikh
    cout << day << '/' << month << '/' << year << endl;
}

bool Date::equals(Date d) {
    //moghaieseye 2 tarikh
    return day == d.day && month == d.month && year == d.year;
}
int Date::days_between(Date d1, Date d2) {
    // Assuming d1 is not later than d2
    int count = 1;
    while (!d1.equals(d2)) {
        d1.inc_one_day();
        count++;
    }
    return count;
}

Date Date::str_to_date(string s) {
    //TODO: Handle formatting errors
    int slash_pos = s.find('/'); //3/12/1394 => slash_pos=1
    int d = stoi(s.substr(0, slash_pos)); //=> d=3
    s = s.substr(slash_pos + 1);//=>s=12/1394
    slash_pos = s.find('/');//=>slash_pos=2
    int m = stoi(s.substr(0, slash_pos));//=>m=12
    int y = stoi(s.substr(slash_pos + 1));//=>y=1394
    return Date(d, m, y);
}
#endif // DATE_H
