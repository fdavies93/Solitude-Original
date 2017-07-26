# Solitude Engine

This is the original version of the Solitude (or Sol) engine, a C++ / Allegro game engine project I worked on in 2014 for several months. It was originally written using Code::Blocks and compiled with MinGW, but has been ported to Visual Studio 2015 for compatibility with Allegro binaries.

## Features
- Loads 2D animations and bitmaps from CSV files.
- Streams graphics loading through multithreading, loading and unloading spritesheets based on need.
- Multiple graphics layers with parallax effects.
- Movable camera
- Separation of logic and graphics systems

## Status

Inactive due to stability & architecture issues.

Has been superceded by Solitude 2 project, a reboot which uses C++11 and SFML, and is much more robust.

https://github.com/fdavies93/Solitude-2.0

## Requirements

To compile Solitude you will need:
- Visual Studio 2015 toolchain
- Allegro library for MSVC 2015 (https://github.com/liballeg/allegro5/releases)

## Thanks

Graphics from PixelBoy at Sparklin Labs:
https://github.com/sparklinlabs/superpowers-asset-packs
