# C of Life 
## What is it?

C of life is an implementation of John Conway's game of life written in C language. I decided to do it mainly for two reasons:
- It is the first time I implement a game of life, so I wanted to understand how it works
- I was curios about raylib and I wanted to give it a try

## how to install

clone this repo, then enter into the directory of the project. To install the software you will need to use these commands:
```
  make install
  make build
```
the first command will download raylib-5.0 library and compile it, then it will move the .so file into /var/lib/ directory

## how to use it

run the executable file, it will appear an 800x800 size window, then click with the mouse some points in order to choose which cells
will be alive for the initial configuration. Once you've done it press enter to start the simulation
