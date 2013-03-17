//
//  BinPolynomial.h
//  OTK_HomeWork
//
//  Created by Nikita Anisimov on 3/16/13.
//  Copyright (c) 2013 Nikita Anisimov. All rights reserved.
//

#ifndef OTK_HomeWork_BinPolynomial_h
#define OTK_HomeWork_BinPolynomial_h

//#define DEBUG_OTK 1
#ifdef DEBUG_OTK
#include <cassert>
#endif

#include <iostream>
#include <algorithm>
#include <vector>

class BinPolynomial {
    bool coutZeroes;
    std::vector<int> koefVec;
    //operators
    friend std::ostream &operator<<(std::ostream &outstream, const BinPolynomial &poly);
public:
    BinPolynomial();
    BinPolynomial(std::vector<int>);
    BinPolynomial(BinPolynomial&);
    ~BinPolynomial();
    //operators
    BinPolynomial operator+(BinPolynomial&);
    BinPolynomial operator*(std::vector<int>&);
    BinPolynomial operator*(BinPolynomial&);
    BinPolynomial operator/(BinPolynomial&);
    BinPolynomial operator%(BinPolynomial&);
    //
    std::vector<int> getKoefVec();
    void setCoutZeroKoefs(bool);
};

void optiSizeVector(std::vector<int>*);

#endif
