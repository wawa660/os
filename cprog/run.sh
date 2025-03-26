#!/bin/bash

# Check if the filename is provided
if [ $# -ne 1 ]; then
	  echo "Usage: $0 <source_file.c>"
	    exit 1
fi

# Extract the source file and binary file names
SOURCE_FILE="$1"
BINARY_FILE="${SOURCE_FILE%.*}"  # Remove the file extension to get the binary file name

# Check if the source file exists
if [ ! -f "$SOURCE_FILE" ]; then
	  echo "Source file $SOURCE_FILE does not exist."
	    exit 1
fi

# Step 1: Compile the C program
echo "Compiling $SOURCE_FILE..."
gcc -o "$BINARY_FILE" "$SOURCE_FILE"

# Check if compilation was successful
if [ $? -ne 0 ]; then
	  echo "Compilation failed."
	    exit 1
fi

# Step 2: Run the binary
echo "Running $BINARY_FILE..."
./"$BINARY_FILE"

# Step 3: Delete the binary
echo "Deleting binary $BINARY_FILE..."
rm "$BINARY_FILE"

# Step 4: Git add, commit, and push
echo "Git adding, committing, and pushing changes..."
git add .
git commit -m "added $SOURCE_FILE"
git push

# Success message
echo "Done!"

