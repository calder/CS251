Overview
========
Our interpreter is interactive, and possesses a minimal library of scheme functions. 
All functions specified in the assignment are implemented, as are some not specified. 
Our error handling is primitive (it distinguishes only between syntax and runtime 
errors) as no further specifications were published for error handling. While we do 
not implement full garbage collection, we do implement reference counting for some 
objects (specifically, those used in the Parser and therefore likely to be lost). 
Thus, our memory leaks, while not eliminated, have been substantially reduced. Our 
interpreter does load files specified by command line arguments.

Specific Notes
--------------
append  - The append function does not conform to racket specifications. In particular,
	  it will turn all non-list arguments passed to it into lists. So, while
	  (append (1) 2 (3) 4) would crash in racket, in our interpretation it will
	  return the list (1 2 3 4).

modulo  - Although not specified in the assignment, modulo is implemented. It also does
	  not conform to racket specifications exactly. In particular, in racket, 
	  passing in (modulo 2.0 3.0) will return 2.0, whereas our implementation will
	  crash if given non-integer arguments (even if they are integral).

range   - The published range test works for our program, but it fails when provided
	  with too large an argument because of stack overflow. Our testing indicates
	  that this happens somewhere between 13000 and 14000, and that DrRacket also
	  requires more memory to evaluate the same code.

tests   - Our test files are in the Scheme directory, labelled test.input.xx


Build Instructions
==================
    1.  Install CMake 2.8.x (http://www.cmake.org/)

    2.  cd to this directory

    3.  To produce a makefile and executables, run:
            mkdir build
            cd build
            cmake ..
            make

    4.  To run the interpreted, run:
	    ./interpreter

    5.  To run the automated test suite, run:
            ./test


Testing Insructions
===================
To run both the parser and tokenizer against all tests at once, use the
RunTests.sh script in the Other folder.  You will need CMake installed.



Coding Standards
================

    File Layout
    ===========
        - 2 blank lines after preprocessor directive at top of file.
        - 2 blank lines before #endif at end of header files.
        - Header files contain all struct definitions, then all function definitions.
        - 2 blank lines after struct declarations.
        - 1 blank line after function declarations.
        - 2 blank lines after function definitions.

    Commenting
    ==========
        Rules:
            - Comments should wrap at 80 characters.
            - But try to keep them on a single line if possible.
            - Doxygen style comments for structs and function declarations.
            - No comment necessary for function definitions.
            - Try to paraphrase the struct or function name rather than repeating it.

        Examples:
            +------------------------------------------------------------------+
            |  /// Perform a surprise operation on a location in memory        |
            |  void doSomething (void* object);                                |
            +------------------------------------------------------------------+

            +------------------------------------------------------------------+
            |  /// Some very mysterious information                            |
            |  struct                                                          |
            |  {                                                               |
            |      void* something;                                            |
            |  }                                                               |
            |  typedef Data;                                                   |
            +------------------------------------------------------------------+