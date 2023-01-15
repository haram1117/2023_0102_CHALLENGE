#include <iostream>
#include <algorithm>
using namespace std;

struct singly_ll_node {
    int data;
    singly_ll_node *next;   // linked list
};

class singly_ll {
public:
    using node = singly_ll_node;
    using node_ptr = node*;
    
    // 앞에 넣는다면 head 포인터를 이동시켜야 함
    void push_front(int val) {
        auto new_node = new node{val, NULL};
        if (head != NULL) {
            // 이미 원소가 있다면 next에 head를 넣어야 함
            new_node->next = head;
        }
        head = new_node;
    }
    
    void pop_front() {
        auto first = head;
        // 만약에 head라면
        if (head) {
            head = head->next;
            delete first;
            // head = NULL; 해줘야 함 아니면 제대로 동작안할지도
        }
    }
    
    // 기본 반복자
    struct singly_ll_iterator {
    private:
        node_ptr ptr;
    public:
        singly_ll_iterator(node_ptr p) : ptr(p) {}
        
        int& operator*() { return ptr->data; }
        
        node_ptr get() {return ptr;}
        
        singly_ll_iterator& operator++() {
            ptr = ptr->next;
            return *this;
        }
        
        singly_ll_iterator operator++(int) {
            singly_ll_iterator result = *this;
            ++(*this);  // 증가시키고 반환
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
    singly_ll_iterator end() {return singly_ll_iterator(NULL);} // 이걸 이렇게 한다고?
    singly_ll_iterator begin() const {return singly_ll_iterator(head);}
    singly_ll_iterator end() const {return singly_ll_iterator(NULL);} // 이걸 이렇게 한다고?
    
    singly_ll() = default;  // 깊은 복사 용
    
    singly_ll(const singly_ll& other) : head(NULL) {
        if (other.head) {
            head = new node{0, NULL};
            auto cur = head;
            auto it = other.begin();
            
            while(1) {
                cur->data = *it;
                
                auto tmp = it;
                ++tmp;
                if (tmp == other.end())
                    break;
                
                cur->next = new node{0, NULL};
                cur = cur->next;
                it = tmp;
            }
        }
    }

    singly_ll(const initializer_list<int>& ilist) : head(NULL) {
        for(auto it = rbegin(ilist); it != rend(ilist); it++) {
            push_front(*it);
        }
    }
    
private:
    node_ptr head;
};

int main() {
    singly_ll sll = {1, 2, 3};
    sll.push_front(0);
    
    cout<<"첫 번재 리스트: ";
    for (auto i : sll) {
        cout<<i<<", ";
    }
    cout<<endl;
    
    auto sll2 = sll;
    sll2.push_front(-1);
    cout<<"복사 후 -1 추가: ";
    for(auto i : sll2) {
        cout<<i<<", ";
    }
    cout<<endl;
}

