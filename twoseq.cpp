#include "twoseq.h"

int match = 5, mismatch = -4, indel = -8;

std::string ReverseString(std::string a) {
    std::string b = "";
    int i = a.size() - 1;
    for (; i >= 0; --i) b += a.at(i);
    return b;
}

void loadFile(std::string filename1, std::string &seq1, 
    std::string filename2, std::string &seq2, 
    std::string filename3, std::string &seq3) {
    if (seq1.size() > 0 || seq2.size() > 0) {
        std::cout << "Input Sequences not empty\n";
        return;
    }
    if (filename3 == "") {
        std::cout << "Third file not included. Using only 2 files\n";
        std::ifstream fin1(filename1.c_str()); std::ifstream fin2(filename2.c_str());
        fin1 >> seq1; fin2 >> seq2;
    }
    else {
        std::ifstream fin1(filename1.c_str()); std::ifstream fin2(filename2.c_str()); std::ifstream fin3(filename3.c_str());
        fin1 >> seq1; fin2 >> seq2; fin3 >> seq3;
    }
}

int max_update (int a, int b, int c) {
    if ( a >= b && a >= c ) return 0;
    else if (b >= a && b >= c) return 1;
    else return 2;
}

int max(int a, int b, int c) {
    return (a >= b && a >= c) ? a : ((b >= a & b >= c) ? b : c);
}

void generate(TableEntry *t, std::string x, std::string y, 
    std::string &res11, std::string &res22) {
    int x_sz = (int) x.size() + 1, y_sz = (int) y.size() + 1;
    int i = x_sz - 1, j = y_sz - 1;
    std::string res1 = "", res2 = "";
    while (i > 0 && j > 0) {
        if ((t + (i*y_sz + j))->direction == 0) {
            res1 = x.at(i-1) + res1;
            res2 = y.at(j-1) + res2;
            --i; --j;
        }
        else if ((t + (i*y_sz + j))->direction == 1) {
            res1 = "-" + res1;
            res2 = y.at(j-1) + res2;
            --j;
        }
        else {
            res1 = x.at(i-1) + res1;
            res2 = "-" + res2;
            --i;
        }
    }
    if (i > 0) {
        res1 = x.at(i-1) + res1;
        res2 = "-" + res2;
        --i;
    }
    if (j > 0) {
        res1 = "-" + res1;
        res2 = y.at(j-1) + res2;
        --j;
    }
    res11 += res1; res22 += res2;
}

void full_DP_updateTable(std::string x, std::string y, 
    std::string &res1, std::string &res2, int &score) {

    TableEntry t[(x.size() + 1) * (y.size() + 1)];

    int i = 0, j = 0, maxy;
    int x_sz = (int) x.size() + 1, y_sz = (int) y.size() + 1;
    
    t->val = 0;
    t->direction = -1;  // Default starting spot
    for (; i < x_sz; ++i) {
        for (j = 0; j < y_sz; ++j) {
            if (i == 0) {
                (t + j)->val = indel * j;                // 1st row
                (t + j)->direction = 1;                 // left
            }
            else if (j == 0) { 
                (t + (i*y_sz))->val = indel * i;    // 1st col
                (t + (i*y_sz))->direction = 2;      // up
            }
            else {
                if (x[i-1] == y[j-1]) {
                    maxy = max_update((t + ((i-1)*y_sz+(j-1)))->val + match, 
                        (t + (i*y_sz + (j-1)))->val +indel,
                        (t + ((i-1)*y_sz + j))->val +indel);
                    if (maxy == 0) {
                        (t + (i*y_sz + j))->val = (t + ((i-1)*y_sz+(j-1)))->val + match;
                        (t + (i*y_sz + j))->direction = 0;
                    }
                    else if (maxy == 1) {
                        (t + (i*y_sz + j))->val = (t + (i*y_sz + (j-1)))->val +indel;
                        (t + (i*y_sz + j))->direction = 1;
                    }
                    else {
                        (t + (i*y_sz + j))->val = (t + ((i-1)*y_sz + j))->val +indel;
                        (t + (i*y_sz + j))->direction = 2;
                    }
                }
                else {
                    maxy = max_update((t + ((i-1)*y_sz+(j-1)))->val + mismatch, 
                        (t + (i*y_sz + (j-1)))->val +indel,
                        (t + ((i-1)*y_sz + j))->val +indel);
                    if (maxy == 0) {
                        (t + (i*y_sz + j))->val = (t + ((i-1)*y_sz+(j-1)))->val + mismatch;
                        (t + (i*y_sz + j))->direction = 0;
                    }
                    else if (maxy == 1) {
                        (t + (i*y_sz + j))->val = (t + (i*y_sz + (j-1)))->val +indel;
                        (t + (i*y_sz + j))->direction = 1;
                    }
                    else {
                        (t + (i*y_sz + j))->val = (t + ((i-1)*y_sz + j))->val +indel;
                        (t + (i*y_sz + j))->direction = 2;
                    }
                }
            }
        }
    }
    generate(t, x, y, res1, res2);
    
    // std::cout << "Result 1: " << res1 << 
    //     "\nResult 2: " << res2 << "\n";
    score += (t + ((x_sz-1)*y_sz + (y_sz-1)))->val;
}

