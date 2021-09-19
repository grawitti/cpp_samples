#include<string>
#include<utility>
#include<any>
#include<iostream>
#include<vector>
#include<map>

namespace ext_aggregate_init {
    void example() {
	std::cout << "ext_aggregate_init example begin\n";
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
	std::cout << "st3 {{" << st3.b1 << "," << st3.b2 << "}, {" << st3.b3 << "}, {" << st3.d << "}}\n";
	std::cout << "ext_aggregate_init example end\n\n";
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
	std::cout << "fold_expression example begin\n";
	printer(1," text ", 2);

	std::vector<int> v;
	push_back_vec(v, 6, 2, 45, 12);
	for (auto e : v) {
	    std::cout << e << ' ';
	}
	std::cout << std::endl;

	std:: cout << sum(1, 3, 5, 10) << std::endl;
	std::cout << "fold_expression example end\n\n";
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
	std::cout << "auto_template_parametres example begin\n";
	cpp_11<int, 10>();
	cpp_11<char, 'A'>();
	cpp_11<long, 100000000000>();

	// c++ 17
	cpp_17<11>();
	cpp_17<'B'>();
	cpp_17<10000000000>();
	std::cout << "auto_template_parametres example end\n\n";
    }
}

// Вывод типов параметров шаблона
namespace tempalte_arg_deduction
{

    void example()
    {
	std::cout << "template_arg_deduction example begin\n";
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

	std::cout << "map: \n";
	std::map int_string_map = {std::pair{1,"string"}, {2, "srt"}};
	for (auto e : int_string_map) {
	    std::cout << e.first << ", " << e.second << ' ' << std::endl;
	}
	std::cout << "template_arg_deduction example end\n\n";
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
	std::cout << "constexpr_if example begin\n";
	S s_obj = {10, 11.f, {5,6,8,9}};

	print<0>(s_obj);
	print<1>(s_obj);
	print<2>(s_obj);
	std::cout << "constexpr_if example end\n\n";
    }
}

namespace struct_binding {
    void example()
    {
	std::cout << "struct_binding example begin\n";

	std::pair p = {1, "Hello"};
	auto[first, second] = p;
	std::cout << first << std::endl << second << std::endl;

	int coord_3d[3] = {1, 2, 3};
	auto [x, y, z] = coord_3d; 
	std::cout << x << std::endl << y << std::endl << z << std::endl;

	struct Config_a
	{
	    int id;
	    std::string name;
	    std::vector<int> data;
	};

	Config_a ca;
	auto & [id, n, d] = ca;
	id = 1;
	n = "Name";
	d.push_back(13);
	std::cout << ca.id << ", " << ca.name << ", " << ca.data[0] << std::endl;

	std::tuple<int &, std::string &&, std::vector<int>> tpl (ca.id, std::move(ca.name), ca.data);
	auto & [id2, name, data] = tpl; // id2 - &, name - &&, data - &
	id2 = 2;
	name = "Name2";
	d[0] = 10;
	std::cout << ca.id << ", " << ca.name << ", " << ca.data[0] << std::endl;

	std::cout << "struct_binding example end\n\n";
    } 
}

namespace constexpr_lambda
{
    constexpr int f_calc(int a_value)
    {
	auto lambda = [a_value]()
	{
	    return a_value + 14;
	};
	return a_value + lambda();
    }

    void example()
    {
	std::cout << "constexpr_lambda example begin\n";

	constexpr auto lambda = [](int a_value){ return a_value + a_value; };
	std::cout << f_calc(12) << std::endl;
	std::cout << lambda(12) << std::endl;

	std::cout << "constexpr_lambda example end\n\n";
    }
}

namespace this_lambda
{
    struct test
    {
	void f_test()
	{
	    auto lambda_const = [*this]()
	    {
		f_const();
		return mA + mA;
	    };

	    auto lambda = [*this]() mutable
	    {
		f();
		return mA + mA;
	    };

	    std::cout << lambda_const() << std:: endl;
	    std::cout << lambda() << std:: endl;
	}


	private:
	    void f_const() const
	    {
		std::cout << __FUNCTION__ << std::endl;
	    }

	    void f()
	    {
		std::cout << __FUNCTION__ << std::endl;
	    }

	    int mA{12};
    };

    void example()
    {
	std::cout << "this_lambda example begin\n";

	test t;
	t.f_test();

	std::cout << "this_lambda example end\n\n";
    }
}

namespace if_switch_initializator
{
    void example()
    {
	std::cout << "if_switch_initializator example begin\n";

	int i = 1;
	int* pi = &i;
	int* pin = nullptr;
	if (int *p = pi; p) {
	    std::cout << "Pointer is OK\n";
	}
	else {
	    std::cout << "Error: Pointer is nullptr\n";
	}

	struct error {
	    std::string msg;
	    int code;
	};

	error err {"Some error message.", 1};
	switch(int code = err.code; code) {
	    case 0:
		std::cout << "case 0\n";
		break;
	    case 1:
		std::cout << "case 1\n";
		break;
	    default:
		std::cout << "Unsupported error code: " << code << std::endl;
		break;
	}

	std::cout << "if_switch_initializator example end\n\n";
    }
}

namespace new_attributes
{
    void f_fallthrough()
    {
	int i = std::rand()%10;

	switch(i)
	{
	    case 0:
		std::cout << "0\n";
	    break;
	    case 1:
		std::cout << "1\n";
	    break;
	    case 3:
		std::cout << "3\n";
	    break;
	    case 4:
		std::cout << "4\n";
		[[fallthrough]]; // подавление предупреждения о провале в case
	    case 5:
		std::cout << "5\n";
	    break;
	}
    }

   [[nodiscard]] int f_nodiscard()
   {
	return 0;
   }

    void example()
    {
	std::cout << "new_attributes example begin\n";

	f_fallthrough();
	f_nodiscard(); // генерирует предупреждение если возвращаемое значение было проигнорировано
	[[maybe_unused]] int i = f_nodiscard();

	std::cout << "new_attributes example end\n\n";
    }
}

namespace std_any
{
    void example()
    {
	std::cout << "std_any example begin\n";

	std::any anythink = 10;
	std::cout << std::any_cast<int>(anythink) << std::endl;

	anythink = std::string("string anythink");
	std::cout << std::any_cast<std::string>(anythink) << std::endl;

	anythink = "char anythink";
	std::cout << std::any_cast<const char*>(anythink) << std::endl;

	std::cout << "std_any example end\n\n";
    }
    
}

namespace namespaces
{
    namespace n1::n2
    {
	void f()
	{
	    std::cout << __FUNCTION__ << std::endl;
	}
    }

    void example()
    {
	std::cout << "namespaces example begin\n";

	n1::n2::f();

	std::cout << "namespaces example end\n\n";
    }
}

namespace size_empty_data
{

    void example()
    {
	std::cout << "size_empty_data example begin\n";

	std::vector vec = {1, 2, 3};
	size_t size = std::size(vec);
	bool is_empty = std::empty(vec);
	auto pointer = std::data(vec);
	std::cout << size << ", " << is_empty << ", " << pointer[0] << std::endl;

	std::cout << "size_empty_data example end\n\n";
    }
}

namespace has_include
{
#if __has_include(<std_experimental>)
#include <std_experimental>
#endif
}

int main()
{
    ext_aggregate_init::example();
    fold_expression::example();
    tempalte_arg_deduction::example();
    constexpr_if::example();
    struct_binding::example();
    constexpr_lambda::example();
    this_lambda::example();
    if_switch_initializator::example();
    std_any::example();
    namespaces::example();
    size_empty_data::example();

    return 0;
}
