/*
 * TWI.h
 *
 * Created: 09.06.2024 11:33:18
 *  Author: dimap
 */ 


#ifndef TWI_H_
#define TWI_H_

typedef enum
{
	standard,
	fast
} TwiMode;

void twi_init(TwiMode mode);
void twi_shut(void);
int twi_master_tx(uint8_t addr, uint8_t *data, int len);
int twi_master_rx(uint8_t addr, uint8_t *data, int len);
int twi_master_tx_rx(uint8_t addr, uint8_t *tx_data, int tx_len, 
					 uint8_t *rx_data, int rx_len);

#endif /* TWI_H_ */