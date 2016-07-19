import socket
 
UDP_IP = "10.0.27.67"
UDP_PORT = 3000
MESSAGE = "-gainmode 2"
 
print "UDP target IP:", UDP_IP
print "UDP target port:", UDP_PORT
print "message:", MESSAGE
 
sock = socket.socket(socket.AF_INET,socket.SOCK_DGRAM)
sock.sendto(MESSAGE, (UDP_IP, UDP_PORT))
