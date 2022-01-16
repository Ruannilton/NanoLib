workspace "NanoLib"
    configurations {"Debug"}
    location "build"
    includedirs { "../../src" }
    
project "data_structure"
    kind "ConsoleApp"
    language "C"
    location "build"
    symbols "On"
    files { "./code/*.h","./code/*.c"}
    
    