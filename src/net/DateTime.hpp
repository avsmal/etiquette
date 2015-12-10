#pragma once
#include <iostream>
#include <vmime/vmime.hpp>
class DateTime {

public:
    DateTime(const vmime::datetime & datetime):
        datetime_(datetime)
    {}
    DateTime(int second, int zone) {
        datetime_  = vmime::datetime(second);
    }
    DateTime() {
    }
    
    int getYear() const {
        return datetime_.getYear();
    }
    int getMonth() const {
        return datetime_.getMonth();
    }
    int getDay() const {
        return datetime_.getDay();
    }
    int getHour() const {
        return datetime_.getHour();
    }
    int getMinute() const {
        return datetime_.getMinute();
    }
    int getSecond() const {
        return datetime_.getSecond();
    }
    int getZone() const {
        return datetime_.getZone();
    }
    bool operator< (const DateTime &other) const {
        return datetime_ < other.datetime_;
    }
    DateTime & operator= (const vmime::datetime &other) {
        datetime_ = other;
        return *this;
    }
    DateTime & operator= (const DateTime &other) {
        datetime_ = other.datetime_;
        return *this;
    }
private:
    vmime::datetime datetime_;
};
