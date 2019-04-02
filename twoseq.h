#pragma once

#include <iostream>
#include <fstream>

struct TableEntry {
    int val;
    int direction;  // 0 if diagonal, 1 if left, 2 if up
};

//  Returns the string backwards
std::string ReverseString(std::string);

//  Loads 2 or 3 files
void loadFile(std::string filename1, std::string &seq1, 
    std::string filename2, std::string &seq2, 
    std::string filename3, std::string &seq3);

//  Put diagonal in a, left in b, and up in c
//  Returns 0 if a is largest, 1 if b is largest, 2 if c is largest
int max_update(int, int, int);

//  Returns the largest integer
int max(int a, int b, int c);

//  Reconstruct the optimal alignment of input strings x and y. 
//  Follows the direction field of TableEntry
//  Store result in res1 and res2
void generate(TableEntry *, std::string, std::string, 
    std::string &, std::string &);

//  Dynamic Programming
void full_DP_updateTable(std::string, std::string, 
    std::string &, std::string&, int &);

//  O(n)
//  Uses 2n memory blocks to calculate the bottom-most row
void spacesavingDP(int *, std::string, std::string);

//  O(n)
//  Uses 2n memory blocks to calculate the topmost row
void r_spacesavingDP(int *, std::string, std::string);

//  Find the optimal midpoint of string y
//  Call spacesavingDP and r_spacesavingDP to find the 
//      desired rows to compare
//  Find the maximum sum between the rows. 
//  This producess the midpoint of y
int findOptimalMid(std::string, std::string, std::string);

//  Space Saving Dynamic Programming Function
//  Called by the main function
void SDP_updateTable(std::string, std::string, 
    std::string &, std::string &, int &);

