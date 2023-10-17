#include "Neopixel.h"

uint16_t  ledPwmData_A[(24 * LEDS_MODULE)+60] = {0};
uint16_t  ledPwmData_B[(24 * LEDS_MODULE)+60] = {0};
uint16_t  ledPwmData_C[(24 * LEDS_MODULE)+60] = {0};
uint16_t  ledPwmData_D[(24 * LEDS_MODULE)+60] = {0};
uint16_t  ledPwmData_E[(24 * LEDS_MODULE)+60] = {0};
dma_channel_config pwm_dma_chan_config;
int pwm_dma_chan;


void initLedPorts()
{
    // Channel A
    gpio_set_function(3, GPIO_FUNC_PWM);

    uint slice_num = pwm_gpio_to_slice_num(3);
    pwm_dma_chan = dma_claim_unused_channel(true);

    pwm_config config = pwm_get_default_config();
    config.top = 212;
    pwm_init(slice_num, &config, true);
    pwm_dma_chan_config = dma_channel_get_default_config(pwm_dma_chan);
    channel_config_set_transfer_data_size(&pwm_dma_chan_config, DMA_SIZE_16);
    channel_config_set_read_increment(&pwm_dma_chan_config, true);
    channel_config_set_write_increment(&pwm_dma_chan_config, false);
    channel_config_set_dreq(&pwm_dma_chan_config, DREQ_PWM_WRAP0 + slice_num);

    //Channel B
        gpio_set_function(3, GPIO_FUNC_PWM);

    slice_num = pwm_gpio_to_slice_num(4);
    pwm_dma_chan = dma_claim_unused_channel(true);

    
    config.top = 212;
    pwm_init(slice_num, &config, true);
    pwm_dma_chan_config = dma_channel_get_default_config(pwm_dma_chan);
    channel_config_set_transfer_data_size(&pwm_dma_chan_config, DMA_SIZE_16);
    channel_config_set_read_increment(&pwm_dma_chan_config, true);
    channel_config_set_write_increment(&pwm_dma_chan_config, false);
    channel_config_set_dreq(&pwm_dma_chan_config, DREQ_PWM_WRAP0 + slice_num);

    // Channel C
    slice_num = pwm_gpio_to_slice_num(5);
    pwm_dma_chan = dma_claim_unused_channel(true);

    
    config.top = 212;
    pwm_init(slice_num, &config, true);
    pwm_dma_chan_config = dma_channel_get_default_config(pwm_dma_chan);
    channel_config_set_transfer_data_size(&pwm_dma_chan_config, DMA_SIZE_16);
    channel_config_set_read_increment(&pwm_dma_chan_config, true);
    channel_config_set_write_increment(&pwm_dma_chan_config, false);
    channel_config_set_dreq(&pwm_dma_chan_config, DREQ_PWM_WRAP0 + slice_num);

    // Channel D
    slice_num = pwm_gpio_to_slice_num(21);
    pwm_dma_chan = dma_claim_unused_channel(true);

   
    config.top = 212;
    pwm_init(slice_num, &config, true);
    pwm_dma_chan_config = dma_channel_get_default_config(pwm_dma_chan);
    channel_config_set_transfer_data_size(&pwm_dma_chan_config, DMA_SIZE_16);
    channel_config_set_read_increment(&pwm_dma_chan_config, true);
    channel_config_set_write_increment(&pwm_dma_chan_config, false);
    channel_config_set_dreq(&pwm_dma_chan_config, DREQ_PWM_WRAP0 + slice_num);

    // Channel E
    slice_num = pwm_gpio_to_slice_num(20);
    pwm_dma_chan = dma_claim_unused_channel(true);

    
    config.top = 212;
    pwm_init(slice_num, &config, true);
    pwm_dma_chan_config = dma_channel_get_default_config(pwm_dma_chan);
    channel_config_set_transfer_data_size(&pwm_dma_chan_config, DMA_SIZE_16);
    channel_config_set_read_increment(&pwm_dma_chan_config, true);
    channel_config_set_write_increment(&pwm_dma_chan_config, false);
    channel_config_set_dreq(&pwm_dma_chan_config, DREQ_PWM_WRAP0 + slice_num);
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
            dma_channel_configure(pwm_dma_chan, &pwm_dma_chan_config, &pwm_hw->slice[slice_num].cc,
                ledPwmData_A,  (24 * LEDS_MODULE)+60, true );
        break;
        case B:
             slice_num = pwm_gpio_to_slice_num(4);
            dma_channel_configure(pwm_dma_chan, &pwm_dma_chan_config, &pwm_hw->slice[slice_num].cc,
                ledPwmData_B,  (24 * LEDS_MODULE)+60, true );           
        break;
        case C:
            slice_num = pwm_gpio_to_slice_num(5);
            dma_channel_configure(pwm_dma_chan, &pwm_dma_chan_config, &pwm_hw->slice[slice_num].cc,
                ledPwmData_C,  (24 * LEDS_MODULE)+60, true );                 
        break;
        case D:
             slice_num = pwm_gpio_to_slice_num(20);
            dma_channel_configure(pwm_dma_chan, &pwm_dma_chan_config, &pwm_hw->slice[slice_num].cc,
                ledPwmData_D,  (24 * LEDS_MODULE)+60, true );                
        break;  
        case E:
             slice_num = pwm_gpio_to_slice_num(21);
            dma_channel_configure(pwm_dma_chan, &pwm_dma_chan_config, &pwm_hw->slice[slice_num].cc,
                ledPwmData_E,  (24 * LEDS_MODULE)+60, true );                
        break;               
    }    

}

 void setLedsModule(struct Leds leds[],int8_t channel)
 {
        int i = 0;
        int x = 0;
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

