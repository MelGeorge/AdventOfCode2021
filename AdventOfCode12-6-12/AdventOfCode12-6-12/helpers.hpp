//
//  helpers.hpp
//  AdventOfCode12-5-21
//
//  Created by Melissa George on 12/5/21.
//  Copyright © 2021 Melissa George. All rights reserved.
//

#ifndef helpers_hpp
#define helpers_hpp

#include <stdio.h>
#include <vector>
#include <string>

struct point
{
    point(int x_, int y_) : x(x_), y(y_) {}
    int x;
    int y;
};

struct line
{
    line(point f, point s) : first(f), second(s) {}
    point first;
    point second;
};

std::vector<std::string> splitOnComma(std::string str);

std::vector<int> splitIntsOnComma(std::string str);

#endif /* helpers_hpp */