void spacesavingDP(int *optRow, std::string x, std::string y) {
    int i = 0, j, y_sz = (int) y.size(), x_sz = (int) x.size();
    int tempRow[y_sz + 1];
    
    //  First row
    for (; i < y_sz + 1; ++i) *(tempRow+i) = indel * i;
    
    //  Rest of the rows
    for (i = 0; i < x_sz; ++i) {
        for (j = 0; j < y_sz + 1; ++j) {
            if (j == 0) *optRow = indel * (i+1);
            else {
                if (x.at(i) == y.at(j-1)) {
                    *(optRow+j) = max( *(tempRow+j - 1) + match, *(optRow+j-1) + indel, *(tempRow+j) + indel);
                }
                else *(optRow+j) = max( *(tempRow+j - 1) + mismatch, *(optRow+j-1) + indel, *(tempRow+j) + indel);
            }
        }
        //  Copy optRow and tempRow
        for (j = 0; j < y_sz + 1; ++j) *(tempRow+j) = *(optRow+j);
    }
}

void r_spacesavingDP(int *optRow, std::string x, std::string y) {
    int i, j, y_sz = (int) y.size(), x_sz = (int) x.size();
    int tempRow[y_sz + 1];
    
    //  Last Row
    for (i = y_sz, j = 0; i >= 0; --i, ++j) *(tempRow + j) = indel * i;
    
    //  Other rows
    for (i = 0; i < x_sz; ++i) {
        for (j = y_sz; j >= 0; --j) {
            if (j == y_sz) *(optRow+j) = indel * (i + 1);
            else {
                if (x.at(i) == y.at(j)) {
                    *(optRow+j) = max( *(tempRow+j+1) + match, *(optRow+j+1) + indel, *(tempRow+j) + indel );
                }
                else {
                    *(optRow+j) = max( *(tempRow+j+1) + mismatch, *(optRow+j+1) + indel, *(tempRow+j) + indel );
                }
            }
        }
        //  Copy optRow and tempRow
        for (j = y_sz; j >= 0; --j) {
            *(tempRow+j) = *(optRow+j);
        }
    }
}

int findOptimalMid(std::string x_fh, std::string x_lh, 
    std::string y) {
    int y_sz = (int) y.size(), i = 0, m = -9999, ind = 0;
    int fh_bot[y_sz + 1];
    
    // fh_bot is now the optimal row of the first half
    spacesavingDP(fh_bot, x_fh, y);     
    
    int lh_top[y_sz + 1];
    std::string x_lh_reverse = ReverseString(x_lh);
    std::string y_reverse = ReverseString(y);

    // lh_top is now the optimal row of the second half
    r_spacesavingDP(lh_top, x_lh_reverse, y_reverse);
    
    for (i = 0; i < y_sz + 1; ++i) {
        if (m < (*(fh_bot + i) + *(lh_top+i))) {
            m = *(fh_bot + i) + *(lh_top + i);
            ind = i;
        }
    }
    
    return ind;
}

void SDP_updateTable(std::string x, std::string y, 
    std::string &res1, std::string &res2, int &score) {
    int mid_y;
    
    if (x.size() < 3 || y.size() < 3) {
        //std::cout << "Something degenerated\n";
        full_DP_updateTable(x, y, res1, res2, score);
        return;
    }
    
    int x_midpoint = (int) x.size() / 2;
    std::string x_firsthalf = x.substr(0, x_midpoint);
    std::string x_lasthalf = x.substr(x_midpoint);
    
    mid_y = findOptimalMid(x_firsthalf, x_lasthalf, y);
    
    std::string y_firsthalf = y.substr(0, mid_y), y_lasthalf = y.substr(mid_y);
    
    //  Want the find the index of the optimal point of the two halves
    SDP_updateTable(x_firsthalf, y_firsthalf, res1, res2, score);
    SDP_updateTable(x_lasthalf, y_lasthalf, res1, res2, score);
}

