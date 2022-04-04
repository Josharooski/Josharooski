Matrix Solver implemented with Dancing Links (Algorithm DLX by Don Knuth)

This probably should have been called "ExactCoverSolver" because that's exactly
its intention. This program will grow to hopefully become a versatile exact cover
problem solver, meaning you could pass in multiple types of exact cover problems
and receive an answer with little effort. The types of problems I have in mind
currently are 0-1 matrices (implemented in this program), Sudoku, pentominoes,
the famous queens problem, hexiamonds, and tetrasticks. Pretty much all of the
examples given in Don Knuth's 2000 paper.

The aforementioned paper, found here: https://arxiv.org/abs/cs/0011047v1,
describes the exact structure implemented in this program. I highly recommend
reading it as it is incredibly interesting and educational. Knuth uses psuedocode
to explain the multi-part algorithm as well as graphical examples.

This program is still in its infancy but the dancing links implementation is almost
complete. As of right now, it randomly generates a 2D boolean array that is used to
determine where to place the active nodes. Once that's complete both the 2D boolean array
and 2D node array (called Table) are printed out for debugging/tracking. The boolean table 
is pretty self-explanatory but the Table is printed using the coordinates of each active node.
Each row is on it's own line and is printed "backwards" by formatting to [column, row]. The
boolean table is to be read from the top-left to top-right with each row extending downward
from the column header. Note: This method won't be used long-term, it's only to prevent having
to hard-code different use cases for developing the Table creation algorithm. There's also a bug
that sometimes causes one or more column to have no 1s. Rather than fix this I just have a 
special case in create_DLX_Matrix() that adds a node to an empty list.

The first node in each column is always active and acts as a header. The linked lists in this
program are circular so it's important to know where to start and end. So the column headers
will wlways point to the node on its left and right while the last node points circularly around
to the header. Similarly, the header node points to the first column header with it's right pointer
and the last one with its left. The column headers are the only nodes that utilize the numNodes
and name variables.

The actual Node class is very basic and probably could've just been a struct in hindsight. But alas,
the wheel of time moves ever onward.

The actual searching for exact cover solutions is almost done as of now but will need extensive testing.