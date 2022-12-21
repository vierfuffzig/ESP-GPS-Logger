#ifndef UBLOX_H
#define UBLOX_H
//https://github.com/iforce2d/inavFollowme/blob/master/FollowMeTag/GPS.h
#include "Arduino.h"
#include "TimeLib.h"
#include "sys/time.h"
#include "SD_card.h"

#define RXD2 32  //geel is Tx Ublox, Beitian wit is Tx
#define TXD2 33  //groen is Rx Ublox, Beitian groen is Rx

const char UBLOX_UBX_OUT[] PROGMEM = {
  0xB5, 0x62, 0x06, 0x00, 0x14, 0x00, 0x01, 0x00, 0x00, 0x00, 0xD0, 0x08, 0x00, 0x00, 0x80, 0x25, 0x00, 0x00, 0x23, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0xBC, 0x89
};                                                                                                                                              //28 bytes
const char UBLOX_UBX_NAVPVT_ON[] PROGMEM = { 0xB5, 0x62, 0x06, 0x01, 0x08, 0x00, 0x01, 0x07, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x18, 0xE1 };  //NAV-PVT on 16 bytes
const char UBLOX_UBX_NAVDOP_ON[] PROGMEM = {0xB5,0x62,0x06,0x01,0x08,0x00,0x01,0x04,0x00,0x01,0x00,0x00,0x00,0x00,0x15,0xCC,};  //NAV-DOP on
const char UBLOX_UBX_BD19200[] PROGMEM = {
  0xB5, 0x62, 0x06, 0x00, 0x14, 0x00, 0x01, 0x00, 0x00, 0x00, 0xD0, 0x08, 0x00, 0x00, 0x00, 0x4B, 0x00, 0x00, 0x23, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x62, 0x2B
};  //set baudrate to 19200, only UBX out
const char UBLOX_UBX_BD38400[] PROGMEM = {
  0xB5, 0x62, 0x06, 0x00, 0x14, 0x00, 0x01, 0x00, 0x00, 0x00, 0xD0, 0x08, 0x00, 0x00, 0x00, 0x96, 0x00, 0x00, 0x23, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0xAD, 0x64
};

const char UBLOX_M10_NMEA_OFF[] PROGMEM = {  //NMEA OFF, generated with ucenter2 !!
  0xB5, 0x62, 0x06, 0x8A, 0x09, 0x00, 0x01, 0x01, 0x00, 0x00, 0x07, 0x00, 0x92, 0x20, 0x00, 0x54, 0x53
};
const char UBLOX_M10_UBX[] PROGMEM = {  //CFG-UART1OUTPROT-UBX = 1, generated with ucenter2 !!
  0xB5, 0x62, 0x06, 0x8A, 0x09, 0x00, 0x01, 0x01, 0x00, 0x00, 0x01, 0x00, 0x74, 0x10, 0x01, 0x21, 0xBC
};
const char UBLOX_M10_INIT[] PROGMEM = {  //CFG-MSGOUT-UBX_NAV2_PVT_UART1, generated with ucenter2 !!
  0xB5, 0x62, 0x06, 0x8A, 0x09, 0x00, 0x01, 0x01, 0x00, 0x00, 0x91, 0x04, 0x91, 0x20, 0x01, 0xE2, 0x13
};
const char UBLOX_M10_UBX_BD19200[] PROGMEM = {  //Set baudrate to 19200 baud, generated with ucenter2 !!
  0xB5, 0x62, 0x06, 0x8A, 0x0C, 0x00, 0x01, 0x01, 0x00, 0x00, 0x01, 0x00, 0x52, 0x40, 0x00, 0x4B, 0x00, 0x00, 0x7C, 0x4A
};

