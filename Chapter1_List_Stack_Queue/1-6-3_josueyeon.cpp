#include <iostream>
#include <algorithm>
#include <string>
using namespace std;

struct singly_ll_node {
    string music;
    singly_ll_node *next;   // linked list
    singly_ll_node *prev;   // circular queue를 위한 이전 데이터
};

class singly_ll {
public:
    using node = singly_ll_node;
    using node_ptr = node*;
    
    singly_ll() : n(0) {
        head = new node{"no name", NULL, NULL};
        head->next = head;
        head->prev = head;
    }
    
    size_t size() const {
        return n;
    }
    
    
    void insert(const string& value) {
        node_ptr newNode = new node{value, NULL, NULL};
        n++;
        auto dummy = head->prev;
        dummy->next = newNode;
        newNode->prev = dummy;
        
        // 데이터가 1개밖에 없었다면
        if (head == dummy) {
            dummy->prev = newNode;
            newNode->next = dummy;
            head = newNode;
            return ;
        }
        
        newNode->next = head;
        head->prev = newNode;
        head = newNode;
    }
    
    void erase(const string& value) {
        auto cur = head, dummy = head->prev;
        // 원형 큐를 한바퀴 돌면서 전부 살펴봄
        while(cur != dummy) {
            // 삭제할 데이터라면
            if((cur->music) == value) {
                cur->prev->next = cur->next;
                cur->next->prev = cur->prev;
                // head 데이터면 delete 해야하니까
                if (cur == head) {
                    head = head->next;
                }
                delete cur;
                cur = NULL;
                n--;
            }
            cur = cur->next;
        }
    }
    
    // 기본 반복자
    struct singly_ll_iterator {
    private:
        node_ptr ptr;
    public:
        singly_ll_iterator(node_ptr p) : ptr(p) {}
        
        string& operator*() { return ptr->music; }
        
        node_ptr get() {return ptr;}
        
        singly_ll_iterator& operator++() {
            ptr = ptr->next;
            return *this;
        }
        
        singly_ll_iterator operator++(int) {
            singly_ll_iterator result = *this;
            ++(*this);  // 반복 연산자 자체를 증가시키고 반환
            return result;
        }
        
        friend bool operator==(const singly_ll_iterator& left, const singly_ll_iterator& right) {
            return left.ptr == right.ptr;
        }
        
        friend bool operator!=(const singly_ll_iterator& left, const singly_ll_iterator& right) {
            return left.ptr != right.ptr;
        }
    };
    
    singly_ll_iterator begin() {return singly_ll_iterator(head);}
    singly_ll_iterator end() {return singly_ll_iterator(head->prev);}
    singly_ll_iterator begin() const {return singly_ll_iterator(head);}
    singly_ll_iterator end() const {return singly_ll_iterator(head->prev);}

    singly_ll(const singly_ll& other) : singly_ll() {
        for(const auto& i : other)
            insert(i);
    }

    singly_ll(const initializer_list<string>& ilist) : head(NULL), n(0) {
        for(const auto& i : ilist)
            insert(i);
    }
    
    ~singly_ll() {
        // 데이터가 있으면
        while(size()) {
            erase(head->music);
        }
        delete head;
        head = NULL;
    }
    
private:
    node_ptr head;
    size_t  n; // circular queue 크기
};

