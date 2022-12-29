-- ConsoleTetris 작업 영역입니다.
workspace "ConsoleTetris"

   -- 빌드 구성 요소입니다.
   configurations { 
      "Debug",
      "Release",
      "Shipping",
   }

   -- 빌드 플랫폼입니다.
   platforms { "Win64" }

   -- 솔루션 경로를 설정합니다.
   location "%{wks.name}"

   -- 소스 코드 경로를 설정합니다.
   source="%{wks.location}/../Source"

   -- 외부 라이브러리 경로를 설정합니다.
   thirdparty="%{wks.location}/../ThirdParty"

   -- ConsoleTetris 프로젝트입니다.
   project "ConsoleTetris"

      -- ConsoleTetris 프로젝트의 종류를 설정합니다.
      kind "ConsoleApp"

      -- 프로그래밍 언어를 설정합니다.
      language "C++"
      
      -- C++의 표준을 설정합니다.
      cppdialect "C++17"

      -- 명령행 인수를 설정합니다.
      debugargs {
         "-Dump=%{wks.location}..\\Dump\\",
         "-Content=%{wks.location}..\\Content\\",
      }

      -- 소스 코드의 include 경로를 추가합니다.
      includedirs {
         "%{source}",
         "%{source}/Public",
         "%{source}/Private",

         "%{thirdparty}",
      }

      -- 소스 코드의 file을 추가합니다.
      files {
         "%{source}/*",
         "%{source}/Public/*",
         "%{source}/Private/*",

         "%{thirdparty}/Json/*",
         "%{thirdparty}/miniaudio/*",
      }

      -- 빌드의 구성 요소별 설정을 수행합니다.
      filter "configurations:Debug"
         defines { "DEBUG" }
         runtime  "Debug"
         optimize "Off"
         symbols "On"

         links {
            "Dbghelp.lib",
         }

      filter "configurations:Release"
         defines { "NDEBUG" }
         runtime "Release"
         optimize "On"
         symbols "On"

         links {
            "Dbghelp.lib",
         }

      filter "configurations:Shipping"
         defines { "NDEBUG" }
         runtime "Release"
         optimize "Full"
         symbols "Off"

         links {
            "Dbghelp.lib",
         }
