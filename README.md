# CG184 code repository
A Mesh editor in process based on OpenGL.
CG184 is currently at the beginning stages of development, so expect an incomplete experience if you try to dive in.
The CMakeLists.txt is not yet tested/finished for OS X.

## Linux building
First make sure you have CMake, Git, and GCC by typing as root (sudo) `apt-get install g++ cmake git` and then get the required packages:
Using root (sudo) and type `apt-get install  libglm-dev libglew-dev libglfw3-dev` . Next, create a build directory and change directory to the new build dir. There we run the `cmake ..`, it will generate necessary files and check for all the dependancies and create a make file. Then just type `make` in the terminal. This will generate the executables in the build folder.

Note that CodeBlocks or other IDEs may have issues running the programs due to problems finding the shader and resource files, however it should still be able to generate the exectuables. To work around this problem it is possible to set an environment variable to tell the IDE where the resource files can be found. 

To sum it up:
```
git clone  https://github.com/surajsubudhi10/CG184.git
mkdir build
cd build
cmake ../.
make .
```

## Windows building (Visual Studio compiler)
All relevant libraries and dll are found in /deps folder and (pre-)compiled for Windows. 
After `cmake ..` command it generates the .sln files and after opening it one can build and run the application. it the programme complains for missing `dll` files for glew and assimp, just copy the dll files from each section to the binary(.exe) folder.

