// implementation of class DArray
#include <iostream>
#include "DArray.h"

// default constructor
DArray::DArray() {
	Init();
}

// set an array with default values
DArray::DArray(int nSize, double dValue) {
	m_nSize = nSize;
	Init();
	for(int i = 0; i < nSize; i++) {
		m_pData[i] = dValue;
	}
	//TODO
}

DArray::DArray(const DArray& arr) {
	m_nSize = arr.m_nSize;
	m_pData = new double[m_nSize];
	for(int i = 0; i < m_nSize; i++) {
		m_pData[i] = arr.m_pData[i];
	}
	//TODO
}

// deconstructor
DArray::~DArray() {
	Free();
}

// display the elements of the array
void DArray::Print() const {
	std::cout << "Size = " << m_nSize <<" " <<  "elements: ";
	for(int i = 0; i < m_nSize; i++) {
		std::cout << m_pData[i] << " ";
	}
	std::cout << std::endl;
	//TODO
}

// initilize the array
void DArray::Init() {
	m_nSize = 0;
	m_pData = nullptr;
	//TODO
}

// free the array
void DArray::Free() {
	delete[] m_pData;
	Init();
	//TODO
}

// get the size of the array
int DArray::GetSize() const {
	int nSize = m_nSize;
	//TODO
	return nSize; // you should return a correct value
}

// set the size of the array
void DArray::SetSize(int nSize) {
	if(nSize < 0){
		std::cout << "Error: size should be non-negative" << std::endl;
		return;
	}
	double* pData = new double[nSize];
	if(m_nSize > nSize){
		for(int i = 0; i < nSize; i++) {
			pData[i] = m_pData[i];
		}
		for(int i = nSize; i < m_nSize; i++) {
			pData[i] = 0.0;
		}
	}
	else{
		for(int i = 0; i < m_nSize; i++) {
			pData[i] = m_pData[i];
		}
		for(int i = m_nSize; i < nSize; i++) {
			pData[i] = 0.0;
		}
	}
	delete[] m_pData;
	m_pData = pData;
	m_nSize = nSize;	
	//TODO
}

// get an element at an index
const double& DArray::GetAt(int nIndex) const {
	if(nIndex < 0 || nIndex >= m_nSize){
        throw std::out_of_range("Error: index out of bounds");
    }
	//TODO
	return m_pData[nIndex]; // you should return a correct value
}

// set the value of an element 
void DArray::SetAt(int nIndex, double dValue) {
	if(nIndex < 0 || nIndex >= m_nSize){
		return;
	}
	m_pData[nIndex] = dValue;
	//TODO
}

// overload operator '[]'
const double& DArray::operator[](int nIndex) const {
	if(nIndex < 0 || nIndex >= m_nSize){
        throw std::out_of_range("Error: index out of bounds");
    }
	//TODO
	return m_pData[nIndex]; // you should return a correct value
}

// add a new element at the end of the array
void DArray::PushBack(double dValue) {
	double* pData = new double[m_nSize + 1];
	for(int i = 0; i < m_nSize; i++) {
		pData[i] = m_pData[i];
	}
	pData[m_nSize] = dValue;
	delete[] m_pData;
	m_pData = pData;
	m_nSize++;
	//TODO
}

// delete an element at some index
void DArray::DeleteAt(int nIndex) {
	if(nIndex < 0 || nIndex >= m_nSize){
		std::cout << "Error: index out of bounds" << std::endl;
		return ;
	}
	double* pData = new double[m_nSize - 1];
	for(int i = 0; i < nIndex; i++) {
		pData[i] = m_pData[i];
	}
	for(int i = nIndex + 1; i < m_nSize; i++) {
		pData[i - 1] = m_pData[i];
	}
	delete[] m_pData;
	m_pData = pData;
	m_nSize--;
	//TODO
}

// insert a new element at some index
void DArray::InsertAt(int nIndex, double dValue) {
	if(nIndex < 0 || nIndex > m_nSize){
		std::cout << "Error: index out of bounds" << std::endl;
		return ;
	}
	double* pData = new double[m_nSize + 1];
	for(int i = 0; i < nIndex; i++) {
		pData[i] = m_pData[i];
	}
	for(int i = nIndex; i < m_nSize; i++) {
		pData[i + 1] = m_pData[i];
	}
	pData[nIndex] = dValue;
	delete[] m_pData;
	m_pData = pData;
	m_nSize++;
	//TODO
}

// overload operator '='
DArray& DArray::operator = (const DArray& arr) {
	//TODO
	if(this != &arr){
		Free();
		m_nSize = arr.m_nSize;
		m_pData = new double[m_nSize];
		for(int i = 0; i < m_nSize; i++) {
			m_pData[i] = arr.m_pData[i];
		}
	}
	return *this;
}
