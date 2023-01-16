//
// Created by haram on 2023-01-13.
//

#include <iostream>
#include <sstream> // string stream
#include <algorithm>
#include <array>
using namespace std;

// 동적 배열 class
template <typename T>
class dynamic_array{
    T* data;
    size_t n;

public:
    // 생성자
    dynamic_array(int n){
        this->n = n;
        data = new T[n];
    }
    // 복사 생성자
    dynamic_array(const dynamic_array<T>& other){
        n = other.n;
        data = new T[n];
        for(int i = 0; i < n; i++)
            data[i] = other[i];
    }


    T& operator[](int index){
        return data[index];
    }
    const T& operator[](int index) const{
        return data[index];
    }
    T& at(int index){
        if (index < n)
            return data[index];
        throw "Index out of range";
    }

    // 배열의 크기 반환
    size_t size() const{
        return n;
    }

    // 소멸자
    ~dynamic_array(){
        delete[] data;
    }

    // iterator
    T* begin(){return data;}
    const T* begin() const{return data;}
    T* end(){return data + n;}
    const T* end() const{return data + n;}

    // + 연산
    friend dynamic_array<T> operator+(const dynamic_array<T>& arr1, dynamic_array<T>& arr2){
        dynamic_array<T> result(arr1.size() + arr2.size());
        copy(arr1.begin(), arr1.end(), result.begin());
        copy(arr2.begin(), arr2.end(), result.begin() + arr1.size());

        return result;
    }

    string to_string(const string& sep = ", "){
        if(n == 0)
            return "";
        stringstream os;
        os << data[0];
        for(int i = 1; i < n; i++)
            os << sep << data[i];
        return os.str();
    }
};

// 학생 정보를 담은 구조체
struct student{
    string name;
    int standard;
};

// 학생 정보 표준 출력
ostream& operator<<(ostream& os, const student& s){
    return os << "[" << s.name << ", " << s.standard << "]";
}

int main(){
    int nStudents;
    cout << "1반 학생 수를 입력하세요: ";
    cin >> nStudents;

    dynamic_array<student> class1(nStudents);
    for(int i = 0; i < nStudents; i++){
        string name;
        int standard;
        cout << i + 1 << "번째 학생 이름과 나이를 입력하세요: ";
        cin >> name >> standard;
        class1[i] = student{name, standard};
    }

    try {
        class1.at(nStudents) = student{"John", 8};
    }
    catch (...){
        cout << "예외 발생" << endl;
    }

    auto class2 = class1;
    cout << "1반을 복사하여 2반 생성: " << class2.to_string() << endl;

    auto class3 = class1 + class2;
    cout << "1반과 2반을 합쳐 3반 생성: " << class3.to_string() << endl;

    return 0;
}