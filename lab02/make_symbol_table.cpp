#include <bits/stdc++.h>
using namespace std;

string keywords[] = {
    "using", "if", "int", "for", "return", "string", "ifstream", "ofstream", "else", "float", "bool"
};

pair<char, string> symbols[] = {
    {'<', "less than"}, {'>', "greater than"}, {'.', "dot"}, {'#', "Hash"},
    {'(', "opening brace"}, {')', "closing brace"}
};

vector<string> tokens;

vector<pair<char, string> > symbol;

pair<int, string> is_symbol(char ch) {
    for (int i = 0; i < 6; i++) {
        if (ch == symbols[i].first) return {1, symbols[i].second};
    }
    return {0, "0"};
}


void make_symbollist() {
    ifstream input("output.txt");
    if (input.is_open()) {
        string lines;
        while (getline(input, lines)) {
            for (int i = 0; i < lines.size(); i++) {
                int sz = lines.size() - 1;
                if (i < sz) {
                    if (lines[i] == '<' && lines[i + 1] == '<') {
                        i++;
                        symbol.push_back({' ', "output stream"});
                        continue;
                    }

                    if (lines[i] == '>' && lines[i + 1] == '>') {
                        i++;
                        symbol.push_back({' ', "input stream"});
                        continue;
                    }
                }
                if (is_symbol(lines[i]).first) {
                    symbol.push_back({lines[i], is_symbol(lines[i]).second});
                }
            }
        }
    }
    input.close();
}

int is_keyword(string s) {
    for (int i = 0; i < 10; i++) { 
        if (s == keywords[i]) return 1;
    }
    return 0;
}
bool is_valid_variable(string var) {

    if (var.empty()) return false;


    if (!isalpha(var[0]) && var[0] != '_') return false;


    for (size_t i = 1; i < var.size(); ++i) {
        if (!isalnum(var[i]) && var[i] != '_') return false;
    }

    if (is_keyword(var)) return false;

    return true; 
}

void make_variable_table() {
    ifstream inputfile("output.txt");
    ofstream var_table("variables.txt");

    if (var_table.is_open()) {
        string line;
        while (getline(inputfile, line)) {
            istringstream iss(line);
            string word;

            while (iss >> word) {
                if (word == "int" || word == "float" || word == "bool") {
                    string type = word;
                    while (iss >> word) {
                        if (word == ";") {
                            break; 
                        }

                        if (word == "(" || word.back() == '(' || word.back() == ')') {
                            break; 
                        }

                        if (word.back() == ',' || word.back() == ';') {
                            word.pop_back();
                        }

                        if (is_valid_variable(word)) {
                            var_table << type << " " << word << endl; 
                        }
                    }
                }
            }
        }
    }

    inputfile.close();
    var_table.close();
}

int main() {
    ifstream inputfile("main.txt");
    ofstream outputfile("output.txt");
    string tmp;

    if (inputfile.is_open()) {
        int blockComment = 0;
        while (getline(inputfile, tmp)) {
            for (int i = 0; i < tmp.size(); i++) {
                if (i < tmp.size() - 1 && tmp[i] == '/' && tmp[i + 1] == '*') {
                    blockComment = 1;
                }
                if (blockComment) {
                    if (i && tmp[i] == '/' && tmp[i - 1] == '*') {
                        blockComment = 0;
                    }
                } else if (i < tmp.size() - 1 && tmp[i] == '/' && tmp[i + 1] == '/') {
                    break;
                } else {
                    outputfile << tmp[i];
                }
            }
            if (blockComment == 0) outputfile << endl;
        }
    }

    inputfile.close();
    make_variable_table();
    for(int i = 0; i < tokens.size(); i++)
    {
        if(is_keyword(tokens[i])){
            outputfile << tokens[i] << endl;
        }

    }

    make_symbollist();
    for(int i = 0; i < symbol.size(); i++)
    {
         outputfile << symbol[i].first << " "  << symbol[i].second<< endl;
    }
    return 0;
}
