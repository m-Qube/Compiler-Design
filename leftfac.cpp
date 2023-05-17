#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <bits/stdc++.h>
using namespace std;
int main()
{
    long long int i, j, k, l, n, m = 9999999999, mini, ma = 0;
    string s[100], st, ch, sc = "", result, fs, maxi, rs = "";
    vector<string> ss;
    vector<string> sp;
    
    // Prompting the user to enter the number of productions
    cout << "Enter the number of productions:";
    cin >> n;
    
    // Prompting the user to enter the productions
    cout << "Enter the productions:\n";
    for (i = 1; i <= n; i++)
    {
        cin >> s[i];
    }
    
    for (i = 1; i <= n; i++)
    {
        st = s[i];
        sc = "";

        for (j = 0; j < st.length(); j++)
        {
            if (i == 1)
            {
                fs = st[0]; // Extracting the left-hand side non-terminal of the first production
            }
            if (st[j] == '=')
            {
                l = j; // Finding the position of the '=' symbol to determine the start of the right-hand side
            }
        }

        if (i == 1)
        {
            // Extracting the different productions on the right-hand side of the first production
            for (k = l + 1; k < st.length(); k++)
            {
                if (st[k] == '|')
                {
                    ss.push_back(sc); // Storing each production in a vector
                    sc = "";
                }
                if (st[k] != '|')
                {
                    ch = st[k];
                    sc = sc + ch;
                }
            }
            ss.push_back(sc);
        }
    }

    for (k = 0; k < ss.size(); k++)
    {
        mini = ss[k].size();
        m = min(m, mini);
        maxi = ss[k];
    }

    for (k = 0; k < m; k++)
    {
        // This loop doesn't seem to have any purpose as it doesn't perform any operations
    }

    for (int i = 0; i < m; i++)
    {
        char current = ss[0][i];

        for (int j = 1; j < ss.size(); j++)
        {
            if (ss[j][i] != current)
            {
                break;
            }
            result.push_back(current); // Finding the common prefix among the productions
        }
    }

    for (j = 0; j < ss.size(); j++)
    {
        maxi = ss[j];
        for (k = 0; k < maxi.length(); k++)
        {
            if (k >= result.length())
            {
                rs = rs + maxi[k]; // Finding the remaining suffix of each production
            }
        }
        if (j != ss.size() - 1)
        {
            rs = rs + '|'; // Adding the '|' symbol between different productions
        }
    }

    // Printing the left-factored productions
    cout << fs << "=" << result << fs << "'" << endl;
    cout << fs << "'" << "=" << rs << endl;

    // Printing the remaining productions
    for (i = 2; i <= n; i++)
    {
        cout << s[i] << endl;
    }

    return 0;
}

//Sample Input
// Enter the number of productions: 3
// Enter the productions:
// S=abc|abd
// A=abc|abd|axy
// B=abc|axy

// S=aS'
// S'=bc|bd
// A=aA'
// A'=bc|bd|xy
// B=aB'
// B'=bc|xy

// A=abc|abd|axy
// B=abc|axy
