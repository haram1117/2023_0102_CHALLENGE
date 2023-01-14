#include <iostream>
#include <forward_list>
#include <vector>
using namespace std;

int main() {
    vector<string> vec = {"Lewis", "Lewis", "Nico", "Sebastian", "Lewis", "Sebastian"};
    
    auto it = vec.begin();
    cout<<"최근 우승자: "<<*it<<endl;    // 반복자니까 포인터로 접근
    
    it += 3;
    cout<<"3년 전 우승자: "<<*it<<endl;
    
    advance(it, -2);
    cout<<"그 후 2년 뒤 우승자(1년 전 우승자): "<<*it<<endl;
    
    forward_list<string> fwd(vec.begin(), vec.end());   // end()는 마지막 원소 + 1을 가리킴
    
    auto it1 = fwd.begin();
    cout<<"최근 우승자: "<<*it1<<endl;
    
    advance(it1, 3);    // 선형 시간이니까 마이너스 말고 그냥
    cout<<"3년 전 우승자: "<<*it1<<endl;
    
    
    //advance(it1, -1);   // 선형 시간이니까 마이너스는 오류 왜냐면 순방향 반복자라서
    
    return 0;
}

