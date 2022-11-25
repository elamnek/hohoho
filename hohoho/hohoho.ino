/*
 Name:		hohoho.ino
 Created:	11/25/2022 9:35:07 PM
 Author:	eugen
*/


//sdcard logging
#include <TMRpcm.h>
#include <pcmRF.h>
#include <pcmConfig.h>
#include <SD.h>
#include <SPI.h>
#include <Servo.h> 

File m_SDFile;
#define SD_ChipSelectPin 4

//sound library
TMRpcm tmrpcm;
#define SpeakerPin 9
#define SpeakerVolume 5

Servo m_servo;
#define ServoPin 7


// the setup function runs once when you press reset or power the board
void setup() {

    tmrpcm.speakerPin = SpeakerPin;

    Serial.begin(9600);

    // SD Card Initialization
    if (SD.begin(SD_ChipSelectPin))
    {
        Serial.println("SD card is ready to use.");
    }
    else
    {
        Serial.println("SD card initialization failed");
        return;
    }

    tmrpcm.setVolume(SpeakerVolume);

    m_servo.attach(ServoPin);
    
     
}

// the loop function runs over and over again until power down or reset
void loop() {


    tmrpcm.play("song1.wav");
    m_servo.write(90);


}
