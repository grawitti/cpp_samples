/**
 * time.h - Setup system time from arguments
 */

#include <ctime>
#include <iostream>
#include <chrono>

#include <sys/time.h>

using namespace std::chrono;

int main(int argc, char** argv)
{
  if (argc <= 3) {
    std::cerr << "Usage:" << argv[0] << "hour minutes seconds\n";
    return -1;
  }

  uint8_t hour = atoi(argv[1]);
  uint8_t min = atoi(argv[2]);
  uint8_t sec = atoi(argv[3]);

  std::time_t current = std::time(nullptr);
  std::cout << std::asctime(std::localtime(&current))
            << current << std::endl;
  
  uint64_t microseconds = current * 1000000;
  std::cout << "microsetconds: " << microseconds << std::endl;

  int64_t microseconds2 = current * 1000000;
  std::cout << "microsetconds2: " << microseconds2 << std::endl;

  auto now = system_clock::now();
  time_t now_t = system_clock::to_time_t(now);
  std::cout << "Whith chrono: " << std::asctime(std::localtime(&now_t))
            << now_t << std::endl;


  struct tm* tm_ptr = localtime(&current);
  tm_ptr->tm_hour = hour;
  tm_ptr->tm_min = min;
  tm_ptr->tm_sec = sec;

  char buf[64];
  strftime(buf, 64, "%d.%m.%y %H:%M:%S", tm_ptr);

  std::cout << "local: " << buf << std::endl;
  std::cout << "UTC: " << std::mktime(tm_ptr) << std::endl;

  // struct timeval tv;
  // tv.tv_sec = std::mktime(tm_ptr);
  // tv.tv_usec = 0;
  // settimeofday(&tv, nullptr);
  
  struct timeval tv;
  gettimeofday(&tv, NULL);
  printf("tv_usec: %li\n", tv.tv_usec);
  std::cout << "tv.tv_sec: " << tv.tv_sec << std::endl << "tv.tv_usec: " << tv.tv_usec << std::endl;

  return 0;
}
