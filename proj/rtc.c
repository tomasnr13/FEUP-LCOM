#include "rtc.h"

#include <assert.h>



int hook_id_rtc;

uint8_t day_time[3];


uint8_t Convert_bcd_to_decimal(uint8_t bcd)
{
    uint8_t dec;

    assert(((bcd & 0xF0) >> 4) < 10);  // More significant nybble is valid
    assert((bcd & 0x0F) < 10);         // Less significant nybble is valid
    dec = ((bcd & 0xF0) >> 4) * 10 + (bcd & 0x0F);

    return dec;
}


int rtc_subscribe_int(uint8_t* bit_no)
{
    
    hook_id_rtc = *bit_no;

    if(sys_irqsetpolicy(IRQ8 ,  IRQ_REENABLE|IRQ_EXCLUSIVE ,&hook_id_rtc) != OK)
    {
        printf("[ERROR] Could not subscribe the rtc interrupts\n");
        return 1;
    }

    
    enable_update_interrupts();


    //if everything went as expected

    return 0;
    
}

int rtc_unsubscribe_int()
{
    if(sys_irqrmpolicy(&hook_id_rtc) != OK)
    {
        printf("[ERROR] Could not unsubscribe rtc interrupts \n");
        return 1;
    }

    disable_update_interrupts();

    //if everything went as expected

    return 0;
}



//ENABLE PROCESSOR INTERRUPTS

void enable()
{
    sys_irqenable(&hook_id_rtc);
}

//Disable Processor Interrupts

void disable()
{
    sys_irqdisable(&hook_id_rtc);
}


void wait_valid_rtc(void)
{
    uint32_t regA = 0;
    do {
        disable();
        sys_outb(RTC_ADDR_REG, RTC_REG_A);
        sys_inb(RTC_DATA_REG, &regA);
        enable();
    } while (regA & UIP_REG_A);

}


void  rtc_read_reg(uint8_t reg)
{

    uint32_t reg_cont;

    wait_valid_rtc();



    //PARA LER OS REGISTOS DO RTC , primeiro precisamos de escrever o endereço do registo para o porto 0x70
    //----------------------------- Segundo precisamos de ler o conteudo do registo a partir do porto 0x71


    sys_outb(RTC_ADDR_REG , reg); //escrever o endereço

    sys_inb(RTC_DATA_REG , &reg_cont); //RECEBER O CONTEUDO


    if(reg == RTC_SECONDS)
    {
        day_time[0] = Convert_bcd_to_decimal(reg_cont);
    }

    else if(reg == RTC_MINUTES)
    {
        day_time[1] = Convert_bcd_to_decimal(reg_cont);
    }

    else if(reg == RTC_HOURS)
    {
        day_time[2] = Convert_bcd_to_decimal(reg_cont);
    }

}

int disable_update_interrupts()
{
    uint32_t reg_cont;


    sys_outb(RTC_ADDR_REG, RTC_REG_B);


    sys_inb(RTC_DATA_REG, &reg_cont);

    reg_cont = reg_cont & (~UIE);


    sys_outb(RTC_ADDR_REG, RTC_REG_B);

    sys_outb(RTC_DATA_REG, reg_cont);

    return 0;

}


int enable_update_interrupts() {
    uint32_t reg_cont;


    sys_outb(RTC_ADDR_REG, RTC_REG_B);


    sys_inb(RTC_DATA_REG, &reg_cont);

    reg_cont = reg_cont | UIE;


    sys_outb(RTC_ADDR_REG, RTC_REG_B);

    sys_outb(RTC_DATA_REG, reg_cont);

    return 0;
}


void rtc_ih()
{

    //Interrupt handler do rtc
    //PRIMEIRO TEREMOS QUE LER O REGISTO C , PARA SABER SE TEMOS UMA UPDATE INTERRUPT PENDING

    uint32_t reg_cont;

    sys_outb(RTC_ADDR_REG , RTC_REG_C);

    sys_inb(RTC_DATA_REG , &reg_cont);

    if(reg_cont & UF)
    {
        rtc_read_reg(RTC_HOURS);
        rtc_read_reg(RTC_MINUTES);
        rtc_read_reg(RTC_SECONDS);

    }
    

}








