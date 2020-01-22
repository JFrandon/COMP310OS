This Shell program has been written for Linux.
This Shell program has been tested and ran on mimi.cs.mcgill.ca (teach-vwc.cs.mcgill.ca)

/!\ Testfile might be calling itself 
# at the beginning of a line signifies a comment

Exit in a script exits the specified script
Every Script gets a copy of its parent shell but cannot modify the parent shell's memory

exit is an alias of quit

Error codes Specification:
	0 - No error
	1 - Unknown Command
	2 - Too few Arguments
	3 - More than 900 recursive Script calls (A Script might be calling itself over and over)
	4 - Shell memory Full (Can't allocate new name->value pair)
	5 - Script file does not exist
	6 - Variable to be printed does not exist in memory