#include <regex>
#include <iostream>

#include <stdio.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>  
#include <fcntl.h>

int main (int argc, char **argv)
{
  if (argc < 2) {
    printf("Error: File name not defined");
    return -1;
  }

  const char *file_name = argv[1];
  const std::regex pattern(R"([.])");

  int fd = -1;
  fd = open(file_name, O_RDWR);

  struct stat st;
  fstat(fd, &st);
  char *contents = (char*)mmap(NULL,
                        st.st_size,
                        PROT_WRITE,
                        MAP_SHARED,
                        fd, 0);

  printf("File contents: %s\n", contents);

  std::cout << "regex_search: " << std::boolalpha
            << std::regex_search(contents, pattern) << std::endl;

  std::string new_string = std::regex_replace(contents,
                                              pattern,
                                              ":");


  std::string big_string = "hieufheiufhu\n iusefieubiebv\n iueiubiub\n iuiub iuhieuh iuhiuseiubi iuh ibiu iu iuh iuh iuh iuhi hiuehfsehfosiie se iuheivueviubiesb iseiu esiuvbisuebiub iseui esiu iuvsbuiebibeibeisubsiohsuheiushei ius ebviubevuibiubesielsue sieu hsiueh iuseh isueh isueh isue isebiusiusbe iusbe uiseb isueb seiu bsieu b...";

  memcpy(contents, (char*)new_string.c_str(),new_string.size());
  // memcpy(contents, (char*)big_string.c_str(), big_string.size());
  printf("out contents: %s\n", contents);

  munmap(contents, st.st_size);
  close(fd);
  return 0;
}
