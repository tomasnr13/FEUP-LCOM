#include <lcom/lcf.h>


#define BIT(n)  (1 << (n))


//PORTOS

#define RTC_ADDR_REG 0x70
#define RTC_DATA_REG 0x71

//TIME

#define RTC_SECONDS 0
#define RTC_ALARM_SECONDS 1
#define RTC_MINUTES 2
#define RTC_ALARM_MINUTES 3
#define RTC_HOURS 4
#define RTC_ALARM_HOURS 5

#define RTC_WEEK_DAY 6
#define RTC_MONTH_DATE 7
#define RTC_MONTH   8
#define RTC_YEAR   9



//REGISTER A

#define RTC_REG_A 10
#define UIP_REG_A BIT(7)


//REGISTER B

#define RTC_REG_B 11
#define SET_REG_B BIT(7)
#define PIE       BIT(6)
#define AIE       BIT(5)
#define UIE       BIT(4)
#define SQWE      BIT(3)


//REGISTER C

#define RTC_REG_C 12
#define IRQF    BIT(7)
#define PF BIT(6) 
#define AF BIT(5)
#define UF BIT(4)


//LINHA DE INTERRUPÇÃO DO RTC

#define IRQ8 8




