//
//  main.cpp
//  AdventOfCode12-9-21
//
//  Created by Melissa George on 12/9/21.
//  Copyright © 2021 Melissa George. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <set>
#include <algorithm>
#include "helpers.hpp"

using namespace std;
using namespace Helpers;

vector<string> vents;
vector<point> lowPoints;
vector<size_t> basinSizes;

void readinput();
void part1();
void part2();
void CheckPointAndInsert(point const& p, set<point>& basin);

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
        vents.push_back(line);
}

void part1()
{
    int risk_sum = 0;
    for(int i = 0; i < vents.size(); ++i)
    {
        for(int j = 0; j < vents[i].length(); ++j)
        {
            int current = vents[i][j] - '0';
            vector<int> adjacent;
            
            if(j + 1 < vents[i].length())
                adjacent.push_back(vents[i][j + 1] - '0');
            if(j - 1 >= 0)
                adjacent.push_back(vents[i][j - 1] - '0');
            if(i + 1 < vents.size())
                adjacent.push_back(vents[i + 1][j] - '0');
            if(i - 1 >= 0)
                adjacent.push_back(vents[i - 1][j] - '0');
            
            if(*min_element(adjacent.begin(), adjacent.end()) > current)
            {
                risk_sum += (current + 1);
                lowPoints.emplace_back(j,i);
            }
        }
    }
    
    std::cout << "Part 1: " << risk_sum << std::endl;
}

void CheckPointAndInsert(point const& p, set<point>& basin)
{
    if(p.inRange(0, (int)vents[p.y].size(),
                 0, (int)vents.size())
       && vents[p.y][p.x] < '9')
    {
        basin.insert(p);
    }
}

void part2()
{
    for(point lowPoint : lowPoints)
    {
        bool pointsAdded = true;
        set<point> basin { lowPoint };
        
        while(pointsAdded)
        {
            size_t lastSize = basin.size();
            
            for(auto p : basin)
            {
                CheckPointAndInsert(point(p.x + 1, p.y), basin);
                CheckPointAndInsert(point(p.x - 1, p.y), basin);
                CheckPointAndInsert(point(p.x, p.y + 1), basin);
                CheckPointAndInsert(point(p.x, p.y - 1), basin);
            }
            
            pointsAdded = lastSize < basin.size();
        }

        basinSizes.push_back(basin.size());
    }
    
    sort(basinSizes.begin(), basinSizes.end());
    size_t len = basinSizes.size();
    size_t result = basinSizes[len-1] * basinSizes[len-2] * basinSizes[len-3];
    std::cout << "Part 2: " << result << std::endl;
}
