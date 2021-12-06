//
//  main.cpp
//  AdventOfCode12-3-21
//
//  Created by Melissa George on 12/5/21.
//  Copyright © 2021 Melissa George. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <bitset>

using namespace std;

const int BITSET_SIZE = 12;

bitset<BITSET_SIZE> GAMMA;
bitset<BITSET_SIZE> EPSILON;
bitset<BITSET_SIZE> EQUALLY_COMMON;
vector<bitset<BITSET_SIZE> > rows;

void part1();
void part2();
unsigned long oxygenGeneratorRating();
unsigned long co2ScrubberRating();

int main(int argc, const char * argv[]) {
    part1();
    part2();
    return 0;
}

void part1()
{
    ifstream infile("input.txt");

    std::string row;
    
    while(infile >> row)
    {
        rows.push_back(bitset<BITSET_SIZE>(row));
    }
    
    for(int i = 0; i < GAMMA.size(); ++i)
    {
        int ones = 0;
        
        for(auto const& bits : rows)
        {
            if(bits[i])
                ++ones;
        }
        
        if (ones >= rows.size() / 2)
        {
            GAMMA[i] = 1;
        }
        else if (ones == rows.size() / 2 && ones % 2 == 0)
        {
            EQUALLY_COMMON[i] = 1;
        }
    }
    
    EPSILON = bitset<BITSET_SIZE>(GAMMA).flip();
    std::cout << "Part1: " << GAMMA.to_ulong() * EPSILON.to_ulong() << std::endl;
}

unsigned long oxygenGeneratorRating()
{
    vector<bitset<BITSET_SIZE> > consider = rows;
    int i = BITSET_SIZE - 1;
    
    while(consider.size() > 1)
    {
        int ones = 0;
        int zeroes = 0;
        
        for(auto row : consider)
        {
            ones += row[i] == 1;
            zeroes += row[i] == 0;
        }
        
        int val;
        
        if (ones > zeroes)
            val = 1;
        else if(ones < zeroes)
            val = 0;
        else
            val = 1;
        
        auto pred = [i, val] (bitset<BITSET_SIZE> const& row)
        {
            return row[i] != val;
        };
        
        auto begin = remove_if(consider.begin(),consider.end(),pred);
        consider.erase(begin, consider.end());
        --i;
    }
    
    return consider[0].to_ulong();
}

unsigned long co2ScrubberRating()
{
    vector<bitset<BITSET_SIZE> > consider = rows;
    int i = BITSET_SIZE - 1;
    
    while(consider.size() > 1)
    {
        int ones = 0;
        int zeroes = 0;
        
        for(auto row : consider)
        {
            ones += row[i] == 1;
            zeroes += row[i] == 0;
        }
        
        int val;
        
        if (ones > zeroes)
            val = 0;
        else if(ones < zeroes)
            val = 1;
        else
            val = 0;
        
        auto pred = [i, val] (bitset<BITSET_SIZE> const& row)
        {
            return row[i] != val;
        };
        
        auto begin = remove_if(consider.begin(),consider.end(),pred);
        consider.erase(begin, consider.end());
        --i;
    }
    
    return consider[0].to_ulong();
}

void part2()
{
    unsigned long o2rating = oxygenGeneratorRating();
    unsigned long co2rating = co2ScrubberRating();
    std::cout << "Oxygen generator rating: " << o2rating << std::endl;
    std::cout << "CO2 scrubber rating: " << co2rating << std::endl;
    std::cout << "Part2: " << o2rating * co2rating << std::endl;
}
