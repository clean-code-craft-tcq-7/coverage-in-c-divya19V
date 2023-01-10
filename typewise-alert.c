#include "typewise-alert.h"
#include <stdio.h>

// Done with test cases
BreachType inferBreach(double value, double lowerLimit, double upperLimit) {
  if(value < lowerLimit) {
    return TOO_LOW;
  }
  if(value > upperLimit) {
    return TOO_HIGH;
  }
  return NORMAL;
}

//Done with test cases
BreachType classifyTemperatureBreach(
  CoolingType coolingType, double temperatureInC) {

  int upperLimit = 0;
  upperLimit = setLimitsBasedOnCoolingType(coolingType);
  
  return inferBreach(temperatureInC, 0, upperLimit); 
}

//Done with test cases
int setLimitsBasedOnCoolingType(CoolingType coolingType)
{
    int upperLimit = (coolingType == PASSIVE_COOLING) ? 35 : ((coolingType == HI_ACTIVE_COOLING) ?  45 : 40 );
    return upperLimit;
}

void checkAndAlert(
    AlertTarget alertTarget, BatteryCharacter batteryChar, double temperatureInC) {

  BreachType breachType = classifyTemperatureBreach(batteryChar.coolingType, temperatureInC);

  switch(alertTarget) {
    case TO_CONTROLLER:
      sendToController(breachType);
      break;
    case TO_EMAIL:
      sendToEmail(breachType);
      break;
  }
}

void sendToController(BreachType breachType) {
  const unsigned short header = 0xfeed;
  printf("%x : %x\n", header, breachType);
}

void sendToEmail(BreachType breachType) {
  const char* recepient = "a.b@c.com";
  switch(breachType) {
    case TOO_LOW:
      printf("To: %s\n", recepient);
      printf("Hi, the temperature is too low\n");
      break;
    case TOO_HIGH:
      printf("To: %s\n", recepient);
      printf("Hi, the temperature is too high\n");
      break;
    case NORMAL:
      break;
  }
}
