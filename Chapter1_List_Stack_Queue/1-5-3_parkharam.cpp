//
// Created by haram on 2023-01-15.
//
#include <iostream>
#include <forward_list>
#include <string>
using namespace std;

// 시민 정보를 저장할 구조체
struct citizen{
    string name;
    int age;
};

// 시민 정보 출력을 위한 << operator
ostream &operator<<(ostream &os, const citizen &c){
    return (os << "[" << c.name << ", " << c.age << "]");
}

int main(){
    forward_list<citizen> citizens = {{"Kim", 22}, {"Lee", 25}, {"Park", 18}, {"Jin", 16}};

    // 깊은 복사
    auto citizens_copy = citizens;

    // 모든 시민 출력
    cout << "ALL citizens: ";
    for(const auto &c: citizens)
        cout << c << " ";
    cout << endl;

    // 람다함수를 이용하여 citizen의 age가 19보다 작은 시민들 list에서 제거
    citizens.remove_if([](const citizen &c){
        return (c.age < 19);
    });

    // 투표할 수 있는 시민 출력
    cout << "citizens(can vote): ";
    for(const auto &c : citizens)
        cout << c << " ";
    cout << endl;

    // 18살이 아닌 시민 list에서 제거
    citizens_copy.remove_if([](const citizen &c){
        return (c.age != 18);
    });

    cout << "citizens(can vote next year): ";
    for(const auto &c : citizens_copy)
        cout << c << " ";
    cout << endl;


    return 0;
}
