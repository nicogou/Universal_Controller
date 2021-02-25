#include "Droideka_Controller.h"

#define RX 7
#define TX 6
#define DNB 4
#define IPNB 3
#define ANB 3
#define INTER 100

Droideka_Controller *con;
int anaPin[NB_MAX_DATA];
int digPin[NB_MAX_DATA];

void print_(String string, bool newline = false)
{
    string = string + "\t";
    Serial.print(string);
    if (newline)
    {
        Serial.println();
    }
}

void setup()
{
    anaPin[0] = A2;
    anaPin[1] = A1;
    anaPin[2] = A0;
    digPin[0] = 5;
    digPin[1] = 2;
    digPin[2] = 3;
    digPin[3] = 4;

    con = new Droideka_Controller(RX, TX, INTER, DNB, ANB, digPin, anaPin, IPNB);
}

void loop()
{
    if (con->state())
    {
        con->getDataFromSensors();

        if (con->sendData(con->interval))
        {
            print_("Data sent at:\t" + String(millis()), true);
        }
    }
    else
    {
        print_("Not connected", true);
    }
}