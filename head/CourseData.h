#pragma once
#include <string>

class CourseData {
public:
    CourseData() : name_(), credits_(0) {}
    CourseData(const std::string& name, double credits) : name_(name), credits_(credits) {}

    const std::string& getName() const { return name_; }
    double getCredits() const { return credits_; }

private:
    std::string name_;
    double credits_;
};
