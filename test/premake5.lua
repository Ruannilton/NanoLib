workspace "NanoLib"
    configurations {"Debug","Release","Test"}
    location "build"
    includedirs { "../src" }
    
project "data_structure"
    kind "ConsoleApp"
    language "C"
    location "build"
    files { "./code/*.h","./code/*.c"}
    
    