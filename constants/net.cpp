#include <projectX/net/addr.cpp>
const int PORT_CHAT = 6000;
const int PORT_UPDATE = 6001;
const int PORT_GRAPHICS = 6002;
const int PORT_API = 6003;

const addr ADDR_API("192.168.178.50", PORT_API);
const addr ADDR_UPDATE("192.168.178.50", PORT_UPDATE);
const addr ADDR_GRAPHICS("192.168.178.50", PORT_GRAPHICS);