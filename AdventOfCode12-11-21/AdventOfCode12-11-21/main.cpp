//
//  main.cpp
//  AdventOfCode12-11-21
//
//  Created by Melissa George on 12/11/21.
//  Copyright © 2021 Melissa George. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <set>
#include <stack>
#include <algorithm>
#include "helpers.hpp"

using namespace std;
using namespace Helpers;

const int DIMENSION = 10;
int FLASHES = 0;

vector<vector<int>> octopi(10);

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
    string filename = string("input") + string(".txt");
    ifstream infile(filename);
    char temp;
    
    for(int y = 0; y < DIMENSION; ++y)
    {
        for(int x = 0; x < DIMENSION; ++x)
        {
            infile >> temp;
            octopi[y].push_back(temp - '0');
        }
    }
}

void printOctopi()
{
    for(int y = 0; y < DIMENSION; ++y)
    {
        for(int x = 0; x < DIMENSION; ++x)
        {
            cout << octopi[y][x];
        }
        cout << endl;
    }
}

bool step()
{
    stack<point> aboutToFlash;
    
    for(int y = 0; y < DIMENSION; ++y)
    {
        for(int x = 0; x < DIMENSION; ++x)
        {
            octopi[y][x]++;
            if(octopi[y][x] == 10)
            {
                aboutToFlash.push(point(x, y));
            }
        }
    }
    
    while(!aboutToFlash.empty())
    {
        point flashing = aboutToFlash.top();
        aboutToFlash.pop();
        
        for(int y = flashing.y - 1; y <= flashing.y + 1; ++y)
        {
            for(int x = flashing.x - 1; x <= flashing.x + 1; ++x)
            {
                if(point(x,y).inRange(0, DIMENSION, 0, DIMENSION))
                {
                    octopi[y][x]++;
                    
                    if(octopi[y][x] == 10)
                    {
                        aboutToFlash.push(point(x, y));
                    }
                }
            }
        }
    }
    
    bool allFlashed = true;
    
    for(int y = 0; y < DIMENSION; ++y)
    {
        for(int x = 0; x < DIMENSION; ++x)
        {
            if (octopi[y][x] > 9)
            {
                octopi[y][x] = 0;
                ++FLASHES;
            }
            else
            {
                allFlashed = false;
            }
        }
    }
    
    return allFlashed;
}

void part1()
{
    for(int i = 0; i < 100; ++i)
        step();
    
    cout << "Part 1: " << FLASHES << endl;
}

void part2()
{
    int steps = 100;
    bool allFlashed = false;
    
    while(!allFlashed)
    {
        allFlashed = step();
        ++steps;
    }
    
    cout << "Part 2: " << steps << endl;
}
