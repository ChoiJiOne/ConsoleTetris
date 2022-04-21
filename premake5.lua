workspace "tetris1.0"

   configurations { "Debug", "Release" }
   platforms { "Win64" }
   location "tetris1.0"

   project "tetris1.0"
      kind "ConsoleApp"
      language "C++"
      
      files { 
         "%{wks.location}/../Source/*.cpp",
         "%{wks.location}/../Source/*.h"
      }

      filter "configurations:Debug"
         defines { "DEBUG" }
         symbols "On"

      filter "configurations:Release"
         defines { "NDEBUG" }
         optimize "On"