const char UBLOX_RATE[] PROGMEM = {
  0xB5, 0x62, 0x06, 0x08, 0x06, 0x00, 0xD0, 0x07, 0x01, 0x00, 0x01, 0x00, 0xED, 0xBD,  //(0,5Hz)0 tot 13 config.sample_rate=1
  0xB5, 0x62, 0x06, 0x08, 0x06, 0x00, 0xE8, 0x03, 0x01, 0x00, 0x01, 0x00, 0x01, 0x39,  //(1Hz)14 tot 27 config.sample_rate=2
  0xB5, 0x62, 0x06, 0x08, 0x06, 0x00, 0xC8, 0x00, 0x01, 0x00, 0x01, 0x00, 0xDE, 0x6A,  //(5Hz)28 tot 41 config.sample_rate=3
  0xB5, 0x62, 0x06, 0x08, 0x06, 0x00, 0x64, 0x00, 0x01, 0x00, 0x01, 0x00, 0x7A, 0x12,  //(10Hz)42 tot 55 config.sample_rate=4
  0xB5, 0x62, 0x06, 0x08, 0x06, 0x00, 0xF4, 0x01, 0x01, 0x00, 0x01, 0x00, 0x0B, 0x77,  //(2Hz)56 tot 69 config.sample_rate=5
  0xB5, 0x62, 0x06, 0x08, 0x06, 0x00, 0x37, 0x00, 0x01, 0x00, 0x01, 0x00, 0x4D, 0x04,  //(18Hz)70 tot 83 config.sample_rate=6
};
const char UBX_ID[] PROGMEM = {
  0xB5, 0x62, 0x27, 0x03, 0x00, 0x00, 0x2A, 0xA5,  //ask unique ID
};
const char UBX_SEA[] PROGMEM = {
  0xB5, 0x62, 0x06, 0x24, 0x24, 0x00, 0xFF, 0xFF, 0x05, 0x03, 0x00, 0x00, 0x00, 0x00, 0x10, 0x27, 0x00, 0x00, 0x05, 0x00, 0xFA, 0x00, 0xFA,  //switch to dynamic sea model
  0x00, 0x64, 0x00, 0x2C, 0x01, 0x00, 0x00, 0x00, 0x00, 0x10, 0x27, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x4C, 0xB9,              ////switch to dynamic sea model
};
const char UBX_PORTABLE[] PROGMEM = {
  0xB5, 0x62, 0x06, 0x24, 0x24, 0x00, 0xFF, 0xFF, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x10, 0x27, 0x00, 0x00, 0x05, 0x00, 0xFA, 0x00, 0xFA,  //switch to dynamic sea model
  0x00, 0x64, 0x00, 0x2C, 0x01, 0x00, 0x00, 0x00, 0x00, 0x10, 0x27, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x47, 0x0F,              ////switch to dynamic sea model
};
const char UBX_AUTOMOTIVE[] PROGMEM = {
  0xB5, 0x62, 0x06, 0x24, 0x24, 0x00, 0xFF, 0xFF, 0x04, 0x03, 0x00, 0x00, 0x00, 0x00, 0x10, 0x27, 0x00, 0x00, 0x05, 0x00, 0xFA, 0x00, 0xFA,  //switch to dynamic automotive model
  0x00, 0x64, 0x00, 0x2C, 0x01, 0x00, 0x00, 0x00, 0x00, 0x10, 0x27, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x4B, 0x97,              ////switch to dynamic automotive model
};
//Set to 3GNSS : GPS, GLONAS and GALILEO, only works with ublox M8N ROM 3.0 version !!!
const char UBX_GNSS3[] PROGMEM = {
  0xB5,0x62,0x06,0x3E,0x3C,0x00,0x00,0x20,0x20,0x07,0x00,0x08,0x10,0x00,0x01,0x00,0x01,0x01,0x01,0x01,0x03,0x00,0x01,0x00,0x01,0x01,0x02,0x04,0x08,0x00,0x01,0x00,0x01,0x01,
  0x03,0x08,0x10,0x00,0x00,0x00,0x01,0x01,0x04,0x00,0x08,0x00,0x00,0x00,0x01,0x03,0x05,0x00,0x03,0x00,0x01,0x00,0x01,0x05,0x06,0x08,0x0E,0x00,0x01,0x00,0x01,0x01,0x56,0x53,
};

const char UBX_MON_GNSS[] PROGMEM = {0xB5,0x62,0x0A,0x28,0x00,0x00,0x32,0xA0};//poll GNSS setting
const char UBX_MON_VER[] PROGMEM =  {0xB5,0x62,0x0A,0x04,0x00,0x00,0x0E,0x34};//poll SW version

const unsigned char UBX_HEADER[] = { 0xB5, 0x62 };
const unsigned char NAV_DUMMY_HEADER[] = { 0x01, 0x00 };
const unsigned char NAV_PVT_HEADER[] = { 0x01, 0x07 };
const unsigned char NAV_ACK_HEADER[] = { 0x05, 0x01 };
const unsigned char NAV_NACK_HEADER[] = { 0x05, 0x00 };
const unsigned char NAV_ID_HEADER[] = { 0x27, 0x03 };
const unsigned char MON_GNSS_HEADER[] = { 0x0A, 0x28 };
const unsigned char NAV_DOP_HEADER[] = { 0x01, 0x04 };
const unsigned char MON_VER_HEADER[] = { 0x0A, 0x04 };

