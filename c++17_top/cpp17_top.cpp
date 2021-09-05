#include<string>
#include<utility>
#include<any>
#include<iostream>
#include<vector>

namespace ext_aggregate_init {
    void example() {
	struct struct_1
	{
	    int b1, b2 = 42;
	};

	struct struct_2
	{
	    struct_2() : b3(42) {}
	    int b3;
	};

	struct struct_3 : struct_1, struct_2
	{
	    int d;
	};

	// Расширенная агрегатная инициализация
	struct_3 st3{ {1, 2}, {}, 3};
    }
}

// Свертка параметров шаблона
namespace fold_expression {

    // Распечатывает все переданные аргументы
    template<typename ...Args>
    void printer(Args&&... args)
    {
	(std::cout << ... << args) << '\n';
    }

    // Добавляет переданные аргументы в переданный по ссылке вектор
    template<typename T, typename... Args>
    void push_back_vec(std::vector<T>& v, Args&&... args)
    {
	(v.push_back(args), ...);
    }

    // возвращает сумму всех переданных аргументов
    template<typename... Args>
    int sum(Args&&... args)
    {
	return (args + ...);
    }

    void example()
    {
	printer(1," text ", 2);

	std::vector<int> v;
	push_back_vec(v, 6, 2, 45, 12);
	for (auto e : v) {
	    std::cout << e << ' ';
	}
	std::cout << std::endl;

	std:: cout << sum(1, 3, 5, 10) << std::endl;
    }
}

// Тип auto для параметров шаблона
namespace auto_template_parameres
{
    // До c++ 17
    template<typename T, T val> void cpp_11()
    {
	std::cout << val << std::endl;
    }

    // В c++ 17
    template<auto val> void cpp_17()
    {
	std::cout << val << std::endl;
    }

    void example()
    {
	cpp_11<int, 10>();
	cpp_11<char, 'A'>();
	cpp_11<long, 100000000000>();

	// c++ 17
	cpp_17<11>();
	cpp_17<'B'>();
	cpp_17<10000000000>();
    }
}

// Вывод типов параметров шаблона
namespace tempalte_arg_deduction
{

    void example()
    {
	// Old style
	std::pair<int, std::string> pair_int_str(1, "test");
	std::vector<int> vec_int = {1,2,3,4};

	// C++ 17 style
	std::pair pair_int_str_17{1, "test2"};
	std::cout << "pair_int_str_17.first: " << pair_int_str_17.first
	          << ", pair_int_str_17.second: " << pair_int_str_17.second << std::endl;
	std::vector vec = {1,2,3,4};
	for (auto e : vec) {
	    std::cout << e << ' ';
	}
	std::cout << std::endl;

	std::cout << std::max(12,23) << std::endl;
    }
}

namespace constexpr_if
{
    struct S
    {
	int mInt{0};
	float mFloat{0.f};
	std::vector<int> mVecInt;
    };

    template<std::size_t aFieldNumber>
    void print(S& s)
    {
	if constexpr (aFieldNumber == 0)
	{
	    std::cout << s.mInt << std::endl;
	}
	else if constexpr (aFieldNumber == 1) {
	    std::cout << s.mFloat << std::endl;
	}
	else if constexpr (aFieldNumber == 2) {
	    for (auto e : s.mVecInt) {
		std::cout << e << ' '; 
	    }
	    std::cout << std::endl;
	}
    }

    void example()
    {
	S s_obj = {10, 11.f, {5,6,8,9}};

	print<0>(s_obj);
	print<1>(s_obj);
	print<2>(s_obj);
    }
}

int main()
{
    ext_aggregate_init::example();
    fold_expression::example();
    tempalte_arg_deduction::example();
    constexpr_if::example();
    return 0;
}
