An easily buildable minimal cairo/SDL example 

I ran this on a Raspberry Pi but it would probably work on any Linux desktop

How to build it:

sudo apt install libsdl2 libsdl2-dev libcairo2dev

sudo apt install cmake ninja-build

Or whatever you like for building
```
mkdir build

cd build

cmake ../ -G Ninja

ninja

```
