#!/bin/bash
# This is basically a bash script to build a c file with the correct options. I got it from chatgpt.

inputFile="$1"

outputFile="${inputFile%.*}.out"
compilerOptions="-lm -Wall -Wextra -pedantic -std=c99 -O0 -Wshadow -Wformat=2 -Wfloat-equal -Wconversion -Wlogical-op -Wcast-qual -Wcast-align -D_GLIBCXX_DEBUG -D_GLIBCXX_DEBUG_PEDANTIC -D_FORTIFY_SOURCE=2 -fsanitize=undefined -fno-sanitize-recover -fstack-protector -ggdb3"
extraOptions="-Wshift-overflow=2 -Wduplicated-cond -fsanitize=address" # For some reason ssn gcc doesn't support these.

compiler="gcc"

# Build the compiler command
compilerCommand="$compiler -o $outputFile $inputFile $compilerOptions"

# Execute the compiler command
echo "Compiling $inputFile..."
eval "$compilerCommand"

# Check if the compilation was successful
# bad practice apparently?
if [ $? -eq 0 ]; then
    echo "Compilation successful. Output file: $outputFile"
    echo "Debugging $outputFile..."
    if [ "$2" = "-r" ]; then
        echo ""
        eval "gdb $outputFile"
    fi
else
    echo "Compilation failed with error code: $?"
fi