// Simple MP3 player using the MD_YX5300 library.
//
// MP3 player has the following functions:
// - Start/pause track playback with switch (press)
// - Play next track with switch (long press)
// - Volume control using potentiometer
// - Run state shown using LED indicator
//
// Implemented using all synchronous calls and kept as simple as possible.
// All tracks need to be placed in folder PLAY_FOLDER (defined below)
//
// Library dependencies:
// MD_UISwitch can be found at https://github.com/MajicDesigns/MD_UISwitch
//

#ifndef USE_SOFTWARESERIAL
#include <Servo.h>
#include <arduino-timer.h>
#define USE_SOFTWARESERIAL 1   ///< Set to 1 to use SoftwareSerial library, 0 for native serial port
#endif

#include <MD_YX5300.h>
#include <MD_UISwitch.h>

#if USE_SOFTWARESERIAL
#include <SoftwareSerial.h>

const uint8_t ARDUINO_RX = 2;    
const uint8_t ARDUINO_TX = 3;    

SoftwareSerial  MP3Stream(ARDUINO_RX, ARDUINO_TX);  // MP3 player serial stream for comms
#define Console Serial           // command processor input/output stream
#else
#define MP3Stream Serial  // Native serial port - change to suit the application
//#define Console   Serial   // command processor input/output stream
#endif

auto timerMinute = timer_create_default();

const uint8_t PLAY_FOLDER = 1;   // tracks are all placed in this folder
MD_YX5300 mp3(MP3Stream);

int m_intServoPin = 5;
Servo m_servo;

long m_lngRandomMinutes;
long m_lngRandomSound;
long m_lngMinuteCounter = 0;

void setup()
{

    m_servo.attach(m_intServoPin);
    m_servo.write(90);

    timerMinute.every(60000, timerMinute_interrupt);

    MP3Stream.begin(MD_YX5300::SERIAL_BPS);
    mp3.begin();
    mp3.setSynchronous(true);
    mp3.volume(30);

    m_lngRandomMinutes = random(1, 2);//always play sound in the first minute when starting up
    m_lngRandomSound = random(4, 6);//two tracks to play (tracks 4 and 5)
  
}

bool timerMinute_interrupt(void*) {
   
    //increment the minute counter
    m_lngMinuteCounter = m_lngMinuteCounter + 1;

    Serial.println("timer hit - minute counter: " + String(m_lngMinuteCounter) + " random minutes: " + String(m_lngRandomMinutes) + " random sound: " + String(m_lngRandomSound));

    if (m_lngMinuteCounter == m_lngRandomMinutes) {

        //play the sound
        mp3.playTrack(m_lngRandomSound);

        //activate servo according to delay scenario
        if (m_lngRandomSound == 4) {
           
            //hohoho
            long arrayData[11] = { 300,550,1000,1440,2250,2710,3060,3440,3900,4300,4800 };
            delay(arrayData[0]);
            for (int i = 1; i < 11; i++) {
                long lngOpenTime = (arrayData[i] - arrayData[i - 1]) / 2;
                m_servo.write(120); //open 
                delay(lngOpenTime);
                m_servo.write(90); //close
                delay(lngOpenTime);
            }

        } else if (m_lngRandomSound == 5){
            
            //burp
            //long arrayData[2] = { 60,1440 };
            delay(60);
            m_servo.write(120); //open
            delay(1380);
            m_servo.write(90); //close
        }

        //reset random numbers
        m_lngRandomMinutes = random(1, 2);
        m_lngRandomSound = random(4, 6);
        m_lngMinuteCounter = 0;
        
    }
    
    return true;
}

void loop()
{
    timerMinute.tick();
    mp3.check();    
}










///*
// Name:		hohoho.ino
// Created:	11/25/2022 9:35:07 PM
// Author:	eugen
//*/
//
//
////sdcard logging
//#include <MD_YX5300.h>
//#include <TMRpcm.h>
//#include <pcmRF.h>
//#include <pcmConfig.h>
//#include <SD.h>
//#include <SPI.h>
//#include <Servo.h> 
//
//File m_SDFile;
//#define SD_ChipSelectPin 4
//
////sound library
///*TMRpcm tmrpcm;
//#define SpeakerPin 9
//#define SpeakerVolume 5*/
//
//Servo m_servo;
//#define ServoPin 5
//
//const short rx = 10; // connect to TX of MP3 Player module
//const short tx = 11; // connect to RX of MP3 Player module
//MD_YX5300 mp3(rx, tx);
//
//
//// the setup function runs once when you press reset or power the board
//void setup() {
//
//    tmrpcm.speakerPin = SpeakerPin;
//
//    Serial.begin(9600);
//
//    //pinMode(SD_ChipSelectPin, OUTPUT);
//
//    // SD Card Initialization
//    /*if (SD.begin(SD_ChipSelectPin))
//    {
//        Serial.println("SD card is ready to use.");
//    }
//    else
//    {
//        Serial.println("SD card initialization failed");
//        return;
//    }*/
//
//    //tmrpcm.volume(0);
//    //tmrpcm.setVolume(6);
//
//    m_servo.attach(ServoPin);
//    
//    //tmrpcm.play("hohoho.wav");
//}
//
// the loop function runs over and over again until power down or reset
//void loop() {
//
//
//    
//    m_servo.write(90);
//    delay(400);
//    m_servo.write(45);
//    delay(400);
//
//}
