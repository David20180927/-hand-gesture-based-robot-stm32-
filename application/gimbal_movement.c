/**
  * @brief      ,
  *             
  * @note       
  * @history
  *  Version    Date            Author          Modification
  *  V1.0.0     2021    		 David           1. Íê³É
  *
  @verbatim
  ==============================================================================



                                                         ------
						--s4(pitch)------s5(roll)---s6(grab)
					  ---								 ------
					---
					---
				--s3(pitch)--
				---
               ---                         
         -s2(pitch)-                         
    -s1(yaw)-
---------------
---chassis-----
---------------


...dbus
...
... s1
... s2
... s3
... s4
... s5
... s6
  ==============================================================================
  @endverbatim
  */
//----------include
#include "gimbal_movement.h"
#include "chassis_movement.h"
#include "usb_receive.h"
#include "cmsis_os.h"
#include "bsp_servo_pwm.h"
#include "CAN_Receive.h"
#include <stdio.h>
//----------define
extern upper_order ai_order;
//----------function
void gimbal_set(gimbal_control_t *gimbal);
static void gimbal_init(gimbal_control_t *gimbal_move_init);
static void gimbal_set_mode(gimbal_control_t *gimbal_mode); //mode change between manual and auto
static void gimbal_data_determine(gimbal_control_t *gimbal_data);
static void angle_to_pwm(gimbal_control_t *gimbal_data);
//----------main task----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
gimbal_control_t gimbal;
void gimbal_movement(void const *pvParameters)
{
	vTaskDelay(gimbal_task_init_time);
	gimbal_init(&gimbal);

	while(1)
	{
		gimbal_set_mode(&gimbal);
		gimbal_data_determine(&gimbal);
		gimbal_set(&gimbal);
		
		
		//os delay
		vTaskDelay(gimbal_task_control_time);
	}









}
//end task
//----------END main task----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//init gimbal data
static void gimbal_init(gimbal_control_t *init)
{
    init->gimbal_rc_ctrl = get_remote_control_point();
	init->gimbal_mode = GIMBAL_MID;
}

static void gimbal_set_mode(gimbal_control_t *gimbal_mode)
{
    if (gimbal_mode == NULL)
    {
        return;
    }
	gimbal_mode->gimbal_mode = GIMBAL_AUTO;
	if (switch_is_mid(gimbal_mode->gimbal_rc_ctrl->rc.s[MODE_CHANNEL]))
    {
      
		gimbal_mode->gimbal_mode = GIMBAL_MID; //write into struct 
    }
    else if (switch_is_down(gimbal_mode->gimbal_rc_ctrl->rc.s[MODE_CHANNEL]))
    {
        
		gimbal_mode->gimbal_mode = GIMBAL_AUTO;
    }
    else if (switch_is_up(gimbal_mode->gimbal_rc_ctrl->rc.s[MODE_CHANNEL]))
    {
        
		gimbal_mode->gimbal_mode = GIMBAL_MANUAL;
    }
	
	
		
		
	
	
}

static void gimbal_data_determine(gimbal_control_t *gimbal_data)
{
	if (gimbal_data == NULL)
    {
        return;
    }

    if (gimbal_data->gimbal_mode == GIMBAL_MID)
    {//500 ~ 2500
        gimbal_data->arm_servo.s1 = node1_rawpoint;
		gimbal_data->arm_servo.s2 = node2_rawpoint;
		gimbal_data->arm_servo.s3 = node3_rawpoint;
		gimbal_data->arm_servo.s4 = node4_rawpoint;
		gimbal_data->arm_servo.s5 = node5_rawpoint;
		gimbal_data->arm_servo.s6 = node6_rawpoint;
    }
    else if (gimbal_data->gimbal_mode == GIMBAL_MANUAL)
    {
		if (switch_is_mid(gimbal_data->gimbal_rc_ctrl->rc.s[1]))
		{
			//gimbal_data->arm_servo.s1 = 1500;
		}
		else if (switch_is_down(gimbal_data->gimbal_rc_ctrl->rc.s[1]))
		{
			//gimbal_data->arm_servo.s1 = 800;
		}
		else if (switch_is_up(gimbal_data->gimbal_rc_ctrl->rc.s[1]))
		{
			//gimbal_data->arm_servo.s1 = 1000;
		}
			
    }
    else if (gimbal_data->gimbal_mode == GIMBAL_AUTO)
    {
		angle_to_pwm(gimbal_data);
		gimbal_data->arm_servo.s1 = ai_order.pwm_one; // test
		gimbal_data->arm_servo.s2 = ai_order.pwm_two;
		gimbal_data->arm_servo.s3 = ai_order.pwm_three;
		gimbal_data->arm_servo.s4 = ai_order.pwm_four;
		gimbal_data->arm_servo.s5 = ai_order.pwm_five;
		gimbal_data->arm_servo.s6 = ai_order.pwm_six;
    }




}


static void angle_to_pwm(gimbal_control_t *gimbal_data)
{
	//if (ai_order.pwm_one == 0|| ai_order.pwm_one == 1 || ai_order.pwm_one == 2)ai_order.pwm_one = int16_constrain(pwm_decide_lor(ai_order.pwm_one,ai_order.d1),600,2400);
	//else 
	ai_order.pwm_one = 900;
	ai_order.pwm_two = 1900 - (ai_order.d2*750/90);
	ai_order.pwm_three = (ai_order.d3*1000/120)+1300;
	ai_order.pwm_four = (ai_order.d4)*1720/180 +680;
	ai_order.pwm_five = int16_constrain(pwm_decide_lor(ai_order.pwm_five,ai_order.d5),420,2500);
	ai_order.pwm_six = (ai_order.d6)*750/250 +1500;
	
	return;
}













void gimbal_set(gimbal_control_t *gimbal)
{
	//servo_set
	servo_pwm_set(gimbal->arm_servo.s1,2);
	servo_pwm_set(gimbal->arm_servo.s2,3);
	servo_pwm_set(gimbal->arm_servo.s3,4);
	servo_pwm_set(gimbal->arm_servo.s4,5);
	servo_pwm_set(gimbal->arm_servo.s5,6);
	servo_pwm_set(gimbal->arm_servo.s6,7);
	//motor_set
	//CAN_cmd_gimbal(gimbal->gimbal_yaw_motor.current_set, 0,0,0);
}














