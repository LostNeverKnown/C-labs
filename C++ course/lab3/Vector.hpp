#pragma once
#include<iostream>
template<typename T>
class Vector {
private:
	T* elements;
	int nrOfElements;
	int m_capacity;
	void expand();
public:
	Vector();
	~Vector();
	Vector(const Vector& other);
	Vector& operator=(const Vector& other);
	Vector(Vector&& other) noexcept;
	Vector& operator=(Vector&& other) noexcept;
	T& at(const int index) const;
	T& operator[](const int index) const;
	T& front() const;
	T& back() const;
	const T* data() const;
	int size() const;
	int capacity() const;
	bool empty() const;
	void clear();
	void insert(const int index, const T& element);
	void erase(const int index);
	void push_back(const T& element);
	void pop_back();
};

template<typename T>
inline void Vector<T>::expand()
{
	this->m_capacity *= 2;
	T* newVec = new T[this->m_capacity]{};
	for (int i = 0; i < this->nrOfElements; i++) {
		newVec[i] = this->elements[i];
	}
	delete[] this->elements;
	this->elements = nullptr;
	this->elements = newVec;
}

template<typename T>
inline Vector<T>::Vector()
	:m_capacity(20), nrOfElements(0)
{
	this->elements = new T[this->m_capacity]{};
}

template<typename T>
inline Vector<T>::~Vector()
{
	delete[] this->elements;
}

template<typename T>
inline Vector<T>::Vector(const Vector& other)
	:m_capacity(other.m_capacity), nrOfElements(other.nrOfElements)
{
	this->elements = new T[this->m_capacity]{};
	for (int i = 0; i < this->nrOfElements; i++) {
		this->elements[i] = other.elements[i];
	}
}

template<typename T>
inline Vector<T>& Vector<T>::operator=(const Vector& other)
{
	if (this != &other) {
		delete[] this->elements;
		this->m_capacity = other.m_capacity;
		this->nrOfElements = other.nrOfElements;
		this->elements = new T[this->m_capacity]{};
		for (int i = 0; i < this->nrOfElements; i++) {
			this->elements[i] = other.elements[i];
		}
	}
	return *this;
}

template<typename T>
inline Vector<T>::Vector(Vector&& other) noexcept
	:m_capacity(other.m_capacity), nrOfElements(other.nrOfElements)
{
	this->elements = other.elements;
	other.elements = nullptr;
	other.nrOfElements = 0;
	other.elements = new T[other.m_capacity]{};
}

template<typename T>
inline Vector<T>& Vector<T>::operator=(Vector&& other) noexcept
{
	if (this != &other) {
		delete[] this->elements;
		this->m_capacity = other.m_capacity;
		this->nrOfElements = other.nrOfElements;
		this->elements = other.elements;
		other.elements = nullptr;
		other.nrOfElements = 0;
		other.elements = new T[other.m_capacity]{};
	}
	return *this;
}

template<typename T>
inline T& Vector<T>::at(const int index) const
{
	if (index < 0 || index >= this->nrOfElements || this->nrOfElements == 0)
		throw (std::out_of_range("Empty vector or bad index"));
	return this->elements[index];
}

template<typename T>
inline T& Vector<T>::operator[](const int index) const
{
	if (index < 0 || index >= this->nrOfElements || this->nrOfElements == 0)
		throw std::out_of_range("Empty vector or bad index");
	return this->elements[index];
}

template<typename T>
inline T& Vector<T>::front() const
{
	if(this->nrOfElements != 0)
		return this->elements[0];
	throw std::out_of_range("Empty vector");
}

template<typename T>
inline T& Vector<T>::back() const
{
	if(this->nrOfElements != 0)
		return this->elements[this->nrOfElements - 1];
	throw std::out_of_range("Empty vector");
}

template<typename T>
inline const T* Vector<T>::data() const
{
	return this->elements;
}

template<typename T>
inline int Vector<T>::size() const
{
	return this->nrOfElements;
}

template<typename T>
inline int Vector<T>::capacity() const
{
	return this->m_capacity;
}

template<typename T>
inline bool Vector<T>::empty() const
{
	return this->nrOfElements == 0;
}

template<typename T>
inline void Vector<T>::clear()
{
	for (int i = 0; i < this->nrOfElements; i++) {
		this->elements[i] = {};
	}
	this->nrOfElements = 0;
}

template<typename T>
inline void Vector<T>::insert(const int index, const T& element)
{
	if (index <= this->nrOfElements && index >= 0) {
		if (this->nrOfElements == this->m_capacity-1) {
			expand();
		}
		for (int i = this->nrOfElements; i > index; i--) {
			this->elements[i] = this->elements[i - 1];
		}
		this->elements[index] = element;
		this->nrOfElements++;
	}
}

template<typename T>
inline void Vector<T>::erase(const int index)
{
	if (index < this->nrOfElements && index >= 0) {
		for (int i = index; i < this->nrOfElements; i++) {
			this->elements[i] = this->elements[i + 1];
		}
		this->elements[--this->nrOfElements] = {};
	}
}

template<typename T>
inline void Vector<T>::push_back(const T& element)
{
	if (this->nrOfElements == this->m_capacity-1) {
		expand();
	}
	this->elements[this->nrOfElements++] = element;
}

template<typename T>
inline void Vector<T>::pop_back()
{
	if (this->nrOfElements > 0) {
		this->elements[--this->nrOfElements] = {};
	}
}
