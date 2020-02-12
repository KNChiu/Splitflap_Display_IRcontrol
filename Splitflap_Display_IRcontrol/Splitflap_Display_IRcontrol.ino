/* 
 2020/02/12 紅外線遙控機械式翻頁顯示器
 
 bits : 32
 decode_type : 3
 0:0xFF6897
 1:0xFF30CF
 2:0xFF18E7
 3:0xFF7A85
 4:0xFF10EF
 */


#include <StepperMotor.h>
#include <IRremote.h>

unsigned long num[] = {0xFF6897, 0xFF30CF, 0xFF18E7, 0xFF7A85, 0xFF10EF};
unsigned long none = 0xFFFFFFFF;
int IR_delay = 0;

StepperMotor motor(3, 4, 5, 6);
int motorSpeed = 1; //步進馬達速度
int RECV_PIN = 2; // 使用數位腳位2接收紅外線訊號
IRrecv irrecv(RECV_PIN); // 初始化紅外線訊號輸入
decode_results results; // 儲存訊號的結構

void setup() {
  Serial.begin(115200);
  motor.setStepDuration(motorSpeed);
  irrecv.blink13(true); // 設為true的話，當收到訊號時，腳位13的LED便會閃爍
  irrecv.enableIRIn(); // 啟動接收
}

void loop() {
  if (irrecv.decode(&results)) { // 接收紅外線訊號並解碼
    Serial.println(results.value, HEX);

    sign_change(results.value);
    
    
    irrecv.resume(); // 準備接收下一個訊號
  }
  
}

void sign_change(unsigned long IR_results){
    if (IR_results == num[0]){          //初始化
      IR_delay = 1;                     //判斷是否有按下過0
      
    }else if (IR_results == num[1]){
      IR_delay = 0;
      motor.step(512);
      delay(1000);
    }else if (IR_results == num[2]){
      IR_delay = 0;
      motor.step(410);
      delay(500);
    }else if (IR_results == num[3]){
      IR_delay = 0;
      motor.step(204);
      delay(500);
    }else if ((IR_results == none) and (IR_delay == 1)){
      motor.step(204);
      delay(100);
    }
}
