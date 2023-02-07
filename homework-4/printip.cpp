/// \mainpage   OTUS C++ Developer Pro Course
///
/// \brief      #4 - Print an IP-address from various data.
/// \author     Игорь Пушкин
/// \date       feb 2023
/// \details
/// OTUS C++ Developer Pro Course - homework #4 - print ip address.\n
/// Самостоятельная работа по курсу OTUS C++ Developer Pro.\n
/// Задача - программа печати ip-адреса из разных типов данных.\n
///

/// \file 		printip.cpp
/// \author 	Игорь Пушкин <ipush@ya.ru>
/// \date       feb 2023
/// \version    1.0
/// \brief 		Program to print out ip-address from various source data.
/// \details
/// OTUS C++ Developer Pro Course - homework #4 - print ip address.\n
/// Данный файл содержит самостоятельную работу по курсу
/// OTUS C++ Developer Pro.\n
/// Задача - программа печати ip-адреса из разных типов данных.\n
///

#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <tuple>
#include <type_traits>

//! \defgroup integer-group (ip-address as integer type)
//! @{

/// \brief вывод одного байта ip-адреса.
/// \param[in] ipAddr - данные для вывода/печати

void print_ip_byte (int8_t ipAddr)
{
    std::cout << (ipAddr & 255);
}

/*!
 \brief выводит ip-адрес из простых типов данных.
 \details выводит ip-адрес из простых типов данных: 
 - int8_t
 - int16_t
 - int32_t
 - int64_t
 \param[in] ipAddr - данные для вывода/печати
 \tparam T - тип данных
 */

template<typename T, int N = sizeof(T)>
typename std::enable_if<std::is_integral<T>::value, void>::type
print_ip (T ipAddr)
{
    for (int i = N; i > 0; --i)
    {
        if (i < N)
            std::cout << ".";
        print_ip_byte (ipAddr >> ((i-1)*8));
    }
};
//! @}

//! \defgroup string-group (ip-address as std::string)
//! @{
/*!
 \brief вывод ip-адреса из std::string
 \param[in] ipAddr - данные для вывода/печати
 */

void print_ip (std::string& ipAddr)
{
    std::cout << ipAddr;
}
//! @}

//! \defgroup container-group (ip-address as a container)
//! @{
template <class T>
struct is_container: std::false_type {};

template <class T>
struct is_container<typename std::list<T>>: std::true_type {} ;

template <class T>
struct is_container<typename std::vector<T>>: std::true_type {};

/*!
 \brief вывод ip-адреса из элементов контейнера
 \details выводит/печатает ip-адрес из элементов контейнеров
 - std::vector
 - std::list
 \param[in] container - данные для вывода/печати
 \tparam C - тип контейнера
 */

template <typename C>
typename std::enable_if<is_container<C>::value,void>::type 
print_ip (C & container) 
{
    bool first = true;
    for (auto ip : container)
    {
        if (first)  
            first = false;
        else
            std::cout << ".";
        std::cout << ip;
    }
}
//! @}

//! \defgroup tuple-group (ip-address as a tuple)
//! @{

/// \brief проверяет что все элементы кортежа имеют одинаковый тип.
/// \tparam Ts - тип кортежа для проверки.
/// \return true если все элементы имеют одинаковый тип, иначе false
template<typename ... Ts
    , typename T = std::tuple_element_t<0, std::tuple<Ts...>>>
constexpr bool is_monotype (std::tuple<Ts...>) 
{
    return std::conjunction_v<std::is_same<T, Ts>...>;
}

/// \brief выводит все элеметы кортежа.
/// \tparam Tp - тип кортежа для вывода
/// \param tp - кортеж для вывода
template<size_t I = 0, typename... Tp>
void print_tp (std::tuple<Tp...>& tp) 
{
    if constexpr (I == sizeof...(Tp))   // is empty tuple
    {
        return;
    }
    else            // not empty
    {
        if constexpr(I > 0)
            std::cout << ".";
        std::cout << std::get<I>(tp);
        if constexpr(I+1 != sizeof...(Tp))
            print_tp<I+1, Tp...>(tp);
    }
}

/// \brief вывод ip-адреса из элементов кортежа.
/// \details выводит/печатает ip-адрес из элементов кортежа.\n
/// На этапе компиляции производится проверка кортежа 
/// на монотипность - т.е. на то, что все элементы кортежа 
/// имеют одинаковый тип, и в случае немонотипности кортежа 
/// выдается ошибка компиляции. 
/// \tparam T - тип кортежа для вывода
/// \param tp - кортеж для вывода/печати

template <typename... T>
void print_ip (std::tuple<T...>& tp) 
{
    static_assert(is_monotype(std::tuple<T...>{}),
                  "Tuple is not monotype.");  // monotype
    print_tp (tp);
}
//! @}

//! \defgroup test-group (testing)
//! @{

/*!    
 \brief драйвер тестирования.
 \details
 производятся последовательные вызовы функции print_ip()
 с различными типами данных:
 - int8_t
 - int16_t
 - int32_t
 - int64_t
 - std::string
 - std::vector
 - std::list
 - std::tuple
 */

int main (int , char * [])
{
    print_ip ( int8_t{-1} );    // 255
    std::cout << std::endl;
    print_ip ( int16_t{0} );    // 0.0
    std::cout << std::endl;
    print_ip ( int32_t{2130706433} );   // 127.0.0.1
    std::cout << std::endl;
    print_ip ( int64_t{8875824491850138409} );      // 123.45.67.89.101.112.131.41
    std::cout << std::endl;
    print_ip ( std::string{"Hello, World!"} );      // Hello, World!
    std::cout << std::endl;
    print_ip ( std::vector<int>{100, 200, 300, 400} );  // 100.200.300.400
    std::cout << std::endl;
    print_ip ( std::list<short>{400, 300, 200, 100} );  // 400.300.200.100
    std::cout << std::endl;
    print_ip ( std::make_tuple(123, 456, 789, 0) );     // 123.456.789.0
    std::cout << std::endl;
    print_ip ( std::make_tuple("123", "456", "789", "0") );     // 123.456.789.0
    std::cout << std::endl;
//    print_ip ( std::make_tuple("123", 456, 789, 0) );     // "123".456.789.0 -> compilation error
//    std::cout << std::endl;
}
//! @}

