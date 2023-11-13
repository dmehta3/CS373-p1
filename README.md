# Nondeterministic-Finite-Automata-Simulator

Reads the definition of the machine from a file (the first command line argument), with the second command line argument being the string to 
simulate the machine running on (the input to the automata). 

The output is written to standard output and it consists of either: 
  1) the word accept followed by a blank space followed by the list of accept states (blank space delimited) that the automata can
     end up in after reading in the input string (if there is a way for the automata to end in an accept state after reading the input)
  3) the word reject followed by a blank space followed by the list of states (blank space delimited) that the automata can end up in after reading
    the string (if there is no way for the automata to end in an accept state after reading the input).

Two sample inputs are included as well.
