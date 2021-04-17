#include <fstream>
#include <vector>
#include <iostream>
#include <string>
  
int main(int argc, char** argv)
{
    if (argc < 4) {
	std::cerr << "Error: using " << argv[0] << " input_file str_find str_repalce\n";
	return -1;
    }

    std::ifstream infile(argv[1]);
    if (!infile) {
	std::cerr << "Can't open file: " << argv[1] << '\n';
    }

    std::string  strtofind(argv[2]);
    std::string  strtoreplace(argv[3]);
    std::vector<std::string> lines;
    
    while(!infile.eof())
    {
	std::string line;
	std::getline(infile, line);
	lines.push_back((line == strtofind ? strtoreplace : line));
    }

    infile.close();

    std::ofstream outfile(argv[1]);
    if (!outfile) {
	std::cerr << "Can't open file: " << argv[1] << '\n';
    }

    for (size_t i = 0; i < lines.size(); i++) {
	outfile << lines[i];
	if (i != lines.size() - 1) {
	    outfile << std::endl;
	}
    }
    outfile.close();

    return 0;
}

