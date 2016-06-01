#ifndef SPIKEHW_H
#define SPIKEHW_H

#define PROMSTART 0x00000000
#define RAMSTART  0x00000800
#define RAMSIZE   0x400
#define RAMEND    (RAMSTART + RAMSIZE)

#define RAM_START 0x40000000
#define RAM_SIZE  0x04000000

#define FCPU      100000000

#define UART_RXBUFSIZE 32

/****************************************************************************
 * Types
 */
typedef unsigned int  uint32_t;    // 32 Bit
typedef signed   int   int32_t;    // 32 Bit

typedef unsigned char  uint8_t;    // 8 Bit
typedef signed   char   int8_t;    // 8 Bit

/****************************************************************************
 * Interrupt handling
 */
typedef void(*isr_ptr_t)(void);

void     irq_enable();
void     irq_disable();
void     irq_set_mask(uint32_t mask);
uint32_t irq_get_mak();

void     isr_init();
void     isr_register(int irq, isr_ptr_t isr);
void     isr_unregister(int irq);

/****************************************************************************
 * General Stuff
 */
void     halt();
void     jump(uint32_t addr);


/****************************************************************************
 * Timer
 */
#define TIMER_EN     0x08    // Enable Timer
#define TIMER_AR     0x04    // Auto-Reload
#define TIMER_IRQEN  0x02    // IRQ Enable
#define TIMER_TRIG   0x01    // Triggered (reset when writing to TCR)

typedef struct {
	volatile uint32_t tcr0;
	volatile uint32_t compare0;
	volatile uint32_t counter0;
	volatile uint32_t tcr1;
	volatile uint32_t compare1;
	volatile uint32_t counter1;
} timer_t;

void msleep(uint32_t msec);
void nsleep(uint32_t nsec);

void tic_init();


/***************************************************************************
 * GPIO0
 */
typedef struct {
	volatile uint32_t gpio_in;   //0x4...000	
	volatile uint32_t gpio_out; //0x4...100
	volatile uint32_t gpio_dir;
	
} gpio_t;

char gpio_get_in();
char gpio_get_out();
char gpio_get_dir();
void gpio_set_in(char c);
void gpio_set_out(char c);
void gpio_set_dir(char c);


/***************************************************************************
 * UART0
 */
#define UART_DR   0x01                    // RX Data Ready
#define UART_ERR  0x02                    // RX Error
#define UART_BUSY 0x10                    // TX Busy

typedef struct {
   volatile uint32_t ucr;
   volatile uint32_t rxtx;
} uart_t;

void uart_init();
void uart_putchar(char c);
void uart_putstr(char *str);
char uart_getchar();

/***************************************************************************
 * SPI0
 */
typedef struct {
	volatile uint32_t spi_rx_tx; //miso=rx, mosi=tx ----- 4b0000 5...00000
	volatile uint32_t spi_run;			//5...0000100
	volatile uint32_t spi_cs;			//5...0001000
	volatile uint32_t spi_divisor;			//5...0001100
		
} spi_t;
<<<<<<< HEAD
char read_adc(spi_t *spi, char cs);
char spi_get_div(spi_t *spi);
char spi_get_mosi(spi_t *spi);
char spi_get_miso(spi_t *spi);
char spi_get_cs(spi_t *spi);
void spi_set_div(spi_t *spi, char c);
void spi_set_mosi(spi_t *spi, char c);
void spi_set_miso(spi_t *spi, char c);
void spi_set_cs(spi_t *spi, char c);

/*********************SPI1****************************/
/*
=======

char read_adc(char cs);
void spi_init();
char spi_get_div();
char spi_get_mosi();
char spi_get_miso();
char spi_get_cs();
void spi_set_div(char c);
void spi_set_mosi(char c);
void spi_set_miso(char c);
void spi_set_cs(char c);
>>>>>>> ffde8aaad70c2b6386f51676d8f79c419a5a5789
char spi1_get_div();
char spi1_get_mosi();
char spi1_get_miso();
char spi1_get_cs();
void spi1_set_div(char c);
void spi1_set_mosi(char c);
void spi1_set_miso(char c);
void spi1_set_cs(char c);


/***************************************************************************
 * Pointer to actual components
 */
extern timer_t  *timer0;
extern uart_t   *uart0; 
extern gpio_t   *gpio0; 
extern spi_t 	*spi0;
extern spi_t    *spi1;
extern uint32_t *sram0; 

#endif // SPIKEHW_H
