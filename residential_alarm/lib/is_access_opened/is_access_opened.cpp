#include <Arduino.h>
bool isAccessOpened(const int accessPort){
    int accessRead = digitalRead(accessPort);
    return accessRead > 50;
}