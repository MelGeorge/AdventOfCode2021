//
//  main.cpp
//  AdventOfCode12-13-21
//
//  Created by Melissa George on 12/18/21.
//  Copyright © 2021 Melissa George. All rights reserved.
//

#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <stack>
#include "helpers.hpp"

using namespace std;
using namespace Helpers;

vector<vector<char>> paper;
vector<fold> folds;

void readInput();
void part1();
void part2();

int main(int argc, const char * argv[]) {
    readInput();
    part1();
    part2();
    return 0;
}

void printPaper()
{
    for(size_t r = 0; r < paper.size(); ++r)
    {
        for(size_t c = 0; c < paper[r].size(); ++c)
        {
            cout << paper[r][c];
        }
        cout << endl;
    }
}

void readInput()
{
    ifstream infile("input.txt");
    string line;
    
    while(infile >> line)
    {
        if(line.find("fold") != line.npos)
            break;
        
        vector<int> splits = splitIntsOnComma(line);
        size_t x = splits[0];
        size_t y = splits[1];
        
        if(paper.size() < y + 1)
        {
            paper.resize(y + 1);
        }
        for(auto& p : paper)
        {
            if(p.size() < x + 1)
                p.resize(x + 1, '.');
        }

        paper[y][x] = '#';
    }
    
    infile >> line >> line;
    folds.push_back(fold(line));
    
    while(infile >> line >> line >> line)
        folds.push_back(fold(line));
}

void performYFold(int value)
{
    for(size_t row = value + 1, copyIntoRow = value - 1; row < paper.size() && copyIntoRow >= 0; ++row, --copyIntoRow)
    {
        for(size_t col = 0; col < paper[row].size(); ++col)
        {
            if(paper[copyIntoRow][col] == '#' || paper[row][col] == '#')
            {
                paper[copyIntoRow][col] = '#';
            }
            else
            {
                paper[copyIntoRow][col] = '.';
            }
        }
    }
    
    paper.resize(value);
}

void performXFold(int value)
{
    for(size_t row = 0; row < paper.size(); ++row)
    {
        for(size_t col = value + 1, copyIntoCol = value - 1; col < paper[row].size() && copyIntoCol >= 0; ++col, --copyIntoCol)
        {
            if(paper[row][copyIntoCol] == '#' || paper[row][col] == '#')
            {
                paper[row][copyIntoCol] = '#';
            }
            else
            {
                paper[row][copyIntoCol] = '.';
            }
        }
    }
    
    for(auto& p : paper)
    {
        p.resize(value);
    }
}

void performFold(fold f)
{
    if(f.direction == 'y')
    {
        performYFold(f.value);
    }
    else
    {
        performXFold(f.value);
    }
}

int countPoints()
{
    int count = 0;
    
    for(auto row : paper)
        for(auto value : row)
            if(value == '#')
                ++count;
    return count;
}

void part1()
{
    fold first = folds[0];
    performFold(first);
    cout << "Part 1: " << countPoints() << endl;
}

void part2()
{
    for(size_t i = 1; i < folds.size(); ++i)
    {
        performFold(folds[i]);
    }
    
    cout << "Part 2: " << endl;
    printPaper();
}
