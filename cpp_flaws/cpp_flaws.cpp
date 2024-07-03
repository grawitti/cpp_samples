#include <iostream>
#include <string>
#include <string_view>
#include <cstring>
#include <typeinfo>
#include <functional>
#include <memory>
#include <optional>

std::unique_ptr<int> f() {
    std::optional<std::unique_ptr<int>> x(std::nullopt);
    return std::move(*x);
}

std::function<int(void)> f(std::shared_ptr<int> x) {
    return [&]() { return *x; };
}

void lambda_failed_link() {
    std::function<int(void)> y(nullptr);
    {
        std::shared_ptr<int> x(std::make_shared<int>(4));
        y = f(x);
    }
    std::cout << y() << std::endl;
}

void hide_link_free_use_after_free()
{
  std::string s = "Hellooooooooooo ";
  std::string_view sv = s + "World\n";
  std::cout << sv;
}

void c_str_buf_overflow()
{
  char name[8];
  std::cout << "Enter you name: ";
  std::cin >> name; ///< Так не правильно
  // std::cin.getline(name, std::size(name)); ///< Так правильно
  std::cout << "You entered: " << name << std::endl; 
}

void strcpy_buf_ofw()
{
  char source[] { "copy this!" };
  char dest[1];
  strcpy(dest, source); ///< Лучше использовать strncpy()
  std::cout << dest << std::endl; 
}

void strncpy_without_null_terminal()
{
  char src[] { 't', 'e', 'e' };
  char dst[2];
  strncpy(dst, src, 5);
  std::cout << dst << std::endl;
}

void typeinfo_example()
{
  int x{4};
  std::cout << typeid(&x).name() << '\n';
}

int main () {
  // hide_link_free_use_after_free();

  // c_str_buf_overflow();

  // strcpy_buf_ofw();
  
  // strncpy_without_null_terminal();

  // typeinfo_example();

  // lambda_failed_link();

  std::cout << *f() << std::endl;

  return 0;
}
