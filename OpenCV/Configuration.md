The configuration is relative to the opencv directory inside library directory
1.  C/C++ - General - Additional Include Directories: $(SolutionDir)..\..\libraries\opencv\build\include; $(SolutionDir)..\..\libraries\opencv\source\include
2.  Linker - General - Additional Library Directory: $(SolutionDir)..\..\libraries\opencv\build\x64\vc16\lib;$(SolutionDir)..\..\libraries\opencv\build\x64\vc16\bin;
3.  Linker - Input - Additional Dependencies: opencv_world490d.lib (for debug), opencv_world412.lib (for release)

Copy  opencv_world490d.dll (or later releases) in the debug directory (the same directory of the .exe file)

the name or numbers in the directory names can change for one version to another of the open cv library