# ParkingLotManagement

## 실행 방법

#### 깃 클론
<pre>
<code>
$ git clone https://github.com/sjoonb/ParkingLotManagement.git
</code>
</pre>

#### make
<pre>
<code>
$ make
</code>
</pre>

#### 실행
<pre>
<code>
$ ./ParkingLotManagement
</code>
</pre>

## 기능 설명
### 첫 화면
<img width="551" alt="스크린샷 2020-12-13 오후 9 42 12" src="https://user-images.githubusercontent.com/70687318/102012180-3fcc4700-3d8c-11eb-913e-4535d0444c03.png">

해당 주차장의 최대 수용 가능한 차량 수를 정수로 입력

### 6가지 기능
<img width="515" alt="스크린샷 2020-12-13 오후 9 45 10" src="https://user-images.githubusercontent.com/70687318/102012223-7ace7a80-3d8c-11eb-83ef-79299570c2a1.png">

[1] : 입차 - 차량 번호 직접 입력 (00가0000 식으로 입력), 차량 사이즈 입력 (소형 / 중형 / 대형)     
[2] : 출차 - 차량 번호 직접 입력 (00가0000 식으로 입력), 요금표에 따라 요금 책정하여 금일 수입에 추가    
   
[3] : 현황 - 주차장크기, 주차 차량 수, 남은 공간 출력, 현재 주차된 모든 차량 출력    
[4] : 과거 내역 - 과거 내역 창으로 이동, 출력, 이전 날짜, 다음 날짜, 메인으로 선택 가능    
[5] : 자동 모드 - 입/출 이 자동으로 실행되는 모드, 실행 중 엔터키 입력시 종료, 자세한 설명은 아래 상세 설명으로    
[6] : 저장 및 종료 - 모든 데이터 저장 후 종료    
[7] : 초기화 - 모든 데이터 초기화 후 프로그램 재실행   

## 상세 설명
### 요금 수정
### 요금 수정
![rate](https://user-images.githubusercontent.com/70687318/102012326-15c75480-3d8d-11eb-9180-0b61d4a8235d.png)    
rate.txt 파일을
수정하여

### 자동 모드



