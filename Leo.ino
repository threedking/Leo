#include "Car.h"

TwoAxleSharpDriftCar *p_stunt_leo;

char BlueBuff=' ';  //Символьная переменная, в которой будем хранить пришедший от телефона символ-команду
int Mode = 0; //Для переключения между режимами управления по блютузу и другим/и

int BL1port = A0;  //Порт левого датчика черной линии
int BL2port = A1; //Порт правого датчика черной линии
void BlackLine();

void setup() {
  p_stunt_leo = new TwoAxleSharpDriftCar(
    new ServoSteeringAxle(11, 0, 180) ,
    new TwinEngineDrivingAxle(new ArduinoMotor3Pins(6, 7, 5), new ArduinoMotor3Pins(8, 9, 10)) );
  
  Serial.begin(9600);
  Serial3.begin(9600); //Блютуз на Лео
  
}

void loop() {
  if (Serial3.available()>0){     
   
    Serial.print("Buff= ");
    Serial.println(Serial3.available());   
    
    BlueBuff = Serial3.read();     
    
    Serial.print("Info= ");Serial.println(BlueBuff);

    switch(BlueBuff){         //Смотрим, что за символ пришел. Проверяем только смену режима и скорости
        case 'X':             //Символ включения аварийной сигнализации. Переходим в режим езды по линии
          Mode = 1;
        break;
        case 'x':         //Символ выключения аварийной сигнализации. Переходим в режим управления по блютузу
          Mode = 0;       
        break;
        case '0':
          p_stunt_leo->SetSpeed(25*0);  //Число - скорость. Преобразуем в ШИМ          
        break;
        case '1':
          p_stunt_leo->SetSpeed(25*1);  //Число - скорость. Преобразуем в ШИМ
        break;
        case '2':
          p_stunt_leo->SetSpeed(25*2);  //Число - скорость. Преобразуем в ШИМ
        break;
        case '3':
          p_stunt_leo->SetSpeed(25*3);  //Число - скорость. Преобразуем в ШИМ
        break;
        case '4':
          p_stunt_leo->SetSpeed(25*4);  //Число - скорость. Преобразуем в ШИМ
        break;
        case '5':
          p_stunt_leo->SetSpeed(25*5);  //Число - скорость. Преобразуем в ШИМ
        break;
        case '6':
          p_stunt_leo->SetSpeed(25*6);  //Число - скорость. Преобразуем в ШИМ
        break;
        case '7':
          p_stunt_leo->SetSpeed(25*7);  //Число - скорость. Преобразуем в ШИМ
        break;
        case '8':
          p_stunt_leo->SetSpeed(25*8);  //Число - скорость. Преобразуем в ШИМ
        break;
        case '9':
          p_stunt_leo->SetSpeed(25*9);  //Число - скорость. Преобразуем в ШИМ
        break;
        case 'q':
          p_stunt_leo->SetSpeed(255);  //Число - скорость. Преобразуем в ШИМ
        break;
    }


    if(Mode == 0){          //Режим управления по блютузу. Проверяем символы управления
      switch(BlueBuff){         
        case 'F':        
          p_stunt_leo->GoForward();        //Если пришедший символ F, то вперед
        break;
        case 'B':
          p_stunt_leo->GoBackward();       //Если пришедший символ B, то назад
        break;
        case 'L':   
          p_stunt_leo->GoLeft();         //Если пришедший символ L, то влево
        break;
        case 'R':      
          p_stunt_leo->GoRight();        //Если пришедший символ R, то вправо
        break;
        case 'G':     
          p_stunt_leo->GoForwardLeft();        //Если пришедший символ G, то вперед и влево
        break;
        case 'I':     
          p_stunt_leo->GoForwardRight();       //Если пришедший символ I, то вперед и вправо
        break;
        case 'H':
          p_stunt_leo->GoBackwardLeft();       //Если пришедший символ H, то назад и влево
        break;
        case 'J':
          p_stunt_leo->GoBackwardRight();      //Если пришедший символ J, то назад и вправо
        break;
        case 'S':  
          p_stunt_leo->Stop();         //Если пришедший символ S, то остановка платформы
        break;
        case 'V':         //Символ включения сигнала
        break;
        case 'v':             //Символ выключения сигнала
        break;
        case 'W':         //Символ включения передних фар
          p_stunt_leo->ActivateSharpAndDrift();
        break;
        case 'w':         //Символ выключения передних фар
          p_stunt_leo->DeactivateSharpAndDrift();
        break;
        case 'U':         //Символ включения задних фар
        break;
        case 'u':         //Символ выключения задних фар
        break;
        case ' ':
        break;
        default: 
        break;
      }  
    }
  }
  if(Mode == 1){
    BlackLine();
  }
}
//--------------------------
void BlackLine(){
  bool BL1 = digitalRead(BL1port);
  bool BL2 = digitalRead(BL2port);
 
  if((BL1 && BL2) ||
     (!BL1 && !BL2) ){
    p_stunt_leo->GoForward();
  }else if(!BL1 && BL2){
    p_stunt_leo->GoRight();
  }else if(BL1 && !BL2){
    p_stunt_leo->GoLeft();
  }
}
//--------------------------
