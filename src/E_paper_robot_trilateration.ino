// include library, include base class, make path known
#include <GxEPD.h>
#include "SD.h"
#include "SPI.h"
#include "WiFi.h"
#include "Wire.h"
#include <Adafruit_I2CDevice.h>
#include <MFRC522.h>
#include <PS4Controller.h>


#include <the_diamond.h>
#include <the_hermit.h>
#include <the_summit.h>
#include <the_temple.h>
#include <hope.h>
#include <merge.h>
#include <the_tower.h>
#include <the_hierophant.h>

//! There are three versions of the 2.13 screen,
//  if you are not sure which version, please test each one,
//  if it is successful then it belongs to the model of the file name
//  关于v2.3版本的显示屏版本,如果不确定购买的显示屏型号,请每个头文件都测试一遍.

//#include <GxGDE0213B1/GxGDE0213B1.h>      // 2.13" b/w
//#include <GxGDEH0213B72/GxGDEH0213B72.h>  // 2.13" b/w new panel
#include <GxGDEH0213B73/GxGDEH0213B73.h> // 2.13" b/w newer panel

int bmpWidth = 150, bmpHeight = 39;
//width:150,height:39
const unsigned char lilygo[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xf7, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x31, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0xfc, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0d, 0xfe, 0x60, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x19, 0xff, 0x20, 0x7f, 0xc0, 0x03, 0xfc, 0x7f, 0x80, 0x07, 0xf8, 0x0f, 0xf0, 0x00, 0xfe, 0x00, 0x03, 0xff, 0x80, 0x19, 0xe7, 0x30, 0x7f, 0xc0, 0x03, 0xfc, 0x7f, 0x80, 0x07, 0xfc, 0x0f, 0xf0, 0x07, 0xff, 0xc0, 0x0f, 0xff, 0xe0, 0x19, 0xe7, 0xb0, 0x7f, 0xc0, 0x03, 0xfc, 0x7f, 0x80, 0x03, 0xfc, 0x1f, 0xe0, 0x0f, 0xff, 0xe0, 0x1f, 0xff, 0xf8, 0x19, 0xff, 0x10, 0x7f, 0xc0, 0x03, 0xfc, 0x7f, 0x80, 0x03, 0xfe, 0x1f, 0xe0, 0x1f, 0xff, 0xf0, 0x3f, 0xff, 0xfc, 0x19, 0xff, 0x10, 0x3f, 0xc0, 0x03, 0xfc, 0x7f, 0x80, 0x03, 0xfe, 0x1f, 0xc0, 0x3f, 0xff, 0xf0, 0x7f, 0xff, 0xfe, 0x19, 0xfe, 0x10, 0x3f, 0xc0, 0x03, 0xfc, 0x7f, 0x80, 0x01, 0xfe, 0x3f, 0xc0, 0x7f, 0xff, 0xe0, 0x7f, 0xff, 0xfe, 0x19, 0xfe, 0x10, 0x3f, 0xc0, 0x03, 0xfc, 0x7f, 0x80, 0x01, 0xff, 0x3f, 0x80, 0xff, 0xc7, 0xc0, 0xff, 0xff, 0xff, 0x1d, 0xfe, 0x10, 0x3f, 0xc0, 0x03, 0xfc, 0x7f, 0x80, 0x00, 0xff, 0x7f, 0x80, 0xff, 0x81, 0x80, 0xff, 0xef, 0xff, 0x1d, 0xef, 0x00, 0x3f, 0xc0, 0x03, 0xfc, 0x7f, 0x80, 0x00, 0xff, 0xff, 0x00, 0xff, 0x00, 0x00, 0xff, 0xc3, 0xff, 0x8f, 0xef, 0x00, 0x3f, 0xc0, 0x03, 0xfc, 0x7f, 0x80, 0x00, 0x7f, 0xff, 0x01, 0xff, 0x00, 0x01, 0xff, 0xc3, 0xff, 0x8f, 0x87, 0x80, 0x3f, 0xc0, 0x03, 0xfc, 0x7f, 0x80, 0x00, 0x7f, 0xfe, 0x01, 0xfe, 0x00, 0x01, 0xff, 0xc1, 0xff, 0x87, 0x81, 0xc0, 0x3f, 0xc0, 0x03, 0xfc, 0x7f, 0x80, 0x00, 0x7f, 0xfe, 0x01, 0xfe, 0x1f, 0x81, 0xff, 0x81, 0xff, 0x83, 0xff, 0x80, 0x3f, 0xc0, 0x03, 0xfc, 0x7f, 0x80, 0x00, 0x3f, 0xfc, 0x01, 0xfe, 0x3f, 0xf9, 0xff, 0x81, 0xff, 0x80, 0xfe, 0x00, 0x3f, 0xc0, 0x03, 0xfc, 0x7f, 0x80, 0x00, 0x3f, 0xfc, 0x01, 0xfe, 0x3f, 0xf9, 0xff, 0x81, 0xff, 0x80, 0x00, 0x00, 0x3f, 0xc0, 0x03, 0xfc, 0x7f, 0x80, 0x00, 0x1f, 0xf8, 0x01, 0xfe, 0x3f, 0xf9, 0xff, 0x81, 0xff, 0x80, 0x00, 0x00, 0x3f, 0xc0, 0x03, 0xfc, 0x7f, 0x80, 0x00, 0x1f, 0xf0, 0x01, 0xff, 0x3f, 0xf9, 0xff, 0xc1, 0xff, 0x80, 0x00, 0x00, 0x3f, 0xc0, 0x03, 0xfc, 0x7f, 0x80, 0x00, 0x0f, 0xf0, 0x01, 0xff, 0x3f, 0xf8, 0xff, 0xc1, 0xff, 0x80, 0x00, 0x00, 0x3f, 0xc0, 0x03, 0xfc, 0x7f, 0x80, 0x00, 0x0f, 0xf0, 0x00, 0xff, 0x9f, 0xf8, 0xff, 0xc1, 0xff, 0x80, 0x00, 0x00, 0x3f, 0xc0, 0x03, 0xfc, 0x7f, 0x80, 0x00, 0x0f, 0xf0, 0x00, 0xff, 0x83, 0xf0, 0xff, 0xe1, 0xff, 0x00, 0x00, 0x00, 0x3f, 0xfc, 0x03, 0xfc, 0x7f, 0xf8, 0x00, 0x0f, 0xf0, 0x00, 0xff, 0xe3, 0xf0, 0x7f, 0xff, 0xff, 0x00, 0x00, 0x00, 0x3f, 0xff, 0xe3, 0xfc, 0x7f, 0xff, 0xc0, 0x0f, 0xf0, 0x00, 0x7f, 0xff, 0xf0, 0x7f, 0xff, 0xfe, 0x00, 0x00, 0x00, 0x3f, 0xff, 0xe3, 0xfc, 0x7f, 0xff, 0xc0, 0x0f, 0xf0, 0x00, 0x7f, 0xff, 0xf0, 0x3f, 0xff, 0xfe, 0x00, 0x00, 0x00, 0x3f, 0xff, 0xe3, 0xfc, 0x7f, 0xff, 0xc0, 0x0f, 0xf0, 0x00, 0x3f, 0xff, 0xf0, 0x3f, 0xff, 0xfc, 0x00, 0x00, 0x00, 0x3f, 0xff, 0xe3, 0xfc, 0x7f, 0xff, 0xc0, 0x0f, 0xf0, 0x00, 0x1f, 0xff, 0xf0, 0x1f, 0xff, 0xfc, 0x00, 0x00, 0x00, 0x3f, 0xff, 0xe3, 0xf8, 0x7f, 0xff, 0xc0, 0x0f, 0xf0, 0x00, 0x0f, 0xff, 0xf0, 0x0f, 0xff, 0xf8, 0x00, 0x00, 0x00, 0x1f, 0xff, 0xc3, 0xf8, 0x1f, 0xff, 0xc0, 0x0f, 0xe0, 0x00, 0x03, 0xff, 0xe0, 0x03, 0xff, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x3f, 0xc0, 0xf0, 0x00, 0x3f, 0x80, 0x07, 0xe0, 0x00, 0x00, 0xff, 0x80, 0x01, 0xff, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

// FreeFonts from Adafruit_GFX
#include <Fonts/FreeMonoBold9pt7b.h>
#include <Fonts/FreeMonoBold12pt7b.h>
#include <Fonts/FreeMonoBold18pt7b.h>
#include <Fonts/FreeMonoBold24pt7b.h>
#include <Fonts/Tiny3x3a2pt7b.h>
#include <Fonts/Picopixel.h>
#include <Fonts/Org_01.h>
#include <Fonts/TomThumb.h>

#include <GxIO/GxIO_SPI/GxIO_SPI.h>
#include <GxIO/GxIO.h>

#define SPI_MOSI 23
#define SPI_MISO -1
#define SPI_CLK 18

#define ELINK_SS 5
#define ELINK_BUSY 4
#define ELINK_RESET 16
#define ELINK_DC 17

#define SDCARD_SS 13
#define SDCARD_CLK 14
#define SDCARD_MOSI 15
#define SDCARD_MISO 2

#define RFID_SS 19
#define RFID_CLK 14
#define RFID_MOSI 15
#define RFID_MISO 2
#define RFID_RST 13


#define BUTTON_PIN 39
#define ADC_PIN 35

#define MOTOR_1A 32
#define MOTOR_1B 0
#define MOTOR_2A 27
#define MOTOR_2B 12

#define MOTOR_1A_CHANNEL 0
#define MOTOR_1B_CHANNEL 1
#define MOTOR_2A_CHANNEL 2
#define MOTOR_2B_CHANNEL 3

#define MOTOR_PWN_FREQUENCY 5000
#define MOTOR_RESOLUTION 8



char buff[512];
int vref = 1040; // battery calibration
GxIO_Class io(SPI, /*CS=5*/ ELINK_SS, /*DC=*/ELINK_DC, /*RST=*/ELINK_RESET);
GxEPD_Class display(io, /*RST=*/ELINK_RESET, /*BUSY=*/ELINK_BUSY);

SPIClass sdSPI(VSPI);
// MFRC522 rfidInstance(RFID_SS, /*Unused pin*/ UINT8_MAX);
MFRC522 rfidInstance(RFID_SS, RFID_RST);

const char *skuNum = "SKU:H239";
bool sdOK = false;
bool rfidOK = false;

int startX = 40, startY = 10;

void show_voltage()
{
	uint16_t v = analogRead(ADC_PIN);
	float battery_voltage = ((float)v / 4095.0) * 2.0 * 3.3 * (vref / 1000.0);
	String voltage = String(battery_voltage) + "V";
	Serial.println(voltage);
	display.setCursor(display.width() - 30, 12);
	display.println(voltage);
}

void wifi_scan()
{
	WiFi.mode(WIFI_STA);
	WiFi.disconnect();
	delay(100);

	int r1i = 0;
	int r2i = 0;
	int r3i = 0;

	for (int z = 0; z < 50; z++)
	{

		int16_t n = WiFi.scanNetworks();
		display.fillScreen(GxEPD_WHITE);
		if (n == 0)
		{
			display.println("no networks found");
		}
		else
		{

			display.setTextColor(GxEPD_BLACK);
			display.setFont(&Org_01);
			display.setCursor(0, 12);
			Serial.printf("Found %d net\n", n);
			for (int i = 0; i < n; ++i)
			{
				Serial.printf("str = \"%s\"\n", WiFi.SSID(i).c_str());
				if (String(WiFi.SSID(i).c_str()) == "beacon_1")
				{
					Serial.printf("beacon_1 found rssi :%d\n", WiFi.RSSI(i));
					r1i = WiFi.RSSI(i) + 100;
					Serial.printf("rayon = %d\n", r1i);
				}
				else if (String(WiFi.SSID(i).c_str()) == "beacon_2")
				{
					Serial.printf("beacon_2 found rssi :%d\n", WiFi.RSSI(i));
					r2i = WiFi.RSSI(i) + 100;
					Serial.printf("rayon = %d\n", r2i);
				}
				else if (String(WiFi.SSID(i).c_str()) == "beacon_3")
				{
					Serial.printf("beacon_3 found rssi :%d\n", WiFi.RSSI(i));
					r3i = WiFi.RSSI(i) + 100;
					Serial.printf("rayon = %d\n", r3i);
				}
				else
				{
					continue;
				}
				sprintf(buff,
						"[%d]:%s(%d)",
						i + 1,
						WiFi.SSID(i).c_str(),
						WiFi.RSSI(i));
				display.println(buff);
			}
			show_voltage();
			display.update();
			delay(1000);
		}
	}
	WiFi.mode(WIFI_OFF);
}

void test_cards()
{
	display.setRotation(0);
	display.fillScreen(GxEPD_BLACK);
	display.drawBitmap(the_diamond_bmp, 0, 0, 122, 250, GxEPD_WHITE);
	display.update();

	delay(10000);

	display.fillScreen(GxEPD_BLACK);
	display.drawBitmap(the_hermit_bmp, 0, 0, 122, 250, GxEPD_WHITE);
	display.update();

	delay(10000);

	display.fillScreen(GxEPD_BLACK);
	display.drawBitmap(the_summit_bmp, 0, 0, 122, 250, GxEPD_WHITE);
	display.update();

	delay(10000);

	display.fillScreen(GxEPD_BLACK);
	display.drawBitmap(the_temple_bmp, 0, 0, 122, 250, GxEPD_WHITE);
	display.update();

	delay(10000);

	display.fillScreen(GxEPD_BLACK);
	display.drawBitmap(hope_bmp, 0, 0, 122, 250, GxEPD_WHITE);
	display.update();

	delay(10000);

	display.fillScreen(GxEPD_BLACK);
	display.drawBitmap(merge_bmp, 0, 0, 122, 250, GxEPD_WHITE);
	display.update();

	delay(10000);

	display.fillScreen(GxEPD_BLACK);
	display.drawBitmap(the_tower_bmp, 0, 0, 122, 250, GxEPD_WHITE);
	display.update();

	delay(10000);

	display.fillScreen(GxEPD_BLACK);
	display.drawBitmap(the_hierophant_bmp, 0, 0, 122, 250, GxEPD_WHITE);
	display.update();
}

void setup()
{
	Serial.begin(115200);
	Serial.println();
	Serial.println("setup");
	SPI.begin(SPI_CLK, SPI_MISO, SPI_MOSI, ELINK_SS);
	display.init(); // enable diagnostic output on Serial
	// pinMode(MOTOR_1A, OUTPUT);
	// pinMode(MOTOR_1B, OUTPUT);
	// pinMode(MOTOR_2A, OUTPUT);
	// pinMode(MOTOR_2B, OUTPUT);
	ledcSetup(MOTOR_1A_CHANNEL, MOTOR_PWN_FREQUENCY, MOTOR_RESOLUTION);
	ledcSetup(MOTOR_1B_CHANNEL, MOTOR_PWN_FREQUENCY, MOTOR_RESOLUTION);
	ledcSetup(MOTOR_2A_CHANNEL, MOTOR_PWN_FREQUENCY, MOTOR_RESOLUTION);
	ledcSetup(MOTOR_2B_CHANNEL, MOTOR_PWN_FREQUENCY, MOTOR_RESOLUTION);

	ledcAttachPin(MOTOR_1A, MOTOR_1A_CHANNEL);
	ledcAttachPin(MOTOR_1B, MOTOR_1B_CHANNEL);
	ledcAttachPin(MOTOR_2A, MOTOR_2A_CHANNEL);
	ledcAttachPin(MOTOR_2B, MOTOR_2B_CHANNEL);



	PS4.begin("01:01:01:01:01:01");


	display.setRotation(1);
	display.fillScreen(GxEPD_WHITE);
	display.setTextColor(GxEPD_BLACK);
	display.setFont(&FreeMonoBold9pt7b);
	display.setCursor(0, 0);

	sdSPI.begin(SDCARD_CLK, SDCARD_MISO, SDCARD_MOSI, SDCARD_SS);

	if (!SD.begin(SDCARD_SS, sdSPI))
	{
		sdOK = false;
	}
	else
	{
		sdOK = true;
	}

	rfidInstance.SPI_Config(sdSPI);
	rfidInstance.PCD_Init();
	rfidInstance.PCD_DumpVersionToSerial();
	//if ();

	display.fillScreen(GxEPD_WHITE);

	// display.drawBitmap(lilygo, startX, startY, bmpWidth, bmpHeight, GxEPD_BLACK);

	display.setCursor(display.width() - display.width() / 2, display.height() - 35);

	display.println(skuNum);

	display.setTextColor(GxEPD_BLACK);

	display.setCursor(display.width() / 2 - 40, display.height() - 10);

	if (sdOK)
	{
		uint32_t cardSize = SD.cardSize() / (1024 * 1024);
		display.println("SDCard:" + String(cardSize) + "MB");
		Serial.println("SDCard:" + String(cardSize) + "MB");
	}
	else
	{
		display.println("SDCard  None");
		Serial.println("SDCard  None");
	}
	display.update();
	display.setRotation(0);

	//test_cards();
	//wifi_scan();

	// goto sleep
	//esp_sleep_enable_ext0_wakeup((gpio_num_t)BUTTON_PIN, LOW);

	//esp_deep_sleep_start();
}

void printHex(uint8_t num)
{
	char hexCar[3];

	sprintf(hexCar, "%02X ", num);
	Serial.print(hexCar);
}

void printByteArray(byte *b)
{
	for (int i = 0; i < sizeof(b); i++)
	{
		printHex(b[i]);
	}

	Serial.println();
}

bool isBytesEquals(byte *b1, byte *b2)
{
	for (int i = 0; i < sizeof(b1) && i < sizeof(b2); i++)
	{
		if (b1[i] != b2[i])
		{
			return (false);
		}
	}
	return (true);
}


void motor_1_activate(uint8_t activate, uint8_t direction)
{
	if (activate == 0)
	{
		digitalWrite(MOTOR_1A, LOW);
		digitalWrite(MOTOR_1B, LOW);
	}
	else
	{
		if (direction == 1)
		{
			digitalWrite(MOTOR_1A, HIGH);
			digitalWrite(MOTOR_1B, LOW);
		}
		else
		{
			digitalWrite(MOTOR_1A, LOW);
			digitalWrite(MOTOR_1B, HIGH);
		}
	}
}

void motor_2_activate(uint8_t activate, uint8_t direction)
{
	if (activate == 0)
	{
		digitalWrite(MOTOR_2A, LOW);
		digitalWrite(MOTOR_2B, LOW);
	}
	else
	{
		if (direction == 1)
		{
			digitalWrite(MOTOR_2A, HIGH);
			digitalWrite(MOTOR_2B, LOW);
		}
		else
		{
			digitalWrite(MOTOR_2A, LOW);
			digitalWrite(MOTOR_2B, HIGH);
		}
	}
}


void showCurrentcard()
{
	byte hope_card[10] = {0x54, 0x30, 0x48, 0x2E};
	byte merge_card[10] = {0x17, 0xF8, 0x7B, 0xB4};
	byte the_diamond_card[10] = {0x37, 0x2A, 0x70, 0xB4};
	byte the_hermit_card[10] = {0x27, 0x02, 0xD7, 0xB5};
	byte the_hierophant_card[10] = {0x67, 0x50, 0xB8, 0xB4};
	byte the_summit_card[10] = {0xF7, 0x00, 0x79, 0xB5};
	byte the_temple_card[10] = {0x47, 0xFD, 0xBD, 0xB5};
	byte the_tower_card[10] = {0x17, 0x17, 0xCA, 0xB4};

	if (isBytesEquals(rfidInstance.uid.uidByte, hope_card))
	{
		Serial.println("Hope card");
		display.fillScreen(GxEPD_BLACK);
		display.drawBitmap(hope_bmp, 0, 0, 122, 250, GxEPD_WHITE);
		display.update();
		delay(1000);
	}
	else if (isBytesEquals(rfidInstance.uid.uidByte, merge_card))
	{
		Serial.println("Merge card");
		display.fillScreen(GxEPD_BLACK);
		display.drawBitmap(merge_bmp, 0, 0, 122, 250, GxEPD_WHITE);
		display.update();
		delay(1000);
	}
	else if (isBytesEquals(rfidInstance.uid.uidByte, the_diamond_card))
	{
		Serial.println("The Diamond card");
		display.fillScreen(GxEPD_BLACK);
		display.drawBitmap(the_diamond_bmp, 0, 0, 122, 250, GxEPD_WHITE);
		display.update();
		delay(1000);
	}
	else if (isBytesEquals(rfidInstance.uid.uidByte, the_hermit_card))
	{
		Serial.println("The Hermit card");
		display.fillScreen(GxEPD_BLACK);
		display.drawBitmap(the_hermit_bmp, 0, 0, 122, 250, GxEPD_WHITE);
		display.update();
		delay(1000);
	}
	else if (isBytesEquals(rfidInstance.uid.uidByte, the_hierophant_card))
	{
		Serial.println("The Hierophant card");
		display.fillScreen(GxEPD_BLACK);
		display.drawBitmap(the_hierophant_bmp, 0, 0, 122, 250, GxEPD_WHITE);
		display.update();
		delay(1000);
	}
	else if (isBytesEquals(rfidInstance.uid.uidByte, the_summit_card))
	{
		Serial.println("The Summit card");
		display.fillScreen(GxEPD_BLACK);
		display.drawBitmap(the_summit_bmp, 0, 0, 122, 250, GxEPD_WHITE);
		display.update();
		delay(1000);
	}
	else if (isBytesEquals(rfidInstance.uid.uidByte, the_temple_card))
	{
		Serial.println("The Temple card");
		display.fillScreen(GxEPD_BLACK);
		display.drawBitmap(the_temple_bmp, 0, 0, 122, 250, GxEPD_WHITE);
		display.update();
		delay(1000);
	}
	else if (isBytesEquals(rfidInstance.uid.uidByte, the_tower_card))
	{
		Serial.println("The Tower card");
		display.fillScreen(GxEPD_BLACK);
		display.drawBitmap(the_tower_bmp, 0, 0, 122, 250, GxEPD_WHITE);
		display.update();
		delay(1000);
	}
}

void dualshock_loop()
{
	if (PS4.isConnected()) {
		Serial.printf("L Sticky Y : %d\n", PS4.LStickY());
		Serial.printf("R Sticky Y : %d\n", PS4.RStickY());
		if (PS4.LStickY() > 5)
		{
			ledcWrite(MOTOR_1A_CHANNEL, map(PS4.LStickY(), 5, 129, 0, 255));
			ledcWrite(MOTOR_1B_CHANNEL, 0);
		}
		else if (PS4.LStickY() < -5)
		{
			ledcWrite(MOTOR_1A_CHANNEL, 0);
			ledcWrite(MOTOR_1B_CHANNEL, map(PS4.LStickY(), -5, -129, 0, 255));
		}
		else
		{
					ledcWrite(MOTOR_1A_CHANNEL, 0);
		ledcWrite(MOTOR_1B_CHANNEL, 0);
		}

		// else if (PS4.LStickY() < 5)
		// {
		// 	ledcWrite(MOTOR_1A_CHANNEL, 0);
		// 	ledcWrite(MOTOR_1B_CHANNEL, map(PS4.LStickY(), -5, -127, 0, 255));
		// }
		// else
		// {
		// 	ledcWrite(MOTOR_1A_CHANNEL, 0);
		// 	ledcWrite(MOTOR_1B_CHANNEL, 0);
		// }
		if (PS4.RStickY() > 5)
		{
			ledcWrite(MOTOR_2A_CHANNEL, map(PS4.RStickY(), 5, 129, 0, 255));
			ledcWrite(MOTOR_2B_CHANNEL, 0);
		}
		else if (PS4.RStickY() < -5)
		{
			ledcWrite(MOTOR_2A_CHANNEL, 0);
			ledcWrite(MOTOR_2B_CHANNEL, map(PS4.RStickY(), -5, -129, 0, 255));
		}
		else
		{
			ledcWrite(MOTOR_2A_CHANNEL, 0);
			ledcWrite(MOTOR_2B_CHANNEL, 0);
		}

		// ledcWrite(MOTOR_2A_CHANNEL, 0);
		// ledcWrite(MOTOR_2B_CHANNEL, 0);

	}
}

void loop()
{
	dualshock_loop();

	if (!rfidInstance.PICC_IsNewCardPresent())
	{
		return;
	}
	if (!rfidInstance.PICC_ReadCardSerial())
	{
		return;
	}
	rfidInstance.PICC_DumpDetailsToSerial(&rfidInstance.uid);
	showCurrentcard();
	delay(100);
	//byte test[10] = {0x54, 0x30, 0x48, 0x2E};
	//printByteArray(test);
	//printByteArray(rfidInstance.uid.uidByte);
	//if (isBytesEquals(test, rfidInstance.uid.uidByte))
	//{
	//	Serial.println("Card one");
	//}
}
