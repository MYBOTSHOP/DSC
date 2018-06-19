#include "rpiDSC.h"

int main(int argc, char **argv)
{

  ros::init(argc, argv, "servo_cnt");
  rpiDSC Servo_board;
	Servo_board.config();
	//ROS_INFO("temp= %d",Servo_board.Getposition(2));


	while (ros::ok())
   {
     //ROS_INFO("posi= %d",Servo_board.Getposition(2));
		 //ROS_INFO("temp= %d",Servo_board.Gettemperature(2));
		 //ROS_INFO("volt= %d",Servo_board.Getvoltage(2));
     ros::spinOnce();
   }
  return 0;
}
