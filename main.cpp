// Project UID db1f506d06d84ab787baf250c265e24e

#include <iostream>
#include <fstream>
#include <map>
#include <set>
#include <string>
#include "csvstream.h"

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

string add_words_to_map(string &words, string label, map<string, map<string, int> > &words_per_label)
{
    set<string> wordset = unique_words(words);
    for (auto &word:wordset)
    {
        words_per_label[label][word] += 1;
    }
    return words;
}

string create_maps(map<string, string> &row, map<string, int> &labels, map<string, map<string, int> > &words_per_label)
{
    string word;
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
            word = add_words_to_map(col.second, label, words_per_label);
        }
    }
    return word;
}

string word_compile(string &words_prev, string &words_new)
{
    return words_prev + words_new;
}


class Classifier
{
    private:
        int number_of_posts;
        int vocabulary_size;
        map<string, double> labels;
        map<string, map<string, double> > words_per_label;
    public:
        Classifier(string inputFile)
        : number_of_posts(0), vocabulary_size(0)
        {
            csvstream csvin("train_small.csv");
            map<string, string> row;
            map<string, int> labels;
            map<string, map<string, int> > words_per_label;
            string words_prev = "";
            while(csvin >> row)
            {
                number_of_posts++;
                string words_new = create_maps(row, labels, words_per_label);
                words_prev += " " + words_new;
            }
            set<string> wordset = unique_words(words_prev);
            vocabulary_size = wordset.size();
        }

        int get_number_of_posts()
        {
            return number_of_posts;
        }

        int get_vocab_size()
        {
            return vocabulary_size;
        }
};

int main()
{
    Classifier classifier("train_small.csv");
    cout << classifier.get_number_of_posts() << " " << classifier.get_vocab_size() << endl;
}