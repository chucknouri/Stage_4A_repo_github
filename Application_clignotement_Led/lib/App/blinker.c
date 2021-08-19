#include "blinker.h"
#include "main.h"

#define BLINKTIME 200

container_t *app;

typedef enum
{
    BLINKER_APP = LUOS_LAST_TYPE
} App_type_t;

int8_t id_led;
unsigned long myTime; //Used to keep track of time
uint8_t led_last_state = 0; //Is the LED on or off?

static void Blinker_MsgHandler(container_t *container, msg_t *msg);

void Blinker_Init(void)
{
    revision_t revision = {.Major = 1, .Minor = 0, .Build = 0};
    app = Luos_CreateContainer(Blinker_MsgHandler, BLINKER_APP, "App_Blinker", revision);
    uint32_t i = 0;
    while(i<100000)
    {
        i++;
    }

    //Detect all containers of your network and create a routing_table
    RoutingTB_DetectContainers(app);

    //Get the ID of our LED from the routing table
    id_led = RoutingTB_IDFromAlias("rgb_led_mod");

    //Set our next timeout to now plus BLINKTIME milliseconds
    myTime = Luos_GetSystick() + BLINKTIME;
}

void Blinker_Loop(void)
{
    //Check to see if we have overshot our counter
    if (myTime < Luos_GetSystick())
    {

        //Reset the counter
        myTime = Luos_GetSystick() + BLINKTIME;

        //Invert the LED state
        led_last_state = (led_last_state == 1 ? 0: 1);

        //Now send a message
        msg_t led_msg;
        led_msg.header.target = id_led; //We are sending this to the LED
        led_msg.header.cmd = COLOR; //We are specifying an IO state (on or off)
        led_msg.header.target_mode = IDACK; //We are asking for an acknowledgement
        led_msg.header.size = 3; //Our message only contains one character, the IO state
        if (led_last_state==1)
        {
            led_msg.data[0] = 255;
            led_msg.data[1] = 155;
            led_msg.data[2] = 100;
            
             //The I/O state of the LED to be sent (1 or 0, on or off)
        }
        else{
            led_msg.data[0] = 0;
            led_msg.data[1] = 0;
            led_msg.data[2] = 0;
        }
        Luos_SendMsg(app, &led_msg); //Now that we have the elements, send the message
    }
}

static void Blinker_MsgHandler(container_t *container, msg_t *msg)
{
}