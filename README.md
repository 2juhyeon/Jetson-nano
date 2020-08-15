# Linux
    linux easy user guide
      -windows환경에서의 JIT시스템을 이용할 수 있는 환경 구축

windows 환경 구축 (visual studio 이용(visual studio community 2017 기준))
  windows환경이 편리한 이유는 visual studio와 같은 좋은 ide가 있기 때문이다.
  리눅스 환경에서는 에디터 용도로 사용하지만 JIT(just in time)기능이 있기 때문에 디버깅이 편리해진다. 
    just in time 컴파일 (https://ko.wikipedia.org/wiki/JIT_%EC%BB%B4%ED%8C%8C%EC%9D%BC)
  
  1. 설치
    - visual studio installer에서 c++를 사용한 linux개발을 클릭해서 다운로드
  
  2. 프로젝트 설정
   - visual studio에서 파일 -> 새로만들기 -> 프로젝트 -> 플랫폼간 -> linux 로 프로젝트 제작
   - 리눅스에서 필요로 하는 헤더파일 인식 및 내부 함수 매개변수 확인 등 실시간(JIT)으로 디버깅 가능
  
  3. 삼바 공유폴더에 옮겨 넣고 Makefile을 작성
    ssh(putty etc..)를 이용하여 리눅스 쉘에서 컴파일 실행

목차(Contents)

1. 타이머(Timer)
