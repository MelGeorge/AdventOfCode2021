//
//  helpers.cpp
//  AdventOfCode12-5-21
//
//  Created by Melissa George on 12/5/21.
//  Copyright © 2021 Melissa George. All rights reserved.
//

#include "helpers.hpp"

std::vector<std::string> splitOnComma(std::string str)
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
