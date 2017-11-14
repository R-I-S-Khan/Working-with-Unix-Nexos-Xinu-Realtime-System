#include <kernel.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>
// Defining two unique usernames
 char USERNAME1[] = "Username1";
 char PASSWORD1[] = "password1";
 char USERNAME2[] = "Username2";
 char PASSWORD2[] = "password2";
 // I have declared local function definitions here
 local chat  (ushort, ushort, char *name);
 // The following command logs a user in, and begins the chat program
 command xsh_chat (ushort stdin, ushort stdout, ushort stderr, ushort nargs, char *args[]) {
 	// Defining variables
 	char username[40];
	char password[40];
 	int logged_in_status = 0; //a variable for checking log in status
 	// Continue trying until the user has logged in
 	do {
 	// Retrieve username and password from user
 	fprintf (stdout, "\nEnter Username: ");
 	read    (stdin,  username, 40);
 															
 	fprintf (stdout, "Enter Password: ");
 																			read    (stdin,  password, 40);
 																					// Checking to see if the login was successfull
 																			if ( (strncmp(username, USERNAME1, 9) == 0   &&
              strncmp(password, PASSWORD1,9) == 0 ) ||
               (strncmp(username, USERNAME2, 9) == 0   &&
                 strncmp(password, PASSWORD2, 9) == 0 ) ) 
 																			{
										  			 			  			// Greeting the user and proceeding to the chat room
								  			 			  						username[9] = '\0';
									  			 			  					fprintf (stdout, "\nWelcome to the chat! %s \n\n", username);
 																										  			 			  						logged_in_status = 1;
 																										  			 			  					}
 																			else 
 	{
																					// Continue prompting for a login if unsuccessful login
               	fprintf (stdout, "\nThe username/password you entered is not recognized by our database. ");
        	fprintf (stdout, "Please try it again! Check for case of alphabets.\n");
	}
 	} while (logged_in_status == 0);
 	// Begin the chat room
	if (stdin == TTY0)
 		chat (TTY0, TTY1, username);
	else if (stdin == TTY1)
        	chat (TTY1, TTY0, username);
		
        return OK;
 																		 }
 																										  			 			  																																								    // Chat room function
    local chat (ushort in, ushort out, char *name) {
	
	// Define local variables
	char message[100];
	int i;
	int exit = 0;
	// Continue the chat room until the user exits
 	while (exit == 0) {
	
        //clear the message buffer for new chat message
          	for (i=0; i<100; i++) {		
                 	message[i] = '\0';
 																				}
	
	// Take in the user message to send
	read(in, message, 100);
	// If the user typed 'exit' then quit the program. Display that user has left the chat room.
	if ( strncmp(message, "exit", 4) == 0) {
        	exit = 1;
	        strcpy(message, "-- HAS LEFT THE CHAT --");
	}
 																			// Sending out the chat message
	fprintf(out, "\x1B[31m" "%s: " "\033[0m", name);
	write(out, message, strlen(message));
        }
	return OK;
	}
