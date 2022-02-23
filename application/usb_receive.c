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
//----------include
#include "usb_receive.h"
#include "usbd_cdc_if.h"
#include "chassis_movement.h"
#include "usb_device.h"
#include <stdio.h>
#include <stdarg.h>
#include "string.h"
#include "define.h"
#include "cmsis_os.h"

//----------define

upper_order ai_order;

//----------function
static void usbtask_init(usb_receive_t *usb_init);
static void usb_loop(usb_receive_t *usb_loop);

//----------main task----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
static uint8_t usb_buf[256];
uint8_t buffer[64];
usb_receive_t usb;
void usb_receive(void const *pvParameters)
{

	vTaskDelay(usb_task_init_time);
	MX_USB_DEVICE_Init();
	usbtask_init(&usb);
	while(1)
	{
		

		CDC_Transmit_FS(usb_buf, 256);

		usb_loop(&usb);
		//HERE CHANGE THE DATA IN UPPER AI, BECAREFUL DO NOT FALL INTO LOOP, THIS LOGIC MUST PASS ON
		
		
		//os delay
		vTaskDelay(usb_task_control_time);
		

	}
	





}//end task
//----------END main task----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

static void usbtask_init(usb_receive_t *usb_init)
{
	usb_init->usb_RC = get_remote_control_point();
	ai_order.test = 0;
	ai_order.vx_set_order = 0.0f;
	ai_order.vy_set_order = 0.0f;
	ai_order.wz_set_order = 0.0f;

}


static void usb_loop(usb_receive_t *usb_loop)
{

	//copy buffer into ai_order
	ai_order.test = buffer[0];
	if(ai_order.test == 0)
	{
	ai_order.control_mode = 0;//none
	ai_order.vx_set_order = 0;
	ai_order.vy_set_order = 0;
	ai_order.wz_set_order = 0;
	ai_order.d1 = 0;
	ai_order.d2 = 108;
	ai_order.d3 = 96;
	ai_order.d4 = 90;
	ai_order.d5 = 0;
	ai_order.d6 = 233;
	}
	else if(ai_order.test == 1)
	{
	ai_order.chassis_command = buffer[1];
	ai_order.control_mode = buffer[2];
	ai_order.vx_set_order = (buffer[11]-100.0f)/20.0f;
	ai_order.vy_set_order = (buffer[12]-100.0f)/20.0f;
	ai_order.wz_set_order = (buffer[13]-100.0f)/20.0f;
	
	//ai_order.pwm_one = buffer[21] * 26;
	//ai_order.pwm_two = buffer[22] * 26;
	//ai_order.pwm_three = buffer[23] * 26; 
	//ai_order.pwm_four = buffer[24] * 26; 
	//ai_order.pwm_five = buffer[25] * 26; 
	//ai_order.pwm_six= buffer[26] * 26; 
	
	ai_order.dynamic_x = buffer[28];
	ai_order.dynamic_y = buffer[29];
	
	ai_order.d1 = buffer[41];
	ai_order.d2 = buffer[42];
	ai_order.d3 = buffer[43];
	ai_order.d4 = buffer[44];
	ai_order.d5 = buffer[45];
	ai_order.d6 = buffer[46];
	}


	
	


}







