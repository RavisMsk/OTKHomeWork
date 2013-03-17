//
//  main.cpp
//  OTK_HomeWork
//
//  Created by Nikita Anisimov on 3/16/13.
//  Copyright (c) 2013 Nikita Anisimov. All rights reserved.
//

#include <iostream>
#include <vector>
#include "Polynom.h"
#include <math.h>

int main(int argc, const char * argv[])
{
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
    Polynom sourcePoly(sourceVec);
    sourcePoly.setCoutZeroKoefs(0);
    std::vector<int> multiVec(n-vecSize+1);
    multiVec[multiVec.size() - (n-vecSize) - 1]=1;
    Polynom multiPoly(multiVec);
    multiPoly.setCoutZeroKoefs(0);
    std::cout << "Multiplying: (" << sourcePoly << ") * (" << multiPoly << ") = ";
    Polynom multiResult;
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
    Polynom gPoly(gVec);
    std::cout << gPoly << "\n";
    Polynom divisionResult;
    divisionResult=multiResult/gPoly;
    divisionResult.setCoutZeroKoefs(0);
    Polynom moduloResult;
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
    std::cout << "Totally there can be " << powf(2, n) << " error vectors.";
    std::cout << "Generating error vectors now...\n";
    for (int i=0;i<powf(2,n);i++){
        std::vector<int> eVec(7);
        
    }
    return 0;
}

