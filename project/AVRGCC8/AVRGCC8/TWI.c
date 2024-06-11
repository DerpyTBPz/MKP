//TWI.c

#include "main.h"
#include "TWI.h"

#define QUIT_TWI_OP { send_stop(); return -1; }

typedef enum
{
	/* TWI Master Status Codes */
	st_start = 0x08,
	st_restart = 0x10,
	st_sla_w_ack = 0x18,
	st_sla_w_noack = 0x20,
	st_data_w_ack = 0x28,
	st_data_w_noack = 0x30,
	st_arb_lost = 0x38,
	st_sla_r_ack = 0x40,
	st_sla_r_noack = 0x48,
	st_data_r_ack = 0x50,
	st_data_r_noack = 0x58,
} TwiStatus;

typedef enum
{
	dir_write,
	dir_read
} TwiOperation;

void twi_init(TwiMode mode)
{
	// 1 = output, 0 = input
	DDRC &= ~0b00000011; // PC0 = SCL; PC1 = SDA
	PORTC |= 0b00000011; // Internal pull-up on both lines

	TWBR = (mode == standard) ? 32 : 2;
	TWSR &= ~(0b11 << TWPS0); // Clearing TWSP to 0

	TWCR |= (1 << TWEN); // Enable TWI, generating the SCLK
}

void twi_shut(void)
{
	TWCR &= ~(1 << TWEN); // Disable TWI

	TWBR = 0;
	TWSR &= ~(0b11 << TWPS0);

	// 1 = output, 0 = input
	DDRC &= ~0b00000011; // PC0 = SCL; PC1 = SDA
	PORTC &= ~0b00000011; // Clear pull-up on both lines
}

static uint8_t get_status(uint8_t status)
{
	uint8_t st;

	while (!(TWCR & (1 << TWINT)))
		;
	if ((st = (TWSR & 0xF8)) == status)
		return 0;
	else
		return st;
}

static int send_start(uint8_t status)
{
	TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);
	return get_status(status);
}

static void send_stop(void)
{
	TWCR = (1 << TWINT) | (1 << TWSTO) | (1 << TWEN);
}

static int send_data(uint8_t data, uint8_t status)
{
	TWDR = data;
	TWCR = (1 << TWINT) | (1 << TWEN);
	return get_status(status);
}

static int recv_data(uint8_t *data, uint8_t status, uint8_t ack)
{
	TWCR = (1 << TWINT) | (ack << TWEA) | (1 << TWEN);
	if (get_status(status) == 0)
	{
		*data = TWDR;
		return 0;
	}
	else
	{
		return -1;
	}
}

int twi_master_tx(uint8_t addr, uint8_t *data, int len)
{
	int i;

	if (send_start(st_start)) QUIT_TWI_OP;
	if (send_data((addr << 1) | dir_write, st_sla_w_ack)) QUIT_TWI_OP;
	for (i = 0; i < len; i++)
	{
		if (send_data(data[i], st_data_w_ack)) QUIT_TWI_OP;
	}
	send_stop();
	return 0;
}

int twi_master_rx(uint8_t addr, uint8_t *data, int len)
{
	int i;

	if (send_start(st_start)) QUIT_TWI_OP;
	if (send_data((addr << 1) | dir_read, st_sla_r_ack)) QUIT_TWI_OP;
	for (i = 0; i < len - 1; i++)
	{
		if (recv_data(&data[i], st_data_r_ack, 1)) QUIT_TWI_OP;
	}
	if (recv_data(&data[i], st_data_r_noack, 0)) QUIT_TWI_OP;
	send_stop();
	return 0;
}

int twi_master_tx_rx(uint8_t addr, uint8_t *tx_data, int tx_len, uint8_t *rx_data,
			int rx_len)
{
	int i;

	if (send_start(st_start)) QUIT_TWI_OP;
	if (send_data((addr << 1) | dir_write, st_sla_w_ack)) QUIT_TWI_OP;
	for (i = 0; i < tx_len; i++)
	{
		if (send_data(tx_data[i], st_data_w_ack)) QUIT_TWI_OP;
	}
	if (send_start(st_restart)) QUIT_TWI_OP;
	if (send_data((addr << 1) | dir_read, st_sla_r_ack)) QUIT_TWI_OP;
	for (i = 0; i < rx_len - 1; i++)
	{
		if (recv_data(&rx_data[i], st_data_r_ack, 1)) QUIT_TWI_OP;
	}
	if (recv_data(&rx_data[i], st_data_r_noack, 0)) QUIT_TWI_OP;
	send_stop();
	return 0;
}
