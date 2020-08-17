// This file contains an implementaton of the screen filling program.

// This file is part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: projects/04/Fill.asm

// Runs an infinite loop that listens to the keyboard input.
// When a key is pressed (any key), the program blackens the screen,
// i.e. writes "black" in every pixel;
// the screen should remain fully black as long as the key is pressed. 
// When no key is pressed, the program clears the screen, i.e. writes
// "white" in every pixel;
// the screen should remain fully clear as long as no key is pressed.

// fill = 0; render = true, last_filled = -1
@fill
M=0
@render
M=1
@lastfill
M=-1
@8192
D=A
@numwords
M=D


// while(true)
//    if(*keyboard == 0)
//        fill = 0
//    else
//        fill = -1;
//   goto update_frame;
(Loop)

@KBD
D=M
@ElseBlock
D;JNE

(Ifblock)
@fill
M=0
@AfterIf
0;JMP

(ElseBlock)
@fill
M=-1

(AfterIf)
@UpdateFrame
0;JMP

// if(fill != last_fill || render)
//    for(i = 0; i < 512*256/16; i++)
//        *(screen + i) = fill
//    last_fill = fill
//    render = false
// goto loop;
(UpdateFrame)

@fill
D=M
@lastfill
D=D-M
@UFBody
D;JNE
@render
D=M
D=D-1
@UFAfter
D;JNE

(UFBody)
@i
M=0

(For)
@numwords
D=M
@i
D=D-M
@EndFor
D;JLE

@i
D=M
@SCREEN
D=D+A
@R0
M=D
@fill
D=M
@R0
A=M
M=D

@i
D=M+1
M=D
@For
0;JMP

(EndFor)
@fill
D=M
@lastfill
M=D
@render
M=0

(UFAfter)
@Loop
0;JMP
