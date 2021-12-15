#include <iostream>

using namespace std;

template <class T> class Vector{
private:
void Expand();
size_t m_size, m_memsize;
T* m_stor;
public:
Vector();

void PushBack(const T& el);

void PopBack();

T& Back();

const T& Back() const;

size_t Size() const;

T& operator[](size_t i);

const T& operator[](size_t i) const;

~Vector();

Vector& operator= (Vector<T>&& rhs);

Vector& operator= (const Vector<T>& rhs);

Vector(Vector<T>&& rhs);

Vector(const Vector<T>& rhs);

T* begin() const;

T* end() const;

friend ostream& operator<<(ostream& out, const Vector& v);
};

template <class T>
void Vector<T>::Expand(){
size_t new_size = m_memsize * 2;
T* new_stor = new T[new_size];
for(size_t i = 0; i < m_memsize; i++){
new_stor[i] = m_stor[i];
}
swap(new_stor, m_stor);
swap(new_size, m_memsize);
delete[] new_stor;
}

template <class T>
Vector<T>::Vector(): m_size(0), m_memsize(16) {
m_stor = new T[m_memsize];
}

template <class T>
void Vector<T>::PushBack(const T& el){
if(m_size >= m_memsize){
Expand();
}
m_stor[m_size] = el;
m_size++;
}

template <class T>
void Vector<T>::PopBack(){
m_size--;
}

template <class T>
T& Vector<T>::Back() {
return m_stor[m_size-1];
}

template <class T>
const T& Vector<T>::Back() const{
return m_stor[m_size-1];
}

template <class T>
size_t Vector<T>::Size() const{
return m_size;
}

template <class T>
T& Vector<T>::operator[](size_t i){
return m_stor[i];
}

template <class T>
const T& Vector<T>::operator[](size_t i) const{
return m_stor[i];
}

template <class T>
Vector<T>::~Vector(){
delete[] m_stor;
}

template <class T>
Vector<T>& Vector<T>::operator= (Vector<T>&& rhs){
if (this == &rhs) return *this;
Vector<T> t(std::move(rhs));

swap(m_size, t.m_size);
swap(m_stor, t.m_stor);
swap(m_memsize, t.m_memsize);

return *this;
}

template <class T>
Vector<T>& Vector<T>::operator= (const Vector<T>& rhs){
if (this == &rhs) return *this;
Vector<T> t(rhs);

swap(m_size, t.m_size);
swap(m_stor, t.m_stor);
swap(m_memsize, t.m_memsize);

return *this;
}

template <class T>
Vector<T>::Vector(Vector<T>&& rhs){
m_size = rhs.m_size;
m_memsize = rhs.m_memsize;
m_stor = rhs.m_stor;

rhs.m_size = 0;
rhs.m_memsize = 0;
rhs.m_stor = nullptr;
}

template <class T>
Vector<T>::Vector(const Vector<T>& rhs): m_size(rhs.m_size), m_memsize(rhs.m_memsize){
m_stor = new T[m_memsize];
for (size_t i = 0; i < m_size; ++i){
m_stor[i] = rhs.m_stor[i];
}
}

template <class T>
T* Vector<T>::begin() const{
return m_stor;
};

template <class T>
T* Vector<T>::end() const{
return m_stor + m_size;
}

template <class T>
ostream& operator<<(std::ostream& out, const Vector<T>& v){
out << "(";
for (size_t i = 0; i<v.m_size-1; ++i){
out << v[i] << ", ";
}
out << v[v.m_size-1]<<")";
return out;
}