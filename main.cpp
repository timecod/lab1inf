#include "helper.hpp"
#include "json.hpp"
#include "sortes.hpp"
#include <fstream>
#include <iostream>
#include <string>
using namespace std;
using namespace nlohmann;
using namespace helper;
const int SORTSCOUNT = 6;

template <typename T> struct functions {
  long long n;
  void (*arr[SORTSCOUNT])(T *, long long);
  functions()
      : arr{sortes::bubble, sortes::selection, sortes::insertion,
            sortes::quick,  sortes::heap,      sortes::merge},
        n(SORTSCOUNT) {}
};
string sorts[] = {"bubble", "selection", "insertion", "quick", "heap", "merge"};
string bases[] = {"sort", "rand", "rsort"};
template <typename T>
void create_data_of_type(json &config, json &output, string type_str,
                         int used_funcs[SORTSCOUNT], int min = -1000,
                         int max = 1000) {
  functions<T> FUNCS;
  int itk = 0;
  for (long long sort_id = 0; sort_id < FUNCS.n; ++sort_id) {
    if (sort_id != used_funcs[itk]) {
      continue;
    }
    itk++;
    for (long long item_number = config["itemNumber"]["start"];
         item_number < config["itemNumber"]["end"];
         item_number += (long long)config["itemNumber"]["step"]) {
      cout << item_number << '\n';
      for (long long accuracy_id = 0; accuracy_id < config["accuracy"];
           ++accuracy_id) {
        for (char base_arr = 0; base_arr < 3; ++base_arr) {
          double delta = -1;
          delta =
              sort_time<T>(FUNCS.arr[sort_id], item_number, base_arr, min, max);
          json r;
          r["type"] = type_str;
          r["itemNumber"] = item_number;
          r["sort"] = sorts[sort_id];
          r["accuracyId"] = accuracy_id;
          r["base"] = bases[base_arr];
          r["time"] = delta;
          output.push_back(r);
        }
      }
    }
  }
}
// del
struct mystruct {
  long bigboy[100];
  bool operator>(mystruct A) { return bigboy[0] > A.bigboy[0]; }
  mystruct() {}
  mystruct(int A) { bigboy[0] = A; }
};
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
