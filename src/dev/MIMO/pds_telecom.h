#ifndef _H_PDS_TELECOM
#define _H_PDS_TELECOM

int * tx_data_read(FILE *fp, long int numBytes);

void rx_data_write(int *s, long int numBytes);

#endif
