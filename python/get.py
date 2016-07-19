import socket
 
UDP_IP = "10.0.27.52"
UDP_PORT = 3000
 
sock = socket.socket(socket.AF_INET,socket.SOCK_DGRAM)
sock.bind((UDP_IP, UDP_PORT))
 
while True:
     data, addr = sock.recvfrom(1024)
     print "received message:", data
