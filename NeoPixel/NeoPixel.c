#include "Neopixel.h"

uint16_t  ledPwmData_A[(24 * LEDS_MODULE)+60] = {0};
uint16_t  ledPwmData_B[(24 * LEDS_MODULE)+60] = {0};
uint16_t  ledPwmData_C[(24 * LEDS_MODULE)+60] = {0};
uint16_t  ledPwmData_D[(24 * LEDS_MODULE)+60] = {0};
uint16_t  ledPwmData_E[(24 * LEDS_MODULE)+60] = {0};
dma_channel_config pwm_dma_chan_config[5];
int pwm_dma_chan[5];


void initLedPorts()
{
    // Channel A
    gpio_set_function(3, GPIO_FUNC_PWM);

    uint slice_num = pwm_gpio_to_slice_num(3);
    pwm_dma_chan[0] = dma_claim_unused_channel(true);

    pwm_config config = pwm_get_default_config();
    config.top = 212;
    pwm_init(slice_num, &config, true);
    pwm_dma_chan_config[0] = dma_channel_get_default_config(pwm_dma_chan[0]);
    channel_config_set_transfer_data_size(&pwm_dma_chan_config[0], DMA_SIZE_16);
    channel_config_set_read_increment(&pwm_dma_chan_config[0], true);
    channel_config_set_write_increment(&pwm_dma_chan_config[0], false);
    channel_config_set_dreq(&pwm_dma_chan_config[0], DREQ_PWM_WRAP0 + slice_num);

    //Channel B
    gpio_set_function(4, GPIO_FUNC_PWM);

    slice_num = pwm_gpio_to_slice_num(4);
    pwm_dma_chan[1] = dma_claim_unused_channel(true);

    
    config.top = 212;
    pwm_init(slice_num, &config, true);
    pwm_dma_chan_config[1] = dma_channel_get_default_config(pwm_dma_chan[1]);
    channel_config_set_transfer_data_size(&pwm_dma_chan_config[1], DMA_SIZE_16);
    channel_config_set_read_increment(&pwm_dma_chan_config[1], true);
    channel_config_set_write_increment(&pwm_dma_chan_config[1], false);
    channel_config_set_dreq(&pwm_dma_chan_config[1], DREQ_PWM_WRAP0 + slice_num);

    // Channel C
    gpio_set_function(5, GPIO_FUNC_PWM);
    slice_num = pwm_gpio_to_slice_num(5);
    pwm_dma_chan[2] = dma_claim_unused_channel(true);

    
    config.top = 212;
    pwm_init(slice_num, &config, true);
    pwm_dma_chan_config[2] = dma_channel_get_default_config(pwm_dma_chan[2]);
    channel_config_set_transfer_data_size(&pwm_dma_chan_config[2], DMA_SIZE_16);
    channel_config_set_read_increment(&pwm_dma_chan_config[2], true);
    channel_config_set_write_increment(&pwm_dma_chan_config[2], false);
    channel_config_set_dreq(&pwm_dma_chan_config[2], DREQ_PWM_WRAP0 + slice_num);

    dma_channel_configure(pwm_dma_chan[2], &pwm_dma_chan_config[2], &pwm_hw->slice[slice_num].cc,
                ledPwmData_C,  (24 * LEDS_MODULE)+60, false );  

    // Channel D
    gpio_set_function(21, GPIO_FUNC_PWM);
    slice_num = pwm_gpio_to_slice_num(21);
    pwm_dma_chan[3] = dma_claim_unused_channel(true);

   
    config.top = 212;
    pwm_init(slice_num, &config, true);
    pwm_dma_chan_config[3] = dma_channel_get_default_config(pwm_dma_chan[3]);
    channel_config_set_transfer_data_size(&pwm_dma_chan_config[3], DMA_SIZE_16);
    channel_config_set_read_increment(&pwm_dma_chan_config[3], true);
    channel_config_set_write_increment(&pwm_dma_chan_config[3], false);
    channel_config_set_dreq(&pwm_dma_chan_config[3], DREQ_PWM_WRAP0 + slice_num);

    // Channel E
    gpio_set_function(20, GPIO_FUNC_PWM);
    slice_num = pwm_gpio_to_slice_num(20);
    pwm_dma_chan[4] = dma_claim_unused_channel(true);

    
    config.top = 212;
    pwm_init(slice_num, &config, true);
    pwm_dma_chan_config[4] = dma_channel_get_default_config(pwm_dma_chan[4]);
    channel_config_set_transfer_data_size(&pwm_dma_chan_config[4], DMA_SIZE_16);
    channel_config_set_read_increment(&pwm_dma_chan_config[4], true);
    channel_config_set_write_increment(&pwm_dma_chan_config[4], false);
    channel_config_set_dreq(&pwm_dma_chan_config[4], DREQ_PWM_WRAP0 + slice_num);
}

