/**
 * 
 */

#include "soc-hw.h"
void irq_handler(uint32_t pending);

void irq_handler(uint32_t pending)
{
<<<<<<< HEAD
	//irq_disable();	
	gpio_set_out(0xFF);
        //irq_enable();
}
=======
	//irq_disable();
	gpio_set_out(0xBB);
	
>>>>>>> ffde8aaad70c2b6386f51676d8f79c419a5a5789

	
}

int main()
{
<<<<<<< HEAD
		
        irq_set_mask(0x04);
        //irq_enable();
        gpio_set_dir(0xF0);

=======
	//gpio_set_out(0x00);
 	gpio_set_dir(0xF0);
        irq_set_mask(0x04);
	//irq_enable();
        //irq_disable();
>>>>>>> ffde8aaad70c2b6386f51676d8f79c419a5a5789
	//uint32_t a2 = 4;
	/*while (gpio0 -> gpio_dir = 0xFF){
			
	gpio0 -> gpio_in;	
	gpio0->gpio_o = 0x01;
	nsleep(5);
	gpio0 -> gpio_in;
	gpio0->gpio_o = 0x00;
	nsleep(5);
}*/ 

uint8_t a ;
uint8_t b ;	
char c ;
char m;
	
	
	//irq_enable();
	//irq_set_mask(0x04);
	
	//irq_set_mask(0x04);
	//irq_enable();
	

	//irq_set_mask(0x0A);
	while (1){
<<<<<<< HEAD
        
	/*spi_set_cs(spi0, ~0x00);
	//msleep(100);
	spi_set_cs(spi0, ~0xFF);
	//msleep(100);			
	spi_set_mosi(spi0, 0xA0);

	spi_set_cs(spi1, ~0x00);
	//msleep(200);
	spi_set_cs(spi1, ~0xFF);
	//msleep(200);			
	spi_set_mosi(spi1, 0x0A);
*/
	read_adc(spi0, ~0x01);
=======
	
	read_adc(~0x01);	

	//spi_set_cs(~0x00);
	//msleep(100);
	//spi_set_cs(~0x0F);
	//msleep(100);	
	//spi_set_mosi(0xAA);

	//spi1_set_cs(~0x00);
	//msleep(100);
	//spi1_set_cs(~0x01);
	//msleep(100);	
	//spi1_set_mosi(0xF0);

	//spi1_set_mosi(0xAA);
			
		/*switch(c){
		case 0x01:
		spi_set_cs(c);
		spi_set_miso(0xFF);		
		break;
	
		case 0x02:
		spi_set_cs(c);
		spi_set_miso(0x0A);
		break;
	
		case 0x04:
		spi_set_cs(c);
		spi_set_miso(m);
		
		break;
	
		case 0x08:
		spi_set_cs(c);
		spi_set_miso(m);
		break;
>>>>>>> ffde8aaad70c2b6386f51676d8f79c419a5a5789
	
		default: 
		uart_putstr("ingrese un modo\n");
		}*/
		
	gpio_set_dir(0xF0);
	a= gpio_get_in();
	gpio_set_out(a);
	b = a << 4;
	gpio_set_out(b);
<<<<<<< HEAD
	nsleep(5);
	

=======
	
>>>>>>> ffde8aaad70c2b6386f51676d8f79c419a5a5789
	if (a == 0x0F){
	uart_putstr("lo ke sea: \n");
	
	}
}
irq_disable();

/*int i=0;	
for(i=0; i<1000000; i++){
	if(i<500000){
		gpio_set_out(0xFF);	
	}
	else{
	gpio_set_out(0x00);
		}

*/	


	/*char id = uart_getchar ();
	
	switch (id) {
		case 'n':
			uart_putstr("su nombre\n");
		break;

		case 'p':
			uart_putstr("su apellido\n");
		break;

		case 'c':
			uart_putstr("su nombre\n");
		break;

		default:
			uart_putstr("ingrese un dato\n");
			}*/
}

