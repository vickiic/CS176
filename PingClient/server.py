# Echo server program
import socket
import random
HOST = ''                 # Symbolic name meaning all available interfaces
PORT = 1236             # Arbitrary non-privileged port
s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
print "Waiting for client"
s.bind((HOST, PORT))

while 1:
  
  rand= random.randint(0,10)
  data,addr = s.recvfrom(1024)
  if rand<4:
  	continue
  print"Received from client:",data
  s.sendto(data,addr);
  if not data: break
