//
// Created by haram on 2023-01-15.
//
#include <iostream>
#include <algorithm>
#include <string>

using namespace std;

struct music_node{
    string data;
    music_node* next;
    music_node* prev;
};

class circular_ll;
struct circular_ll_iterator{
private:
    music_node* ptr;
public:
    explicit circular_ll_iterator(music_node* p) : ptr(p){}
    string& operator*(){return ptr->data;}

    music_node* get(){return ptr;}

    circular_ll_iterator& operator++(){
        ptr = ptr->next;
        return *this;
    }
    circular_ll_iterator operator++(int){
        circular_ll_iterator result = *this;
        ++(*this);
        return result;
    }
    circular_ll_iterator operator--(){
        ptr = ptr->prev;
        return *this;
    }
    circular_ll_iterator operator--(int){
        circular_ll_iterator result = *this;
        --(*this);
        return result;
    }

    friend bool operator==(const circular_ll_iterator& left, const circular_ll_iterator& right){
        return left.ptr == right.ptr;
    }
    friend bool operator!=(const circular_ll_iterator& left, const circular_ll_iterator& right){
        return left.ptr != right.ptr;
    }
};
class circular_ll{
public:
    using node = music_node;
    using node_ptr = node*;

private:
    node_ptr head;
    size_t n;

public:
    // 현재 head 앞에 value 값을 갖는 노드 추가
    void insert(const string& value){
        auto newNode = new node {value, nullptr, nullptr};
        n++;

        auto temp = head->prev;
        temp->next = newNode;
        newNode->prev = temp;

        if(temp == head){ // 첫 elem 삽입
            temp->prev = newNode;
            newNode->next = temp;
            head = newNode;
            return;
        }

        // 현재 head와 newNode 이어주기
        newNode->next = head;
        head->prev = newNode;
        head = newNode;
    }

    void erase(const string& value){
        auto current = head;
        auto temp = head->prev;
        while (current != temp){
            if(current->data == value){
                // 지워야 하는 node 앞 뒤 포인터 연결
                current->next->prev = current->prev;
                current->prev->next = current->next;

                // 가장 앞에 있는 node면 head 포인터 뒤로 옮기기
                if(current == head)
                    head = head->next;
                delete current;
                n--;
                return;
            }
            current = current->next;
        }
    }
    circular_ll_iterator begin(){return circular_ll_iterator{head};}
    circular_ll_iterator end(){return circular_ll_iterator{nullptr};}
    [[nodiscard]] circular_ll_iterator begin() const{return circular_ll_iterator{head};}
    [[nodiscard]] circular_ll_iterator end() const{return circular_ll_iterator{nullptr};}

    circular_ll():n(0){
        head = new node{"", nullptr, nullptr};
        head->next = head;
        head->prev = head;
    }
    [[nodiscard]] size_t size() const{
        return n;
    }
};

struct playlist{
    circular_ll list;
    circular_ll_iterator nowSong = list.begin();
    void insert(const string& song){
        list.insert(song);
        nowSong = list.begin();
    }
    void remove(const string& song){
        list.erase(song);
        nowSong = list.begin();
    }
    string next(){
        nowSong++;
        return nowSong.get()->data;
    }
    string previous(){
        nowSong--;
        return nowSong.get()->data;
    }
    void printall(int value){
        auto it = list.begin();
        for(int i = 0; i < value; i++){
            if(*it == ""){
                i--;
                ++it;
                continue;
            }
            cout << *it << " ";
            ++it;
        }
        cout << endl;
    }
    void printNowMusic(){
        cout << nowSong.get()->data << endl;
    }
};

int main(){
    playlist music_playlist;
    music_playlist.insert("music4");
    music_playlist.insert("music3");
    music_playlist.insert("music2");
    music_playlist.insert("music1");

    cout << "all Music: ";
    music_playlist.printall(music_playlist.list.size());

    cout << "nowMusic: ";
    music_playlist.printNowMusic();

    cout << "nextMusic: ";
    music_playlist.next();
    music_playlist.printNowMusic();

    cout << "prevMusic: ";
    music_playlist.previous();
    music_playlist.printNowMusic();

    cout << "music(6): ";
    music_playlist.printall(6);

    cout << "erase 3: ";
    music_playlist.remove("music3");
    music_playlist.printall(music_playlist.list.size());
}