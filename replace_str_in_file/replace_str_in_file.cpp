#include <fstream>  // std::ofstream
#include <iostream> // std::streambuf, std::cout
#include <iterator> // std::ofstream
#include <regex>

int main(int argc, char **argv) {
  if (argc < 2) {
    std::cerr << "Using: " << argv[0] << " path_to_file\n";
    return -1;
  }

  std::ifstream ifs;
  ifs.open(argv[1]);
  if (ifs.bad()) {
    std::cerr << "Error: cannot open file: " << argv[1] << '\n';
    return -2;
  }

  std::string content(std::istreambuf_iterator<char>{ifs}, {});
  ifs.close();

  std::cout << content.c_str();

  const std::regex pattern(
      R"(server ((25[0-5]|(2[0-4]|1[0-9]|[1-9]|)[0-9])(\.(?!$)|)){4})");

  std::cout << "\nregex_search: " << std::boolalpha
            << std::regex_search(content, pattern) << "\n\n";

  std::string replaced_content =
      std::regex_replace(content, pattern, "server 0.0.0.0");

  std::cout << replaced_content;

  std::ofstream ofs(argv[1], std::ios::trunc);
  if (ofs.bad()) {
    std::cerr << "Error: cannot open file: " << argv[1] << '\n';
    return -3;
  }

  ofs << replaced_content;

  ofs.close();

  return 0;
}
