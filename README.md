# Raytracer

Following Peter Shirley's Raytracing series to slowly iterate on and upgrade a custom raytracer

## Installation

For Windows x86, first clone the source code. Run `make precompile` first, and then run `make` (be sure to use bash).

## Use

`scene.cpp` contains a funtion `createScene()` that represents the objects to be rendered. To render, run `./program.exe > image.ppm` in bash, input your desired settings in the GUI, and click 'Render.' Once the console says the image has been fully rendered, you can view it using a PPM viewer online.

There are also several example renders in PNG format in the `images` folder.
