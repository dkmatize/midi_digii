#include "soc-hw.h"

uart_t   *uart0  = (uart_t *)   0x20000000;
timer_t  *timer0 = (timer_t *)  0x30000000;
gpio_t   *gpio0  = (gpio_t *)   0x40000000;
spi_t	*spi0 	= (spi_t *)  	0x50000000;
spi_t   *spi1   = (spi_t *)	0x60000000;

//isr_ptr_t isr_table[32];


void tic_isr();
/***************************************************************************
 * IRQ handling
 */ /*
void isr_null()
{
}

void irq_handler(uint32_t pending)
{
	int i;

	for(i=0; i<32; i++) {
		if (pending & 0x01) (*isr_table[i])();
		pending >>= 1;
	}
}

void isr_init()
{
	int i;
	for(i=0; i<32; i++)
		isr_table[i] = &isr_null;
}

void isr_register(int irq, isr_ptr_t isr)
{
	isr_table[irq] = isr;
}

void isr_unregister(int irq)
{
	isr_table[irq] = &isr_null;
}
*/


/***************************************************************************
 * TIMER Functions
 */
void msleep(uint32_t msec)
{
	uint32_t tcr;

	// Use timer0.1
	timer0->compare1 = (FCPU/1000)*msec;
	timer0->counter1 = 0;
	timer0->tcr1 = TIMER_EN;

	do {
		//halt();
 		tcr = timer0->tcr1;
 	} while ( ! (tcr & TIMER_TRIG) );
}

void nsleep(uint32_t nsec)
{
	uint32_t tcr;

	// Use timer0.1
	timer0->compare1 = (FCPU/1000000)*nsec;
	timer0->counter1 = 0;
	timer0->tcr1 = TIMER_EN;

	do {
		//halt();
 		tcr = timer0->tcr1;
 	} while ( ! (tcr & TIMER_TRIG) );
}


uint32_t tic_msec;

void tic_isr()
{
	tic_msec++;
	timer0->tcr0     = TIMER_EN | TIMER_AR | TIMER_IRQEN;
}

void tic_init()
{
	tic_msec = 0;

	// Setup timer0.0
	timer0->compare0 = (FCPU/10000);
	timer0->counter0 = 0;
	timer0->tcr0     = TIMER_EN | TIMER_AR | TIMER_IRQEN;

	//isr_register(1, &tic_isr);
}


/***************************************************************************
 * UART Functions
 */
void uart_init()
{
	//uart0->ier = 0x00;  // Interrupt Enable Register
	//uart0->lcr = 0x03;  // Line Control Register:    8N1
	//uart0->mcr = 0x00;  // Modem Control Register

	// Setup Divisor register (Fclk / Baud)
	//uart0->div = (FCPU/(57600*16));
}

char uart_getchar()
{   
	while (! (uart0->ucr & UART_DR)) ;
	return uart0->rxtx;
}

void uart_putchar(char c)
{
	while (uart0->ucr & UART_BUSY) ;
	uart0->rxtx = c;
}

void uart_putstr(char *str)
{
	char *c = str;
	while(*c) {
		uart_putchar(*c);
		c++;
	}
}

/***************************************************************************
 * GPIO Functions
 */


char gpio_get_in(){
	return gpio0->gpio_in;
}

char gpio_get_dir(){
	return gpio0->gpio_dir;

}

char gpio_get_out(){
	return gpio0->gpio_out;

}

void gpio_set_in(char c){
	 gpio0->gpio_in = c;
}

void gpio_set_dir(char c){
	 gpio0->gpio_dir = c;
}

void gpio_set_out(char c){
	 gpio0->gpio_out = c;
}

/*****************************************SPI Functions****/

char read_adc(char cs){
	spi_set_cs(0xF);
	nsleep(20);	
	char msb = 0x00;
	char lsb = 0x00;
	char lsb2 = 0x00;	
	spi_set_cs(cs);
	nsleep(30);
	spi_set_mosi(0xC0);
	msb = spi_get_miso();
	spi_set_cs(cs);
	spi_set_mosi(0x00);
	lsb = spi_get_miso();
	spi_set_cs(cs);
	spi_set_mosi(0x00);
	lsb2 = spi_get_miso();

	if(msb == 0x00 && lsb == 0x00 && lsb == 0x00){
	gpio_set_out(0xFF);
	}

	else
	switch(cs){
		case ~0x01:
		gpio_set_out(0xE0);		
		break;
	
		case ~0x02:
		gpio_set_out(0xD0);
		break;
	
		case ~0x04:
		gpio_set_out(0xB0);
		break;
	
		case ~0x08:
		gpio_set_out(0x70);
		break;
	
		default: 
		gpio_set_out(0xFF);
		break;
		}
			

	//msleep(50);	
	//spi_set_cs(0x01);
	return msb|lsb;
	
}

void spi_init(){
	read_adc(0x01);
	read_adc(0x02);
	read_adc(0x04);
	read_adc(0x08);
}

void midi_wr(char mode, char data1 ,char data2, char status){
	

	if(mode == 0){ //init
	status = 0;
	data1 = 0;
	data2 = 0;
	}	

	if(mode == 1){//note on
	status = 0x9A;
	data1 = 0x1F;
	}
	
	if (mode == 2){//note off
	status = 0x9A;
	data1 = 0x1F;
	data2 = 0x00;
	}
	
	uart_putchar(status);
	uart_putchar(data1);
	uart_putchar(data2);



}

void midi_set_vol(char data2, char vol){
	data2 = vol & 0x7F;
}

char spi_get_div(){
	return spi0->spi_divisor;
}


char spi_get_mosi(){
	return spi0->spi_rx_tx;

}


char spi_get_cs(){
	return spi0->spi_cs;

}
char spi_get_miso(){
	while ((spi0 -> spi_run));
	return spi0->spi_rx_tx;

}

void spi_set_div(char c){
	 spi0->spi_divisor = c;
}


void spi_set_cs(char c){
	spi0->spi_cs=c;
}
void spi_set_mosi(char c){
	 while ((spi0 -> spi_run));
	 spi0->	spi_rx_tx = c;
}

void spi_set_miso(char c){
	 while ((spi0 -> spi_run));
	 spi0->spi_rx_tx = c;
}

/*****************************************SPI1 Functions****/

char spi1_get_div(){
	return spi1->spi_divisor;
}


char spi1_get_mosi(){
	return spi1->spi_rx_tx;

}


char spi1_get_cs(){
	return spi1->spi_cs;

}
char spi1_get_miso(){
	while ((spi1 -> spi_run));
	return spi1->spi_rx_tx;

}

void spi1_set_div(char c){
	 spi1->spi_divisor = c;
}


void spi1_set_cs(char c){
	spi1->spi_cs=c;
}
void spi1_set_mosi(char c){
	 while ((spi1 -> spi_run));
	 spi1->	spi_rx_tx = c;
}

void spi1_set_miso(char c){
	 while ((spi1 -> spi_run));
	 spi1->spi_rx_tx = c;
}




