//
//  helpers.hpp
//  AdventOfCode12-7-21
//
//  Created by Melissa George on 12/7/21.
//  Copyright © 2021 Melissa George. All rights reserved.
//

#ifndef helpers_hpp
#define helpers_hpp

#include <stdio.h>
#include <vector>
#include <string>
#include <string>

namespace Helpers
{
    struct fold
    {
        fold(char d, int v)
        : direction(d), value(v) {}
        
        fold(std::string line)
        {
            auto y_pos = line.find("y=");
            auto x_pos = line.find("x=");
            
            if(y_pos != line.npos)
            {
                direction = 'y';
                value = std::stoi(line.substr(y_pos + 2));
            }
            else if(x_pos != line.npos)
            {
                direction = 'x';
                value = std::stoi(line.substr(x_pos + 2));
            }
        }
        
        char direction;
        int value;
    };

    std::vector<std::string> splitOnComma(std::string str);
    std::vector<int> splitIntsOnComma(std::string str);
};

#endif /* helpers_hpp */
