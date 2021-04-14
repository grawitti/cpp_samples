#include <iostream>
#include <fstream>
#include <regex>

#include <map>
#include <stdexcept>
#include <string>

using replace_map_t = std::map<std::string, std::string>;

struct ReplaceContentException : public std::runtime_error
{
	ReplaceContentException(const char* what) : runtime_error(what) {}
};

void replace_content(std::string& content,
                     replace_map_t const& replace_map)
{
	for (auto const& item: replace_map) {
		const std::string& key   = item.first;
		const std::string& value = item.second;

		std::regex reg("%%" + key + "%%");

		// проверяем что такой ключ существует в шаблоне
		if (!std::regex_search(content, reg)) {
			// пропускаем, если не найден
			continue;
		}

		// производим замену
		content = std::regex_replace(content, reg, value);
	}

	// проверяем что в шаблоне больше не осталось незамененных ключей
	std::regex reg("%%(\\w+)%%");
	std::smatch match;
	if (std::regex_search(content, match, reg)) {
		std::string key = match[1];
		std::string err_msg = "Key '" + key + "' was not replaced in the template";
		throw ReplaceContentException(err_msg.c_str());
	}
}

int main(int argc, char **argv)
{
  if (!argc) {
    std::cerr << "Not argument path to file\n";
    return -1;
  }

  std::string path = argv[1];

	std::string conf_str =
    "# %%path_to_ntpd_conf%%, configuration for ntpd; see ntp.conf(5) for help\n"
    "\n"
    "# Path to drift file. By default: /var/lib/ntp/ntp.drift\n"
    "driftfile %%path_to_drift_file%%\n"
    "\n"
    "# Server NTP IP(master ip) for slave or 127.127.1.0 for master\n"
    "server %%server_ip%% %%server_options%%\n"
    "\n"
    "# Access control configuration\n"
    "# By default, exchange time with everybody, but don't allow configuration.\n"
    "restrict %%restrict_options%%\n"
    "\n";

  replace_map_t replace_map = {
    { "path_to_ntpd_conf", "/etc/ntp.conf" },
    { "path_to_drift_file", "/var/lib/ntp/ntp.drift" },
    { "server_ip", "127.127.1.0" },
    { "server_options", "iburst prefer" },
    { "restrict_options", "default kod notrap nomodify noquery limited" },
  };

  try {
		replace_content(conf_str, replace_map);
	}
	catch (ReplaceContentException& ex) {
    std::cerr << ex.what() << std::endl;
	}

  std::ofstream ostr(path, std::ios::trunc);

  if(ostr.is_open()) {
    std::cout << "Write file\n";
    ostr.write(conf_str.c_str(), conf_str.size());
  }
  else {
    std::cerr << "Can't open file: " << path << '\n';
    return -2;
  }

  ostr.close();
  return 0;
}
