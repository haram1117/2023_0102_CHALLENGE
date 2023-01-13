#include <array>
#include <iostream>
#include <type_traits>
using namespace std;

template<typename ... Args>
array<?,?> build_array(Args&&... args)


template<typename ... Args>
auto build_array(Args&&... args) -> array<typename std::common_type<Args...>::type, ?> {
    using commonType = typename common_type<Args...>::type;
}

template<typename ... Args>
auto build_array(Args&&... args) -> array<typename std::common_type<Args...>::type, sizeof...(args)> {
    using commonType = typename common_type<Args...>::type;
    return {std::forward<commonType>((Args&&)args)...}
}

int main() {
    auto data = build_array(1, 0u, 'a', 3.2f, false);
    for(auto i : data)
        cout<<i<<" ";
    cout<<endl;
    return 0;
}