void setLedPwmData(struct Leds leds,uint8_t ledNum, uint8_t channel)
{
    uint32_t ledData =  leds.r | leds.g <<8 | leds.b <<16;
    for(int i = (24 + ((24 * ledNum)-24)); i<(24 + (24 * ledNum)); i++)
    {
        if((ledData >> (i-(24 + ((24 * ledNum)-24))) ) & 0x01)
        {
            switch(channel)
            {
                case A:
                    ledPwmData_A[i] = 161;
                break;
                case B:
                    ledPwmData_B[i] = 161;
                break;
                case C:
                    ledPwmData_C[i] = 161;
                break;
                case D:
                    ledPwmData_D[i] = 161;
                break;  
                case E:
                    ledPwmData_E[i] = 161;
                break;               
            }
            
        }
        else
        {
            switch(channel)
            {
                case A:
                    ledPwmData_A[i] = 51;
                break;
                case B:
                    ledPwmData_B[i] = 51;
                break;
                case C:
                    ledPwmData_C[i] = 51;
                break;
                case D:
                    ledPwmData_D[i] = 51;
                break;  
                case E:
                    ledPwmData_E[i] = 51;
                break;               
            }
        }    
    }
}

void sendLedPwmData(uint8_t channel)
{ 
    uint slice_num;
    switch(channel)
    {
        case A:
             slice_num = pwm_gpio_to_slice_num(3);
            dma_channel_configure(pwm_dma_chan[0], &pwm_dma_chan_config[0], &pwm_hw->slice[slice_num].cc,
                ledPwmData_A,  (24 * LEDS_MODULE)+60, true );
        break;
        case B:

            gpio_set_function(4, GPIO_FUNC_PWM);
            gpio_set_function(5, GPIO_FUNC_NULL);
            gpio_set_function(20, GPIO_FUNC_NULL);
            gpio_set_function(21, GPIO_FUNC_NULL);

             slice_num = pwm_gpio_to_slice_num(4);
            dma_channel_configure(pwm_dma_chan[1], &pwm_dma_chan_config[1], &pwm_hw->slice[slice_num].cc,
                ledPwmData_B,  (24 * LEDS_MODULE)+60, true );           
        break;
        case C:
        gpio_set_function(4, GPIO_FUNC_NULL);
            gpio_set_function(5, GPIO_FUNC_PWM);
            gpio_set_function(20, GPIO_FUNC_NULL);
            gpio_set_function(21, GPIO_FUNC_NULL);
            slice_num = pwm_gpio_to_slice_num(5);
            dma_channel_set_read_addr(pwm_dma_chan[2], ledPwmData_C, true);
        break;
        case D:
        gpio_set_function(4, GPIO_FUNC_NULL);
            gpio_set_function(5, GPIO_FUNC_NULL);
            gpio_set_function(20, GPIO_FUNC_NULL);
            gpio_set_function(21, GPIO_FUNC_PWM);
             slice_num = pwm_gpio_to_slice_num(21);
            dma_channel_configure(pwm_dma_chan[3], &pwm_dma_chan_config[3], &pwm_hw->slice[slice_num].cc,
                ledPwmData_D,  (24 * LEDS_MODULE)+60, true );                
        break;  
        case E:
        gpio_set_function(4, GPIO_FUNC_NULL);
            gpio_set_function(5, GPIO_FUNC_NULL);
            gpio_set_function(20, GPIO_FUNC_PWM);
            gpio_set_function(21, GPIO_FUNC_NULL);
             slice_num = pwm_gpio_to_slice_num(20);
            dma_channel_configure(pwm_dma_chan[4], &pwm_dma_chan_config[4], &pwm_hw->slice[slice_num].cc,
                ledPwmData_E,  (24 * LEDS_MODULE)+60, true );                
        break;               
    }    

}

 void setLedsModule(struct Leds leds[],int8_t channel)
 {
        int i = 0;
        int x = channel*2;
        int y = 0;
        int z = 0;
        while(i<LEDS_MODULE)
        {
            for(z = 0 ;z<LED_STRIP;z++)
            {
                setLedPwmData(leds[CALCULATE_INDEX(x,y,z)],i++,channel);
            }
            x++;
            for(z = 9;z>=0;z--)
            {
                setLedPwmData(leds[CALCULATE_INDEX(x,y,z)],i++,channel);
            }
            y++;
            x--;
        }
 }

void displayLedCube(struct Leds leds[])
{
    setLedsModule(leds,A);
    setLedsModule(leds,B);
    setLedsModule(leds,C);
    setLedsModule(leds,D);
    setLedsModule(leds,E);
    
    sendLedPwmData(A);
    while(dma_channel_is_busy(pwm_dma_chan[0])){}
    sendLedPwmData(B);
    while(dma_channel_is_busy(pwm_dma_chan[1])){}
    sendLedPwmData(C);
    while(dma_channel_is_busy(pwm_dma_chan[2])){}
    sendLedPwmData(D);
    while(dma_channel_is_busy(pwm_dma_chan[3])){}
    sendLedPwmData(E);
    while(dma_channel_is_busy(pwm_dma_chan[4])){}
}

void clearLEDMatrix()
{
    struct Leds leds[1000];

    memset(leds,0,sizeof(struct Leds)*1000);
    setLedsModule(leds,A);
    setLedsModule(leds,B);
    setLedsModule(leds,C);
    setLedsModule(leds,D);
    setLedsModule(leds,E);
    
    sendLedPwmData(A);
    while(dma_channel_is_busy(pwm_dma_chan[0])){}
    sendLedPwmData(B);
    while(dma_channel_is_busy(pwm_dma_chan[1])){}
    sendLedPwmData(C);
    while(dma_channel_is_busy(pwm_dma_chan[2])){}
    sendLedPwmData(D);
    while(dma_channel_is_busy(pwm_dma_chan[3])){}
    sendLedPwmData(E);
    while(dma_channel_is_busy(pwm_dma_chan[4])){}
}