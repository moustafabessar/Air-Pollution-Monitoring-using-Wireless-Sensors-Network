#ifndef _XBEE_H_
#define _XBEE_H_

#include <stdint.h>

#define XBEE_ADDR_BROADCAST     0x000000000000FFFF
#define XBEE_ADDR_COORDINATOR   0x0000000000000000


typedef enum {
    XBEE_FT_AT_CMD = 0x08,
    XBEE_FT_AT_CMD_QUEUED = 0x09,
    XBEE_FT_AT_CMD_RESPONSE = 0x88,
    XBEE_FT_REMOTE_CMD_REQUEST = 0x17,
    XBEE_FT_REMOTE_CMD_RESPONSE = 0x97,
    XBEE_FT_MODEM_STATUS = 0x8A,
    XBEE_FT_TX_REQUEST = 0x10,
    XBEE_FT_TX_RESPONSE = 0x8B,
    XBEE_FT_RX_RECIEVED = 0x90,
    XBEE_FT_RX_DATA_RECIEVED = 0x92,
    XBEE_FT_NODE_IDENT_INDICATOR = 0x95,
    XBEE_FT_UNKNOWN = 0xFF,
} xbee_frame_type;

typedef enum {
    XBEE_AT_STATUS_OK = 0,
    XBEE_AT_STATUS_ERROR,
    XBEE_AT_STATUS_INVALID_CMD,
    XBEE_AT_STATUS_INVALID_PARAM,
    XBEE_AT_STATUS_TX_FAILURE
} xbee_at_status;

typedef enum {
    XBEE_TX_STATUS_SUCCESS = 0x00,
    XBEE_TX_STATUS_MAC_ACK_FAIL = 0x01,
    XBEE_TX_STATUS_CCA_FAIL = 0x02,
    XBEE_TX_STATUS_INVALID_DEST = 0x15,
    XBEE_TX_STATUS_NETWORK_ACK_FAIL = 0x21,
    XBEE_TX_STATUS_NO_NETWORK = 0x22,
    XBEE_TX_STATUS_SELF_ADDR = 0x23,
    XBEE_TX_STATUS_ADDR_NOT_FOUND = 0x24,
    XBEE_TX_STATUS_NO_ROUTE = 0x25,
    XBEE_TX_STATUS_NO_RELAY = 0x26,
    XBEE_TX_STATUS_INVALID_BIND_TABLE = 0x2B,
    XBEE_TX_STATUS_RESOURCE_ERR = 0x2C,
    XBEE_TX_STATUS_BROADCAST_APS = 0x2D,
    XBEE_TX_STATUS_UNICAST_APS = 0x2E,
    XBEE_TX_STATUS_RESOURCE2_ERR = 0x32,
    XBEE_TX_STATUS_DATA_TOO_LARGE = 0x74,
    XBEE_TX_STATUS_IND_MSG_UNREQUEST = 0x75
} xbee_tx_status;

typedef enum {
    XBEE_DISC_STATUS_NO_OVERHEAD = 0x00,
    XBEE_DISC_STATUS_ADDR_DISCOVERY = 0x01,
    XBEE_DISC_STATUS_RESOURCE_ERR = 0x32,
    XBEE_DISC_STATUS_DATA_TOO_LARGE = 0x74,
    XBEE_DISC_STATUS_IND_MSG_UNREQUEST = 0x75
} xbee_discovery_status;

typedef enum {
    XBEE_TX_OPT_DISABLE_ACK = 0x01,
    XBEE_TX_OPT_ENABLE_APS_ENC = 0x20,
} tx_request_option;

typedef enum {
    XBEE_RX_OPT_ACK = 0x01,
    XBEE_RX_OPT_BROADCAST = 0x01,
    XBEE_RX_OPT_APS = 0x20,
    XBEE_RX_OPT_END_DEVICE = 0x40
} rx_packet_option;

struct xbee_frame {
    uint8_t delimiter;
    uint16_t len;
    uint8_t frame_type;
    uint8_t id;
    uint16_t payload_len;
    unsigned char *data;
    int8_t checksum;
};

struct xbee_tx_request {
    int64_t addr;
    uint16_t network ;
    uint8_t radius ;
    tx_request_option opts;
    unsigned char * data;
    int len;
};

struct xbee_at_cmd {
	char cmd[2];
	unsigned int param_len;
	char *param;
};

struct xbee_at_response {
    uint8_t id;
    char cmd[2];
    xbee_at_status status;
    unsigned int reg_len;
    unsigned char *reg;
};

struct xbee_tx_status {
    uint8_t id;
    uint16_t addr;
    uint8_t retries;
    uint8_t status;
    uint8_t discovery_status;
};

struct xbee_rx_packet {
    uint16_t addr;
    uint8_t network;
    rx_packet_option opts;
    int len;
    unsigned char * data;
};

struct xbee_tx_request_frame {
    uint8_t delimiter;
    uint16_t len;
    uint8_t frame_type;
    uint8_t id;
    uint64_t destination;
    uint16_t network;
    uint8_t broadcast_radius;
    uint8_t options;
    char data[8];
    uint8_t checksum;
};

struct xbee_frame *xbee_create_at_frame(uint8_t req_id, unsigned char cmd[2], void *param, int len);
struct xbee_frame *xbee_create_tx_request_frame(uint8_t req_id, struct xbee_tx_request *r);
int xbee_frame_to_at_response(unsigned char *data, struct xbee_at_response *r);
int xbee_frame_to_tx_status(unsigned char *data, struct xbee_tx_status *s);
int xbee_frame_to_rx_packet(unsigned char *data, struct xbee_rx_packet *p);
void xbee_free_at_response(struct xbee_at_response *r);
uint8_t get_frame_id(unsigned char *frame);
xbee_frame_type get_frame_type(unsigned char *data, int len);
unsigned char *xbee_frame_to_bytes(struct xbee_frame *, unsigned int *);
uint16_t endian_swap_16(uint16_t);
uint64_t endian_swap_64(uint64_t);

#endif
