#!/bin/bash

# Change to the script directory
dir=`dirname ${0}`
current=$(pwd)
cd "${dir}/.."

# Build everything
mkdir -p build
cd build
cmake ..
make
cd ..

# Test tokenizer and parser
for FILE in Scheme/test.input.*
do
    cat $FILE | build/tokenize    > Scheme/test.tokens.${FILE##*.}
    cat $FILE | build/parse       > Scheme/test.parsed.${FILE##*.}
    cat $FILE | build/interpreter > Scheme/test.output.${FILE##*.}
done

# Change back to original directory
cd "${current}"