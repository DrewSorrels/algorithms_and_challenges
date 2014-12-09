import socket, sys
from struct import *

HOST = socket.gethostbyname(socket.gethostname())

s = socket.socket(socket.AF_INET, socket.SOCK_RAW, socket.IPPROTO_IP)
#s.bind((HOST, 0))

totalSize = 0;

while True:
    packet = s.recvfrom(65565)
    packet = packet[0]
    
    eth_length = 14
    
    eth_header = packet[:eth_length]
    eth = unpack('!6s6sH' , eth_header)
    eth_protocol = socket.ntohs(eth[2])

    print str(eth_protocol)
    print str(sys.sizeof(packet))

    #s.setsockopt(socket.IPPROTO_IP, socket.IP_HDRINCL, 1)

    #s.ioctl(socket.SIO_RCVALL, socket.RCVALL_ON)

    # packets = (s.recvfrom(65565)[0], "--", s.recvfrom(65565)[1])
    
    # print str(packets[0]) + "--" + str(packets[1] +"\n"
 #   size = sys.getsizeof(s.recvfrom(65565)[0])
 #   totalSize += size
 #   print "\bTotal Size: " + str(totalSize)
 #   print "Most Recent Packet Size: " +str(size) +"\nFrom: "+ str(s.recvfrom(65565)[1])
    #print s.recvfrom(65565)
    #s.ioctl(socket.SIO_RCVALL, socket.RCVALL_OFF)
