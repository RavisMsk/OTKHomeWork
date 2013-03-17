//
//  main.cpp
//  OTK_HomeWork
//
//  Created by Nikita Anisimov on 3/16/13.
//  Copyright (c) 2013 Nikita Anisimov. All rights reserved.
//

#include <iostream>
#include <vector>
#include "BinPolynomial.h"
#include <math.h>
#include <bitset>
#include <map>

struct CustomComparer {
    bool operator()(const std::bitset<3>&b1, const std::bitset<3>&b2) const {
        return b1.to_ulong() < b2.to_ulong();
    }
};

int main(int argc, const char * argv[])
{
    //array for counting solved errors
    //generate syndroms table
    std::bitset<3> mass[7];
    for (int i=0;i<7;i++){
        std::bitset<3> bits(i+1);
        mass[i]=bits;
    }
    std::map<std::bitset<3>, int, CustomComparer> syndromsTable = {
        {mass[0], 0},
        {mass[1], 1},
        {mass[2], 3},
        {mass[3], 2},
        {mass[4], 6},
        {mass[5], 4},
        {mass[6], 5}
    };
//    syndromsTable[mass[1]]=1;
//    syndromsTable[mass[2]]=3;
//    syndromsTable[mass[3]]=2;
//    syndromsTable[mass[4]]=6;
//    syndromsTable[mass[5]]=4;
//    syndromsTable[mass[6]]=5;
    //
    std::cout << "Hello, World!\nThis application is created by Anisimov Nikita (c) 2013\n";
    std::cout << "Set input vector size: ";
    int vecSize=0;
    int n;
    std::cin >> vecSize;
    if (vecSize==4)
        n=7;
    std::vector<int> sourceVec(vecSize);
    std::cout << "Input vector bits.\n";
    int i=0;
    while (i < vecSize) {
        std::cout << "Bit " << i << ": ";
        int buff;
        std::cin >> buff;
        if (buff!=0 && buff!=1){
            std::cout << "It's a BIT, you idiot!\n";
            continue;
        }
        sourceVec[i]=buff;
        i++;
    }
    std::cout << "Your data vector: ";
    for (std::vector<int>::iterator it=sourceVec.begin(); it!=sourceVec.end(); ++it)
        std::cout << *it;
    std::cout << "\nWill encode it now...\n";
    BinPolynomial sourcePoly(sourceVec);
    sourcePoly.setCoutZeroKoefs(0);
    std::vector<int> multiVec(n-vecSize+1);
    multiVec[multiVec.size() - (n-vecSize) - 1]=1;
    BinPolynomial multiPoly(multiVec);
    multiPoly.setCoutZeroKoefs(0);
    std::cout << "Multiplying: (" << sourcePoly << ") * (" << multiPoly << ") = ";
    BinPolynomial multiResult;
    multiResult=sourcePoly*multiPoly;
    multiResult.setCoutZeroKoefs(0);
    std::cout << multiResult << "\nDividing it by g(x) = ";
    std::vector<int> gVec(n-vecSize+1);
    switch (gVec.size()-1) {
        case 3:
            gVec[0]=1;
            gVec[2]=1;
            gVec[3]=1;
            break;
        case 4:
            gVec[0]=1;
            gVec[3]=1;
            gVec[4]=1;
            break;
        case 5:
            gVec[0]=1;
            gVec[3]=1;
            gVec[5]=1;
            break;
        default:
            std::cout << "Got problem with your g(x), there's no case for it.\n";
            std::cout << "You can write it inside main.cpp by yourself.\n";
            return 0;
            break;
    }
    BinPolynomial gPoly(gVec);
    std::cout << gPoly << "\n";
    BinPolynomial divisionResult;
    divisionResult=multiResult/gPoly;
    divisionResult.setCoutZeroKoefs(0);
    BinPolynomial moduloResult;
    moduloResult=multiResult%gPoly;
    moduloResult.setCoutZeroKoefs(1);
    std::cout << "Division result is: " << divisionResult << "\n";
    std::cout << "Modulo result is: " << moduloResult << "\n";
    std::vector<int> concated(multiResult.getKoefVec());
    std::vector<int> reversedModulo=moduloResult.getKoefVec();
    std::reverse(reversedModulo.begin(), reversedModulo.end());
    for (int i=0;i<reversedModulo.size();i++){
        concated[concated.size()-1-i]=reversedModulo[i];
    }
    std::cout << "####\nConcatenated data vector: ";
    for (std::vector<int>::iterator it=concated.begin();it!=concated.end();++it)
        std::cout << *it;
    std::cout << "\n####\n";
    std::cout << "Totally there can be " << powf(2, n)-1 << " error vectors(with out 0-vector).";
    std::cout << "Generating error vectors now...\n####\n";
    for (int i=1;i<powf(2,n);i++){
        std::vector<int> sVec(concated);
        std::vector<int> eVec(7);
        std::bitset<7> bits(i);
        unsigned short int multiplicity=0;
        for (int i=0;i<eVec.size();i++){
            eVec[i]=bits[i];
            if (eVec[i]) multiplicity++;
        }
        std::cout << "##\nError vector = ";
        for (std::vector<int>::iterator it=eVec.begin();it!=eVec.end();++it)
            std::cout << *it;
        std::cout << "\nError multiplicity = " << multiplicity;
        std::cout << "\nReceived vector = ";
        for (int i=0;i<sVec.size();i++){
            sVec[i]=(sVec[i]+eVec[i])%2;
            std::cout << sVec[i];
        }
        std::cout << "\nDecoding - again modulo of division by g(x):\n";
        BinPolynomial rPoly(sVec);
        BinPolynomial modulo;
        modulo=rPoly%gPoly;
        modulo.setCoutZeroKoefs(0);
        std::cout << "Error syndrom = " << modulo;
        if (modulo.getKoefVec().size()==0){
            std::cout << "\nError syndrom is empty, so algorithm says there is no error in received message\n##\n";
            break;
        }
        if (multiplicity>1){
            int weight=100;
            int i=1;
            BinPolynomial buffer;
            while (weight>multiplicity){
                BinPolynomial modPoly=modulo;
                BinPolynomial syndPoly;
                std::vector<int> syndVec(i);
                syndVec[i]=1;
                BinPolynomial mulPoly(syndVec);
                syndPoly=mulPoly*modPoly;
                syndPoly=syndPoly%gPoly;
                weight=(int)syndPoly.getKoefVec().size();
                buffer=syndPoly;
                i+=1;
            }
            std::cout << i << " new syndrom vector iterations passed.\nError syndrom = " << buffer;
            break;
        }
        std::bitset<3> checkBits;
        for (int i=0;i<modulo.getKoefVec().size();i++) checkBits[i]=modulo.getKoefVec()[modulo.getKoefVec().size() - 1 - i];
        int errorInDegree=syndromsTable[checkBits];
        std::cout << "\nError in bit #" << errorInDegree << " (BinPolynomialial term with degree " << errorInDegree << ")";
        std::cout << "\nRecovered vector: ";
        sVec[errorInDegree]=!sVec[errorInDegree];
        for (std::vector<int>::iterator it=sVec.begin();it!=sVec.end();++it) std::cout << *it;
        std::cout << "\n##\n";
    }
    return 0;
}

