# Style Guide for SplineLib
SplineLib sticks to the [*Google C++ Style Guide*](https://google.github.io/styleguide/cppguide.html) in general;
hence, this document — i.e., the SplineLib style guide — only describes the few modifications made to it.

To check whether code is compliant with Google's C++ style guide, [*cpplint*](https://github.com/cpplint/cpplint) can
be used. cpplint can be configured to account for below modifications using the `CPPLINT.cfg` file.

## Naming
### [File Names](https://google.github.io/styleguide/cppguide.html#File_Names)
Google requires header files names and source file names to end in `.h` and `.cc`, respectively.  To signal the use of
the C++ programming language, the extensions `.hpp` and `.cpp` are used.

## Formatting
### [Line Length](https://google.github.io/styleguide/cppguide.html#Line_Length)
Google restricts the lengths of lines to a maximum of 80 characters.  This limit is reached frequently when using
descriptive names.  Also, this is a very narrow restriction for modern displays.  Therefore, the restriction on line
lengths is relaxed to a maximum of 120 characters.
