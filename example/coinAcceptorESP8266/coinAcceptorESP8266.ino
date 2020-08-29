#include <ESPCoinAcceptor.h>
ESPCoinAcceptor coin(14);//D5 GPIO

int credit;//just a coin counter

void setup()
{
  Serial.begin(115200);
  Serial.println("Coin Acceptor Test");

  coin.begin();//init coin acceptor library

  credit = 0;
}

void loop()
{
  coin.loop();//keep this loop

  if (coin.isCoinInserted()) //check if coin was inserted
  {
    Serial.print("Coin Inserted. Credits : ");
    credit++;
    Serial.println(credit);
  }
}