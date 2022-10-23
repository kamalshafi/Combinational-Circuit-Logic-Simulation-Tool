# Combinational-Circuit-Logic-Simulation-Tool
The objective of the project is to implement a logic simulation tool in C language for combinational circuits. Logic simulation is defined as the process of applying values at the primary inputs (Input vector) and observe and report the values at the primary outputs (Output Response).
This project uses basic C data structures (Arrays, Structures and Pointers). The input to your program is an ISCAS’85 benchmark combinational circuit(.isc) and corresponding file that contains the input vectors(.vec).
The nodes of the circuit have been labeled topological where each node representa a circuit element and each edge represents a connection.


## Input Files
".isc" This file contains information about the combinational circuit

".vec" This file contains information about the input vectors (values at the primary inputs). Each line in this file is a input vector. The total number of characters in each line is equal to the number of primary inputs in the corresponding circuit.The characters in the line represents ’0’: logic zero, ’1’: logic one, ’x’: don’t care value. During simulation, the ’x’ is considered as ’ 2’ for this part of the project. The .vec file contains only few input vector of all possible input vectors of the circuit.

## Implementation
Run the make file with arrguments of input and output 
