#include <iostream>
#include <string>
#include <map>
#include <vector>
#include "cpr/cpr.h"

int main() {
  std::vector<cpr::Pair> arguments;
  std::string argument;
  std::string responseType;

  while (1) {
    std::cout << "Enter the first argument:" << std::endl;
    std::cin >> argument;
    if (argument == "post") {
      if (arguments.empty()) {
        std::cerr << "Wrong input!" << std::endl;
        continue;
      }

      std::vector<cpr::Pair> data;
      for (int i = 0; i < arguments.size(); i++) {
        data.push_back(arguments[i]);
      }

      arguments.clear();
      cpr::Response r = cpr::Post(cpr::Url{"http://httpbin.org/post"},
                                  cpr::Payload(data.begin(), data.end()));
      std::cout << r.text << std::endl;
    } else if (argument == "get") {
      if (arguments.empty()) {
        std::cout << "No data for request" << std::endl;
        continue;
      }

     std::string q = "?";
      for (int i = 0; i < arguments.size(); i++) {
        q += arguments[i].key + "=" + arguments[i].value + "&";
      }
       
      q.erase(--q.end());
      arguments.clear();
      cpr::Response r = cpr::Get(cpr::Url{"http://httpbin.org/get" + q});
      std::cout << r.text << std::endl;
    } else {
      std::cout << "Enter the second argument:" << std::endl;
      std::cin >> responseType;
      arguments.push_back(cpr::Pair(argument, responseType));
    }
  }
}