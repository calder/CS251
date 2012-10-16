Build Instructions
==================
    1.  Install CMake

    2.  cd to this directory

    3.  To produce a makefile and executables, run:
            mkdir build
            cd build
            cmake ..
            make

    4.  For command line development, the following is handy so long as you
        remember to re-CMake every time you add a new file:
            make && ./test

    5.  To produce an Xcode project file, run:
            mkdir build
            cd build
            cmake .. -G Xcode


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