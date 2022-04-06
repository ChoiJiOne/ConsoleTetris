# tetris1.0
- C++ 기반의 Console 테트리스 게임 구현 프로젝트
<br><br>



## goal
- 콘솔 환경에서 플레이할 수 있는 간단한 테트리스 게임 제작
<br><br>



## platform
- windows 10 pro / home
<br><br>



## key
- Up : 회전
- Down : 아래로 이동
- Left : 왼쪽으로 이동
- Right : 오른쪽으로 이동
- Space : 가장 아래로 이동
<br><br>



## build
게임 프로젝트 빌드를 위한 단계로는 아래와 같다.  

### 1. 사전 준비

다음 요소를 설치  
  
- [git](https://git-scm.com/)
- [cmake](https://cmake.org/)
- [Visual Studio](https://visualstudio.microsoft.com/ko/)

### 2. Visual Studio 솔루션 생성

`CMD` 혹은 `Windows Tetminal` 에서 아래와 같이 수행  
  
```
// 소스 얻기
> git clone https://github.com/ChoiJiOne/tetris1.0

// Visual Studio 솔루션을 생성할 폴더
> mkdir <folder-name>
> cd <folder-name>

// cmake 실행
> cmake ..
-- Building for: Visual Studio 16 2019
-- Selecting Windows SDK version 10.0.19041.0 to target Windows 10.0.19043.
-- The C compiler identification is MSVC 19.29.30141.0
-- The CXX compiler identification is MSVC 19.29.30141.0
-- Detecting C compiler ABI info
-- Detecting C compiler ABI info - done
-- Check for working C compiler: C:/Program Files (x86)/Microsoft Visual Studio/2019/Community/VC/Tools/MSVC/14.29.30133/bin/Hostx64/x64/cl.exe - skipped
-- Detecting C compile features
-- Detecting C compile features - done
-- Detecting CXX compiler ABI info
-- Detecting CXX compiler ABI info - done
-- Check for working CXX compiler: C:/Program Files (x86)/Microsoft Visual Studio/2019/Community/VC/Tools/MSVC/14.29.30133/bin/Hostx64/x64/cl.exe - skipped
-- Detecting CXX compile features
-- Detecting CXX compile features - done
-- Configuring done
-- Generating done
-- Build files have been written to: <project-directory>
> 
```

### 3. 프로젝트 빌드
`tetris1.0.sln` 실행 후 `tetris1.0` 프로젝트를 빌드  
<br><br>



## play
<img src="play.gif" width="960" height="540">
<br><br>



## note
- **참고** : 실행 시 콘솔 창을 임의로 종료할 경우 memory leak issue 발생 확인
- 테트리스 보드의 단순한 색상 구성 변경 필요
  - 내부에 다양한 색상을 가지도록 변경 필요
<br><br>
