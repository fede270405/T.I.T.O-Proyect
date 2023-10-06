#include "SwichHandler.h"

struct DebouncedButton enter;
struct DebouncedButton up;
struct DebouncedButton down;

void initButton()
{
    gpio_init(ENTER);
    gpio_init(UP);
    gpio_init(DOWN);
    
    gpio_set_dir(ENTER,GPIO_IN);
    gpio_set_dir(UP,GPIO_IN);
    gpio_set_dir(DOWN,GPIO_IN);

    enter.pin = ENTER;
    enter.pin = UP;
    enter.pin = DOWN;
}



bool deBounceButton(struct DebouncedButton * button)
{
    bool currenButtonState =  gpio_get(button->pin);

    uint32_t currentTime = time_us_32();

    if(currenButtonState != button->state)
    {
        if((currentTime - button->last_pressed_time) >= DEBOUNCEDELAYUS)
        {
            button->state = currenButtonState;
            button->last_pressed_time = currentTime;
            if(currenButtonState)
            {
                return true;
            }
        }
    }
    return false;
}