//
//  Polynom.h
//  OTK_HomeWork
//
//  Created by Nikita Anisimov on 3/16/13.
//  Copyright (c) 2013 Nikita Anisimov. All rights reserved.
//

#ifndef OTK_HomeWork_Polynom_h
#define OTK_HomeWork_Polynom_h

//#define DEBUG_OTK 1
#ifdef DEBUG_OTK
#include <cassert>
#endif

#include <iostream>
#include <algorithm>
#include <vector>

class Polynom {
    bool coutZeroes;
    std::vector<int> koefVec;
    //operators
    friend std::ostream &operator<<(std::ostream &outstream, const Polynom &poly);
public:
    Polynom();
    Polynom(std::vector<int>);
    Polynom(Polynom&);
    ~Polynom();
    //operators
    Polynom operator+(Polynom&);
    Polynom operator*(std::vector<int>&);
    Polynom operator*(Polynom&);
    Polynom operator/(Polynom&);
    Polynom operator%(Polynom&);
    //
    std::vector<int> getKoefVec();
    void setCoutZeroKoefs(bool);
};

void optiSizeVector(std::vector<int>*);

#endif
