SET mypath=%~dp0
echo %mypath:~0,-1%
mkdir lib\yaml\build
cd lib\yaml\build
cmake ..
for /f "delims=" %%i in ('"%ProgramFiles(x86)%\Microsoft Visual Studio\Installer\vswhere.exe" -latest -prerelease -products * -requires Microsoft.Component.MSBuild -find MSBuild\**\Bin\MSBuild.exe') do set msbuild=%%i
"%msbuild%" YAML_CPP.sln
cd %mypath%
vendor\bin\premake\premake5.exe vs2022
PAUSE