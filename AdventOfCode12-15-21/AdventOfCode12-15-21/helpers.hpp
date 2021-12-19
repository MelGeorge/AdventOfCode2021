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
        point(unsigned long x_, unsigned long y_) : x(x_), y(y_) {}
        
        bool inRange(unsigned long x_start, unsigned long x_end, unsigned long y_start, unsigned long y_end) const
        {
            return x >= x_start && x < x_end &&
                    y >= y_start && y < y_end;
        }
        
        // no diagonals.
        bool adjacentTo(point const& other)
        {
            if(other.x == x && (other.y == y - 1 || other.y == y + 1))
            {
                return true;
            }
            else if(other.y == y && (other.x == x - 1 || other.x == x + 1))
            {
                return true;
            }
            
            return false;
        }
        
        unsigned long x;
        unsigned long y;
    };

    bool operator<(point const& p, point const& q);
}
#endif /* helpers_hpp */
