//
//  main.cpp
//  AdventOfCode12-5-21
//
//  Created by Melissa George on 12/5/21.
//  Copyright © 2021 Melissa George. All rights reserved.
//

#include <iostream>
#include <vector>
#include <map>
#include <fstream>
#include "helpers.hpp"

std::vector<line> lines;
std::map<std::pair<int, int>, int> spots;
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
    std::ifstream infile("input.txt");
    
    std::string first;
    std::string second;
    std::string garbage;
    
    while(infile >> first >> garbage >> second)
    {
        std::vector<std::string> pt1 = splitOnComma(first);
        std::vector<std::string> pt2 = splitOnComma(second);
        point point1(std::stoi(pt1[0]), std::stoi(pt1[1]));
        point point2(std::stoi(pt2[0]), std::stoi(pt2[1]));
        line nextLine(point1, point2);
        lines.push_back(nextLine);
    }
}

void part1()
{
    for(line l : lines)
    {
        if (l.first.x == l.second.x)
        {
            int y_start = std::min(l.first.y, l.second.y);
            int y_end = std::max(l.first.y, l.second.y);
            int x = l.first.x;
            
            for(int y = y_start; y <= y_end; ++y)
            {
                spots[std::pair<int, int>(x, y)]++;
            }
        }
        else if (l.first.y == l.second.y)
        {
            int x_start = std::min(l.first.x, l.second.x);
            int x_end = std::max(l.first.x, l.second.x);
            int y = l.first.y;
            
            for(int x = x_start; x <= x_end; ++x)
            {
                spots[std::pair<int, int>(x, y)]++;
            }
        }
    }
    
    int result = 0;
    for (auto spot : spots)
    {
        if (spot.second > 1)
        {
            ++result;
        }
    }
    
    std::cout << "Part 1: " << result << std::endl;
}

void part2()
{
    spots.clear();
    
    for(line l : lines)
    {
        int x = l.first.x;
        int y = l.first.y;
        
        int x_dir = 0;
        int y_dir = 0;
        
        if (l.second.x < l.first.x)
        {
            x_dir = -1;
        }
        else if(l.second.x > l.first.x)
        {
            x_dir = 1;
        }
        
        if (l.second.y < l.first.y)
        {
            y_dir = -1;
        }
        else if(l.second.y > l.first.y)
        {
            y_dir = 1;
        }
        
        while(x != l.second.x || y != l.second.y)
        {
            spots[std::pair<int, int>(x, y)]++;
            x += x_dir;
            y += y_dir;
        }
        
        spots[std::pair<int, int>(x, y)]++;
    }
    
    int result = 0;
    for (auto spot : spots)
    {
        if (spot.second > 1)
        {
            ++result;
        }
    }
    
    std::cout << "Part 2: " << result << std::endl;
}
