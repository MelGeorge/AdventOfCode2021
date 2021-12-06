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

void part1();
void part2();

int main(int argc, const char * argv[]) {
    part1();
    part2();
    return 0;
}

void part1()
{
    std::ifstream infile("input.txt");
    
    int horizontal = 0;
    int depth = 0;
    
    std::string direction;
    int magnitude;
    
    while(infile >> direction >> magnitude)
    {
        switch(direction[0])
        {
            case 'f':
                horizontal += magnitude;
                break;
            case 'u':
                depth -= magnitude;
                break;
            case 'd':
                depth += magnitude;
                break;
            default:
                exit(0);
        }
    }
    
    std::cout << "Depth: " << depth << std::endl;
    std::cout << "Horizontal: " << horizontal << std::endl;
    std::cout << "Product: " << depth * horizontal << std::endl;
}

void part2()
{
    std::ifstream infile("input.txt");
    
    int aim = 0;
    int horizontal = 0;
    int depth = 0;
    
    std::string direction;
    int magnitude;
    
    while(infile >> direction >> magnitude)
    {
        switch(direction[0])
        {
            case 'f':
                horizontal += magnitude;
                depth += aim * magnitude;
                break;
            case 'u':
                aim -= magnitude;
                break;
            case 'd':
                aim += magnitude;
                break;
            default:
                exit(0);
        }
    }
    
    std::cout << "Depth: " << depth << std::endl;
    std::cout << "Horizontal: " << horizontal << std::endl;
    std::cout << "Product: " << depth * horizontal << std::endl;
}
