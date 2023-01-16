//
// Created by haram on 2023-01-15.
//
#include <iostream>

using namespace std;

// 단일 노드 클래스 정의
struct singly_ll_node
{
    int data;
    singly_ll_node* next;
};

// singly_ll_node를 사용하는 연결 리스트 클래스
class singly_ll{
public:
    using node = singly_ll_node;
    using node_ptr = node*;

private:
    node_ptr head;

public:

    // 맨 앞에 val 추가
    void push_front(int val){
        auto new_node = new node {val, nullptr};
        if(head != nullptr){
            new_node->next = head;
        }
        head = new_node;
    }

    // 맨 앞에 있는 element 제거
    void pop_front(){
        auto first = head;
        if(head){
            head = head->next;
            delete first;
            head = nullptr;
        }
    }

    // singly_ll의 반복자
    struct singly_ll_iterator{
    private:
        node_ptr ptr;
    public:
        singly_ll_iterator(node_ptr p) : ptr(p){}

        int& operator*(){return ptr->data;}

        node_ptr get(){return ptr;}

        // 선행 증가
        singly_ll_iterator& operator++(){
            ptr = ptr->next;
            return *this;
        }
        // 후행 증가
        singly_ll_iterator operator++(int){
            singly_ll_iterator result = *this;
            ++(*this);
            return result;
        }

        // 관계 연산자
        friend bool operator==(const singly_ll_iterator& left, const singly_ll_iterator& right){
            return left.ptr == right.ptr;
        }
        friend bool operator!=(const singly_ll_iterator& left, const singly_ll_iterator& right){
            return left.ptr != right.ptr;
        }
    };

    // begin, end 함수
    singly_ll_iterator begin(){return singly_ll_iterator(head);}
    singly_ll_iterator end(){return singly_ll_iterator(NULL);}
    singly_ll_iterator begin() const{return singly_ll_iterator(head);}
    singly_ll_iterator end() const{return singly_ll_iterator(NULL);}

    // 생성자
    singly_ll() = default;

    // 복사 생성자 (깊은 복사)
    singly_ll(const singly_ll& other) : head(NULL){
        if(other.head){
            head = new node{0, NULL};
            auto cur = head;
            auto it = other.begin();
            while(true){
                cur->data = *it;
                auto tmp = it;
                ++tmp;

                if(tmp == other.end())
                    break;

                cur->next = new node {0, NULL};
                cur = cur->next;
                it = tmp;
            }
        }
    }

    // 초기화 리스트를 사용하는 생성자
    singly_ll(const initializer_list<int>& ilist) : head(NULL){
        for(auto it = rbegin(ilist); it != rend(ilist); it++)
            push_front(*it);
    }

};

int main(){
    singly_ll sll = {1, 2, 3};
    sll.push_front(0);

    cout << "첫 번째 리스트: ";
    for(auto i : sll)
        cout << i << " "; // 출력: 0 1 2 3
    cout << endl;

    auto sll2 = sll;
    sll2.push_front(-1);
    cout << "첫 번째 리스트를 복사한 후, 맨 앞에 -1 추가: ";
    for(auto i : sll2)
        cout << i << " ";
    cout << endl;

    cout << "깊은 복사 후 첫 번째 리스트: ";
    for(auto i : sll)
        cout << i << " ";
    cout << endl;


    return 0;
}