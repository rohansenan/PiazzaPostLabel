// Project UID db1f506d06d84ab787baf250c265e24e

#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include "csvstream.h"

using namespace std;

class Classifier
{
    private:
        int number_of_posts;
        int vocabulary_size;
        map<string, double> labels;
        map<string, map<string, double> > words_per_label;
    public:
        Classifier(string inputFile)
        {
            csvstream csvin(inputFile);
            map<string, string> row;
            while(csvin >> row)
            {
            }
            
        }
};

int main()
{
    cout << "hello" << endl;
}