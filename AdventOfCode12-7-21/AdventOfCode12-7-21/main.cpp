//
//  main.cpp
//  AdventOfCode12-7-21
//
//  Created by Melissa George on 12/7/21.
//  Copyright © 2021 Melissa George. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstdlib>
#include <numeric>
#include <functional>
#include "helpers.hpp"

std::vector<int> crabsAtIndex;

void readInput();
int calculateCost(std::function<int(int,int)> costFunction);

int main() {
    readInput();
    
    auto constantCost = [](int endLocation, int currentLocation)
        { return std::abs(int(endLocation - currentLocation)); };
    
    auto linearCost = [](int endLocation, int currentLocation)
        {
            int cost = 0;
            for(int v = 1; v <= std::abs(int(endLocation - currentLocation)); ++v)
                cost += v;
            return cost;
        };
    
    std::cout << "Part1: " << calculateCost(constantCost) << std::endl;
    std::cout << "Part2: " << calculateCost(linearCost) << std::endl;
    return 0;
}

void readInput()
{
    std::ifstream infile("input.txt");
    std::string csv;
    infile >> csv;
    
    std::vector<int> crabs = splitIntsOnComma(csv);
    
    int max = *std::max_element(crabs.begin(), crabs.end());
    crabsAtIndex.resize(max + 1);
    for(size_t i = 0; i < crabs.size(); ++i)
    {
        crabsAtIndex[crabs[i]]++;
    }
}

int calculateCost(std::function<int(int,int)> costFunction)
{
    int leastCost = INT_MAX;
    
    for(int endLocation = 0; endLocation < (int)crabsAtIndex.size(); ++endLocation)
    {
        int currentCost = 0;
        for(int i = 0; i < crabsAtIndex.size(); ++i)
        {
            currentCost += costFunction(endLocation, i) * crabsAtIndex[i];
        }
        
        if(currentCost < leastCost)
            leastCost = currentCost;
    }
    
    return leastCost;
}
