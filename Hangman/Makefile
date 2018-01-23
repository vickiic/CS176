all: hangman_client hangman_server

hangman_client: hangman_client.c
	gcc -o hangman_client hangman_client.c
hangman_server: hangman_server.c
	gcc -o hangman_server hangman_server.c

clean:
	$(RM) hangman_client hangman_server