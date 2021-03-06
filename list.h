//
//双端链表
// Created by 王银峰 on 2021/4/8.
//

#ifndef DATA_AND_STRUCTURE_LIST_H
#define DATA_AND_STRUCTURE_LIST_H

#include <exception>

template <typename T>
class List {
private:
    struct Node {
        T data;
        Node* prev;
        Node* next;
        Node(const T& _data = T(), Node* _prev = nullptr, Node* _next = nullptr)
        : data(_data), prev(_prev), next(_next) {}
    };

public:
    class const_iterator {
    public:
        const_iterator() : cur(nullptr) {}

        const T& operator* () const {return retrieve(); }

        const_iterator& operator++ (){
            cur = cur->next;
            return *this;
        }

        const_iterator operator++ (int) {
            const_iterator old = *this;
            ++(*this);
            return old;
        }

        bool operator== (const const_iterator& rhs) const { return cur == rhs.cur; }

        bool operator!= (const const_iterator& rhs) const { return !(*this == rhs); }

    protected:
        const List<T>* m_List;
        Node* cur;
        T& retrieve() const { return cur->data; }

        //const_iterator(Node* p): cur(p) {}

        const_iterator(const List<T>* lst ,Node* p) : m_List(lst), cur(p) {}

        void assertIsValid() const {
            if(m_List == nullptr || cur==nullptr || cur == m_List->head)
                throw IteratorOutOfBoundsException();
        }

        friend class List<T>;
    };

    class iterator :public const_iterator{
    public:
        iterator() = default;

        T& operator* () { return this->retrieve(); }

        const T& operator* () const { return const_iterator::operator*(); }
        //前缀自增运算符
        iterator& operator++ () {
            this->cur = this->cur->next;
            return *this;
        }
        //后缀自增运算符
        iterator operator++ (int) {
            iterator old = *this;
            ++(*this);
            return old;
        }

    protected:

        iterator(List<T>* lst, Node* p):const_iterator(lst, p) {}

        friend class List<T>;
    };

public:
    List() { init(); }

    List(const List& rhs) {
        init();
        *this = rhs;
    }

    ~List() {
        clear();
        delete head;
        delete tail;
    }

    const List& operator= (const List& rhs) {
        if(this == &rhs)
            return *this;

        clear();
        for(const_iterator itr = rhs.begin(); itr != rhs.end(); ++itr){
            push_back(*itr);
        }
        return *this;
    }

    iterator insert(iterator itr, const T& data){
        itr.assertIsValid();
        if(itr.m_List != this){
            throw IteratorMismatchException();
        }
        Node* p = itr.cur;
        m_size++;
        /*
         * Node* newNode = new Node(data, p->prev, p);
         * p->prev->next = newNode;
         * p->prev = newNode;
         * */
        return iterator( this, p->prev = p->prev->next = new Node(data, data->prev, p) );
    }

    iterator erase(iterator itr){
        Node* p = itr.cur;
        iterator retVal(p->next);
        p->prev->next = p->next;
        p->next->prev = p->prev;
        delete p;
        m_size--;

        return retVal;
    }

    iterator erase(iterator start, iterator end){
        for(iterator itr = start; itr != end; erase(itr));

        return end;
    }

    int size() const { return m_size; }

    bool empty() const { return size() == 0; }

    void clear() {
        while(!empty()){
            pop_front();
        }
    }

    T& front() { return *begin(); }

    const T& front() const { return *begin(); }

    T& back() { return *--end(); }

    const T& back() const { return *--end(); }

    void push_front(const T& object) { insert(begin(), object); }

    void push_back(const T& object) { insert(end(), object); }

    void pop_front() { erase(begin()); }

    void pop_back() { erase(--end()); }

    iterator find(iterator start, iterator end, const T& object) {
        for(iterator itr = start; itr!=end; ++itr){
            if(itr.retrieve() == object)
                return itr;
        }
        return end();
    }

    iterator begin() { return iterator(this, head->next); }

    const_iterator begin() const { return const_iterator(this, head->next); }

    iterator end() { return iterator(this, tail); }

    const_iterator end() const { return const_iterator(this, tail); }

private:
    int m_size;
    Node* head;
    Node* tail;
    void init() {
        m_size = 0;
        head=  new Node;
        tail = new Node;
        head->next = tail;
        tail->prev = head;
    }

    struct IteratorOutOfBoundsException : public std::exception {
        const char* what() const throw () {
            return "IteratorOutOfBoundsException";
        }
    };

    struct IteratorMismatchException : public std::exception {
        const char* what() const throw () {
            return "IteratorMismatchException";
        }
    };
};


#endif //DATA_AND_STRUCTURE_LIST_H
