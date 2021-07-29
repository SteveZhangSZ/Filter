#include <tuple>
#include <type_traits>
#include "Filter.hpp"
int main(){
    static_assert(std::is_same_v<szFilter::filter<std::is_reference, std::tuple>, std::tuple<>>); //No types provided, return empty tuple
  	static_assert(std::is_same_v<szFilter::filter<std::is_reference, std::tuple, int>, std::tuple<>>);
  	static_assert(std::is_same_v<szFilter::filter<std::is_reference, std::tuple, int&>, std::tuple<int &>>);
  	static_assert(std::is_same_v<szFilter::filter<std::is_reference, std::tuple, int, int&, char>, std::tuple<int &>>);
  	static_assert(std::is_same_v<szFilter::filter<std::is_reference, std::tuple, int, int&, char, char&>, std::tuple<int &, char &>>);
  	static_assert(std::is_same_v<szFilter::filter<std::is_reference, std::tuple, char&,int, int&, char, char&>, std::tuple<char&,int &, char &>>);
}