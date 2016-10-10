//使用中断调整快门时间和间隔 2016-10-08
//电路图 https://circuits.io/circuits/2906659-romote-ir-shutter
/*
  待办任务
  研究使用中断与按键防抖
  或许只要一个固定时间就行了？研究一下常用的曝光时间。
  使用Fusion设计外壳？
*/
/*******************************************

   Name.......:  multiCameraIrControl Library - Sony Example
   Description:  A small example sketch how to use multiCameraIrControl library. Please check the project page for wiring and leave a comment.
   Author.....:  Sebastian Setz
   Version....:  1.3
   Date.......:  2013-02-11
   Project....:  http://sebastian.setz.name/arduino/my-libraries/multi-Camera-IR-Control
   Contact....:  http://Sebastian.Setz.name
   License....:  This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 3.0 Unported License.
                 To view a copy of this license, visit http://creativecommons.org/licenses/by-nc-sa/3.0/ or send a letter to
                 Creative Commons, 171 Second Street, Suite 300, San Francisco, California, 94105, USA.
   Keywords...:  arduino, library, camera, ir, control, canon, nikon, olympus, minolta, sony, pentax, interval, timelapse
   History....:  2010-12-08 V1.0 - release
                 2011-01-04 V1.1
                 2011-01-25 V1.2 - changing pin number, because the wiring at the homepage was different
                            V1.3 - adding toggleVideo

 ********************************************/

#include <multiCameraIrControl.h>

Sony A900(9);
//控制拍摄时长的插口、时长(毫秒)
const int capture_start_pin = 2;
int capture_start = 100;
boolean capture_start_interrupted = false;
//控制间隙时长的插口和时长(毫秒),用于等待相机处理图片
const int capture_end_pin = 18;
int capture_end = 100;
boolean capture_end_interrupted = false;




void setup() {
  pinMode(capture_start_pin, INPUT_PULLUP);
  pinMode(capture_start_pin, INPUT_PULLUP);
  pinMode(9, OUTPUT);
  digitalWrite(9, HIGH);
  attachInterrupt(0, capture_start_delay, RISING);
  attachInterrupt(5, capture_end_delay, RISING);
  //速度指示器
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  digitalWrite(5, LOW);
  digitalWrite(6, LOW);
  digitalWrite(7, HIGH);
  digitalWrite(10, LOW);
  digitalWrite(11, LOW);
  digitalWrite(12, HIGH);
}

void loop() {

  if (capture_start_interrupted)
  { switch (capture_start) {
      case 100:
        capture_start = 1000;
        capture_start_interrupted = false;
        digitalWrite(10, LOW);
        digitalWrite(11, HIGH);
        digitalWrite(12, HIGH);
        delay(200);
        break;
      case 1000:
        capture_start = 5000;
        capture_start_interrupted = false;
        digitalWrite(10, HIGH);
        digitalWrite(11, HIGH);
        digitalWrite(12, HIGH);
        delay(200);
        break;
      case 5000:
        capture_start = 100;
        capture_start_interrupted = false;
        digitalWrite(10, LOW);
        digitalWrite(11, LOW);
        digitalWrite(12, HIGH);
        delay(200);
        break;
    }
  }


  if (capture_end_interrupted)
  { switch (capture_end) {
      case 100:
        capture_end = 1000;
        capture_end_interrupted = false;
        digitalWrite(5, LOW);
        digitalWrite(6, HIGH);
        digitalWrite(7, HIGH);
        delay(500);
        break;
      case 1000:
        capture_end = 5000;
        capture_end_interrupted = false;
        digitalWrite(5, HIGH);
        digitalWrite(6, HIGH);
        digitalWrite(7, HIGH);
        delay(500);
        break;
      case 5000:
        capture_end = 100;
        capture_end_interrupted = false;
        digitalWrite(5, LOW);
        digitalWrite(6, LOW);
        digitalWrite(7, HIGH);
        delay(500);
        break;
    }
  }

  //  A900.shutterNow();
  digitalWrite(9, HIGH);
  //Serial.print("Start: ");
  //Serial.print(capture_start);
  //Serial.print(" ");
  delay(capture_start);
  //    A900.shutterNow();
  digitalWrite(9, LOW);
  //Serial.print("END: ");
  // Serial.println(capture_end);
  //    Serial.println('End: '+capture_end);
  delay(capture_end);

  //  A900.shutterDelayed();
  //  delay(5000);
  //  A900.toggleVideo();
  //  delay(5000);
}

void capture_start_delay() {
  capture_start_interrupted = true;
}


void capture_end_delay() {
  capture_end_interrupted = true;
}
