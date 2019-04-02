#include "twoseq.h"

int main(int argc, char **argv) {
    
    std::string seq1 = "", seq2 = "", seq3 = "";
    int score = 0;
    
    //  Check number of command-line arguments
    //  Terminate program if it's not 3 or 4
    if (argc < 3) {
        std::cout << "Too few arguments. Need executable input1 input2\n";
        return 0;
    }
    if (argc == 3) {
        loadFile(argv[1], seq1, argv[2], seq2, "", seq3);
    }
    else if (argc == 4) {
        std::cout << "TODO Multiple Alignment\n";
        loadFile(argv[1], seq1, argv[2], seq2, argv[3], seq3);
    }
    else {
        std::cout << "Too many arguments\n";
        return 0;
    }
    
    std::cout << "Seq1: " << seq1 << "\nSeq2: " << seq2 << "\n";
    std::cout << "\nGenerating Alignment\n\n";

    
    std::string new_seq1 = "", new_seq2 = "";
    SDP_updateTable(seq1, seq2, new_seq1, new_seq2, score);
    std::cout << "Seq1: " << new_seq1 << "\nSeq2: " << new_seq2 << "\n";
    std::cout << "Final score: " << score << "\n";
    
    return 0;
}