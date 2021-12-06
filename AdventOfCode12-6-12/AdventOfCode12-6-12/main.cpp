//
//  main.cpp
//  AdventOfCode12-6-12
//
//  Created by Melissa George on 12/5/21.
//  Copyright © 2021 Melissa George. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <bitset>
#include "helpers.hpp"

using namespace std;

vector<int> lanternfish;

void part1();
void part2();
void readInput();

int main(int argc, const char * argv[]) {
    readInput();
    part1();
    part2();
    return 0;
}

void readInput()
{
    ifstream infile("input.txt");
    std::string row;
    infile >> row;
    
    lanternfish = splitIntsOnComma(row);
}

void part1()
{
    int days = 0;
    vector<int> fish = lanternfish;
    
    while(days < 80)
    {
        size_t originalFish = fish.size();
        
        for(int f = 0; f < originalFish; ++f)
        {
            if(fish[f] == 0)
            {
                fish.push_back(8);
                fish[f] = 6;
            }
            else
            {
                --fish[f];
            }
        }
        
        ++days;
    }
    
    std::cout << "Part1: " << fish.size() << std::endl;
}

void part2()
{
    vector<unsigned long> fishAtDay(9,0);
    
    for(auto fish : lanternfish)
    {
        fishAtDay[fish]++;
    }
    
    int days = 0;
    
    while(days < 256)
    {
        unsigned long newFish = fishAtDay[0];
        unsigned long resetFish = fishAtDay[0];
        for(int i = 1; i < fishAtDay.size(); ++i)
        {
            fishAtDay[i - 1] = fishAtDay[i];
        }
        
        fishAtDay[6] += resetFish;
        fishAtDay[8] = newFish;
        
        ++days;
    }
    
    unsigned long sum = 0;
    for(auto fish : fishAtDay)
    {
        sum += fish;
    }
    
    std::cout << "Part2: " << sum << std::endl;
}
