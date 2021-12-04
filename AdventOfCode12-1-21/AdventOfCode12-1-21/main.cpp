//
//  main.cpp
//  AdventOfCode12.1.21
//
//  Created by Melissa George on 12/1/21.
//  Copyright © 2021 Melissa George. All rights reserved.
//

#include <iostream>
#include <vector>
#include <fstream>

std::vector<int> values;

void readInput(std::string filename);
void part1();
void part2();

int main(int argc, const char * argv[]) {
    readInput("input.txt");
    part1();
    part2();
    
    return 0;
}

void readInput(std::string filename)
{
    std::ifstream infile(filename);
    
    int next;
    while(infile >> next)
    {
        values.push_back(next);
    }
}

void part1()
{
    int last = values[0];
    
    int increases = 0;
    for(auto value : values)
    {
        if (value > last)
            ++increases;
        last = value;
    }
    
    std::cout << "Increases: " << increases << std::endl;
}

void part2()
{
    int increases = 0;
    int window1 = values[0] + values[1] + values[2];
    int window2 = values[0] + values[1] + values[2];
    
    for(size_t i = 3; i < values.size(); ++i)
    {
        window2 += values[i];
        window2 -= values[i - 3];
        
        if (window2 > window1)
            ++increases;
        
        window1 = window2;
    }
    
    std::cout << "Increases: " << increases << std::endl;
}
