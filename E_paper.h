#ifndef E_PAPER_H
#define E_PAPER_H
#include <GxEPD.h>//was GxEPD.h
#include "Ublox.h"
#include "GPS_data.h"
//! There are four versions of the 2.13 screen,
//  if you are not sure which version, please test each one,
//  if it is successful then it belongs to the model of the file name

#include <GxDEPG0213BN/GxDEPG0213BN.h>  //Huidige schermen
//#include <GxGDEH0213B73/GxGDEH0213B73.h>  //Eerste schermen
//#include <GxGDEM0213B74/GxGDEM0213B74.h>  // 2.13", opgepast hier rst en busy aanpassen 
//#include <GxGDEW0213M21/GxGDEW0213M21.h>  //nog een andere versie, resolutie NIET OK


// https://oleddisplay.squix.ch/#/home font-converter online, used for 48pt font !!
// FreeFonts from Adafruit_GFX
#include <Fonts/FreeSansBold12pt7b.h>//gebruikt
#include <Fonts/FreeSansBold18pt7b.h>//gebruikt
#include <Fonts/SansSerif_bold_96_nr.h>//bijgevoegd in lib
#include <GxIO/GxIO_SPI/GxIO_SPI.h>//niet voor GxEPD2
#include <GxIO/GxIO.h>//niet voor GxEPD2

#define ELINK_SS 5
#define ELINK_BUSY 4
#define ELINK_RESET 16
#define ELINK_DC 17

#define BUTTON_PIN 39
#define BOOT_SCREEN 0
#define SPEED 1
#define AVG_10S 2
#define STATS1 3
#define STATS2 4
#define STATS3 5
#define STATS4 6
#define WIFI_ON 7
#define WIFI_STATION 8
#define WIFI_SOFT_AP 9
extern GxEPD_Class display;//not for GxEPD2
extern int sdTrouble,wifi_search;
extern bool sdOK;
extern bool Wifi_on;
extern bool SoftAP_connection;
extern bool GPS_Signal_OK;
extern float voltage_bat,alfa_window;
extern  double delta_heading,ref_heading;
extern int bootCount,run_count,stat_count;
extern int ftpStatus;
extern String IP_adress;
extern char SW_version[32];
extern RTC_DATA_ATTR float RTC_distance;
extern RTC_DATA_ATTR float RTC_avg_10s;
extern RTC_DATA_ATTR float RTC_max_2s;
extern GPS_speed M100;
extern GPS_speed M250;
extern GPS_speed M500;
extern Alfa_speed A250;
extern Alfa_speed A500;
extern GPS_time S1800;
extern GPS_time S3600;
void Boot_screen(void);
void Off_screen(void);
void sleep_screen(void);
void Sleep_screen(int info);
void Update_screen(int screen);
void Bat_level(int offset);
#endif
