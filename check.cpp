#include "csvstream.h"
#include <iostream>
#include <string>
#include <map>
#include <set> 
using namespace std;

set<string> unique_words(const string &str) {
    istringstream source(str);
    set<string> words;
    string word;
    while (source >> word) {
    words.insert(word);
    }
    return words;
}

void add_words_to_map(string &words, string label, map<string, map<string, int> > &words_per_label)
{
    set<string> wordset = unique_words(words);
    for (auto &word:wordset)
    {
        words_per_label[label][word] += 1;
    }
}

int main() {
  csvstream csvin("train_small.csv");
    map<string, string> row;
    map<string, int> labels;
    map<string, map<string, int> > words_per_label;
    while(csvin >> row)
    {
        for (auto &col:row)
        {
            string label;
            if (col.first == "tag")
            {
                labels[col.second] += 1;
                words_per_label[col.second];
                label = col.second;
            }
            else if (col.first == "content")
            {
                add_words_to_map(col.second, label, words_per_label);
            }
        }
    }
}