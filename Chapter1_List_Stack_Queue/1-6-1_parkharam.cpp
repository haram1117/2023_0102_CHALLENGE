//
// Created by haram on 2023-01-15.
//
#include <iostream>
#include <forward_list>
#include <vector>
#include <string>

using namespace std;

int main(){
    vector<string> vec = {
            "Lewis Hamilton", "Lewis Hamilton", "Nico Roseberg", "Sebastian Vettel", "Lewis Hamilton",
            "Sebastion Vettel", "Sebastion Vettel", "Sebastion Vettel", "Fernando Alonso"
    };

    auto it = vec.begin();
    cout << "가장 최근 우승자: " << *it << endl;

    it += 8;
    cout << "8년 전 우승자: " << *it << endl;

    advance(it, -3);
    cout << "그 후 3년 뒤 우승자: " << *it << endl;

    forward_list<string> fwd(vec.begin(), vec.end());

    auto it2 = fwd.begin();
    cout << "가장 최근 우승자: " << *it2 << endl;

    advance(it2, 5); // 선형 시간
    cout << "5년 전 우승자: " << *it2 << endl;

    // forward_list는 순방향으로만 이동할 수 있음
    // advance(it1, -2);는 안됨

    // it1 += 2; 도 안됨

    return 0;

}