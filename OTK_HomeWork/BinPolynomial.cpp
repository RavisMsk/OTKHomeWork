//
//  BinPolynomial.cpp
//  OTK_HomeWork
//
//  Created by Nikita Anisimov on 3/16/13.
//  Copyright (c) 2013 Nikita Anisimov. All rights reserved.
//

#include "BinPolynomial.h"

BinPolynomial::BinPolynomial(){
    this->coutZeroes=1;
}

BinPolynomial::BinPolynomial(std::vector<int> koefs){
    this->koefVec=koefs;
    this->coutZeroes=1;
}

BinPolynomial::BinPolynomial(BinPolynomial &copy){
    this->koefVec=copy.koefVec;
    this->coutZeroes=copy.coutZeroes;
}

BinPolynomial::~BinPolynomial(){
    
}

std::vector<int> BinPolynomial::getKoefVec(){
    return this->koefVec;
}

void BinPolynomial::setCoutZeroKoefs(bool zeroes){
    this->coutZeroes=zeroes;
}

std::ostream &operator<<(std::ostream& outstream, const BinPolynomial &poly){
    long polyKoef;
    for (polyKoef=poly.koefVec.size()-1;polyKoef>=0;polyKoef--){
        if (!poly.coutZeroes&&!poly.koefVec[poly.koefVec.size()-1-polyKoef])
            continue;
        if (polyKoef!=poly.koefVec.size()-1)
            outstream<<" + ";
        outstream<<poly.koefVec[poly.koefVec.size() - 1 - polyKoef] << "x^" << polyKoef;
    }
    return outstream;
}

BinPolynomial BinPolynomial::operator*(std::vector<int>&otherVec){
    std::vector<int> thisVec=this->koefVec;
    std::vector<int> resultVec(thisVec.size()-1+otherVec.size());
    
    long count;
    for (count=thisVec.size()-1;count>=0;count--){
        long realPos=thisVec.size()-1-count;
        if (thisVec[realPos]==0)
            continue;
        long otherCount;
        for (otherCount=otherVec.size()-1;otherCount>=0;otherCount--){
            long otherRealPos=otherVec.size()-1-otherCount;
            if (otherVec[otherRealPos]==0)
                continue;
            
            long sumDegree=count+otherCount;
            resultVec[resultVec.size() - 1 - sumDegree]=1;
        }
    }
    
    BinPolynomial resPoly(resultVec);
    return resPoly;
}

BinPolynomial BinPolynomial::operator*(BinPolynomial&poly){
    std::vector<int> thisVec=this->koefVec;
    std::vector<int> otherVec=poly.koefVec;
    std::vector<int> resultVec(thisVec.size()-1+otherVec.size());

    long count;
    for (count=thisVec.size()-1;count>=0;count--){
        long realPos=thisVec.size()-1-count;
        if (thisVec[realPos]==0)
            continue;
        long otherCount;
        for (otherCount=otherVec.size()-1;otherCount>=0;otherCount--){
            long otherRealPos=otherVec.size()-1-otherCount;
            if (otherVec[otherRealPos]==0)
                continue;
            
            long sumDegree=count+otherCount;
            resultVec[resultVec.size() - 1 - sumDegree]=1;
        }
    }
    
    BinPolynomial resPoly(resultVec);
    return resPoly;
}

BinPolynomial BinPolynomial::operator/(BinPolynomial&poly){
    std::vector<int> tVec=this->koefVec;
    std::vector<int> oVec=poly.koefVec;
    std::reverse(tVec.begin(), tVec.end());
    std::reverse(oVec.begin(), oVec.end());
    
    std::vector<int> buffer1(tVec);
    std::vector<int> buffer2(tVec.size());
    std::vector<int> buffer3(tVec.size());
    std::vector<int> result(tVec.size());
#ifdef DEBUG_OTK
    int i=0;
#endif
    while (buffer3.size()>=oVec.size()){
#ifdef DEBUG_OTK
        std::cout << "Iteration " << i << "\n";
#endif
        int delta=(int)(buffer1.size()-oVec.size());
        result[delta]=1;
#ifdef DEBUG_OTK
        std::cout << "Got delta = " << delta << "\n";
#endif
        for (int i=0;i<oVec.size();i++){
            if (oVec[i]==1) buffer2[i+delta]=1;
            else buffer2[i+delta]=0;
        }
#ifdef DEBUG_OTK
        std::cout << "Buffer 1(Delemited) = " << buffer1 << "\n";
        std::cout << "Buffer 2(Delimiter) = " << buffer2 << "\n";
#endif
        for (int i=0;i<tVec.size();i++) buffer3[i]=(buffer1[i] + buffer2[i]) % 2;
        for (int i=0;i<buffer3.size();i++) buffer1[i]=buffer3[i];
#ifdef DEBUG_OTK
        std::cout << "Buffer 3(Resulter) = " << buffer3 << "\n";
#endif
        optiSizeVector(&buffer3);
        optiSizeVector(&buffer2);
        optiSizeVector(&buffer1);
#ifdef DEBUG_OTK
        i++;
        if (i>6)
            break;
#endif
    }
    std::reverse(result.begin(), result.end());
    BinPolynomial res(result);
    return res;
}

BinPolynomial BinPolynomial::operator%(BinPolynomial&poly){
    std::vector<int> tVec=this->koefVec;
    std::vector<int> oVec=poly.koefVec;
    std::reverse(tVec.begin(), tVec.end());
    std::reverse(oVec.begin(), oVec.end());
    
    std::vector<int> buffer1(tVec);
    std::vector<int> buffer2(tVec.size());
    std::vector<int> buffer3(tVec.size());
    std::vector<int> result(tVec.size());
#ifdef DEBUG_OTK
    int i=0;
#endif
    while (buffer3.size()>=oVec.size()){
#ifdef DEBUG_OTK
        std::cout << "Iteration " << i << "\n";
#endif
        int delta=(int)(buffer1.size()-oVec.size());
        result[delta]=1;
#ifdef DEBUG_OTK
        std::cout << "Got delta = " << delta << "\n";
#endif
        for (int i=0;i<oVec.size();i++){
            if (oVec[i]==1) buffer2[i+delta]=1;
            else buffer2[i+delta]=0;
        }
#ifdef DEBUG_OTK
        std::cout << "Buffer 1(Delimited) = " << buffer1 << "\n";
        std::cout << "Buffer 2(Delimiter) = " << buffer2 << "\n";
#endif
        for (int i=0;i<tVec.size();i++) buffer3[i]=(buffer1[i] + buffer2[i]) % 2;
        for (int i=0;i<buffer3.size();i++) buffer1[i]=buffer3[i];
#ifdef DEBUG_OTK
        std::cout << "Buffer 3(Resulter) = " << buffer3 << "\n";
#endif
        optiSizeVector(&buffer3);
        optiSizeVector(&buffer2);
        optiSizeVector(&buffer1);
#ifdef DEBUG_OTK
        i++;
        if (i>6)
            break;
#endif
    }
    std::reverse(buffer3.begin(), buffer3.end());
    BinPolynomial modulo(buffer3);
    return modulo;
}

void optiSizeVector(std::vector<int>*vec){
    for (int i=(int)vec->size()-1;i>=0;i--){
        if ((*vec)[i]==0){
            vec->resize(vec->size()-1);
        }
        else{
            break;
        }
    }
#ifdef DEBUG_OTK
    std::cout << "In optiSize vec size on out = " << vec->size() << "\n";
#endif
}

BinPolynomial BinPolynomial::operator+(BinPolynomial&poly){
#ifdef DEBUG_OTK
    assert(false);
#endif
}



