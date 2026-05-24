@echo off
for /f "delims=" %%i in ('"%ProgramFiles(x86)%\Microsoft Visual Studio\Installer\vswhere.exe" -latest -prerelease -products * -requires Microsoft.Component.MSBuild -find MSBuild\**\Bin\MSBuild.exe') do set msbuild=%%i
"%msbuild%" "build\Oblivion Engine.sln" /p:Configuration=Debug /p:Platform=x64 /m /verbosity:minimal
