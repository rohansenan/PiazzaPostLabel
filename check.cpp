#include "csvstream.h"
#include <iostream>
#include <string>
#include <map>
using namespace std;


int main() {
  // Open file
  csvstream csvin("train_small.csv");
    map<string, string> row;
    map<string, string> tag_with_content;
    while(csvin >> row)
    {
        for (auto &col:row)
        {
            if (col.first == "tag")
            {
                row[col.second]
                
            }
        }
    }
}