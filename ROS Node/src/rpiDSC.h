#ifndef RPIDSC_H_
#define RPIDSC_H_

#include "ros/ros.h"
#include <servo_board/Dynservo.h>
#include <servo_board/Motors_data.h>
#include <servo_board/Motors_id.h>
#include <boost/thread/thread.hpp>
#include <boost/thread/mutex.hpp>
#include <std_msgs/Float64.h>


using namespace std;

class rpiDSC
{
private:

	std::vector<int>  positions;
	std::vector<int>  temperatures;
	std::vector<int>  voltages;
	int m_number;
	servo_board::Dynservo commands;
	servo_board::Motors_id motconf;
	ros::NodeHandle n;
  ros::Publisher cmd_pub;
	ros::Publisher con_pub;
  ros::Subscriber sub;
	std::vector<ros::Subscriber> command;

  boost::mutex mutex;
  std::string s;
	std::vector<std::string> joint_names;
  std::vector<int> m_ids;
  std::map<std::string,std::vector<int>> joints;
  XmlRpc::XmlRpcValue list;
public:

rpiDSC();
~rpiDSC();

void dataCallback(const servo_board::Motors_data& msg);

void config();

void cmdCb(const std_msgs::Float64::ConstPtr& msg, int i);

int Getposition(uint8_t mot_n);


int Gettemperature(uint8_t mot_n);


int Getvoltage(uint8_t mot_n);


void Sendcommands(string const &joint_name,uint16_t  cmds);

};
#endif
