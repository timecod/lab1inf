#include "helper.hpp"
#include "json.hpp"
#include <fstream>
#include <iostream>
#include <string>
using namespace std;
using namespace nlohmann;
using namespace helper;

int main() {
  ifstream config_file("config.json");
  json config;
  config_file >> config;
  ofstream output_file(config["outputName"]);
  json output;
  int used_funcs[SORTSCOUNT] = {};
  int itk = 0;
  for (int i = 0; i < SORTSCOUNT; ++i)
    for (string sort_name : config["sorts"])
      if (sort_name == sorts[i])
        used_funcs[itk++] = i;

  for (string type_str : config["types"]) {
    cout << type_str << '\n';
    if (type_str == "char")
      create_data_of_type<char>(config, output, "char", used_funcs, 0, 255);
    else if (type_str == "short")
      create_data_of_type<short>(config, output, "short", used_funcs);
    else if (type_str == "long")
      create_data_of_type<long>(config, output, "long", used_funcs);
    else if (type_str == "unsigned")
      create_data_of_type<unsigned>(config, output, "unsigned", used_funcs, 0);
    else if (type_str == "long long")
      create_data_of_type<long long>(config, output, "long long", used_funcs);
    else if (type_str == "mystruct")
      create_data_of_type<mystruct>(config, output, "mystruct", used_funcs);
    else
      create_data_of_type<int>(config, output, "int", used_funcs);
  }
  output_file << output;
  return 0;
}
