workspace "ConsoleTetris"

   configurations { "Debug", "Release" }
   platforms { "Win64" }
   location "ConsoleTetris"

   project "ConsoleTetris"
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


