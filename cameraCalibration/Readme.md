# README

This Program makes a camera calibration.

To compile, run the following commands:

mkdir build
cd build
cmake ..
make

You should have CMake 3.2 minimum version and a C++11 compatible compiler.

You can run the program in 2 different ways:

1. If you have already captured the images, you should put them all inside the **images/** directory. Then, run "./calib" with **no** arguments.


2. If you want to capture the images now, you should run "./calib NUMBER_OF_FRAMES", for example: ./calib 15 . Then you will be prompted for an amount of seconds to wait between each shot. The images will be saved to "images/boardSEQUENTIALNUMBER.jpg".

In both cases, you should write at least the board width and height, the square size and the images source path to **"configuration.json"**. An example file is provided.

Should you have any doubt, contact: hallpaz@impa.br
