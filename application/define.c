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

  ==============================================================================
  @endverbatim
  */
#include "define.h"
#include "CAN_receive.h"
#include "bsp_delay.h"
#include "bsp_servo_pwm.h"


extern upper_order ai_order;
//Behavior
void knot(void)
{
	servo_pwm_set(1500,1);
	delay_ms(400);
	servo_pwm_set(800,1);
	delay_ms(400);
	
	
}

void shake(void)
{
	//ai_order.wz_set_order = 5;
	//delay_ms(80);
	//ai_order.wz_set_order = -5;
	//delay_ms(80);
}


void forward(void)
{
	ai_order.vx_set_order = FORWARD_SPEED;
	ai_order.vy_set_order = 0;
	ai_order.wz_set_order = 0;	
}
void backward(void)
{
	ai_order.vx_set_order = BACKWARD_SPEED;
	ai_order.vy_set_order = 0;
	ai_order.wz_set_order = 0;	
}
void left(void)
{
	ai_order.vx_set_order = 0;
	ai_order.vy_set_order = LEFT_SPEED;
	ai_order.wz_set_order = 0;	
}
void right(void)
{
	ai_order.vx_set_order = 0;
	ai_order.vy_set_order = RIGHT_SPEED;
	ai_order.wz_set_order = 0;	
}
void stop(void)
{
	ai_order.vx_set_order = 0;
	ai_order.vy_set_order = 0;
	ai_order.wz_set_order = 0;	
}


int pwm_decide_lor(int pwm, int decide)
{
	if (decide == 1) pwm++;
	if (decide == 2) pwm--;
	return pwm;
}

