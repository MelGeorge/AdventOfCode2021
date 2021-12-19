//
//  main.cpp
//  AdventOfCode12-16-21
//
//  Created by Melissa George on 12/18/21.
//  Copyright © 2021 Melissa George. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <functional>
#include <numeric>

using namespace std;
unsigned long long VERSION_SUM = 0;

unsigned long long parseEncodedString(string const& encoded, int& bitsParsed);
string convertToBinary(string hex);

int main(int argc, const char * argv[]) {
    ifstream infile("input.txt");
    string encoded;
    
    infile >> encoded;
    
    int bitsParsed = 0;
    unsigned long long result = parseEncodedString(convertToBinary(encoded), bitsParsed);
    cout << "Version sum: " << VERSION_SUM << endl;
    cout << "Result: " << result << endl;
}

unsigned long long parseEncodedString(string const& encoded, int& bitsParsed)
{
    unsigned long long version = strtoull(encoded.substr(0, 3).c_str(), nullptr, 2);
    unsigned long long typeID = strtoull(encoded.substr(3, 3).c_str(), nullptr, 2);
    
    VERSION_SUM += version;
    
    bitsParsed += 6;
    
    if(typeID == 4) // packet is a literal value.
    {
        string value = "";
        while(encoded[bitsParsed] == '1')
        {
            value += encoded.substr(bitsParsed, 5).substr(1);
            bitsParsed += 5;
        }
        
        value += encoded.substr(bitsParsed, 5).substr(1);
        bitsParsed += 5;
        
        return strtoull(value.c_str(), nullptr, 2);
    }
    
    // packet is an "operator."
    vector<unsigned long long> subs;
    
    if (encoded[bitsParsed] == '0')
    {
        unsigned long long expectedBits =
            strtoull(encoded.substr(7, 15).c_str(), nullptr, 2);
        bitsParsed += 16;
        int subpacketBits = 0;
        while(subpacketBits < expectedBits)
        {
            int parsed = 0;
            subs.push_back(
                      parseEncodedString(encoded.substr(bitsParsed), parsed));
            subpacketBits += parsed;
            bitsParsed += parsed;
        }
    }
    else if(encoded[bitsParsed] == '1')
    {
        unsigned long long expectedPackets =
            strtoull(encoded.substr(7, 11).c_str(), nullptr, 2);
        bitsParsed += 12;
        while(subs.size() < expectedPackets)
        {
            int parsed = 0;
            subs.push_back(
                      parseEncodedString(encoded.substr(bitsParsed), parsed));
            bitsParsed += parsed;
        }
    }
    
    unsigned long long result = 0;
    
    switch (typeID)
    {
        case 0: // sum
        {
            for(auto s : subs)
                result += s;
            break;
        }
        case 1: // product
        {
            result = 1;
            for(auto s : subs)
                result *= s;
            break;
        }
        case 2: // min
        {
            result = *min_element(subs.begin(), subs.end());
            break;
        }
        case 3: // max
        {
            result = *max_element(subs.begin(), subs.end());
            break;
        }
        case 5: // >
        {
            result = (unsigned long long)(subs[0] > subs[1]);
            break;
        }
        case 6: // <
        {
            result = (unsigned long long)(subs[0] < subs[1]);
            break;
        }
        case 7: // ==
        {
            result = (unsigned long long)(subs[0] == subs[1]);
            break;
        }
        default:
            break;
    }
    
    return result;
}

string convertToBinary(string hex)
{
    string binary = "";
    
    for(auto c : hex)
    {
        switch (c)
        {
            case '0': binary += "0000"; break;
            case '1': binary += "0001"; break;
            case '2': binary += "0010"; break;
            case '3': binary += "0011"; break;
            case '4': binary += "0100"; break;
            case '5': binary += "0101"; break;
            case '6': binary += "0110"; break;
            case '7': binary += "0111"; break;
            case '8': binary += "1000"; break;
            case '9': binary += "1001"; break;
            case 'A': binary += "1010"; break;
            case 'B': binary += "1011"; break;
            case 'C': binary += "1100"; break;
            case 'D': binary += "1101"; break;
            case 'E': binary += "1110"; break;
            case 'F': binary += "1111"; break;
            default: break;
        }
    }
    
    return binary;
}
