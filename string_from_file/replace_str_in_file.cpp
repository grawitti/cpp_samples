#include <fstream>  // std::ofstream
#include <iostream> // std::streambuf, std::cout
#include <iterator> // std::ofstream

int main(int argc, char **argv) {
  if (argc < 2) {
    std::cerr << "Using: " << argv[0] << " path_to_file\n";
    return -1;
  }

  std::ifstream ifstr(argv[1]);
  if (ifstr.bad()) {
    std::cerr << "Error: cannot open file: " << argv[1] << '\n';
    return -2;
  }

  std::string content(std::istreambuf_iterator<char>{ifstr}, {});

  ifstr.close();

  std::cout << content.c_str();

  return 0;
}
