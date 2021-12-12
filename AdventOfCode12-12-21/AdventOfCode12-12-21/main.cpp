//
//  main.cpp
//  AdventOfCode12-12-21
//
//  Created by Melissa George on 12/12/21.
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

map<string, set<string>> connected;

struct path
{
    path(vector<string> v, bool twice = false)
    : visited(v), visitedSmallCaveTwice(twice) {}
    
    vector<string> visited;
    bool visitedSmallCaveTwice = false;
};

void readInput();
void part1();
void part2();

int main(int argc, const char * argv[]) {
    readInput();
    part1();
    part2();
    return 0;
}

void readInput()
{
    ifstream infile("input.txt");
    string line;
    
    while (infile >> line)
    {
        string first = line.substr(0, line.find('-'));
        string second = line.substr(line.find('-') + 1, line.size());

        connected[first].insert(second);
        connected[second].insert(first);
    }
}

void part1()
{
    stack<vector<string>> paths;
    vector<string> temp { "start" };
    paths.push(temp);
    
    int pathsMade = 0;
    while(!paths.empty())
    {
        temp = paths.top();
        paths.pop();
        
        if(temp.back() == "end")
        {
            ++pathsMade;
            continue;
        }
        
        for(auto next : connected[temp[temp.size() - 1]])
        {
            if(find(temp.begin(), temp.end(), next) == temp.end()
               || ('A' <= next[0] && next[0] <= 'Z'))
            {
                temp.push_back(next);
                paths.push(temp);
                temp.pop_back();
            }
        }
    }
    
    cout << "Part 1: " << pathsMade << endl;
}

void part2()
{
    stack<path> paths;
    path temp({"start"});
    paths.push(path(temp));
    
    int pathsMade = 0;
    while(!paths.empty())
    {
        temp = paths.top();
        paths.pop();
        vector<string>& visited = temp.visited;
        
        if(temp.visited.back() == "end")
        {
            ++pathsMade;
            continue;
        }
        
        for(auto next : connected[visited[visited.size() - 1]])
        {
            if(find(visited.begin(), visited.end(), next) == visited.end()
               || ('A' <= next[0] && next[0] <= 'Z'))
            {
                visited.push_back(next);
                paths.push(temp);
                visited.pop_back();
            }
            else if(temp.visitedSmallCaveTwice == false &&
                    next != "start")
            {
                temp.visitedSmallCaveTwice = true;
                visited.push_back(next);
                paths.push(temp);
                visited.pop_back();
                temp.visitedSmallCaveTwice = false;
            }
        }
    }
    
    cout << "Part 2: " << pathsMade << endl;
}
