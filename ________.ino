#include <IRremote.h>  //적외선 리모컨 라이브러리
#include <Servo.h>     //서보모터 라이브러리

int remote=A0;         //적외선 리모컨 신호선
int motor=6;           //서보모터
 
Servo servo;           //servo 라이브러리를 사용해주기 위해 servo객체 생성
IRrecv irrecv(remote); //IRremote를 사용해주기 위해 irrecv객체 생성
decode_results results;//디코드한 결과값

int angle=0; //서보모터 각도 값

void setup() {
  // put your setup code here, to run once:

irrecv.enableIRIn();
pinMode(motor,OUTPUT); // 모터 출력
pinMode(remote,INPUT); // 입력       
}
void loop(){
  // put your main code here, to run repeatedly:
if(irrecv.decode(&results)){  //적외선 리모컨의 신호를 받을 때
  switch(results.value){
    case 0xFFA857:  // +버튼을 눌렀을 때
    servo.attach(motor); // 모터 시작
    angle+=60;      // 각도값 60 추가
    if(angle>180)   // 각도가 180이 넘어갈 때
    angle=180;      // 각도값 최대를 180으로
    servo.write(angle); // 서보모터 각도 이동
    delay(500);
    servo.detach();
    break;
    
    case 0xFFE01F:  // -버튼을 눌렀을 때
    servo.attach(motor); // 모터 시작
    angle-=60;      // 60도 감소
    if(angle<0)     // 각도값이 0보다 작을 때
    angle=0;        // 각도값 최소값을 0으로
    servo.write(angle); //서보모터 각도 이동
    delay(500);
    servo.detach();
    break;
  }
    irrecv.resume(); // 다음 값 받기
}
  }
