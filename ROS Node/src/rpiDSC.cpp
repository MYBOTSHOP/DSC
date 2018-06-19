#include "rpiDSC.h"

#include "ros/ros.h"
#include <servo_board/Dynservo.h>
#include <servo_board/Motors_data.h>
#include <servo_board/Motors_id.h>
#include <vector>


rpiDSC::rpiDSC()
	{
	    cmd_pub = n.advertise<servo_board::Dynservo>("/positions", 100);
			con_pub = n.advertise<servo_board::Motors_id>("/config", 100);
		  ros::Duration(2).sleep();
			m_number=0;
	}

	rpiDSC::~rpiDSC()
		{

		}

void rpiDSC::dataCallback(const servo_board::Motors_data& msg)
{
boost::mutex::scoped_lock lock(this->mutex);
for(unsigned int i=0;i<msg.position.size();i++){
 positions[i]=msg.position[i];
 temperatures[i]=msg.temperature[i];
 voltages[i]=msg.voltage[i];
 }
}

void rpiDSC::config()
{

	sub = n.subscribe("/mydata", 100, &rpiDSC::dataCallback,this);
	ros::Duration(2).sleep();

	if (!n.getParam("/joints", list)) {
	  ROS_ERROR("Can't find '/joints' in the YAML configuration file.");
	}

	if (!n.getParam("/use_lib", s)) {
		ROS_ERROR("Can't find 'use_lib' in the YAML configuration file.");
	}

	for (auto it = list.begin(); it != list.end(); it++) {
	  joint_names.push_back(it->first);
	}
	for (int i = 0; i<joint_names.size(); i++) {
	  std::string topic("/joints/");
	  topic += joint_names[i]+"/id";
		if(s == "false")
		command.push_back(n.subscribe<std_msgs::Float64>(joint_names[i]+"/command", 1,boost::bind(&rpiDSC::cmdCb,this,_1,i)));
	  n.getParam(topic,m_ids);
	  joints[joint_names[i]]=m_ids;
		m_number+=m_ids.size();
		for(int j=0;j<m_ids.size();j++)
		motconf.Ids.push_back(m_ids[j]);
	}

	positions.resize(m_number);
	temperatures.resize(m_number);
	voltages.resize(m_number);

	con_pub.publish(motconf);
}

void rpiDSC::cmdCb(const std_msgs::Float64::ConstPtr& msg, int i)
{
this->Sendcommands(joint_names[i],(int)msg->data);
}

int rpiDSC::Getposition(uint8_t mot_n)
	  {
		boost::mutex::scoped_lock lock(this->mutex);
		for(unsigned int i=0;i<positions.size();i++)
    return positions[mot_n];
	  }

int rpiDSC::Gettemperature(uint8_t mot_n)
		{
		boost::mutex::scoped_lock lock(this->mutex);
		return temperatures[mot_n];
		}

int rpiDSC::Getvoltage(uint8_t mot_n)
		{
		boost::mutex::scoped_lock lock(this->mutex);
		return voltages[mot_n];
		}

void rpiDSC::Sendcommands(string const &joint_name,uint16_t  cmds)
		{
    std::vector<int> motors=joints[joint_name];
		if(motors.size() == 0)
		ROS_ERROR("WRONG JOINT NAME");

		uint8_t len = motors.size();
		commands.pos_cmd.resize(len);
		commands.index.resize(len);
    for(uint8_t j=0;j<len;j++){
		commands.pos_cmd[j]=cmds;
		commands.index[j]=motors[j];
		ROS_INFO("index= %d, cmd=%d",motors[j],cmds);
	  }
		cmd_pub.publish(commands);
		}
