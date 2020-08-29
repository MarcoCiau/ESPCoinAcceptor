#include "ESPCoinAcceptor.h"

volatile uint32_t coinCredit = 0;
volatile uint32_t previousCoinCredit = 0;
uint32_t lastCreditChangeTime = 0;

ICACHE_RAM_ATTR void attendCoinPulse();

ESPCoinAcceptor::ESPCoinAcceptor(int pin = DEFAULT_COIN_PIN)
{
    coinPin = pin;
    coinInserted = false;
}

void ESPCoinAcceptor::process()
{
    if (previousCoinCredit != coinCredit) 
    {
        unsigned long now = millis();
        if (now - lastCreditChangeTime > PULSE_TIMEOUT_MS) 
        {
            coinInserted = true;
            previousCoinCredit = coinCredit;
        }
    }
}

void ESPCoinAcceptor::begin()
{
/*
*COIN is just a NO or NC switch to GND according to the switch on the back, so it requires a pull-up.
*It's recommended to configure the COIN as NO to reduce power consumption through the pull-up when idle.
*In NO, we trigger the interrupt on falling-edge.
*/
  pinMode(interruptPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(coinPin), attendCoinPulse, FALLING);
}

void ESPCoinAcceptor::loop()
{
    process();
}

bool ESPCoinAcceptor::isCoinInserted()
{
  bool CoinStatus = coinInserted;
  coinInserted = false;
  return CoinStatus;
}


void attendCoinPulse()
{
  // Make sure this is a real pulse and not a spurious glitch
  delay(1);
  if(digitalRead(coinPin) == LOW) 
  {
    coinCredit += 1;
    lastCreditChangeTime = millis();
  }
}
