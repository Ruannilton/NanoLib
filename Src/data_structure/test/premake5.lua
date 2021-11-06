workspace "NanoLib"
    configurations {"Debug","Release","Test"}
    system "Windows"
    architecture "x86"
    location "build"
  

filter "configurations:Debug"
    defines { "DEBUG" }
    flags { "Symbols" }

filter "configurations:Test"
    defines { "DEBUG" }
    flags { "Symbols" }


filter "configurations:Release"
    defines { "RELEASE" }
    optimize "On"

project "data_structure"
    kind "StaticLib"
    language "C"
    location "build"
    files { "*.h","*.c"}
    

    filter "configurations:Test"
        includedirs {"../../../DevDeps/"}
        files {"*.c","../../../DevDeps/munit/*.c","../../../DevDeps/munit/*.h"}
        kind "ConsoleApp"
