/*#include <bits/stdc++.h>

using namespace std;


int main() {

    freopen("main.txt", "r", stdin);
    freopen("output.txt", "w", stdout);


    char ch;
    bool inBlockComment = false, inLineComment = false;

    while (cin.get(ch)) {

        if(inBlockComment == false and inLineComment == false and ch == '"')
        {
            cout << ch;
            cin.get(ch);
            while(ch != '"')
            {
                cout << ch;
                cin.get(ch);
            }
            cout << ch;
        }
        else if (inBlockComment) {

            if (ch == '*' && cin.peek() == '/') {
                cin.get();
                inBlockComment = false;
            }
        }
        else if (inLineComment) {

            if (ch == '\n') {
                inLineComment = false;
                cout << ch;
            }
        }
        else
        {

            if (ch == '/' && cin.peek() == '*') {
                cin.get();
                inBlockComment = true;
             }

            else if (ch == '/' && cin.peek() == '/') {
                cin.get();
                inLineComment = true;
            }

            else {
                cout << ch;
            }
        }
    }
    return 0;
}*/

