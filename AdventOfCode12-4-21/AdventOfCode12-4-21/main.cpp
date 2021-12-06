//
//  main.cpp
//  AdventOfCode12.4.21
//
//  Created by Melissa George on 12/4/21.
//  Copyright © 2021 Melissa George. All rights reserved.
//

#include <iostream>
#include <vector>
#include <fstream>
#include "helpers.hpp"

std::vector<std::vector<std::vector<int>>> boards;
std::vector<int> called;

bool hasBoardWon(std::vector<std::vector<int>> const& board);
int boardScore(std::vector<std::vector<int>> const& board,
               int called);
void printBoard(std::vector<std::vector<int>> board);

void readInput(std::string filename);
void part1();
void part2();

int main(int argc, const char * argv[]) {
    readInput("input.txt");
    std::vector<std::vector<std::vector<int>>> boardsCopy = boards;
    part1();
    boards = boardsCopy;
    part2();
    return 0;
}

void readInput(std::string filename)
{
    std::ifstream infile(filename);
    std::string calledString;
    infile >> calledString;
    
    std::vector<std::string> nums = splitOnComma(calledString);
    
    for (auto n : nums)
        called.push_back(std::stoi(n));
    
    int c1, c2, c3, c4, c5;
    
    while (infile >> c1 >> c2 >> c3 >> c4 >> c5)
    {
        std::vector<std::vector<int>> board;
        {
            std::vector<int> row { c1, c2, c3, c4, c5 };
            board.push_back(row);
        }
        
        for(size_t i = 0; i < 4; ++i)
        {
            infile >> c1 >> c2 >> c3 >> c4 >> c5;
            board.push_back({ c1, c2, c3, c4, c5 });
        }
        
        boards.push_back(board);
    }
}

void part2()
{
    int roundNumber = 0;
    int numberCalled = called[roundNumber];
    int lastScore = -1;
    
    while(boards.size() > 0)
    {
        numberCalled = called[roundNumber];
        
        for(int b = 0; b < boards.size(); ++b)
        {
            auto& board = boards[b];
            for(auto& row : board)
            {
                for(auto& column : row)
                {
                    if(column == numberCalled)
                    {
                        column = -1;
                    }
                }
            }
            
            if (hasBoardWon(board))
            {
                lastScore = boardScore(boards[b], numberCalled);
                boards.erase(boards.begin() + b);
                --b;
            }
        }
        
        ++roundNumber;
    }
    
    std::cout << "Part2: " << lastScore << std::endl;
}

void part1()
{
    for(int number : called)
    {
        for(auto& board : boards)
        {
            for(auto& row : board)
            {
                for(auto& column : row)
                {
                    if(column == number)
                    {
                        column = -1;
                    }
                }
            }
            
            if (hasBoardWon(board))
            {
                std::cout << "Part1: " <<
                boardScore(board, number) << std::endl;
                return;
            }
        }
    }
}

bool hasBoardWon(std::vector<std::vector<int>> const& board)
{
    // Fix row num: check columns.
    for(int row = 0; row < 5; ++row)
    {
        bool columnFilled = true;
        
        for(int col = 0; col < 5; ++col)
        {
            if (board[row][col] != -1)
            {
                columnFilled = false;
                break;
            }
        }
        
        if (columnFilled)
            return true;
    }
    
    // Fix column num: check rows.
    for(int col = 0; col < 5; ++col)
    {
        bool rowFilled = true;
        for(int row = 0; row < 5; ++row)
        {
            if (board[row][col] != -1)
            {
                rowFilled = false;
                break;
            }
        }
        
        if (rowFilled)
            return true;
    }
    
    // Check diagonals.
    bool diagonalFilled = true;
    for(int col = 0, row = 0; col < 5 && row < 5; ++col, ++row)
    {
        if(board[row][col] != -1)
        {
            diagonalFilled = false;
            break;
        }
    }
    
    if (diagonalFilled)
        return true;
    
    diagonalFilled = true;
    for(int col = 4, row = 4; col >= 0 && row >= 0; --col, --row)
    {
        if(board[row][col] != -1)
        {
            diagonalFilled = false;
            break;
        }
    }
    
    if (diagonalFilled)
        return true;
    
    return false;
}

int boardScore(std::vector<std::vector<int>> const& board, int called)
{
    int score = 0;
    
    for(int row = 0; row < 5; ++row)
    {
        for(int col = 0; col < 5; ++col)
        {
            if (board[row][col] != -1)
            {
                score += board[row][col];
            }
        }
    }
    
    score *= called;
    return score;
}

void printBoard(std::vector<std::vector<int>> board)
{
    for(int row = 0; row < 5; ++row)
    {
        for(int col = 0; col < 5; ++col)
        {
            std::cout << board[row][col] << " ";
        }
        
        std::cout << std::endl;
    }
}
