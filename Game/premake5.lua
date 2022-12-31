workspace "sfml_project"
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
    "{COPY} ../lib/SFML-2.5.1/bin ../bin/Debug"
}

filter "configurations:*"
defines { "SFML_DYNAMIC" }
includedirs { "lib/SFML-2.5.1/include", "lib/box2d-main/include/box2d", "lib/imgui" }
libdirs { "lib/SFML-2.5.1/lib", "lib/box2d-main/lib" }
links
{
    "opengl32",
    "box2d"
}

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
    "sfml-graphics-s",
    "sfml-window-s",
    "sfml-system-s",
    "sfml-audio-s",
    "sfml-network-s"
}
