// This file contains the implementaton of the Mult assembly program.

// This file is part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: projects/04/Mult.asm

// Multiplies R0 and R1 and stores the result in R2.
// (R0, R1, R2 refer to RAM[0], RAM[1], and RAM[2], respectively.)

// final = 0; i= R1
@final
M=0
@R1
D=M
@i
M=D

// if R0 == 0, skip loop
@R0
D=M
@EndLoop
D;JEQ

// while(i > 0) { final += R0; i--; }
(Loop)
@i
D=M
@EndLoop
D;JLE
@R0
D=M
@final
M=M+D
@i
M=M-1
D=M
@Loop
0;JMP

(EndLoop)
// Move result to R2
@final
D=M
@R2
M=D
