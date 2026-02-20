// implementation of class DArray
#include <iostream>
#include "DArray.h"
#include <cassert>

// default constructor
DArray::DArray() {
	Init();
}

// set an array with default values
DArray::DArray(int nSize, double dValue) {
	//TODO
	m_nMax = nSize;
	m_nSize = nSize;
	m_pData = new double[m_nSize];
	for(int i = 0; i < m_nSize; i++) {
		m_pData[i] = dValue;
	}

}

DArray::DArray(const DArray& arr) {
	//TODO
	m_nMax = arr.m_nSize;
	m_nSize = arr.m_nSize;
	m_pData = new double[m_nSize];

	for(int i = 0; i < m_nSize; i++) {
		m_pData[i] = arr.m_pData[i];
	}

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
	//TODO
	m_nSize = 0;
	m_nMax = 0;
	m_pData = nullptr;
}

// free the array
void DArray::Free() {
	delete[] m_pData;
	Init();
	//TODO
}

// get the size of the array
int DArray::GetSize() const {
	//TODO
	return m_nSize; // you should return a correct value
}

void DArray::Reserve(int nSize) {
	if(nSize <= m_nMax) {
		return ;
	}
	
	while(m_nMax < nSize) {
		m_nMax = m_nMax == 0 ? 1 : m_nMax * 2;
	}

	double* pNewData = new double[m_nMax];
	for(int i = 0; i < m_nSize; i++) {
		pNewData[i] = m_pData[i];
	}
	delete[] m_pData;
	m_pData = pNewData;
}

// set the size of the array
void DArray::SetSize(int nSize) {
	if(nSize < 0){
		std::cout << "Error: size cannot be negative" << std::endl;
		return ;
	}
	Reserve(nSize);
	for(int i = m_nSize; i < nSize; i++) {
		m_pData[i] = 0.0;
	}
	m_nSize = nSize;
	//TODO
}

// get an element at an index
const double& DArray::GetAt(int nIndex) const {
	//TODO
	if(nIndex < 0 || nIndex >= m_nSize) {
		std :: cout << "Error: index out of range" << std :: endl;
		assert(false); 
	}

	return	m_pData[nIndex]; // you should return a correct value
}

// set the value of an element 
void DArray::SetAt(int nIndex, double dValue) {
	//TODO
	assert(nIndex >= 0 && nIndex < m_nSize);
	m_pData[nIndex] = dValue;
}

// overload operator '[]'
double& DArray::operator[](int nIndex) {
	// TODO
	assert(nIndex >= 0 && nIndex < m_nSize);
	return m_pData[nIndex]; // you should return a correct value
}

// add a new element at the end of the array
void DArray::PushBack(double dValue) {
	//TODO
	
	Reserve(m_nSize + 1);

	m_pData[m_nSize] = dValue;
	m_nSize++;
}

// delete an element at some index
void DArray::DeleteAt(int nIndex) {
	assert(nIndex >= 0 && nIndex < m_nSize);
	for(int i = nIndex; i < m_nSize - 1; i++) {
		m_pData[i] = m_pData[i + 1];
	}
	m_nSize--;
	//TODO
}

// insert a new element at some index
void DArray::InsertAt(int nIndex, double dValue) {
	assert(nIndex >= 0 && nIndex <= m_nSize);
	
	Reserve(m_nSize + 1);

	for(int i = m_nSize; i > nIndex; i--) {
		m_pData[i] = m_pData[i - 1];
	}
	m_pData[nIndex] = dValue;
	m_nSize++;
	//TODO
}

// overload operator '='
DArray& DArray::operator = (const DArray& arr) {
	//TODO
	Reserve(arr.m_nSize);
	m_nSize = arr.m_nSize;
	for(int i = 0; i < m_nSize; i++) {
		m_pData[i] = arr.m_pData[i];
	}

	return *this;
}
