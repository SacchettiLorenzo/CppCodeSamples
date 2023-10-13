The file structure:
C:.
│   Conway Game Of Life.sln
│
├───Conway Game Of Life
│   │   Conway Game Of Life.aps
│   │   Conway Game Of Life.cpp //main
│   │   Conway Game Of Life.vcxproj
│   │   Conway Game Of Life.vcxproj.filters
│   │   Conway Game Of Life.vcxproj.user
│   │   GridSpawner.cpp
│   │   GridSpawner.h //grid of square
│   │   Simulation.cpp
│   │   Simulation.h // simulation manager
│   │   Square.cpp
│   │   Square.h //single sqare in the grid
│   │
│   └───x64
│
└───x64
    └───Debug
            //actual exe
            Conway Game Of Life.exe 
            Conway Game Of Life.pdb
            //dll for sfml (release or debug version)
            openal32.dll 
            sfml-audio-2.dll
            sfml-audio-d-2.dll
            sfml-graphics-2.dll
            sfml-graphics-d-2.dll
            sfml-network-2.dll
            sfml-network-d-2.dll
            sfml-system-2.dll
            sfml-system-d-2.dll
            sfml-window-2.dll
            sfml-window-d-2.dll

In the program there is a difference between grid positiona and position inside the windown