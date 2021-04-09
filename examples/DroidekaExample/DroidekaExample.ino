#include "Universal_Controller.h"

#define RX 2
#define TX 3
#define DNB 14
#define ANB 4
#define INTER 100

Universal_Controller *con;
int anaPin[NB_MAX_DATA];
int digPin[NB_MAX_DATA];
bool digInputPullup[NB_MAX_DATA];
bool digReversedLogic[NB_MAX_DATA];
int16_t threshold[NB_MAX_DATA];
int16_t middle[NB_MAX_DATA];

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
    anaPin[0] = A4;
    anaPin[1] = A5;
    anaPin[2] = A7;
    anaPin[3] = A6;

    threshold[0] = 4;
    threshold[1] = 4;
    threshold[2] = 4;
    threshold[3] = 4;

    middle[0] = 420;
    middle[1] = 465;
    middle[2] = 465;
    middle[3] = 460;

    digPin[0] = 10;
    digPin[1] = 8;
    digPin[2] = 7;
    digPin[3] = 9;
    digPin[4] = 6;
    digPin[5] = 4;
    digPin[6] = 12;
    digPin[7] = 5;
    digPin[8] = 11;
    digPin[9] = 13;
    digPin[10] = 17;
    digPin[11] = 15;
    digPin[12] = 16;
    digPin[13] = 14;

    digInputPullup[0] = true;
    digInputPullup[1] = true;
    digInputPullup[2] = true;
    digInputPullup[3] = true;
    digInputPullup[4] = true;
    digInputPullup[5] = true;
    digInputPullup[6] = true;
    digInputPullup[7] = true;
    digInputPullup[8] = false;
    digInputPullup[9] = false;
    digInputPullup[10] = true;
    digInputPullup[11] = true;
    digInputPullup[12] = true;
    digInputPullup[13] = true;

    digReversedLogic[0] = false;
    digReversedLogic[1] = false;
    digReversedLogic[2] = false;
    digReversedLogic[3] = false;
    digReversedLogic[4] = false;
    digReversedLogic[5] = false;
    digReversedLogic[6] = false;
    digReversedLogic[7] = false;
    digReversedLogic[8] = true;
    digReversedLogic[9] = true;
    digReversedLogic[10] = false;
    digReversedLogic[11] = false;
    digReversedLogic[12] = false;
    digReversedLogic[13] = false;

    con = new Universal_Controller(RX, TX, INTER, DNB, ANB, digPin, anaPin, digInputPullup, digReversedLogic, threshold, middle, BT_HW_HC05);
}

void loop()
{
    if (con->state())
    {
        con->getDataFromSensors();
        con->sendData(con->interval);
    }
}