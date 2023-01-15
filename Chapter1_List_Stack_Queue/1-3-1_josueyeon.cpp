#include <iostream>
#include <sstream>  // string stream용 클래스 헤더
#include <algorithm>
using namespace std;

template <typename T>
class dynamic_array {
    T* data;
    size_t n;
    
public:
    // 생성자
    dynamic_array(int n) {
        this->n = n;
        data = new T[n];
    }
    
    // 복사 생성자: 자신과 같은 클래스 타입의 다른 객체에 대한 참조(reference)를 인수로 전달받아, 그 참조를 가지고 자신을 초기화하는 방법
    dynamic_array(const dynamic_array<T>& other) {
        n = other.n;
        data = new T[n];
        
        for(int i = 0;i < n;i++) {
            data[i] = other.data[i];
        }
    }
    
    // 멤버 데이터 접근 연산자
    T& operator[] (int index) {
        return data[index];
    }
    
    // 앞의 const: 반환값이 const -> 멤버 변수는 일반 변수 가능이지만 반환값을 전달할 때는 const 변수에만 받을 수 있음
    // 뒤의 const: 함수가 const -> const변수만 다룰 수 있으며, const로 선언되어있기 때문에 맴버변수의 값을 변경할 수 없음
    // 값 복사가 아니라 레퍼런스 반환
    const T& operator[] (int index) const {
        return data[index];
    }
    
    // index의 유효성 검사
    T& at(int index) {
        if (index < n)
            return data[index];
        throw "Index out of range";
    }
    
    // 배열 크기 반환
    size_t size() const {
        return n;
    }
    
    ~dynamic_array() {
        delete[] data;
    }
    
    // 순회용 반복자
    T* begin() {return data;}
    const T* begin() const {return data;}
    T* end() {return data + n;}
    const T* end() const {return data + n;}
    
    // + 연산자
    // friend: private 및 protected 멤버에 접근할 수 있는 권한
    friend dynamic_array<T> operator+(const dynamic_array<T>& arr1, dynamic_array<T>& arr2) {
        dynamic_array<T> result(arr1.size() + arr2.size());
        copy(arr1.begin(), arr1.end(), result.begin());
        copy(arr2.begin(), arr2.end(), result.begin() + arr1.size());
        
        return result;
    }
    
    // 문자열로 반환
    // 기본값 지정 가능
    string to_string(const string& sep = ", ") {
        if (n == 0)
            return "";
        
        // 문자열 format을 조합하여 저장할 때 사용
        ostringstream os;
        os<<data[0];
        for(int i = 1;i < n;i++) {
            os<<sep<<data[i];
        }
        return os.str();
    }
};

// 학생 정보 저장 구조체
struct student {
    string name;
    int standard;
};

// 표준 출력 연산자 오버로딩
ostream& operator<<(ostream& os, const student& s) {
    return (os<<"["<<s.name<<", "<<s.standard<<"]");
}

int main() {
    int nStudents;
    cout<<"1반 학생수를 입력하세요: ";
    cin>>nStudents;
    
    dynamic_array<student> class1(nStudents);
    for(int i = 0;i < nStudents;i++) {
        string name;
        int standard;
        cout<<i + 1<<"번째 학생 이름과 나이를 입력하세요: ";
        cin>>name>>standard;
        class1[i] = student{name, standard};    // 구조체는 {}
    }
    
    try {
        // 이 접근 연산자는 인덱스 값의 유효성 검사를 하지 않음 -> seg fault
        // class1[nStudents] = student{"John", 8};
        
        // at() 함수는 index 값이 유효하지 않을 시 exception -> 예외 처리 가능
        class1.at(nStudents) = student{"John", 8};
    }
    catch (...){
        cout<<"예외 발생!"<<endl;
    }
    
    // 깊은 복사
    auto class2 = class1;
    cout<<"1반 복사: "<<class2.to_string()<<endl;
    
    // 새로운 학습
    auto class3 = class1 + class2;
    cout<<"1반 + 2반: "<<class3.to_string()<<endl;
    
    return 0;
    
}

