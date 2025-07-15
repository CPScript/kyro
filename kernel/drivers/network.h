#ifndef NETWORK_H
#define NETWORK_H

#include <stdint.h>
#include <stdbool.h>

// Network interface types
typedef enum {
    NET_INTERFACE_ETHERNET,
    NET_INTERFACE_WIRELESS,
    NET_INTERFACE_LOOPBACK
} net_interface_type_t;

// Network interface status
typedef enum {
    NET_STATUS_DOWN,
    NET_STATUS_UP,
    NET_STATUS_CONNECTING,
    NET_STATUS_ERROR
} net_status_t;

// MAC address structure
typedef struct {
    uint8_t addr[6];
} mac_address_t;

// IPv4 address structure
typedef struct {
    uint8_t addr[4];
} ipv4_address_t;

// Network packet structure
typedef struct {
    uint8_t *data;
    uint16_t length;
    uint16_t capacity;
    mac_address_t src_mac;
    mac_address_t dst_mac;
    uint16_t ethertype;
} net_packet_t;

// Network interface structure
typedef struct {
    char name[16];
    net_interface_type_t type;
    net_status_t status;
    mac_address_t mac_addr;
    ipv4_address_t ip_addr;
    ipv4_address_t netmask;
    ipv4_address_t gateway;
    uint32_t mtu;
    uint64_t rx_packets;
    uint64_t tx_packets;
    uint64_t rx_bytes;
    uint64_t tx_bytes;
    uint64_t rx_errors;
    uint64_t tx_errors;
    void *driver_data;
} net_interface_t;

// Network driver operations
typedef struct {
    int (*init)(net_interface_t *interface);
    int (*send)(net_interface_t *interface, net_packet_t *packet);
    int (*receive)(net_interface_t *interface, net_packet_t *packet);
    int (*set_mac)(net_interface_t *interface, mac_address_t *mac);
    int (*get_link_status)(net_interface_t *interface);
    int (*set_promiscuous)(net_interface_t *interface, bool enable);
    int (*cleanup)(net_interface_t *interface);
} net_driver_ops_t;

// Common Ethernet controllers
#define NET_VENDOR_INTEL     0x8086
#define NET_VENDOR_REALTEK   0x10EC
#define NET_VENDOR_BROADCOM  0x14E4

// Intel NICs
#define NET_DEVICE_I82540EM  0x100E
#define NET_DEVICE_I82545EM  0x100F
#define NET_DEVICE_I82574L   0x10D3

// Realtek NICs
#define NET_DEVICE_RTL8139   0x8139
#define NET_DEVICE_RTL8169   0x8169

// Ethernet frame types
#define ETH_TYPE_IPV4        0x0800
#define ETH_TYPE_ARP         0x0806
#define ETH_TYPE_IPV6        0x86DD

// Network protocols
#define IP_PROTOCOL_ICMP     1
#define IP_PROTOCOL_TCP      6
#define IP_PROTOCOL_UDP      17

// Network buffer sizes
#define NET_BUFFER_SIZE      1518
#define NET_MAX_INTERFACES   8
#define NET_PACKET_QUEUE_SIZE 64

// Network packet queue
typedef struct {
    net_packet_t packets[NET_PACKET_QUEUE_SIZE];
    int head;
    int tail;
    int count;
} net_packet_queue_t;

// Network statistics
typedef struct {
    uint64_t total_packets_sent;
    uint64_t total_packets_received;
    uint64_t total_bytes_sent;
    uint64_t total_bytes_received;
    uint64_t packet_errors;
    uint64_t dropped_packets;
} net_statistics_t;

// Function prototypes
void network_init(void);
int network_register_interface(net_interface_t *interface, net_driver_ops_t *ops);
int network_unregister_interface(net_interface_t *interface);
net_interface_t *network_get_interface(const char *name);
int network_send_packet(net_interface_t *interface, net_packet_t *packet);
int network_receive_packet(net_interface_t *interface, net_packet_t *packet);
net_packet_t *network_alloc_packet(uint16_t size);
void network_free_packet(net_packet_t *packet);
void network_set_ip_address(net_interface_t *interface, ipv4_address_t *ip, ipv4_address_t *netmask);
void network_set_gateway(net_interface_t *interface, ipv4_address_t *gateway);
bool network_interface_up(net_interface_t *interface);
bool network_interface_down(net_interface_t *interface);
void network_get_statistics(net_interface_t *interface, net_statistics_t *stats);
void network_reset_statistics(net_interface_t *interface);

// Packet queue functions
void network_queue_init(net_packet_queue_t *queue);
bool network_queue_empty(net_packet_queue_t *queue);
bool network_queue_full(net_packet_queue_t *queue);
int network_queue_put(net_packet_queue_t *queue, net_packet_t *packet);
net_packet_t *network_queue_get(net_packet_queue_t *queue);

// Utility functions
bool mac_address_equal(mac_address_t *addr1, mac_address_t *addr2);
bool mac_address_is_broadcast(mac_address_t *addr);
bool mac_address_is_multicast(mac_address_t *addr);
void mac_address_to_string(mac_address_t *addr, char *str);
bool mac_address_from_string(const char *str, mac_address_t *addr);
bool ipv4_address_equal(ipv4_address_t *addr1, ipv4_address_t *addr2);
void ipv4_address_to_string(ipv4_address_t *addr, char *str);
bool ipv4_address_from_string(const char *str, ipv4_address_t *addr);
uint16_t network_checksum(void *data, uint16_t length);
uint16_t network_checksum_add(uint16_t sum, void *data, uint16_t length);
uint16_t network_checksum_finish(uint16_t sum);

// Hardware abstraction functions
void network_enable_interrupts(net_interface_t *interface);
void network_disable_interrupts(net_interface_t *interface);
void network_interrupt_handler(net_interface_t *interface);

// Loopback interface functions
int loopback_init(void);
net_interface_t *loopback_get_interface(void);

// Common NIC driver functions (to be implemented per driver)
int rtl8139_init(net_interface_t *interface);
int e1000_init(net_interface_t *interface);
int ne2k_init(net_interface_t *interface);

// Global network state
extern net_interface_t *network_interfaces[NET_MAX_INTERFACES];
extern int network_interface_count;
extern net_statistics_t global_network_stats;

// Network event callback types
typedef void (*network_packet_callback_t)(net_interface_t *interface, net_packet_t *packet);
typedef void (*network_link_callback_t)(net_interface_t *interface, bool link_up);

// Callback registration
void network_set_packet_callback(network_packet_callback_t callback);
void network_set_link_callback(network_link_callback_t callback);

// Network debugging
void network_dump_packet(net_packet_t *packet);
void network_dump_interface(net_interface_t *interface);

#endif // NETWORK_H
