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

namespace Helpers
{
    struct point
    {
        point(int x_, int y_) : x(x_), y(y_) {}
        
        bool inRange(int x_start, int x_end, int y_start, int y_end) const
        {
            return x >= x_start && x < x_end &&
                    y >= y_start && y < y_end;
        }
        
        int x;
        int y;
    };

    bool operator<(point const& p, point const& q);
}
#endif /* helpers_hpp */
