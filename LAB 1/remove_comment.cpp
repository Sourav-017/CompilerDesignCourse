#include<bits/stdc++.h>
using namespace std;

string keywords[] = {
"using", "if", "int", "for", "return", "string", "ifstream", "ofstream"
};
vector<string> tokens;

void keyword_list()
{
    ifstream input("output.txt");
    string lines;

    if(input.is_open())
    {
        while(getline(input, lines))
        {
            string s = "";
            for(int i = 0; i < lines.size(); i++)
            {
                if(lines[i] == ' ')
                {
                    tokens.push_back(s);
                    s = "";
                }
                else s += lines[i];
            }
        }
    }
    input.close();
}

int is_keyword(string s)
{
    for(int i = 0; i < 8; i++ )
    {
        if(s == keywords[i]) return 1;
    }
    return 0;
}

int main()
{
    ifstream inputfile("main.txt");
    ofstream outputfile("output.txt");
    int i;
    string tmp, tmp2;
    if(inputfile.is_open())
    {
        int blockComment = 0;
        while(getline(inputfile, tmp))
        {
            for(int i = 0; i < tmp.size(); i++)
            {
                if(i < tmp.size() - 1 and tmp[i] == '/' and tmp[i + 1] == '*')
                {
                        blockComment = 1;
                }
                if(blockComment)
                {
                    if(i and tmp[i] == '/' and tmp[i - 1] == '*')
                    {
                        blockComment = 0;
                    }
                }
                else if(i < tmp.size() - 1 and tmp[i] == '/' and tmp[i + 1] == '/')
                {
                    break;
                }
                else outputfile << tmp[i];
            }

            if(blockComment == 0) outputfile << endl;
        }
    }

    inputfile.close();
    keyword_list();
    //cout << "Hello world";
    //freopen("output.txt", "w", stdout);

    for(int i = 0; i < tokens.size(); i++)
    {
        if(is_keyword(tokens[i])){
            outputfile << tokens[i] << endl;
        }

    }

}
