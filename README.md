# Console Tetris *v0.0*
- Console 테트리스 게임의 *v0.0* 버전입니다.
<br><br>


## Release

[여기](https://github.com/ChoiJiOne/ConsoleTetris/releases/tag/v0.0) 에서 Console 테트리스 게임 *v0.0* 버전을 다운받을 수 있습니다.  
<br><br>


## 사전 준비

이 프로젝트를 빌드 및 유지 개발을 진행하기 위해서는 다음 요소가 필요합니다.
- [Visual Studio 2019 혹은 그 이상](https://visualstudio.microsoft.com/ko/)
- [git](https://git-scm.com/)
<br><br>


## 소스 코드 얻기

`CMD` 에서 다음과 같이 수행하시면 *v0.0* 버전의 소스 코드를 얻을 수 있습니다.
```
> git clone https://github.com/ChoiJiOne/ConsoleTetris --single-branch -b v0.0
```
<br><br>


## Visual Studio Solution 생성

`CMD` 에서 다음과 같이 수행하시면 `Visual Studio` Solution를 생성할 수 있습니다.
```
> GenerateProjectFiles.bat
```
<br><br>


## 빌드

이 프로젝트는 `Visual Studio` 에서의 빌드 이외의 빌드 기능을 제공합니다.  
`CMD` 에서 다음과 같이 수행하시면 프로젝트를 빌드할 수 있습니다.  

### `Debug` 빌드
```
> Build.bat Debug
```

### `Release` 빌드
```
> Build.bat Release
```

### `Shipping` 빌드
```
> Build.bat Shipping
```
<br><br>


## 플레이

`ConsoleTetris.exe` 를 클릭해서 게임을 실행하면, 시작 화면에서 메뉴를 선택할 수 있습니다.  
메뉴의 경우, `UP` 와 `DOWN`키로 제어할 수 있고, 선택은 `ENTER` 키로 할 수 있습니다.  
`게임 시작` 을 선택하면, LEVEL을 1에서 6까지 선택할 수 있습니다. 이때, 1에서 6은 테트로미노의 떨어지는 속도의 빠르기를 의미합니다. 큰 수에 가까울수록 테트로미노의 떨어지는 속도는 빨라집니다.  
게임 플레이를 하게 되면 `LEFT`, `RIGHT`, `UP`, `DOWN` 으로 테트로미노를 움직일 수 있고, `SPACE` 키를 입력하면 테트로미노가 가장 아래로 이동합니다.  
게임을 중지하고 싶다면 `ESC` 키를 입력하면 됩니다.
