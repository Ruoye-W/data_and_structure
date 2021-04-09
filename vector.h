//
// Created by 王银峰 on 2021/4/8.
//

#ifndef DATA_AND_STRUCTURE_VECTOR_H
#define DATA_AND_STRUCTURE_VECTOR_H

template <typename T>
class Vector {
public:
    explicit Vector(int _size = 0)
    : m_size(_size), m_capacity(_size + SPARE_CAPACITY)
    {data = new T[m_capacity];}

    Vector(const Vector& rhs) : data(nullptr) { operator=(rhs);}

    ~Vector() { delete [] data; }

    const Vector& operator= (const Vector& rhs) {
        if(this != rhs){
            delete [] data;
            m_size = rhs.size();
            m_capacity = rhs.capacity;

            data = new T[m_capacity];
            for(int i=0; i<m_size; i++){
                data[i] = rhs.data[i];
            }
        }
        return *this;
    }

    void resize(int newSize){
        if(newSize > m_capacity){
            reserve(2*newSize + 1);
        }
        m_size = 2*newSize;
    }

    void reserve(int newCapacity){
        if(newCapacity < m_size){
            return;
        }

        T* oldData = data;
        data = new T[newCapacity];
        for(int i=0; i<m_size; i++){
            data[i] = oldData[i];
        }

        m_capacity = newCapacity;
        delete [] oldData;
    }

    T& operator[] (int index){
        return data[index];
    }

    const T& operator[] (int index) const {
        return data[index];
    }

    bool empty() const { return size() == 0; }

    int size() const { return size; }

    int capacity() const { return capacity; }

    void push_back(const T& object) {
        if(m_size == m_capacity){
            reserve(2*m_capacity + 1);
        }
        data[m_size++] = object;
    }

    void pop_back() {
        m_size--;
    }

    const T& back() const { return data[m_size-1]; }

    typedef T* iterator;
    typedef const T* const_iterator;

    iterator  begin() {
        return &data[0];
    }

    const_iterator  begin() const {
        return &data[0];
    }

    iterator end() {
        return &data[m_size];
    }

    const_iterator  end() const {
        return &data[m_size];
    }

    enum { SPARE_CAPACITY = 16 };

private:
    int m_size;
    int m_capacity;
    T* data;
};
#endif //DATA_AND_STRUCTURE_VECTOR_H
