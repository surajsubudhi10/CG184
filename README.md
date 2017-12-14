# CG184 code repository
A Render Engine in process based on OpenGL.
CG184 is currently at the beginning stages of development, so expect an incomplete experience if you try to dive in.
The CMakeLists.txt is not yet tested/finished for OS X and Windows.

## Windows building
All relevant libraries and dll are found in /external-dependencies folder and (pre-)compiled for Windows. 
The .sln file have all the settings updated so to run the project you need Visual Studio 2015 or up.

Keep in mind the supplied libraries were generated with a specific compiler version which may or may not work on your system (generating la large batch of link errors). In that case it's advised to build the libraries yourself from the source.

## Linux building
First make sure you have CMake, Git, and GCC by typing as root (sudo) `apt-get install g++ cmake git` and then get the required packages:
Using root (sudo) and type `apt-get install  libglm-dev libglew-dev libglfw3-dev` . Next, create a build directory and change directory to the new build dir. There we run the `cmake ..`, it will generate necessary files and check for all the dependancies and create a make file. Then just type `make` in the terminal. This will generate the executables in the build folder.

Note that CodeBlocks or other IDEs may have issues running the programs due to problems finding the shader and resource files, however it should still be able to generate the exectuables. To work around this problem it is possible to set an environment variable to tell the IDE where the resource files can be found. 

To sum it up:
```
git clone --recursive https://github.com/surajsubudhi10/CG184.git
mkdir build
cd build
cmake ../.
make .
```

