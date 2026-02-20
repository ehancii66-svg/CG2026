#pragma once
#include <iostream>
#include <cassert>

// interfaces of Dynamic Array class DArray
template<class T>
class DArray {
public:
	DArray(); // default constructor
	DArray(int nSize, const T& dValue = static_cast<T>(0)); // set an array with default values
	DArray(const DArray& arr); // copy constructor
	~DArray(); // deconstructor

	void Print() const; // print the elements of the array

	int GetSize() const; // get the size of the array
	void SetSize(int nSize); // set the size of the array

	const T& GetAt(int nIndex) const; // get an element at an index
	void SetAt(int nIndex, T dValue); // set the value of an element

	T& operator[](int nIndex); // overload operator '[]'
	const T& operator[](int nIndex) const; // overload operator '[]'

	void PushBack(T dValue); // add a new element at the end of the array
	void DeleteAt(int nIndex); // delete an element at some index
	void InsertAt(int nIndex, T dValue); // insert a new element at some index

	DArray& operator = (const DArray& arr); //overload operator '='

private:
	T* m_pData; // the pointer to the array memory
	int m_nSize; // the size of the array
	int m_nMax;

private:
	void Init(); // initilize the array
	void Free(); // free the array
	void Reserve(int nSize); // allocate enough memory
};




// default constructor
template<class T>
DArray<T>::DArray() {
	Init();
}

// set an array with default values
template<class T>
DArray<T>::DArray(int nSize, const T& dValue) {
	m_nMax = nSize;
	m_nSize = nSize;
	m_pData = new T[m_nSize];
	for(int i = 0; i < m_nSize; i++) {
		m_pData[i] = dValue;
	}

}
template<class T>
DArray<T>::DArray(const DArray& arr) {
	//TODO
	m_nMax = arr.m_nSize;
	m_nSize = arr.m_nSize;
	m_pData = new T[m_nSize];

	for(int i = 0; i < m_nSize; i++) {
		m_pData[i] = arr.m_pData[i];
	}

}

// deconstructor
template<class T>
DArray<T>::~DArray() {
	Free();
}

// display the elements of the array
template<class T>
void DArray<T>::Print() const {
	std::cout << "Size = " << m_nSize <<" " <<  "elements: ";
	for(int i = 0; i < m_nSize; i++) {
		std::cout << m_pData[i] << " ";
	}
	std::cout << std::endl;
	//TODO
}

// initilize the array
template<class T>
void DArray<T>::Init() {
	//TODO
	m_nSize = 0;
	m_nMax = 0;
	m_pData = nullptr;
}

// free the array
template<class T>
void DArray<T>::Free() {
	delete[] m_pData;
	Init();
	//TODO
}

// get the size of the array
template<class T>
int DArray<T>::GetSize() const {
	//TODO
	return m_nSize; // you should return a correct value
}

template<class T>
void DArray<T>::Reserve(int nSize) {
	if(nSize <= m_nMax) {
		return ;
	}
	
	while(m_nMax < nSize) {
		m_nMax = m_nMax == 0 ? 1 : m_nMax * 2;
	}

	T* pNewData = new T[m_nMax];
	for(int i = 0; i < m_nSize; i++) {
		pNewData[i] = m_pData[i];
	}
	delete[] m_pData;
	m_pData = pNewData;
}

// set the size of the array
template<class T>
void DArray<T>::SetSize(int nSize) {
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
template<class T>
const T& DArray<T>::GetAt(int nIndex) const {
	//TODO
	if(nIndex < 0 || nIndex >= m_nSize) {
		std :: cout << "Error: index out of range" << std :: endl;
		assert(false); 
	}

	return	m_pData[nIndex]; // you should return a correct value
}

// set the value of an element 
template<class T>
void DArray<T>::SetAt(int nIndex, T dValue) {
	//TODO
	assert(nIndex >= 0 && nIndex < m_nSize);
	m_pData[nIndex] = dValue;
}

// overload operator '[]'
template<class T>
T& DArray<T>::operator[](int nIndex) {
	// TODO
	assert(nIndex >= 0 && nIndex < m_nSize);
	return m_pData[nIndex]; // you should return a correct value
}

// add a new element at the end of the array
template<class T>
void DArray<T>::PushBack(T dValue) {
	//TODO
	
	Reserve(m_nSize + 1);

	m_pData[m_nSize] = dValue;
	m_nSize++;
}

// delete an element at some index
template<class T>
void DArray<T>::DeleteAt(int nIndex) {
	assert(nIndex >= 0 && nIndex < m_nSize);
	for(int i = nIndex; i < m_nSize - 1; i++) {
		m_pData[i] = m_pData[i + 1];
	}
	m_nSize--;
	//TODO
}

// insert a new element at some index
template<class T>
void DArray<T>::InsertAt(int nIndex, T dValue) {
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
template<class T>
DArray<T>& DArray<T>::operator = (const DArray& arr) {
	//TODO
	Reserve(arr.m_nSize);
	m_nSize = arr.m_nSize;
	for(int i = 0; i < m_nSize; i++) {
		m_pData[i] = arr.m_pData[i];
	}

	return *this;
}

