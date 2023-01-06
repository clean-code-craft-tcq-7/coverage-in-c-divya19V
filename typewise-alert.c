#include "typewise-alert.h"
#include <stdio.h>
#define LOWERLIMIT 0
#define UPPERLIMIT 1
void setLimitsBasedOnCoolingType(CoolingType coolingType, int *limits);

BreachType inferBreach(double value, double lowerLimit, double upperLimit) {
  if(value < lowerLimit) {
    return TOO_LOW;
  }
  if(value > upperLimit) {
    return TOO_HIGH;
  }
  return NORMAL;
}

BreachType classifyTemperatureBreach(
    CoolingType coolingType, double temperatureInC) {
 
  int limits[2] = {0,0};
  setLimitsBasedOnCoolingType(coolingType,&limits);
  
  return inferBreach(temperatureInC, limits[0], limits[1]); 
}

void setLimitsBasedOnCoolingType(CoolingType coolingType, int *limits)
{
    (limits + LOWERLIMIT) = 0;
    (limits + UPPERLIMIT) = (coolingType == PASSIVE_COOLING) ? 35 : ((coolingType == HI_ACTIVE_COOLING) ?  45 : 40 );
}

void checkAndAlert(
    AlertTarget alertTarget, BatteryCharacter batteryChar, double temperatureInC) {

  BreachType breachType = classifyTemperatureBreach(
    batteryChar.coolingType, temperatureInC
  );

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
