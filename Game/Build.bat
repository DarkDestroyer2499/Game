SET mypath=%~dp0
echo %mypath:~0,-1%
mkdir lib\yaml\build
cd lib\yaml\build
cmake ..
msbuild YAML_CPP.sln
cd %mypath%
vendor\bin\premake\premake5.exe vs2022
PAUSE