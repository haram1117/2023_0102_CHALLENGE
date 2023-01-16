//
// Created by haram on 2023-01-15.
//

#include <array>
#include <iostream>
#include <type_traits> // 타입 관련 연산을 위한 템플릿 메타 함수 제공


// 빌더 함수(builder function) - 입력 데이터 타입이 모호할 때 사용할 수 있다.
// 후행 반환 형식(trailing return type)
// auto 키워드로 정의된 함수의 반환형을 명시적으로 알려줌
template<typename ... Args> // ... template parameter pack
auto build_array(Args&&... args) -> std::array<typename std::common_type<Args...>::type, sizeof... (args)>
{
    // common_type을 이용해서 array에 저장할 타입 결정
    using commonType = typename std::common_type<Args...>::type;
    // lvalue와 rvalue
    // lvalue: 단일 표현식 이후에도 없어지지 않고 지속되는 객체
        // lvalue의 ref -> &x
    // rvalue: 표현식 이후에는 더이상 존재하지 않는 임시 값
        // rvalue의 ref -> &&x

    // 템플릿을 사용하는 경우에는 컴파일러가 l-value인지 r-value인지 구별하지 못한다.
    // std::forward를 통해 각 l-value와 r-value 타입을 정확하게 전달할 수 있다.
    return {std::forward<commonType>((Args&&)args)...};
}

int main(){
    auto data = build_array(1, 0u, 'a', 3.2f, false);
    for(auto i: data)
        std::cout << i << " ";
    std::cout << std::endl;

    // 모든 데이터 타입을 하나의 공통 타입으로 변환할 수 없음
    // -> 에러 발생 (template argument deduction/substitution failed)"
//    auto data2 = build_array(1, "Packt", 2.0);
}