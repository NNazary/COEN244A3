//
//  TA.hpp
//  244A3
//
//  Created by Najmuddin Nazary on 2023-04-14.
//

#ifndef TA_hpp
#define TA_hpp

#include <stdio.h>
#include <iostream>
using namespace std;



class TA {
public:
    string firstName;
    int workingHours;
    string status;
    int age;
    int Id;

    TA(string firstName, int workingHours, string status, int age, int Id)
        : firstName(firstName), workingHours(workingHours), status(status), age(age), Id(Id) {}
};

#endif /* TA_hpp */
