#include <string>
#include <iostream>
#include <forward_list>
using namespace std;

struct citizen {
    string name;
    int age;
};

ostream &operator<<(ostream &os, const citizen &c) {
    return (os<<"["<<c.name<<", "<<c.age<<"]");
}

int main() {
    forward_list<citizen> citizens = {{"Kim", 22}, {"Lee", 25}, {"Jo", 24}};
    auto citizens_copty = citizens; // deep copy
    
    cout<<"전체 시민들: ";
    for(const auto &c : citizens)
        cout<<c<<" ";
    cout<<endl;
    
    citizens.remove_if([](const citizen &c) {
        return (c.age < 19);
    });
    
    cout<<"투표권: ";
    for(const auto &c : citizens)
        cout<<c<<" ";
    cout<<endl;
    
    return 0;
}

