#include "Universal_Controller.h"

#define RX 7
#define TX 6
#define DNB 4
#define ANB 3
#define INTER 100

Droideka_Controller *con;
int anaPin[NB_MAX_DATA];
int digPin[NB_MAX_DATA];
bool digInputPullup[NB_MAX_DATA];
bool digReversedLogic[NB_MAX_DATA];

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
    digInputPullup[0] = false;
    digInputPullup[1] = true;
    digInputPullup[2] = true;
    digInputPullup[3] = true;
    digReversedLogic[0] = false;
    digReversedLogic[1] = false;
    digReversedLogic[2] = false;
    digReversedLogic[3] = false;

    con = new Droideka_Controller(RX, TX, INTER, DNB, ANB, digPin, anaPin, digInputPullup, digReversedLogic, BT_HW_HM10);
}

void loop()
{
    if (con->state())
    {
        con->getDataFromSensors();

        if (con->sendData(con->interval))
        {
            print_("Data sent at:\t" + String(millis()), true);
            for (int ii = 0; ii < con->analogNb; ii++)
            {
                print_(String(con->txdata.analog[ii]));
            }
            for (int ii = 0; ii < con->digitalNb; ii++)
            {
                print_(String(con->txdata.digital[ii]));
            }
            print_("", true);
        }
    }
    else
    {
        print_("Not connected", true);
    }
}