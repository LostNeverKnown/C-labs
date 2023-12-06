/**
 *  TODO:
 *  1. Create include guard / header guard
 *  2. Define the class 'Vector'
 *  3. Declare necessary members
 *  4. Define templated member functions in this file
 */
#pragma once
template<typename T>
class Vector {
private:
	T* elements;
	int nrOfElements;
	int capacity;
	void expand();
public:
	Vector();
	~Vector();
	Vector(const Vector& other);
	Vector& operator=(const Vector& other);
	Vector(Vector&& other);
	Vector& operator=(Vector&& other);
	T& at(const int index) const;
	T& operator[](const int index) const;
	T& front() const;
	T& back() const;
	const T* data() const;
	int size() const;
	int getCapacity() const;
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
	this->capacity *= 2;
	T* newVec = new T[this->capacity]{};
	for (int i = 0; i < this->nrOfElements; i++) {
		newVec[i] = this->elements[i];
	}
	delete[] this->elements;
	this->elements = newVec;
}

template<typename T>
inline Vector<T>::Vector()
	:capacity(3), nrOfElements(0)
{
	this->elements = new T[this->capacity]{};
}

template<typename T>
inline Vector<T>::~Vector()
{
	delete[] this->elements;
}

template<typename T>
inline Vector<T>::Vector(const Vector& other)
	:capacity(other.capacity), nrOfElements(other.nrOfElements)
{
	this->elements = new T[this->capacity]{};
	for (int i = 0; i < this->nrOfElements; i++) {
		this->elements[i] = other.elements[i];
	}
}

template<typename T>
inline Vector<T>& Vector<T>::operator=(const Vector& other)
{
	if (this != &other) {
		delete[] this->elements;
		this->capacity = other.capacity;
		this->nrOfElements = other.nrOfElements;
		this->elements = new T[this->capacity]{};
		for (int i = 0; i < this->nrOfElements; i++) {
			this->elements[i] = other.elements[i];
		}
	}
	return *this;
}

template<typename T>
inline Vector<T>::Vector(Vector&& other)
	:capacity(other.capacity), nrOfElements(other.nrOfElements)
{
	this->elements = other.elements;
	other.elements = nullptr;
}

template<typename T>
inline Vector<T>& Vector<T>::operator=(Vector&& other)
{
	if (this != &other) {
		delete[] this->elements;
		this->capacity = other.capacity;
		this->nrOfElements = other.nrOfElements;
		this->elements = other.elements;
		other.elements = nullptr;
	}
	return *this;
}

template<typename T>
inline T& Vector<T>::at(const int index) const
{
	if (index < this->nrOfElements && index >= 0) {
		return this->elements[index];
	}
}

template<typename T>
inline T& Vector<T>::operator[](const int index) const
{
	if (index < this->nrOfElements && index >= 0) {
		return this->elements[index];
	}
}

template<typename T>
inline T& Vector<T>::front() const
{
	return this->elements[0];
}

template<typename T>
inline T& Vector<T>::back() const
{
	return this->elements[this->nrOfElements - 1];
}

template<typename T>
inline const T* Vector<T>::data() const
{
	return this;
}

template<typename T>
inline int Vector<T>::size() const
{
	return this->nrOfElements;
}

template<typename T>
inline int Vector<T>::getCapacity() const
{
	return this->capacity;
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
}

template<typename T>
inline void Vector<T>::insert(const int index, const T& element)
{
	if (index <= this->nrOfElements && index >= 0) {
		if (this->nrOfElements == this->capacity) {
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
	if (index <= this->nrOfElements && index >= 0) {
		for (int i = index; i < this->nrOfElements; i++) {
			this->elements[i] = this->elements[i + 1];
		}
		this->elements[--this->nrOfElements] = {};
	}
}

template<typename T>
inline void Vector<T>::push_back(const T& element)
{
	if (this->nrOfElements == this->capacity) {
		expand();
	}
	this->elements[this->nrOfElements] = element;
	this->nrOfElements++;
}

template<typename T>
inline void Vector<T>::pop_back()
{
	if (this->nrOfElements > 0) {
		this->elements[this->nrOfElements - 1] = {};
		this->nrOfElements--;
	}
}
