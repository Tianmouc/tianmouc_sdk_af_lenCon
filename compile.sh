
#!/bin/bash
# Ask the user to input a number
rm -r tmp_lib 

mkdir build
mkdir tmp_lib

read -p "Enter a number (0 for x86_64, 1 for arm): " number
# Define paths for x86_64 and arm
x86_64_path="./lens_sdk/lib/x86_64"
arm_path="./lens_sdk/lib/arm7"

# Choose the path based on the user input
if [ $number -eq 0 ]; then
    chosen_path=$x86_64_path
elif [ $number -eq 1 ]; then
    chosen_path=$arm_path
else
    echo "if you use different OS, please compile the dynamic lib under lens_sdk/src_pkg."
    exit 1
fi

# Copy the file from the chosen path to ./lib
cp -r $chosen_path ./tmp_lib/
# make these .so file be installed in the system
sudo cp -r $chosen_path/* /usr/lib
echo "File copied successfully to ./tmp_lib"

# cd into build folder to build the project
cd build
cp ./lib/*.so ./

DEFAULTPATH="/home/lyh/codes/tianmouc_sdk"
echo "please input the Tianmouc_sdk path, the default is: $DEFAULTPATH (enter for defualt)"
read SDK_PATH
if [ -z "$SDK_PATH" ]; then
  echo "Using default name: $DEFAULTPATH"
  SDK_PATH="$DEFAULTPATH"
else
  echo "Using input name: $SDK_PATH"
fi

cmake -DSDK_PATH=$SDK_PATH ..
make

cd ..
rm -r tmp_lib 
