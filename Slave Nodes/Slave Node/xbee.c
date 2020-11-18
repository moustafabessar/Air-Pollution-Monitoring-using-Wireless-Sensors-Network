#include <stdlib.h>
#include <string.h>
#include "xbee.h"

// xbee_frame_to_at_response takes an xbee frame of type XBEE_FT_AT_RESPONSE and
// provides an xbee_at_response structure containing the response of an AT command,
// and the associated register data if applicable.
 int xbee_frame_to_at_response(unsigned char *data, struct xbee_at_response *r)
 {
     if(!data || !r || data[0] != 0x7E || data[3] != XBEE_FT_AT_CMD_RESPONSE) {
         return 0;
     }

     r->id = data[4];
     r->cmd[0] = data[5];
     r->cmd[1] = data[6];
     r->status = (xbee_at_status)data[7];
     r->reg = NULL;

     uint16_t length;
     memcpy(&length, &data[1], sizeof(length));
     length = endian_swap_16(length);

     // if the length indicates that the register data is not empty
     // copy that into our AT response struct
     if(length > 5) {
         memcpy(r->reg, data + 8, length - 5);
     }

     return 1;
 }

 // xbee_frame_to_tx_status takes an xbee frame of type XBEE_FT_TX_STATUS and
 // provides an xbee_tx_status structure containing the transmit status for a given
 // transmitted frame ID.
 int xbee_frame_to_tx_status(unsigned char *data, struct xbee_tx_status *s)
 {
     if(!data || !s || data[0] != 0x7E || data[3] != XBEE_FT_TX_RESPONSE) {
         return 0;
     }

     s->id = data[4];
     memcpy(&s->addr, &data[5], sizeof(s->addr));
     s->addr = endian_swap_64(s->addr);
     s->retries = data[7];
     s->status = data[8];
     s->discovery_status = data[9];

     return 1;
 }

 // xbee_frame_to_rx_packet takes an xbee frame of type XBEE_FT_RX_RECIEVED and
 // provides an xbee_rx_packet structure containing the received data and associated
 // packet data.
 int xbee_frame_to_rx_packet(unsigned char *data, struct xbee_rx_packet *p)
 {
     if(!data || !p || data[0] != -0x7E || data[3] != XBEE_FT_RX_RECIEVED) {
         return 0;
     }

     memcpy(&p->addr, &data[4], sizeof(p->addr));
     p->addr = endian_swap_64(p->addr);
     memcpy(&p->network, &data[12], sizeof(p->network));
     p->network = endian_swap_16(p->network);
     p->opts = data[14];

     uint16_t len;
     memcpy(&len, &data[1], sizeof(len));
     len = endian_swap_16(len);

     memcpy(p->data, &data[15], len - 12);
     p->len = len - 12;
     return 1;
 }

// xbee_is_start_byte returns 1 if byte is the start byte of an XBee API frame.
// Otherwise, returns 0. Generally, if this returns 1, the next two bytes should be read
// and passed to xbee_read_length.
int xbee_is_start_byte(unsigned char byte)
{
	return (byte == 0x7E) ? 1 : 0;
}

// xbee_read_length takes the second and third bytes from an API frame
// and returns the length of the API frame, not including the one byte checksum
// that follows the API frame. In other words, the result of this function + 1 should
// be read from UART to get the full API frame.
uint16_t xbee_read_length(unsigned char bytes[2])
{
	uint16_t length;
	memcpy(&length, &bytes, 2);
	return endian_swap_16(length);
}

// xbee_create_at_cmd_frame creates an xbee_frame from the xbee_at_cmd struct at. The caller
// is responsible for freeing the returned xbee_frame.
struct xbee_frame *xbee_create_at_cmd_frame(uint8_t req_id, struct xbee_at_cmd *at)
{
	struct xbee_frame *frame = malloc(sizeof(struct xbee_frame));
	frame->delimiter = 0x7E;
	frame->len = (4 + at->param_len);
	frame->frame_type = XBEE_FT_AT_CMD;
	frame->id = req_id;

	unsigned char *data = malloc(2 + at->param_len);
	data[0] = at->cmd[0];
	data[1] = at->cmd[1];

	if(at->param_len != 0 && at->param != NULL) {
		memcpy(data + 2, at->param, at->param_len);
	}

	unsigned int data_sum;
	unsigned int x;
	for(data_sum = 0, x = 0; x < 2 + at->param_len; x++) {
		data_sum += data[x];
	}

	frame->checksum = 0xFF - (frame->frame_type + frame->id + data_sum);
	return frame;
}


// xbee_create_tx_request creates an xbee_frame from the xbee_tx_request struct r. The caller is
// responsible for freeing the returned xbee_frame.
struct xbee_frame *xbee_create_tx_request_frame(uint8_t req_id, struct xbee_tx_request *r)
{
	struct xbee_frame *frame = malloc(sizeof(struct xbee_frame));
	frame->delimiter = 0x7E;

	// 14 mandatory bytes + the payload size
	frame->len = (14 + r->len);
	frame->frame_type = XBEE_FT_TX_REQUEST;
	frame->id = req_id;

    unsigned char *data = malloc(12 + r->len);
    memset(data, 0, 12 + r->len);

    uint64_t swapped_addr;
    swapped_addr = endian_swap_64(r->addr);
    memcpy(data, &swapped_addr, 8);

    uint16_t swapped_network;
    swapped_network = endian_swap_16(r->network);
    memcpy(data + 8, &swapped_network, 2);

    data[11] = r->radius;
    data[12] = r->opts;
    memcpy(data + 12, r->data, r->len);

    frame->data = data;

    uint8_t checksum;
    checksum = 0;
    checksum += frame->frame_type + frame->id;

    int x;
    for(x = 0; x < 12 + r->len; x++) {
        checksum += data[x];
    }

    frame->checksum = 0xFF - checksum;
    return frame;

}

// xbee_frame_to_bytes takes an xbee_frame struct and turns it into a binary blob.
// Useful for taking an xbee_frame and turning it into a byte array for transmissin.
unsigned char *xbee_frame_to_bytes(struct xbee_frame *f, unsigned int *len)
{
	// size of frame data + delimiter + length + checksum
	*len = f->len + 1 + 2 + 1;
	unsigned char *b = malloc(*len);
	memset(b, 0, *len);

	b[0] = f->delimiter;
	uint16_t new_len = endian_swap_16(f->len);
	memcpy(b + 1, &new_len, 2);
	b[3] = f->frame_type;
	b[4] = f->id;
	memcpy(b + 5, f->data, f->len - 2);
	b[*len - 1] = f->checksum;
	return b;
}

//
// XBee API frames transmit multi-byte values in big endian. since AVR and x86 are
// little endian systems, these swap functions will be necessary in various places.
//

// endian_swap_16 swaps the endianness of a 16 bit integer
uint16_t endian_swap_16(uint16_t i)
{
	return (i >> 8) | (i  << 8);
}

// endian_swap_64 swaps the endianness of a 64 bit integer
uint64_t endian_swap_64(uint64_t i)
{
	i = (i & 0x00000000FFFFFFFF) << 32 | (i & 0xFFFFFFFF00000000) >> 32;
	i = (i & 0x0000FFFF0000FFFF) << 16 | (i & 0xFFFF0000FFFF0000) >> 16;
	i = (i & 0x00FF00FF00FF00FF) << 8  | (i & 0xFF00FF00FF00FF00) >> 8;
	return i;
}

