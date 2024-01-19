#!/usr/bin/env python3

import sys
import re

# Function to check password validity
def is_valid_password(password):
	# Password validity flag
	valid = False
	# Flag to check if password is too short
	too_short = len(password) < 8
	# Flag to check if password contains Non ASCII
	nonascii = bool(re.search(r'[^\x00-\x7F]', password))

	# If password isn't too short and doesn't contain no ASCII, function returns True
	if too_short and nonascii:
		print("0,INVALID,TOO_SHORT,NONASCII")
	elif too_short:
		print("0,INVALID,TOO_SHORT")	
	elif nonascii:
		print("0,INVALID,NONASCII")
	else:
		valid = True
	return valid

# Function to determine the strength of a valid password
def compute_password_strength(password):
	strength = 1
	# Array to store password attributes
	attributes = []

	# Check if there's at least one uppercase character, if so, +1 strength & append "UPPERCASE" to array
	if re.search(r'[A-Z]', password):
		attributes.append("UPPERCASE")
		strength+=1	
	# Check if there's at least one lowercase character, if so, +1 strength & append "LOWERCASE" to array
	if re.search(r'[a-z]', password):
		attributes.append("LOWERCASE")
		strength+=1
	# Check if there's at least one number, if so, +1 strength & append "NUMBER" to array
	if re.search(r'\d', password):
		attributes.append("NUMBER")
		strength+=1
	# Check if there's at least one special character, if so, +1 strength & append "SPECIAL" to array
	if re.search(r'[!#$%&()*+,\-./:;<=>?@[\]^_`{|}~]', password):
		attributes.append("SPECIAL")
		strength+=1
	# Check if there's three characters repeated in sequence, if so, -1 strength & append "sequence" to array
	if re.search(r'(.)\1\1', password):
		attributes.append("sequence")
		strength-=1
	
	# Call helper function to get the strength category based on strength score
	strength_category = get_strength_category(strength)

	# Print the strength score, category, and the password attributes
	print(f"{strength},{strength_category},{','.join(attributes)}")

# Helper function to get the strength category from the strength score
def get_strength_category(strength):
	if strength == 1:
		return "VERY_WEAK"
	elif strength == 2:
		return "WEAK"
	elif strength == 3:
		return "MEDIUM"
	elif strength == 4:
		return "STRONG"
	elif strength == 5:
		return "VERY_STRONG"


def main():
	""" This script reads a text from standard input,
	analyzes the validity of a password in each line,
	if valid assesses the strength of the password,
	and writes results of the password analysis into
	the standard output  """

	# if arguments provided, show error message
	if len(sys.argv) != 1:
		print("No arguments should be provided.")
		print("Usage: %s" % sys.argv[0])
		return 1;

	# Get lines(passwords) from stdin
	line = sys.stdin.readline().strip()
	while line:
		# If password is valid, compute its strength
		if is_valid_password(line): 
			compute_password_strength(line)
		line = sys.stdin.readline().strip()

	# end the script normally
	return 0

if __name__ == "__main__":
	main()

