// Project UID db1f506d06d84ab787baf250c265e24e

#include <iostream>
#include <fstream>
#include <map>
#include <set>
#include <string>
#include <math.h>
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

string add_words_to_map(string &words, string &label, map<string, 
map<string, int> > &words_per_label)
{
    set<string> wordset = unique_words(words);
    for (auto &word:wordset)
    {
        words_per_label[label][word] += 1;
    }
    return words;
}

string create_maps(map<string, string> &row, map<string, int> &labels, 
map<string, map<string, int> > &words_per_label, bool debug)
{
    string word;
    string label;
    string words;
    for (auto &col:row)
    {
        if (col.first == "tag" && debug)
        {
            labels[col.second] += 1;
            words_per_label[col.second];
            label = col.second;
            word = add_words_to_map(words, label, words_per_label);
            cout << "  label = " << label << ", content = " << word << endl;
        }
        else if (col.first == "tag")
        {
            labels[col.second] += 1;
            words_per_label[col.second];
            label = col.second;
            word = add_words_to_map(words, label, words_per_label);
        }
        else if (col.first == "content")
        {
            words = col.second;
        }
    }
    return word;
}


class Classifier
{
 private:
    double number_of_posts;
    int vocabulary_size;
    map<string, int> labels;
    map<string, map<string, int> > words_per_label;
 public:
    Classifier(string inputFile, bool debug)
    : number_of_posts(0), vocabulary_size(0)
    {
        csvstream csvin(inputFile);
        map<string, string> row;
        string words_prev = "";
        if (debug)
        {
            cout << "training data:" << endl;
        }
        while(csvin >> row)
        {
            number_of_posts++;
            string words_new = create_maps(row, labels, words_per_label, debug);
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

    int findWordNoLabel(string word)
    {
        int number = 0;
        for (auto &label:words_per_label)
        {
            number += label.second[word];
        }
        return number;
    }

    double calcLabelProb(string label)
    {
        double number = labels[label];
        return log(number/number_of_posts);
    }

    double calcWordProb(string word, string label)
    {
        int number = words_per_label[label][word];
        if (number != 0)
        {
            double numberOne = labels[label];
            return log(number/numberOne);
        }
        int numberTwo = findWordNoLabel(word);
        if (numberTwo != 0)
        {
            return log(numberTwo/number_of_posts);
        }
        else
        {
            return log(1.0/number_of_posts);
        }
    }

    void print_debug_data()
    {
        cout << "vocabulary size = " << vocabulary_size << endl;
        cout << "classes:" << endl; 
        for (auto &label:labels)
        {
            cout << "  " << label.first << ", " << label.second << 
            " examples, log-prior = " << calcLabelProb(label.first) << endl;
        }
        cout << "classifier parameters:" << endl;
        for (auto &label:labels)
        {
            map<string, int> wordsValues = words_per_label[label.first];
            for (auto &words:wordsValues)
            {
                cout << "  " << label.first << ":" << words.first 
                << ", count = " << words.second 
                << ", log-likelihood = " << calcWordProb(words.first, label.first) 
                << endl;
            }
        }
        cout << endl;
    }

    string if_one_or_other(pair<const string, string> &col, double &maxProb, 
    string &maxLabel, string &words)
    {
        if (col.first == "content")
        {
            words = col.second;
            find_max_prob(words, maxProb, maxLabel);
        }
        else if (col.first == "tag")
        {
            print(words, maxProb, maxLabel, col.second);
            return col.second;
        }
        return "";
    }

    void find_max_prob(string &words, double &maxProb, string &maxLabel)
    {
        set<string> wordset = unique_words(words);
        for (auto &label:labels)
        {
            double prob = calcLabelProb(label.first);
            for (auto &word:wordset)
            {
                prob += calcWordProb(word, label.first);
            }
            if (prob > maxProb)
            {
                maxProb = prob;
                maxLabel = label.first;
            }
        }
    }

    void print(string &words, double &maxProb, string &maxLabel, string column)
    {
        cout << "  correct = " << column << ", predicted = " << maxLabel 
        << ", log-probability score = " << maxProb << endl 
        << "  content = " << words << endl;
    }

    void test(string testFile)
    {
        csvstream csvin(testFile);
        map<string, string> row;
        cout << "test data:" << endl;
        int counterRight = 0;
        int counterAll = 0;
        string column;
        while (csvin >> row)
        {
            double maxProb = log(0);
            string maxLabel;
            string words;
            for (auto &col:row)
            {
                column = if_one_or_other(col, maxProb, maxLabel, words);
                if (column == maxLabel)
                {
                    counterRight++;
                }
            }
            cout << endl;
            counterAll++;
        }
        cout << "performance: " << counterRight << " / " << counterAll 
        << " posts predicted correctly" << endl;
    }

};

int main(int argc, char *argv[])
{
    cout.precision(3);
    bool debug;
    if (argc == 3)
    {
        debug = false;
    }
    else if (argc == 4)
    {
        string debugSelection = argv[3];
        if (debugSelection != "--debug")
        {
            cout << argv[3] << endl;
            cout << "Usage: main.exe TRAIN_FILE TEST_FILE [--debug]" << endl;
            return 1;
        }
        else
        {
            debug = true;
        }
    }
    else
    {
        cout << "Usage: main.exe TRAIN_FILE TEST_FILE [--debug]" << endl;
        return 1;
    }
    string trainFile = argv[1];
    string testFile = argv[2];
    try
    {
        Classifier classifier(trainFile, debug);
        cout << "trained on " << classifier.get_number_of_posts() << " examples" 
        << endl;
        if (debug == true)
        {
            classifier.print_debug_data();
        }
        classifier.test(testFile);
    }
    catch(const csvstream_exception &e)
    {
        cout << "Error opening file: " << trainFile << endl;
        return 1;
    }
}