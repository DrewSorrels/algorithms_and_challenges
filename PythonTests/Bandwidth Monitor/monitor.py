import socket, sys, pcapy
from struct import *

def main(argv):
    devs = pcapy.findalldevs()
    for d in devs:
        print d
    
    dev = raw_input("Enter device name to sniff: ")



    p = pcapy.open_live(dev, 65563, 1, 0)
    totalData = 0

    while True:
        (header, packet) = p.next()
        totalData += header.getlen()
        print time.strftime("%H:%M:%S", time.localtime())+": captured " + header.getlen() + " bytes, truncated to " + header.getcaplen() + " bytes."
        parse_packet(packet)

def parse_packet(p):
    eth_length = 14

    eth_header = packet[:eth_length]
    eth = unpack('!6s6sh', eth_header)
    eth_protocol = socket.ntohs(eth[2])
    
    if eth_protocol == 8:
        ip_header = packet[eth_length:20+eth_length]
        print "Packet Length: " + str(len(packet))


if __name__ == "__main__":
    main(sys.argv)
        
