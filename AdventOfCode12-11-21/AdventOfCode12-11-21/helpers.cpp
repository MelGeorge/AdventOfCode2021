//
//  helpers.cpp
//  AdventOfCode12-5-21
//
//  Created by Melissa George on 12/5/21.
//  Copyright © 2021 Melissa George. All rights reserved.
//

#include "helpers.hpp"

bool Helpers::operator<(point const& p, point const& q)
{
    return (p.x < q.x) || (p.x == q.x && p.y < q.y);
}
