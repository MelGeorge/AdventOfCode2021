//
//  main.cpp
//  AdventOfCode12-10-21
//
//  Created by Melissa George on 12/9/21.
//  Copyright © 2021 Melissa George. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <stack>

using namespace std;

vector<string> lines;

void readinput();
void part1();
void part2();

int main(int argc, const char * argv[]) {
    readinput();
    part1();
    part2();
    return 0;
}


void readinput()
{
    ifstream infile("input.txt");
    string line;
    
    while(infile >> line)
        lines.push_back(line);
}

char firstIllegalChar(string line)
{
    stack<char> braces {};
    braces.push(line[0]);
    int index = 1;
    
    while(!braces.empty() && index < line.length())
    {
        char next = line[index];
        
        if(next == '(' || next == '[' || next == '{' || next == '<')
            braces.push(next);
        else if(next == ')')
        {
            if(braces.top() != '(')
                return next;
            else
                braces.pop();
        }
        else if(next == ']')
        {
            if(braces.top() != '[')
                return next;
            else
                braces.pop();
        }
        else if(next == '}')
        {
            if(braces.top() != '{')
                return next;
            else
                braces.pop();
        }
        else if(next == '>')
        {
            if(braces.top() != '<')
                return next;
            else
                braces.pop();
        }
        
        ++index;
    }
    
    return 'X';
}

void part1()
{
    int score = 0;
    for(int i = 0; i < lines.size(); ++i)
    {
        char found = firstIllegalChar(lines[i]);
        
        score += 3 * (found ==')')
                + 57 * (found == ']')
                + 1197 * (found == '}')
                + 25137 * (found == '>');
        
        if(found != 'X')
        {
            lines.erase(lines.begin() + i);
            --i;
        }
    }
    
    std::cout << "Part 1: " << score << std::endl;
}

unsigned long long lineScore(string line)
{
    stack<char> braces {};
    braces.push(line[0]);
    int index = 1;
    
    while(index < line.length())
    {
        char next = line[index];
        
        if(next == '(' || next == '[' || next == '{' || next == '<')
            braces.push(next);
        else
            braces.pop();
        ++index;
    }
    
    unsigned long long score = 0;
    
    while(!braces.empty())
    {
        char next = braces.top();
        
        score = (score * 5) + (1 * (next == '('))
            + 2 * (next == '[')
            + 3 * (next == '{')
            + 4 * (next == '<');

        braces.pop();
    }
    
    return score;
}

void part2()
{
    vector<unsigned long long> scores;
    
    for(int i = 0; i < lines.size(); ++i)
    {
        scores.push_back(lineScore(lines[i]));
    }
    
    sort(scores.begin(), scores.end());
    cout << "Part 2: " << scores[scores.size()/2] << std::endl;
}
