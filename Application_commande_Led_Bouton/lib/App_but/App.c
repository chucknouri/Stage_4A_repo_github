#include "button.h"
#include "gpio.h"
#include "template_state.h"
#include "App.h"
#include "routing_table.h"
#include "main.h"
#include "luos.h"

container_t *but_app;
int16_t id_but;
int16_t id_led;


static void App_MsgHandler(container_t *container, msg_t *msg);

typedef enum
{
     TEST_APP = LUOS_LAST_TYPE
} App_type_t;

void App_Init(void)
{
    revision_t revision = {.Major = 1, .Minor = 0, .Build = 0};
    // Container creation following template
    but_app = Luos_CreateContainer(App_MsgHandler, TEST_APP, "button_app", revision);
    uint32_t i = 0;
    while(i<100000)
    {
        i++;
    } 
    RoutingTB_DetectContainers(but_app);

    //Get the ID of our LED and button from the routing table
    id_but = RoutingTB_IDFromAlias("button");
    id_led = RoutingTB_IDFromAlias("rgb_led_mod");
    LUOS_ASSERT(id_led!=0);
    LUOS_ASSERT(id_but!=0);
}   

void App_Loop(void)
{  
    static uint32_t time=0;
    if((Luos_GetSystick()-time) >=10)
    {
        msg_t msg_but;
        msg_but.header.target_mode = IDACK;
        msg_but.header.target = id_but;
        msg_but.header.cmd = ASK_PUB_CMD ;
        msg_but.header.size = 0;
        Luos_SendMsg(but_app, &msg_but);
        time=Luos_GetSystick();
    }
}

static void App_MsgHandler(container_t *container, msg_t *msg)
{
    if (msg->header.cmd == IO_STATE)
    {
        msg_t msg_led;
        msg_led.header.cmd         = COLOR;
        msg_led.header.target_mode = IDACK;
        msg_led.header.target      = id_led;
        msg_led.header.size        = 3;
        if (msg->data[0]==true)
        {
            msg_led.data[0]            = 255;
            msg_led.data[1]            = 0;
            msg_led.data[2]            = 0;
        }
        else 
        {
            msg_led.data[0]            = 0;
            msg_led.data[1]            = 0;
            msg_led.data[2]            = 0;

        }
        Luos_SendMsg(but_app, &msg_led);
        return;
    }
}


