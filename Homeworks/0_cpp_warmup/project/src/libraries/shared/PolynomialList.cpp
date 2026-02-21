#include "PolynomialList.h"
#include <iostream>
#include <cassert>
#include <cmath>
#include <algorithm>
#include <fstream>

using namespace std;

PolynomialList::PolynomialList(const PolynomialList& other) {
    // TODO
    for(auto iter = other.m_Polynomial.begin(); iter!= other.m_Polynomial.end(); ++iter){
        m_Polynomial.push_back(*iter);
    }
}

PolynomialList::PolynomialList(const string& file) {
    // TODO
    ReadFromFile(file);
}

PolynomialList::PolynomialList(const double* cof, const int* deg, int n) {
    // TODO
    assert(n > 0);
    for(int i = 0; i < n; i++) {
       AddOneTerm(Term(deg[i], cof[i]));
    }
    
}

PolynomialList::PolynomialList(const vector<int>& deg, const vector<double>& cof) {
    // TODO
    int n = deg.size();
    assert(n == cof.size());
    assert(n > 0);
    for(int i = 0; i < n; i++) {
        AddOneTerm(Term(deg[i], cof[i]));
    }
}

double PolynomialList::coff(int i) const {
    // TODO
    for(auto iter = m_Polynomial.begin(); iter!= m_Polynomial.end(); ++iter){
        if(iter->deg > i){
            break;
        }
        if(iter->deg == i) {
            return iter->cof;
        }
    }
    return 0.0;                 //only for read,if not found,return 0.0
}             

double& PolynomialList::coff(int i) {
    return AddOneTerm(Term(i, 0)).cof;
}

void PolynomialList::compress() {
    // TODO
    for(auto iter = m_Polynomial.begin(); iter != m_Polynomial.end(); ++iter){
        if(fabs(iter->cof) <= 1.0e-10) {
            iter = m_Polynomial.erase(iter);
            iter--;
        }
    }
}

PolynomialList PolynomialList::operator+(const PolynomialList& right) const {
    // TODO
    PolynomialList result = (*this);
    for(auto iter = right.m_Polynomial.begin(); iter != right.m_Polynomial.end(); ++iter) {
        result.AddOneTerm(*iter);
    }
    result.compress();
    return result;
}

PolynomialList PolynomialList::operator-(const PolynomialList& right) const {
    // TODO
    PolynomialList result = (*this);
    for(auto iter = right.m_Polynomial.begin(); iter != right.m_Polynomial.end(); ++iter) {
        result.AddOneTerm(Term(iter->deg, -iter->cof));
    }
    result.compress();
    return result;
}

PolynomialList PolynomialList::operator*(const PolynomialList& right) const {
    // TODO
    PolynomialList result;
    for(auto iter1 = m_Polynomial.begin(); iter1 != m_Polynomial.end(); ++iter1) {
        for(auto iter2 = right.m_Polynomial.begin(); iter2 != right.m_Polynomial.end(); ++iter2) {
            result.AddOneTerm(Term(iter1->deg + iter2->deg, iter1->cof * iter2->cof));
        }
    }
    result.compress();
    return result;
}

PolynomialList& PolynomialList::operator=(const PolynomialList& right) {
    // TODO
    if (this != &right) {
        m_Polynomial = right.m_Polynomial;
    }
    return *this;
}

void PolynomialList::Print() const {
    // TODO
    if(m_Polynomial.empty()){
        cout << "0" << endl;
        return ;
    }
    for(auto iter = m_Polynomial.begin(); iter != m_Polynomial.end(); ++iter) {
        if(iter != m_Polynomial.begin() && iter->cof > 0) {
            cout << "+";
        }
        if(iter->deg == 0) {
            cout << iter->cof << " ";
        }
        else if(iter->deg == 1) {
            cout << iter->cof << "x ";
        }
        else {
        cout << iter->cof << "x^" << iter->deg << " ";
        }
    }
    cout << endl;
}

bool PolynomialList::ReadFromFile(const string& file) {
    // TODO
    m_Polynomial.clear();

    ifstream fin(file);
    if(!fin.is_open()){
        std::cout << "Error: cannot open file " << file << std::endl;
        return false;
    }
    char c;
    int n;
    fin >> c;
    fin >> n;
    for(int i = 0; i < n; i++) {
        int deg;
        double cof;
        fin >> deg;
        fin >> cof;
        AddOneTerm(Term(deg, cof));
    }
    fin.close();
    return true; // you should return a correct value
}

PolynomialList::Term& PolynomialList::AddOneTerm(const Term& term) {
    // TODO
    auto iter = m_Polynomial.begin();
    for(; iter != m_Polynomial.end(); ++iter) {
        if(iter->deg == term.deg){
            iter->cof += term.cof;
            return *iter;
        }
        if(iter->deg > term.deg) {
           break;
        }
    }
    return *m_Polynomial.insert(iter, term);
}
