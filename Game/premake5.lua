workspace "Oblivion Engine"
configurations { "Debug", "Release" }
location "build"

project "sfml_project"
architecture "x64"
kind "ConsoleApp"
language "C++"
targetdir "bin/%{cfg.buildcfg}"
cppdialect "C++20"
files { "src/**.*", "lib/imgui/**.cpp" }

postbuildcommands
{
    "{COPY} ../lib/SFML-2.5.1/bin ../bin/Debug",
    "{COPY} ../vendor/Config/imgui.ini ."
}

filter "configurations:*"
flags("MultiProcessorCompile")
defines { "SFML_DYNAMIC" }
includedirs { "lib/**", "resources", "src" }
libdirs { "lib/**" }
links
{
    "opengl32",
    "box2d"
}

staticruntime "off"
runtime "Debug"

filter "configurations:Debug"
defines { "DEBUG" }
symbols "On"
links
{
    "sfml-graphics-d",
    "sfml-window-d",
    "sfml-system-d",
    "sfml-audio-d",
    "sfml-network-d"
}

filter "configurations:Release"
defines { "NDEBUG" }
optimize "On"
links
{
    "sfml-graphics-d",
    "sfml-window-d",
    "sfml-system-d",
    "sfml-audio-d",
    "sfml-network-d"
}

staticruntime "off"
runtime "Debug"

postbuildcommands
{
    "{COPY} ../lib/SFML-2.5.1/bin ../bin/Release",
    "{COPY} ../vendor/Config/imgui.ini imgui.ini"
}
