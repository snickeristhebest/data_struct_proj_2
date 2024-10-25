#include <iostream>
#include <cassert>
#include <fstream>
#include <string>
#include <unordered_map>
#include <sstream>
#include <vector>
#include <algorithm>
#include <cctype>
#include "queue.hpp"
using namespace std;

// Function to clean up words (remove punctuation and convert to lowercase)
string cleanLine(const string& line) {
    string cleaned;
    int spaces = 0;
    for (char ch : line) {
        if (isalpha(ch) || isdigit(ch) || ch == '\'') {
            if (spaces != 0) spaces = 0;
            cleaned += tolower(ch);  // Keep letters and apostrophes, convert to lowercase
        } else if (isspace(ch)) {
            if (spaces < 1) {
                cleaned += ' ';
                spaces++;
            }
        } else if (ch == '-' || ch == '.') {
            cleaned += ' ';  // Replace - and . with space
            spaces++;
        }
    }
    return cleaned;
}

// Helper function to compare pairs (for sorting)
bool comparePairs(const pair<string, int>& a, const pair<string, int>& b) {
    if (a.second == b.second) return a.first < b.first;
    return a.second > b.second;  // Sort by frequency in descending order
}

int main() {
    ofstream output("output.txt");  // Open output file

    for (int n = 1; n <= 10; n++) {
        ifstream Hfile("huckleberry.txt");
        ifstream Tfile("tom_sawyer.txt");

        if (!Hfile.is_open()) {
            cerr << "Error opening huckleberry.txt" << endl;
            return 1;
        }
        if (!Tfile.is_open()) {
            cerr << "Error opening tom_sawyer.txt" << endl;
            return 1;
        }

        unordered_map<string, int> Hmap;
        unordered_map<string, int> Tmap;
        StringQueue Hreader(n);

        string line;

        // Reading and processing huckleberry.txt
        while (getline(Hfile, line)) {
            line = cleanLine(line);
            istringstream iss(line);
            string word;
            while (iss >> word) {
                if (Hreader.full()) {
                    Hmap[Hreader.concatenate()]++;
                }
                Hreader.enqueue(word);
            }
        }

        StringQueue Treader(n);

        // Reading and processing tom_sawyer.txt
        while (getline(Tfile, line)) {
            line = cleanLine(line);
            istringstream iss(line);
            string word;
            while (iss >> word) {
                if (Treader.full()) {
                    Tmap[Treader.concatenate()]++;
                }
                Treader.enqueue(word);
            }
        }

        // Finding common phrases and storing the smaller count from both maps
        vector<pair<string, int>> commonPhrases;
        for (const auto& hEntry : Hmap) {
            auto tIt = Tmap.find(hEntry.first);
            if (tIt != Tmap.end()) {
                int commonCount = min(hEntry.second, tIt->second);
                commonPhrases.push_back(make_pair(hEntry.first, commonCount));
            }
        }

        // Sort the common phrases by their smaller count in descending order
        sort(commonPhrases.begin(), commonPhrases.end(), comparePairs);

        // Output the top 10 most frequent common phrases
        int phrasesCount = 10;
        output << "\nTop " << phrasesCount << " most frequent phrases for length " << n << ":\n\n";


        int count = 0;
        for (const auto& phrase : commonPhrases) {
            if (count >= phrasesCount) break;
            output << "phrase: " << phrase.first << "\t\t Tom Sawyer Freq: " << Tmap[phrase.first] << "\t\t Huckleberry Finn Freq: " << Hmap[phrase.first] << endl;
            count++;
        }
        Hfile.close();
        Tfile.close();
    }

    output.close();  // Close output file

    return 0;
}
