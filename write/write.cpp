#include <iostream>

#include <unistd.h>
#include <fcntl.h>
#include <string.h>

int main(int argc, char *argv[])
{
	char str[7] = "\tTEST\n";
	char* str2 = "test";
	
	auto fd       = open("get_file", O_WRONLY);
	if (write(fd, str, strlen(str)) < 0) {
		std::cout << "file not written" << std::endl;
		perror("File");
	}

	close(fd);

	return 0;
}
