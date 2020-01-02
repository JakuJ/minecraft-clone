# Minecraft clone

An attempt to recreate a subset of the popular game Minecraft, learning OpenGL along the way.

## What works

* Creating and removing grass blocks
* Chunks (naive, really just 3D arrays of pointers to Blocks)
* A quad tree for storing and lazy creation of chunks
* A free-floating camera

A screenshot showing a simple scene made of grass blocks:

![A screenshot of the current state](images/screenshot.png)