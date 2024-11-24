#!/bin/bash

make clean 
rm -r lib

# Ask the user to input a number
read -p "Enter a number (0 for x86_64, 1 for arm): " number

# Define paths for x86_64 and arm
x86_64_path="../CP2112/lib/x86_64"
arm_path="../CP2112/lib/arm7"

# Choose the path based on the user input
if [ $number -eq 0 ]; then
    chosen_path=$x86_64_path
elif [ $number -eq 1 ]; then
    chosen_path=$arm_path
else
    echo "Invalid input. Please enter 0 or 1."
    exit 1
fi

# Copy the file from the chosen path to ./lib
cp -r $chosen_path ./lib/

# make these .so file be installed in the system
sudo cp -r $chosen_path/* /usr/lib

echo "File copied successfully to ./lib"

make