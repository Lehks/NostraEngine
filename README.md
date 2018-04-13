# NostraEngine
A 3D game engine.

It is a project made by students of the htw saar (https://www.htwsaar.de/) and supervised by Dipl-Inf (FH) 
Christopher Olbertz.

GitHub: https://github.com/Lehks/NostraEngine

If you do not have the code yet, use the following command to clone the repository to your local
machine:  
```bash
git clone https://github.com/Lehks/NostraEngine.git
```` 
or download the ZIP-compressed directly from GitHub using the link above.

## Dependencies

This Engine relies on a bunch of 3rd Party libraries. Here is a full list of all of them:

- **GLFW** (http://www.glfw.org/): Source Code has not been altered, but only the files that are required for 
  building the library (this excludes e.g. the examples) have been imported. The CMakeLists.txt files have
  been altered.
- **GLAD** (http://glad.dav1d.de/): None of the files have been altered.
- **SQLite3** (https://www.sqlite.org/index.html): Both the sqlite3.c and sqlite3.h files were altered to 
  allow for the generation of shared libraries.
