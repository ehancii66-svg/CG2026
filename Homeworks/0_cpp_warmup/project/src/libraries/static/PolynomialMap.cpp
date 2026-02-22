#include "PolynomialMap.h"

#include <iostream>
#include <fstream>
#include <cassert>
#include <cmath>

using namespace std;

PolynomialMap::PolynomialMap(const PolynomialMap& other) {
    // TODO
	m_Polynomial = other.m_Polynomial;
}

PolynomialMap::PolynomialMap(const string& file) {
    ReadFromFile(file);
}

PolynomialMap::PolynomialMap(const double* cof, const int* deg, int n) {
	// TODO
	assert(n > 0);
	for(int i = 0; i < n; i++) {
		m_Polynomial[deg[i]] = cof[i];
	}
}

PolynomialMap::PolynomialMap(const vector<int>& deg, const vector<double>& cof) {
	assert(deg.size() == cof.size());
	// TODO
	for(int i = 0; i < deg.size(); i++) {
		m_Polynomial[deg[i]] = cof[i];
	}
}

double PolynomialMap::coff(int i) const {
	// TODO
	auto iter = m_Polynomial.find(i);
	if(iter != m_Polynomial.end()) {
		return iter->second;
	}
	return 0.f; // you should return a correct value
}

double& PolynomialMap::coff(int i) {
	// TODO
	return m_Polynomial[i];
}

void PolynomialMap::compress() {
	// TODO
	auto iter = m_Polynomial.begin();
	while(iter!= m_Polynomial.end()) {
		if(abs(iter->second) < 1e-10) {
			iter = m_Polynomial.erase(iter);
		}
		else {
			++iter;
		}
	}
}

PolynomialMap PolynomialMap::operator+(const PolynomialMap& right) const {
	// TODO
	PolynomialMap result(right);
	for(auto iter = m_Polynomial.begin(); iter!= m_Polynomial.end(); ++iter){
		result.m_Polynomial[iter->first] += iter->second;
	}
	result.compress();
	return result;
}


PolynomialMap PolynomialMap::operator-(const PolynomialMap& right) const {
	// TODO
	PolynomialMap result(right);
	for(auto iter = m_Polynomial.begin(); iter!= m_Polynomial.end(); ++iter){
		result.m_Polynomial[iter->first] -= iter->second;
	}
	result.compress();
	return result;
}

PolynomialMap PolynomialMap::operator*(const PolynomialMap& right) const {
	// TODO
	PolynomialMap result;
	for(auto iter1 = m_Polynomial.begin(); iter1!= m_Polynomial.end(); ++iter1){
		for(auto iter2 = right.m_Polynomial.begin(); iter2!= right.m_Polynomial.end(); ++iter2){
			result.m_Polynomial[iter1->first + iter2->first] += iter1->second * iter2->second;
		}
	}
	result.compress();
	return result;
}


PolynomialMap& PolynomialMap::operator=(const PolynomialMap& right) {
	// TODO
	m_Polynomial = right.m_Polynomial;
	return *this;
}

void PolynomialMap::Print() const {
	// TODO
	if(m_Polynomial.empty()){
        cout << "0" << endl;
        return ;
    }
    for(auto iter = m_Polynomial.begin(); iter != m_Polynomial.end(); ++iter) {
        if(iter != m_Polynomial.begin() && iter->second > 0) {
            cout << "+";
        }
        if(iter->first == 0) {
            cout << iter->second << " ";
        }
        else if(iter->first == 1) {
            cout << iter->second << "x ";
        }
        else {
        cout << iter->second << "x^" << iter->first << " ";
        }
    }
    cout << endl;
}

bool PolynomialMap::ReadFromFile(const string& file) {
    m_Polynomial.clear();
	// TODO
	ifstream fin(file);
	if(!fin.is_open()) {
		cout << "Failed to open file: " << file << endl;
		return false;
	}
	string line;
	int n;
	fin >> line;
	fin >> n;
	for(int i = 0; i < n; i++) {
		int deg;
		double cof;
		fin >> deg >> cof;
		m_Polynomial[deg] = cof;
	}
	compress();
	fin.close();
 	return true; // you should return a correct value
}
