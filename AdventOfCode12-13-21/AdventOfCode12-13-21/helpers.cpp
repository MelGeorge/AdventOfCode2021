//
//  helpers.cpp
//  AdventOfCode12-7-21
//
//  Created by Melissa George on 12/7/21.
//  Copyright © 2021 Melissa George. All rights reserved.
//

#include "helpers.hpp"

std::vector<std::string> Helpers::splitOnComma(std::string str)
{
    std::vector<std::string> result;
    
    std::string next = "";
    
    for(char c : str)
    {
        if (c == ',')
        {
            result.push_back(next);
            next = "";
        }
        else
        {
            next += c;
        }
    }
    
    result.push_back(next);
    
    return result;
}

std::vector<int> Helpers::splitIntsOnComma(std::string str)
{
    std::vector<std::string> strings = Helpers::splitOnComma(str);
    std::vector<int> result;
    for(auto s : strings)
        result.push_back(stoi(s));
    
    return result;
}
