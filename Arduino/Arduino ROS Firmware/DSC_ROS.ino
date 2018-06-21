/*
  MYBOTSHOP Dynamixel Servo Controllerboard (DSC)
  
  Product: https://www.mybotshop.de/Raspberry-Pi-Dynamixel-Servo-Controllerboard
  German Quick Start Guide: https://www.mybotshop.de/DSC
  English Quick Start Guide: https://www.mybotshop.de/DSC_EN

  Please read the manual carefully before using the DSC.

  modified 10.06.2018
  by MYBOTSHOP.DE
  
*/

#include <ros.h>
#include <servo_board/Dynservo.h>
#include <servo_board/Motors_data.h>
#include <servo_board/Motors_id.h>
#include <DynamixelSerial1.h>
//#include <EEPROM.h>

ros::NodeHandle nh;
servo_board::Motors_data data_msg;
servo_board::Motors_id id_msg;

ros::Publisher data("mydata", &data_msg);
int Temperature, Voltage, Position;
int address = 0;
byte data_len;
int pos[30];
int temp[30];
int volt[30];
uint8_t ids[30];

void controlCb(const servo_board::Dynservo& msg) {
  char lenght=msg.pos_cmd_length;
  for(char i=0;i<lenght;i++){
  Dynamixel.move(msg.index[i],msg.pos_cmd[i]);
  
  }
 
}

void configCb(const servo_board::Motors_id& configmsg) {
   //EEPROM.write(address, configmsg.Ids_length);
   data_len=configmsg.Ids_length;
   data_msg.position_length=data_len;
   data_msg.temperature_length=data_len;
   data_msg.voltage_length=data_len;
   id_msg.Ids_length=data_len;
   for(char j=0;j<data_len;j++)
   id_msg.Ids[j]=configmsg.Ids[j];
}

ros::Subscriber<servo_board::Dynservo> s("positions", controlCb);
ros::Subscriber<servo_board::Motors_id> con("config", configCb);

void setup()
{
  Dynamixel.begin(1000000,0);
  data_len = 6;
  nh.initNode();
  nh.subscribe(s);
  nh.subscribe(con);
  nh.advertise(data);
  data_msg.position=pos;
  data_msg.temperature=temp;
  data_msg.voltage=volt;
  id_msg.Ids=ids;
  data_msg.position_length=data_len;
  data_msg.temperature_length=data_len;
  data_msg.voltage_length=data_len;
  id_msg.Ids_length=data_len;
}

void loop()
{

  for (char i = 0; i < data_len; i++) {
  data_msg.position[i]=Dynamixel.readPosition(id_msg.Ids[i]);
  data_msg.temperature[i]=Dynamixel.readTemperature(id_msg.Ids[i]);
  data_msg.voltage[i]=Dynamixel.readVoltage(id_msg.Ids[i]);
  }

  data.publish(&data_msg);
  nh.spinOnce();
  //delay(1);
}

