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

using namespace std;
unsigned long VERSION_SUM = 0;

void readInput();
string convertToBinary(string hex);
void part1();

int main(int argc, const char * argv[]) {
    readInput();
    part1();
    return 0;
}

int parseEncodedString(string const& encoded)
{
    unsigned long version = strtoul(encoded.substr(0, 3).c_str(), nullptr, 2);
    unsigned long typeID = strtoul(encoded.substr(3, 3).c_str(), nullptr, 2);
    
    //cout << "version: " << version << endl;
    //cout << "typeID: " << typeID << endl;
    
    VERSION_SUM += version;
    
    int bitsParsed = 6;
    
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
        //cout << "value: " << strtoul(value.c_str(), nullptr, 2) << endl;
    }
    else // packet is an "operator."
    {
        if (encoded[bitsParsed] == '0')
        {
            unsigned long expectedBits = strtoul(encoded.substr(7, 15).c_str(), nullptr, 2);
            //cout << "expected bits: " << expectedBits << endl;
            bitsParsed += 16;
            int subpacketBits = 0;
            while(subpacketBits < expectedBits)
            {
                int parsed = parseEncodedString(encoded.substr(bitsParsed));
                subpacketBits += parsed;
                bitsParsed += parsed;
            }
        }
        else if(encoded[bitsParsed] == '1')
        {
            unsigned long expectedPackets = strtoul(encoded.substr(7, 11).c_str(), nullptr, 2);
            //cout << "expected packets: " << expectedPackets << endl;
            bitsParsed += 12;
            int subpackets = 0;
            while(subpackets < expectedPackets)
            {
                subpackets++;
                bitsParsed += parseEncodedString(encoded.substr(bitsParsed));
            }
        }
    }
    
    return bitsParsed;
}

void readInput()
{
    ifstream infile("input.txt");
    string encoded;
    
    infile >> encoded;
    
    parseEncodedString(convertToBinary(encoded));
    cout << "Version sum: " << VERSION_SUM << endl;
}

string convertToBinary(string hex)
{
    string binary = "";
    
    for(auto c : hex)
    {
        switch (c)
        {
            case '0':
                binary += "0000";
                break;
            case '1':
                binary += "0001";
                break;
            case '2':
                binary += "0010";
                break;
            case '3':
                binary += "0011";
                break;
            case '4':
                binary += "0100";
                break;
            case '5':
                binary += "0101";
                break;
            case '6':
                binary += "0110";
                break;
            case '7':
                binary += "0111";
                break;
            case '8':
                binary += "1000";
                break;
            case '9':
                binary += "1001";
                break;
            case 'A':
                binary += "1010";
                break;
            case 'B':
                binary += "1011";
                break;
            case 'C':
                binary += "1100";
                break;
            case 'D':
                binary += "1101";
                break;
            case 'E':
                binary += "1110";
                break;
            case 'F':
                binary += "1111";
                break;
            default:
                break;
        }
    }
    
    return binary;
}
