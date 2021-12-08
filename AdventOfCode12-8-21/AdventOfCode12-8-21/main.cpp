//
//  main.cpp
//  AdventOfCode12-8-21
//
//  Created by Melissa George on 12/8/21.
//  Copyright © 2021 Melissa George. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <set>
#include <string>

using namespace std;

vector<vector<string>> digits;
vector<vector<string>> outputValues;

void readInput();
void part1();
void part2();
int decode(int index);

int main(int argc, const char * argv[]) {
    readInput();
    part1();
    part2();
    return 0;
}

void readInput()
{
    ifstream infile("input.txt");
    
    string val;
    
    while (infile >> val)
    {
        vector<string> nextDigits(10);
        
        for(int i = 0; i < 10; ++i)
        {
            nextDigits[i] = val;
            infile >> val;
        }
        
        vector<string> nextOutputs(4);
        
        for(int i = 0; i < 4; ++i)
        {
            infile >> val;
            nextOutputs[i] = val;
        }
        
        digits.push_back(nextDigits);
        outputValues.push_back(nextOutputs);
    }
}

void part1()
{
    int count = 0;
    
    for(auto output : outputValues)
    {
        for(auto val : output)
        {
            if (val.length() == 2 ||
                val.length() == 4 ||
                val.length() == 3 ||
                val.length() == 7)
            {
                ++count;
            }
        }
    }
    
    std::cout << "Part1: " << count << std::endl;
}

void part2()
{
    int sum = 0;
    for(int i = 0; i < digits.size(); ++i)
        sum += decode(i);
    
    std::cout << "Part2: " << sum << std::endl;
}

int decode(int index)
{
    map<int, set<char>> mapping;
    
    for(auto str : digits[index])
    {
        if (str.length() == 2) // 1
        {
            mapping[1].insert(str.begin(), str.end());
        }
        else if(str.length() == 4) // 4
        {
            mapping[4].insert(str.begin(), str.end());
        }
        else if(str.length() == 3) // 7
        {
            mapping[7].insert(str.begin(), str.end());
        }
        else if(str.length() == 7) // 8
        {
            mapping[8].insert(str.begin(), str.end());
        }
    }
    
    char a = 'z', b = 'z', d = 'z', e = 'z', g = 'z', c = 'z', f = 'z';
    
    for (char x = 'a'; x < 'h'; ++x)
    {
        if (mapping[7].find(x) != mapping[7].end() && mapping[1].find(x) == mapping[1].end())
        {
            a = x;
        }
        else if (mapping[4].find(x) != mapping[4].end() &&
                 mapping[1].find(x) == mapping[1].end())
        {
            if (b == 'z') b = x;
            else d = x;
        }
        else if (mapping[8].find(x) != mapping[8].end() &&
                 mapping[1].find(x) == mapping[1].end() &&
                 mapping[4].find(x) == mapping[4].end() &&
                 mapping[7].find(x) == mapping[7].end())
        {
            if (e == 'z') e = x;
            else g = x;
        }
        if (x != a && x != b && x != d && x != e && x != g &&
            mapping[1].find(x) != mapping[1].end())
        {
            if (c == 'z') c = x;
            else f = x;
        }
    }

    // Disambiguate pairs: c/f, b/d, e/g
    for(auto str : digits[index])
    {
        if (str.length() == 6)
        {
            if (str.find(b) == string::npos) // digit 0.
            {
                swap(b,d);
            }
            else if (str.find(f) == string::npos) // digit 6.
            {
                swap(c,f);
            }
            else if (str.find(g) == string::npos) // digit 9.
            {
                swap(e,g);
            }
        }
    }
    
    std::string num = "";
    for(auto val : outputValues[index])
    {
        if (val.length() == 2 )
        {
            num += "1";
        }
        else if(val.length() == 3)
        {
            num += "7";
        }
        else if(val.length() == 4)
        {
            num += "4";
        }
        else if(val.length() == 5) // 2, 3, 5
        {
            if(val.find(c) != string::npos &&
               val.find(f) != string::npos)
                num += "3";
            else if(val.find(c) != string::npos)
                num += "2";
            else
                num += "5";
        }
        else if(val.length() == 6) // 0, 6, 9
        {
            if(val.find(d) == string::npos)
                num += "0";
            else if(val.find(c) == string::npos)
                num += "6";
            else
                num += "9";
        }
        else if(val.length() == 7)
        {
            num += "8";
        }
    }

    return std::stoi(num);
}
