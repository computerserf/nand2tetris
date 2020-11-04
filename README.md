# nand2tetris

This repository contains source code implentations for, and files needed to compile and run, projects from the first edition of [*The Elements of Computing Systems*](https://www.nand2tetris.org/). For those unfamiliar, it is a sequence of projects starting from the lowly the NAND gate, proceeding up the computing stack to operating systems, where the reader implements a computer and its various software systems.

## Contents ##

### Project 1: Boolean Logic ###

This project contains combinational circuits needed to build the computer system. It uses a NAND gate as a primitive building block. Introduced here are the HDL (hardware descriptor language) and TSL (test scripting language).

### Project 2: Boolean Arithmetic ###

Proceeding forward, this project enails building circuits capable of doing basic 2's complement arithmetic, such as an adder or ALU.

### Project 3: Sequential Logic ###

Using data flip-flops as a primitive, this project requires building sequential circuits such as, registers and memory. The simulator simulates a clock.

### Project 4: Machine Language ###

Hitherto, every project was digital design. This project is a preview of writing assembly language programs to motivate the architecture of the computer. Introduced here are the Hack assembler and the CPU simulator.

### Project 5: Computer Architecture ###

This capstone hardware project consisted of putting together all the circuits to virtualy build the Hack computer, consisting of RAM, ROM and CPU. I/O is memory mapped.

### Project 6: Assembler ###

This first software project consisted of writing an assembler for the Hack computer. This implementation was done in C++,  using the CMake build system. All code was written from scratch.

### Project 7: Virtual Machine I: Stack Arithmetic ###

This project was to build a virtual machine translator to convert several files containing virtual machine commands to a single Hack assembly file. This implementation was done in C++,  using the CMake build system and the Boost filesystem library.

### Project 8: Virtual Machine II: Program Control ###

In this project the virtual machine translator was completed. This project called for control flow and function calling commands. The dpendencies are the same. In addition the Google Test library was used. Tests were written for only new features.

### Other projects ###

**To be continued**