enum _ubxMsgType {
  MT_NONE,
  MT_NAV_DUMMY,
  MT_NAV_PVT,
  MT_NAV_ACK,
  MT_NAV_NACK,
  MT_NAV_ID,
  MT_MON_GNSS,
  MT_NAV_DOP,
  MT_MON_VER
};
struct NAV_DUMMY {
  unsigned char cls;
  unsigned char id;
  unsigned short len;
  unsigned char msg_cls;
  unsigned char msg_id;
  unsigned char chkA;
  unsigned char chkB;
}__attribute__((__packed__));
struct NAV_PVT {  // 88 bytes payload, 92 bytes total, with Beitian BN220 100 bytes total ????
  unsigned char cls;
  unsigned char id;
  unsigned short len;
  unsigned long iTOW;        // GPS time of week of the navigation epoch (ms)
  unsigned short year;       // Year (UTC)
  unsigned char month;       // Month, range 1..12 (UTC)
  unsigned char day;         // Day of month, range 1..31 (UTC)
  unsigned char hour;        // Hour of day, range 0..23 (UTC)
  unsigned char minute;      // Minute of hour, range 0..59 (UTC)
  unsigned char second;      // Seconds of minute, range 0..60 (UTC)
  char valid;                // Validity Flags (see graphic below)
  unsigned long tAcc;        // Time accuracy estimate (UTC) (ns)
  long nano;                 // Fraction of second, range -1e9 .. 1e9 (UTC) (ns)
  unsigned char fixType;     // GNSSfix Type, range 0..5
  char flags;                // Fix Status Flags
  unsigned char reserved1;   // reserved
  unsigned char numSV;       // Number of satellites used in Nav Solution
  long lon;                  // Longitude (deg)
  long lat;                  // Latitude (deg)
  long height;               // Height above Ellipsoid (mm)
  long hMSL;                 // Height above mean sea level (mm)
  unsigned long hAcc;        // Horizontal Accuracy Estimate (mm)
  unsigned long vAcc;        // Vertical Accuracy Estimate (mm)
  long velN;                 // NED north velocity (mm/s)
  long velE;                 // NED east velocity (mm/s)
  long velD;                 // NED down velocity (mm/s)
  long gSpeed;               // Ground Speed (2-D) (mm/s)
  long heading;              // Heading of motion 2-D (deg)
  unsigned long sAcc;        // Speed Accuracy Estimate
  unsigned long headingAcc;  // Heading Accuracy Estimate
  unsigned short pDOP;       // Position dilution of precision
  short reserved2;           // Reserved
  unsigned long reserved3;   // Reserved
  long headVeh;              //only valid for adr4.1, beitian bn220 !
  short magDec;              //only valid for adr4.1,beitian bn220 !
  short magAcc;              //only valid for adr4.1,beitian bn220 !
  unsigned char chkA;
  unsigned char chkB;
}__attribute__((__packed__));
struct NAV_ACK {
  unsigned char cls;
  unsigned char id;
  unsigned short len;
  unsigned char msg_cls;
  unsigned char msg_id;
  unsigned char chkA;
  unsigned char chkB;
}__attribute__((__packed__));
struct NAV_NACK {
  unsigned char cls;
  unsigned char id;
  unsigned short len;
  unsigned char msg_cls;
  unsigned char msg_id;
  unsigned char chkA;
  unsigned char chkB;
}__attribute__((__packed__));
struct NAV_ID {
  unsigned char cls;
  unsigned char id;
  unsigned short len;
  byte Version;
  byte reserved1;
  byte reserved2;
  byte reserved3;
  byte ubx_id_1;
  byte ubx_id_2;
  byte ubx_id_3;
  byte ubx_id_4;
  byte ubx_id_5;
  unsigned char chkA;
  unsigned char chkB;
}__attribute__((__packed__));
struct MON_GNSS {
  unsigned char cls;
  unsigned char id;
  unsigned short len;
  byte Version;
  byte supported_Gnss;
  byte default_Gnss;
  byte enabled_Gnss;
  byte simultaneous;
  byte reserved1;
  byte reserved2;
  byte reserved3;
  unsigned char chkA;
  unsigned char chkB;
}__attribute__((__packed__));
struct NAV_DOP {  //payload 18 bytes, total 22 bytes, without (__packed__) 24 bytes !!!
  unsigned char cls;
  unsigned char id;
  unsigned short len;
  unsigned long iTOW;//4
  unsigned short gDOP;//6
  unsigned short pDOP;//8
  unsigned short tDOP;//10
  unsigned short vDOP;//12
  unsigned short hDOP;//14
  unsigned short nDOP;//16
  unsigned short eDOP;//18
  unsigned char chkA;
  unsigned char chkB;
}__attribute__((__packed__));

struct MON_VER {
        unsigned char cls;
        unsigned char id;
        unsigned short len;
        char swVersion[30];
        char hwVersion[10];
        unsigned char chkA;
        unsigned char chkB;
    }__attribute__((__packed__));

struct UBXMessage {//was union, but messages are overwritten by next message
  NAV_DUMMY navDummy;
  NAV_PVT navPvt;
  NAV_DOP navDOP;
  NAV_ACK navAck;
  NAV_NACK navNack;
  NAV_ID ubxId; 
  MON_GNSS monGNSS;
  MON_VER monVER;
}__attribute__((__packed__));

extern UBXMessage ubxMessage;  //declaration here, definition in Ublox.cpp
//extern GPS_data Ublox(1000);
extern bool sdOK;

extern char dataStr[255];  //string for logging NMEA in txt, test for write 2000 chars !!
extern char Buffer[50];
//void calcChecksum(unsigned char* CK, int msgSize);
void calcChecksum(unsigned char* CK,int msgType,int msgSize);
boolean compareMsgHeader(const unsigned char* msgHeader);
void Ublox_on();
void Ublox_off();
void Ublox_serial2(int delay_ms);
void Init_ublox(void);
void Init_ubloxM10(void);
void Set_rate_ublox(int);
void Set_GPS_Time(int time_offset);
int processGPS();
#endif
