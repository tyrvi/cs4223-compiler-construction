# SGC - Slic to GSTAL Compiler
**Implemented by Thais Minet**
* Run on cygwin

A compiler for the Slic (Simple Language for an Instructional Compiler) language that compiles to 
GSTAL (Georgetown Stack Assembly Language). In order to run the output of SGC you will need to have
access to a GSTAL interpreter.
 
## Installation
Requirements: make, gcc, flex, bison

* Linux - `make`
* Mac OSX - `make osx`

In addition to building for Linux and OSX the make file contains 2 additional commands `make clean` which will remove all files created by make and `make cleangstal` which will remove all files with the `.gstal` extension. The only difference in installation between OSX and Linux is that OSX requires the flag `-ll` for gcc while Linux requires `-lfl`

## Usage
sgc [-h] [-o outfile] [-d] infile
* `-h` displays usage information and exits.
* `-d` prints the symbol table and compiled gstal to stdout. When this option is selected nothing will be written to any output file even if the `-o` option is used
.
* `-o outfile` specify a file to output the gstal to if not included defaults to `a.gstal`. It is recommended to name your files with the .gstal exstension although not required.

## Known Bugs
* There is a known issue in the grammar where an expression in counting loops that ends in a 
real constant will cause a syntax error ie. `0+0.1` causes a syntax error but `0.1+0` does not. 
This seems to be an issue in the range part of the grammar in counting loops and it is possible 
it may be caused by the 2 shift reduce conflicts existing in the grammar.
