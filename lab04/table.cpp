#include <bits/stdc++.h>
using namespace std;

string keywords[] = {
    "using", "if", "int", "for", "return", "string", "ifstream", "ofstream", "else", "float", "bool"
};

pair<char, string> symbols[] = {
    {'<', "less than"}, {'>', "greater than"}, {'.', "dot"}, {'#', "Hash"},
    {'(', "opening brace"}, {')', "closing brace"}, 
    {'{', "left curly brace"}, {'}', "right curly brace"},
    {',', "comma"}, {';', "semicolon"}, {'=', "assignment"}
};

vector<string> tokens;
map<string, pair<string, int>> symbolTable; // Variable name, type, and entry number
int entryCount = 0;

// Check if a character is a symbol
pair<int, string> is_symbol(char ch) {
    for (const auto &sym : symbols) {
        if (ch == sym.first) return {1, sym.second};
    }
    return {0, "0"};
}

// Check if a string is a keyword
bool is_keyword(const string &s) {
    for (const auto &kw : keywords) {
        if (s == kw) return true;
    }
    return false;
}

// Check if a variable is valid
bool is_valid_variable(const string &var) {
    if (var.empty() || (!isalpha(var[0]) && var[0] != '_')) return false;
    for (size_t i = 1; i < var.size(); ++i) {
        if (!isalnum(var[i]) && var[i] != '_') return false;
    }
    return !is_keyword(var);
}

// Remove comments and process lexemes
string remove_comments(const string &line, int &blockComment) {
    string result;
    size_t i = 0;
    while (i < line.size()) {
        if (!blockComment && i < line.size() - 1 && line[i] == '/' && line[i + 1] == '*') {
            blockComment = 1;
            i += 2;
        } else if (blockComment && i < line.size() - 1 && line[i] == '*' && line[i + 1] == '/') {
            blockComment = 0;
            i += 2;
        } else if (!blockComment && i < line.size() - 1 && line[i] == '/' && line[i + 1] == '/') {
            break; // Ignore rest of line after "//"
        } else if (!blockComment) {
            result += line[i++];
        } else {
            i++;
        }
    }
    return result;
}

void process_line(const string &line, ofstream &txtFile) {
    istringstream iss(line);
    string word;
    while (iss >> word) {
        if (is_keyword(word)) {
            txtFile << left << setw(15) << word << setw(20) << "keyword" << "-" << endl;
        } else if (is_valid_variable(word)) {
            if (symbolTable.find(word) == symbolTable.end()) {
                symbolTable[word] = {"id", entryCount++};
            }
            txtFile << left << setw(15) << word << setw(20) << "id" << "pointer to symbol table entry" << endl;
        }

        // Check for operators and symbols in the current word
        for (char ch : word) {
            if (is_symbol(ch).first) {
                txtFile << left << setw(15) << ch << setw(20) << "special symbol" << is_symbol(ch).second << endl;
            }
            // Check if the character is an operator
            if (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '%') {
                txtFile << left << setw(15) << ch << setw(20) << "operator" << "arithmetic operator" << endl;
            }
        }
    }
}

void make_symbol_table() {
    ifstream inputfile("main.txt");
    ofstream txtFile("output.txt");

    // Lexemes table
    txtFile << "Lexemes Table" << endl;
    txtFile << left << setw(15) << "Lexemes" << setw(20) << "Token Name" << "Attribute Value" << endl;
    txtFile << string(50, '-') << endl;

    if (inputfile.is_open()) {
        string line;
        int blockComment = 0;
        while (getline(inputfile, line)) {
            string cleanLine = remove_comments(line, blockComment);
            process_line(cleanLine, txtFile);
        }
    }
    txtFile << endl;

    // Symbol table
    txtFile << "* Symbol Table" << endl;
    txtFile << left << setw(15) << "Symbol" << setw(10) << "Token" << setw(15) << "Data Type" << "Pointer to Symbol Table Entry" << endl;
    txtFile << string(50, '-') << endl;

    for (const auto &entry : symbolTable) {
        txtFile << left << setw(15) << entry.first
                << setw(10) << entry.second.first
                << setw(15) << "int"  // Assuming type "int" for simplicity
                << entry.second.second << endl;
    }

    inputfile.close();
    txtFile.close();
}

int main() {
    make_symbol_table();
    return 0;
}
