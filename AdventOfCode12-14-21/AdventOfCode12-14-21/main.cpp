//
//  main.cpp
//  AdventOfCode12-14-21
//
//  Created by Melissa George on 12/14/21.
//  Copyright © 2021 Melissa George. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stack>
#include <map>
#include <set>

using namespace std;

map<string, string> mappings;
map<string, unsigned long long> pairs;
string polymer = "";
string originalPolymer = "";

void readInput();
void part1();
void part2();

int main(int argc, const char * argv[]) {
    readInput();
    part1();
    part2();
}

void readInput()
{
    ifstream infile("input.txt");
    string pair, arrow, replacement;
    
    infile >> polymer;
    originalPolymer = polymer;
    
    while (infile >> pair)
    {
        infile >> arrow >> replacement;
        mappings[pair] = replacement;
    }
}

void step()
{
    string newPolymer = "";
    
    for(unsigned long long i = 0; i < polymer.size() - 1; ++i)
    {
        newPolymer += polymer[i];
        
        if(mappings.find(polymer.substr(i, 2)) != mappings.end())
        {
            newPolymer += mappings[polymer.substr(i, 2)];
        }
    }
    
    newPolymer += polymer[polymer.size() - 1];
    polymer = newPolymer;
}

void part1()
{
    for(int i = 1; i <= 10; i++)
        step();
    
    map<char, int> freq;
    
    for(auto c : polymer)
    {
        if(c <= 'Z' && c >= 'A')
            freq[c]++;
    }
    
    pair<char, int> most = *freq.begin();
    pair<char, int> least = *freq.begin();
    
    for(auto f : freq)
    {
        if (f.second > most.second)
        {
            most = f;
        }
        else if(f.second < least.second)
        {
            least = f;
        }
    }

    cout << "Part 1: " << most.second - least.second << endl;
}

void stepV2()
{
    map<string, unsigned long long> newPairs;
    
    for(auto pair : pairs)
    {
        if(mappings.find(pair.first) != mappings.end())
        {
            string first = pair.first[0] + mappings[pair.first];
            string second  = mappings[pair.first] + pair.first[1];
            newPairs[first] += pair.second;
            newPairs[second] += pair.second;
        }
    }
    
    pairs = newPairs;
}

void part2()
{
    for(unsigned long long i = 0; i < originalPolymer.size() - 1; ++i)
    {
        pairs[originalPolymer.substr(i, 2)]++;
    }
    
    for(int i = 1; i <= 40; i++)
        stepV2();
    
    map<char, unsigned long long> freq;
    
    for(auto p : pairs)
    {
        for(auto c : p.first)
        {
            freq[c] += p.second;
        }
    }
    
    pair<char, unsigned long long> most = *freq.begin();
    pair<char, unsigned long long> least = *freq.begin();
    
    for(auto f : freq)
    {
        if (f.second > most.second)
        {
            most = f;
        }
        else if(f.second < least.second)
        {
            least = f;
        }
    }
    
    // Divide by two because this method double-counts.
    unsigned long long m = most.second / 2 + (most.second % 2);
    unsigned long long l = least.second / 2 + (least.second % 2);
    cout << "Part 2: " << m - l << endl;
}
