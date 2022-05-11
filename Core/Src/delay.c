#include "delay.h"
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
void _delay_ms(unsigned int __ms)
{
	HAL_Delay(__ms);
	// while(__ms)
	// {
	// 	_delay_us(1000);
	// 	__ms--;
	// }
}
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
void _delay_us(unsigned int __us)
{
	unsigned int wait_loop_index;
	wait_loop_index = (__us * (SystemCoreClock / 1000000U));
	while(wait_loop_index != 0U)
	{
		wait_loop_index--;
	}
}
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
inline uint32_t GetCurrentMicro(void)
{
  /* Ensure COUNTFLAG is reset by reading SysTick control and status register */

  uint32_t m = HAL_GetTick();
  uint32_t u = SysTick->LOAD - SysTick->VAL;

  return ( m * 1000 + (u * 1000) / SysTick->LOAD);
}
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
// uint32_t micros( void )
// {
//  return GetCurrentMicro();
// }
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
uint32_t pulseIn(GPIO_TypeDef *port,uint32_t pin,uint8_t state, unsigned long timeout)
{
  // Cache the port and bit of the pin in order to speed up the
  // pulse width measuring loop and achieve finer resolution.
  // Calling digitalRead() instead yields much coarser resolution.
	
  uint32_t bit = pin;//(uint16_t) ( 1 << pin);	
  uint32_t stateMask = (state ? bit : 0);
  uint32_t startMicros = micros();

  // wait for any previous pulse to end
  while ((port->IDR & bit) == stateMask) 
	{
    if (micros() - startMicros > timeout)
      return 0;
  }

  // wait for the pulse to start
  while ((port->IDR & bit) != stateMask) 
	{
    if (micros() - startMicros > timeout)
      return 0;
  }

  uint32_t start = micros();
  // wait for the pulse to stop
  while ((port->IDR & bit) == stateMask) 
	{
    if (micros() - startMicros > timeout)
      return 0;
  }
  return (micros() - start);
}
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
