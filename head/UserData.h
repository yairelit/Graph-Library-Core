// UserData.h
#pragma once
#include <string>

class UserData {
public:
    UserData() : name(""), age(0), gender('m') {}
    UserData(const std::string& name_, int age_, char gender_) : name(name_), age(age_), gender(gender_) {}

    std::string name;
    int age;
    char gender;
};
