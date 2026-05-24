SET mypath=%~dp0
echo %mypath:~0,-1%
mkdir lib\yaml\build
cd lib\yaml\build
cmake -T v143 -DCMAKE_POLICY_VERSION_MINIMUM=3.5 ..
cmake --build .
cd %mypath%
vendor\bin\premake\premake5.exe vs2022
PAUSE