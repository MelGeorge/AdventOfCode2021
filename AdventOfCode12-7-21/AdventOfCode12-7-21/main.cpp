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
    
    // The linear cost is the triangular number sum(1..n) where n
    // is the constantCost. The nth triangular number = n + 1 C 2 = n(n+1)/2.
    auto linearCost = [&constantCost](int endLocation, int currentLocation)
        {
            int n = constantCost(endLocation, currentLocation);
            return n * (n + 1) / 2;
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
