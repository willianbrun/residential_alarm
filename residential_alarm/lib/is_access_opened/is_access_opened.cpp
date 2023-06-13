#include <Arduino.h>
bool isAccessOpened(const int accessPort)
{
    int accessRead = analogRead(accessPort);
    return accessRead > 50;
}