# Linear Space Alignment of two sequences

The main application of this program is intended for nucleotide sequences (A, G, C, T, U) but will work for other sequences as well.

Generally in gene sequencing, the problem is to determine the optimal alignment of two sequences, assuming there is a scoring metric provided. The main types of alignment metrics are matches (same characters), mismatches (different characters), or indels (at least one sequence is missing a character). An example of indel is

A-

AG

where the hyphen represents an indel event. The naive solution to determine this optimal alignment is to use dynamic programming which will determine all possible cases and choose the alignment that generates the highest score. However, this uses up quadratic time and space. Can we do better?

Using the ideas provided by Myers and Miller, given two nucleotide sequences, this program will determine the optimal alignment of two sequences in linear space and quadratic time. The trick is to mainly use only two rows of the table (which represents 2n space). These two rows of memory blocks will be repeatedly used, which eliminates the need for quadratic space.

The concept of divide and conquer is paramount in this method. One sequence is split in half. Two rows of memory blocks are then continuously used to determine the optimal split in the other sequence. This process is repeated over and over until the sizes of one of the sequences is "small enough" (a size of three is used in this particular program). The normal dynamic programming is then performed in order to find the optimal alignment of the subparts. Then the rest of the subparts are merged together to produce the optimal alignment. Although dynamic programming is performed, it is only used when one of the sequences is extremely small, therefore resulting in minimal space usage. Therefore, quadratic space is never really reached.

![alt text](https://github.com/pipluppers/LinearSpaceAlignment/blob/master/ssdp.JPG "Divide and Conquer Diagram")

Image provided by Dr. Tao Jiang's slides.
