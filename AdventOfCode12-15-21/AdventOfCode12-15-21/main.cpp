//
//  main.cpp
//  AdventOfCode12-15-21
//
//  Created by Melissa George on 12/15/21.
//  Copyright © 2021 Melissa George. All rights reserved.
//

#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <stack>
#include "helpers.hpp"

using namespace std;
using namespace Helpers;

vector<vector<unsigned long>> originalMap;
vector<vector<unsigned long>> extendedMap;

void readInput();
void printMap(vector<vector<unsigned long>> const& toPrint);
void part1();
void part2();

int main(int argc, const char * argv[]) {
    readInput();
    printMap(originalMap);
    part1();
    part2();
    return 0;
}

void readInput()
{
    ifstream infile("input.txt");
    
    string line;
    
    while(infile >> line)
    {
        originalMap.push_back(vector<unsigned long>());
        
        for(auto c : line)
        {
            originalMap[originalMap.size() - 1].push_back(c - '0');
        }
    }
}

void printMap(vector<vector<unsigned long>> const& toPrint)
{
    cout << "map:" << endl;
    for(size_t i = 0; i < toPrint.size(); ++i)
    {
        for(size_t j = 0; j < toPrint[i].size(); ++j)
        {
            if(toPrint[i][j] == UINT_MAX)
                cout << 'X';
            else
                cout << toPrint[i][j];
        }
        cout << endl;
    }
}

unsigned long minDistanceTo(unsigned long row, unsigned long col,
                        vector<vector<unsigned long>> const& map,
                        vector<vector<unsigned long>> const& dist,
                        vector<vector<bool>> const& visited)
{
    unsigned long min = UINT_MAX;
    unsigned long columns = map[0].size();
    unsigned long rows = map.size();
    
    if(!point(col, row).inRange(0, columns, 0, rows))
    {
        return min;
    }
    
    if(point(col+1, row).inRange(0, columns, 0, rows)
       && visited[row][col+1]
       && dist[row][col+1] + map[row][col] < min)
    {
        min = dist[row][col+1] + map[row][col];
    }
    
    if(point(col-1, row).inRange(0, columns, 0, rows)
       && visited[row][col-1]
       && dist[row][col-1] + map[row][col] < min)
    {
        min = dist[row][col-1] + map[row][col];
    }
    
    if(point(col, row+1).inRange(0, columns, 0, rows)
       && visited[row+1][col]
       && dist[row+1][col] + map[row][col] < min)
    {
       min = dist[row+1][col] + map[row][col];
    }
    
    if(point(col, row-1).inRange(0, columns, 0, rows)
       && visited[row-1][col]
       && dist[row-1][col] + map[row][col] < min)
    {
        min = dist[row-1][col] + map[row][col];
    }
    
    return min;
}

point minDistance(vector<vector<unsigned long>> const & map,
                  vector<vector<unsigned long>> & dist, vector<vector<bool>> & visited)
{
    unsigned long min = UINT_MAX, min_row = 0, min_col = 0;
    
    for(int row = 0; row < dist.size(); ++row)
    {
        for(int col = 0; col < dist[0].size(); ++col)
        {
            if(!visited[row][col] && minDistanceTo(row, col, map, dist, visited) < min)
            {
                min = minDistanceTo(row, col, map, dist, visited);
                min_row = row;
                min_col = col;
            }
        }
    }
    
    visited[min_row][min_col] = true;
    dist[min_row][min_col] = min;
    
    return point(min_col, min_row);
}

unsigned long dijkstras(vector<vector<unsigned long>> const& map)
{
    size_t rows = map.size();
    size_t columns = map[0].size();
    
    vector<vector<unsigned long>> dist(rows);
    vector<vector<bool>> visited(rows);
    
    for(size_t row = 0; row < rows; ++row)
    {
        dist[row].resize(columns, UINT_MAX);
        visited[row].resize(columns, false);
    }
    
    // mark source as 0
    dist[0][0] = 0;
    visited[0][0] = true;
    
    while(!visited[rows-1][columns-1])
    {
        point p = minDistance(map, dist, visited);
        
        for(unsigned long row = 0; row < rows; ++row)
        {
            for(unsigned long col = 0; col < columns; ++col)
            {
                if(!visited[row][col] && point(col, row).adjacentTo(p) && dist[row][col] > map[row][col] + dist[p.y][p.x])
                {
                    dist[row][col] = map[row][col] + dist[p.y][p.x];
                }
            }
        }
        
        //printMap(dist);
    }
    
    return dist[rows-1][columns-1];
}

void part1()
{
    cout << "Part 1: " << dijkstras(originalMap) << endl;
}

void part2()
{
    unsigned long originalRows = originalMap.size();
    unsigned long originalCols = originalMap[0].size();
    
    extendedMap.resize(originalRows * 5, vector<unsigned long>(originalCols * 5, 0));
    
    for(auto row = 0; row < originalRows * 5; ++row)
    {
        for(auto col = 0; col < originalCols * 5; ++col)
        {
            extendedMap[row][col] = originalMap[row % originalRows][col % originalCols];
            
            extendedMap[row][col] += (row / originalRows);
            extendedMap[row][col] += (col / originalCols);
            
            if(extendedMap[row][col] > 9)
                extendedMap[row][col] %= 9;
        }
    }
    
    printMap(extendedMap);
    
    cout << "Part2: " << dijkstras(extendedMap) << endl;
}
