#include <string>
#include <string_view>
#include <iostream>

bool solution(std::string const &str, std::string const &ending) {
  if (str.size() >= ending.size()) {
    std::string_view subs = str;
    subs.remove_prefix(str.size() - ending.size());
    if (subs == ending) {
      return true;
    }
  }
  return false;
}

int main()
{
  std::string a = "abcd";
  std::string b = "cd";
  std::string c = "ab";
  std::string e = "";


  std::cout << "a: " << a << "\nb: " << b << "\nc: " << c << std::endl; 
  std::cout << solution(a, b) << std::endl;
  std::cout << solution(a, c) << std::endl;
  std::cout << solution(a, e) << std::endl;

  return 0;
}
