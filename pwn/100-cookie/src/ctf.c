#include "cookie.h"
#include "ctf.h"
#include <unistd.h>

//user to drop privileges to
const char *USER = "nobody";
//port to bind and listen on
const unsigned short PORT = 53000;

int child_main(int sd)		//handler for incoming connections
{
	int choice = 0;
	FILE *fp;
	char path[1000];
	char bin[100];

	if (choice != 2) {
		write(sd, "\nWelcome to the BSidesPDX Pwn 100 Server!\n", 51);
		write(sd, "Please enter one of the following options:\n\n", 45);
		write(sd, "1 - Download this binary\n", 27);
		fflush(stdout);

		recv(sd, &choice, 1, 0);

		switch (choice) {
		case 51:
			fp = popen("/usr/bin/xxd /opt/cookie/cookie", "r");
			if (fp == NULL) {
				printf("Failed to run command\n");
				exit(1);
			}
			while (fgets(path, sizeof(path) - 1, fp) != NULL) {
				cookie_writes(sd, path);
			}
			break;
            
		case 80:
			write(sd, "\n\nH", 4);
			usleep(60000);
			write(sd, "i", 1);
			usleep(60000);
			write(sd, "d", 1);
			usleep(60000);
			write(sd, "d", 1);
			usleep(60000);
			write(sd, "e", 1);
			usleep(60000);
			write(sd, "n", 1);
			usleep(60000);
			write(sd, " ", 1);
			usleep(60000);
			write(sd, "c", 1);
			usleep(60000);
			write(sd, "o", 1);
			usleep(60000);
			write(sd, "m", 1);
			usleep(60000);
			write(sd, "m", 1);
			usleep(60000);
			write(sd, "a", 1);
			usleep(60000);
			write(sd, "n", 1);
			usleep(60000);
			write(sd, "d", 1);
			usleep(60000);
			write(sd, " ", 1);
			usleep(60000);
			write(sd, "d", 1);
			usleep(60000);
			write(sd, "e", 1);
			usleep(60000);
			write(sd, "t", 1);
			usleep(60000);
			write(sd, "e", 1);
			usleep(60000);
			write(sd, "c", 1);
			usleep(60000);
			write(sd, "t", 1);
			usleep(60000);
			write(sd, "e", 1);
			usleep(60000);
			write(sd, "d", 1);
			usleep(60000);
			write(sd, "!\n\n", 4);
			usleep(60000);
			write(sd, "Enter a short message to share with BSidesPDX (please allow 10 seconds) => ", 75);
			fflush(stdin);
			sgstatd(sd);

			cookie_writes(sd, "\nRequest Completed!\n\n");
			break;

		default:
			write(sd, "Invalid choice!\n", 17);
			break;

		}
		shutdown(sd, SHUT_WR);
	}
	return 0;
}

int cookie_exit()
{
	printf("Canary not repaired.\n");
	exit(0);
}

int sgstatd(sd)
{
	__asm__("movl $0x01C0ff33, -4(%ebp)");
	char bin[100];
	write(sd, "\nThis function is protected!\n", 30);
	fflush(stdin);
	cookie_readn(sd, &bin, 200);
	__asm__("movl -4(%ebp), %edx\n\t" "xor $0x01C0ff33, %edx\n\t"	
		"jne cookie_exit");
	return 0;

}

int main(int argc, char **argv)	
{
	(void)argc;
	(void)argv;
	printf("Server started...\n");
	int sd;
	sd = cookie_listen(PORT, IPPROTO_TCP, NULL);
	cookie_server(sd, USER, child_main);
	return 0;
}

void jmpesp()
{
    asm ("jmp %esp");
}
