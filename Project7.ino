#include "ADXL345.h"
ADXL345 accelerometer;
#include <SPI.h>
#include "LCD.h"
#include "DEV_Config.h"
const float pi = 3.141592;
const int sample_no = 100; // no of samples for aproximation
int16_t ax, ay, az;
float x, y, z;
int  sample;
float pitch, _angle_y, roll, yaw;
long ax_sum, ay_sum, az_sum;
void setup() {
  accelerometer.begin();
  accelerometer.setRange(ADXL345_RANGE_4G);
  Serial.begin(9600);

  pinMode(LCD_CS, OUTPUT);
  pinMode(LCD_RST, OUTPUT);
  pinMode(LCD_DC, OUTPUT);

  SPI.begin();

  LCD_SCAN_DIR Lcd_ScanDir = SCAN_DIR_DFT;
  LCD.LCD_Init(Lcd_ScanDir);
  LCD.LCD_Show();
  LCD.LCD_Clear(BLACK);
}

void loop() {
  Vector norm = accelerometer.readNormalize();
  Vector filtered = accelerometer.lowPassFilter(norm, 0.15);

  ax = filtered.XAxis;
  ay = filtered.YAxis;
  az = filtered.ZAxis;
  ax_sum = ax_sum + ax;
  ay_sum = ay_sum + ay;
  az_sum = az_sum + az;
  sample++;

  if (sample == sample_no)
  {
    // mean values
    x = ax_sum / sample_no;
    y = ay_sum / sample_no;
    z = az_sum / sample_no;

    // Calculate of roll and pitch in deg
    pitch = atan2(x, sqrt(square(y) + square(z))) / (pi / 180);
    roll = atan2(y, sqrt(square(x) + square(z))) / (pi / 180);
    yaw = atan2(y, sqrt(square(x) + square(z))) / (pi / 180);

    // Reset values for next aproximation
    sample = 0;
    ax_sum = 0;
    ay_sum = 0;
    az_sum = 0;

    Serial.println(pitch);
    Serial.println(roll);
    Serial.println(yaw);
    
    char resultP[8]; // Buffer big enough for 7-character float
    char resultR[8]; // Buffer big enough for 7-character float
    char resultY[8]; // Buffer big enough for 7-character float
    dtostrf(pitch, 6, 2, resultP);
    dtostrf(roll, 6, 2, resultR);
    dtostrf(yaw, 6, 2, resultY);
    Serial.println("dsgfeg");
    LCD.LCD_DisplayString(0, 0, "pitch", &Font12, BLACK, YELLOW);
    LCD.LCD_DisplayString(0, 12, resultP, &Font12, BLACK, YELLOW);
    LCD.LCD_DisplayString(0, 24, "yaw", &Font12, BLACK, YELLOW);
    LCD.LCD_DisplayString(0, 36, resultY, &Font12, BLACK, YELLOW);
    LCD.LCD_DisplayString(0, 48, "roll", &Font12, BLACK, YELLOW);
    LCD.LCD_DisplayString(0, 60, resultR, &Font12, BLACK, YELLOW);

    char result_x[8]; // Buffer big enough for 7-character float
    char result_y[8]; // Buffer big enough for 7-character float
    char result_z[8]; // Buffer big enough for 7-character float
    dtostrf(x, 6, 2, result_x);
    dtostrf(y, 6, 2, result_y);
    dtostrf(z, 6, 2, result_z);

    LCD.LCD_DisplayString(50, 0, "x", &Font12, BLACK, YELLOW);
    LCD.LCD_DisplayString(50, 12, result_x, &Font12, BLACK, YELLOW);
    LCD.LCD_DisplayString(50, 24, "y", &Font12, BLACK, YELLOW);
    LCD.LCD_DisplayString(50, 36, result_y, &Font12, BLACK, YELLOW);
    LCD.LCD_DisplayString(50, 48, "z", &Font12, BLACK, YELLOW);
    LCD.LCD_DisplayString(50, 60, result_z, &Font12, BLACK, YELLOW);
  }
}
