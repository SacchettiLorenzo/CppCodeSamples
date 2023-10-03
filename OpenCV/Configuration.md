The configuration is relative to the opencv directory inside library directory
1.  C/C++ - General - Additional Include Directories: $(SolutionDir)..\..\libraries\opencv\build\include; $(SolutionDir)..\..\libraries\opencv\source\include
2.  Linker - General - Additional Library Directory: $(SolutionDir)..\..\libraries\opencv\build\x64\vc15\lib;$(SolutionDir)..\..\libraries\opencv\build\x64\vc15\bin;
3.  Linker - Input - Additional Dependencies: opencv_world412d.lib (for debug), opencv_world412.lib (for release)

Copy  opencv_world412d.dll in the debug directory (the same directory of the .exe file)