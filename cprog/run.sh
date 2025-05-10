#!/bin/bash

# Step 1: Get the current directory and its parent directory
current_dir=$(basename "$PWD")
parent_dir=$(dirname "$PWD")  # Parent of the current directory

# Step 2: List files in the current directory
echo "Files in $PWD:"
files=(*)
for i in "${!files[@]}"; do
  echo "$i) ${files[i]}"
done

# Step 3: Ask the user to select a file to keep
read -p "Select a file to keep by number: " choice
chosen_file="${files[$choice]}"

# Step 4: Move the chosen file to the parent directory
mv "$PWD/$chosen_file" "$parent_dir/$chosen_file"
echo "$chosen_file has been moved to $parent_dir"

# Step 5: Delete all other files in the current directory (the child directory)
for file in "${files[@]}"; do
  if [[ "$file" != "$chosen_file" ]]; then
    rm -f "$file"
    echo "Deleted $file from $PWD"
  fi
done
