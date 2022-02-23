/**
  * @brief      ,
  *             
  * @note       
  * @history
  *  Version    Date            Author          Modification
  *  V1.0.0     2021    		 David           1. ���
  *
  @verbatim
  ==============================================================================

  ==============================================================================
  @endverbatim
  */

#ifndef DEFINE_H
#define DEFINE_H
#include "struct_typedef.h"
#include "bsp_buzzer.h"
#include "user_lib.h"
//-------------Testrun

#define buzzer_high() buzzer_on(95, 10000);
#define buzzer_low() buzzer_on(31, 19999);

//-------------AI MAIN CONTROL 
typedef struct
{
	uint16_t test;//[0]for test only, ignore it
	uint16_t chassis_command; //[1]
	uint16_t control_mode;//[2]
	
	fp32 vx_set_order; //[11]
	fp32 vy_set_order; //[12]
	fp32 wz_set_order; //[13]
	
	//direct servo control
	uint16_t pwm_one;  //[21]
	uint16_t pwm_two;  //[22]
	uint16_t pwm_three; //[23]
	uint16_t pwm_four; //[24]
	uint16_t pwm_five; //[25]
	uint16_t pwm_six; //[26]
	
	//indirect servo control
	fp32 dynamic_x; //28
	fp32 dynamic_y; //29
	
	
	//^x  <-y->
	fp32 x_point; //[31]
	fp32 y_point; //[32]
	fp32 z_point; //[33]
	
	uint16_t d1;//[41]
	uint16_t d2;//[42]
	uint16_t d3;//[43]
	uint16_t d4;//[44]
	uint16_t d5;//[45]
	uint16_t d6;//[46]
	
	int rc_is_alive ;
	
	
	
	

}upper_order; //store all the data from master machine, this define all data that will be pass from master

//-------------BEHAVIOR PARAM
#define FORWARD_SPEED 1.0f
#define BACKWARD_SPEED -1.0f
#define LEFT_SPEED -0.7f
#define RIGHT_SPEED 0.7f
//-------------BEHAVIOR

#define yaw_turn_left CAN_cmd_gimbal(8000,0,0,0)
#define yaw_turn_right CAN_cmd_gimbal(-8000,0,0,0)


#define KNOT knot()
#define SHAKE shake()
#define FORWARD forward()
#define BACKWARD backward()
#define LEFT left()
#define RIGHT right()
#define STOP stop()

//-------------RTOS

//control interval
#define chassis_task_control_time 3
#define gimbal_task_control_time 2
#define usb_task_control_time 1

//init time
#define chassis_task_init_time 357
#define gimbal_task_init_time 201
#define usb_task_init_time 197


//-------------RC PARAM
//rocker value deadline
//ҡ������(��ҡ�����м�value���ܲ���0)
#define RC_DEADLINE 10



//-------------CHASSIS PARAM

//the channel num of controlling vertial speed 
//ǰ���ң����ͨ������
#define CHASSIS_X_CHANNEL 1
//the channel num of controlling horizontal speed
//���ҵ�ң����ͨ������
#define CHASSIS_Y_CHANNEL 0
//the channel num of controlling rotating speed
//��ת��ң����ͨ������
#define CHASSIS_WZ_CHANNEL 2

#define CHASSIS_ACCEL_X_NUM 0.1666666667f
#define CHASSIS_ACCEL_Y_NUM 0.3333333333f
//chassis forward or back max speed
//�����˶��������ǰ���ٶ�
#define NORMAL_MAX_CHASSIS_SPEED_X 2.0f
//chassis left or right max speed
//�����˶��������ƽ���ٶ�
#define NORMAL_MAX_CHASSIS_SPEED_Y 1.5f

//rocker value (max 660) change to vertial speed (m/s) 
//ң����ǰ��ҡ�ˣ�max 660��ת���ɳ���ǰ���ٶȣ�m/s���ı���
//660*0.006= 3.96m/s
#define CHASSIS_VX_RC_SEN 0.006f
//rocker value (max 660) change to horizontal speed (m/s)
//ң��������ҡ�ˣ�max 660��ת���ɳ��������ٶȣ�m/s���ı���
#define CHASSIS_VY_RC_SEN 0.005f
//in not following yaw angle mode, rocker value change to rotation speed
//��������̨��ʱ�� ң������yawң�ˣ�max 660��ת���ɳ�����ת�ٶȵı���
#define CHASSIS_WZ_RC_SEN 0.01f

#define MODE_CHANNEL 0 //right = 0, left = 1

#define MOTOR_SPEED_TO_CHASSIS_SPEED_VX 0.25f
#define MOTOR_SPEED_TO_CHASSIS_SPEED_VY 0.25f
#define MOTOR_SPEED_TO_CHASSIS_SPEED_WZ 0.25f

//m3508 rmp change to chassis speed,
//m3508ת���ɵ����ٶ�(m/s)�ı�����
#define M3508_MOTOR_RPM_TO_VECTOR 0.000415809748903494517209f
#define CHASSIS_MOTOR_RPM_TO_VECTOR_SEN M3508_MOTOR_RPM_TO_VECTOR
#define CHASSIS_CONTROL_FREQUENCE 500.0f

#define MOTOR_DISTANCE_TO_CENTER 0.2f

#define INS_YAW_ADDRESS_OFFSET    0
#define INS_PITCH_ADDRESS_OFFSET  1
#define INS_ROLL_ADDRESS_OFFSET   2

//single chassis motor max speed
//�������̵������ٶ�
#define MAX_WHEEL_SPEED 4.0f
//chassis forward or back max speed
//�����˶��������ǰ���ٶ�
#define NORMAL_MAX_CHASSIS_SPEED_X 2.0f
//chassis left or right max speed
//�����˶��������ƽ���ٶ�
#define NORMAL_MAX_CHASSIS_SPEED_Y 1.5f
#define CHASSIS_WZ_SET_SCALE 0.1f

//chassis motor speed PID
//���̵���ٶȻ�PID
#define M3505_MOTOR_SPEED_PID_KP 15000.0f
#define M3505_MOTOR_SPEED_PID_KI 10.0f
#define M3505_MOTOR_SPEED_PID_KD 0.0f
#define M3505_MOTOR_SPEED_PID_MAX_OUT MAX_MOTOR_CAN_CURRENT
#define M3505_MOTOR_SPEED_PID_MAX_IOUT 2000.0f

//����3508���can���͵���ֵ
#define MAX_MOTOR_CAN_CURRENT 16000.0f
//����3508���can���͵���ֵ
#define MAX_MOTOR_CAN_CURRENT 16000.0f



//-------------GIMBAL PARAM
#define node1_rawpoint 900 //500 ~ 2500
#define node2_rawpoint 1000
#define node3_rawpoint 2100
#define node4_rawpoint 1540
#define node5_rawpoint 910
#define node6_rawpoint 2200










void knot(void);
void shake(void);

void forward(void);
void backward(void);
void left(void);
void right(void);
void stop(void);
//chassis


int pwm_decide_lor(int pwm, int decide);












#endif

