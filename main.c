#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

int esVocal(char letra) {
    char letraEnMayuscula = (char) toupper(letra);
    return letraEnMayuscula == 'A' ||
           letraEnMayuscula == 'E' ||
           letraEnMayuscula == 'I' ||
           letraEnMayuscula == 'O' ||
           letraEnMayuscula == 'U';
}

int readFile(char *fileName)
{
    FILE *file = fopen(fileName, "r");
    char *code;
    size_t n = 0;
    int c;
    int consonates = 0;

    if (file == NULL)
        return -1; //could not open file

    code = malloc(1000);

    while ((c = fgetc(file)) != EOF)
    {
        if (!esVocal((char) c))
            consonates++;
    }

    // don't forget to terminate with the null character
    return consonates;
}

void error(const char *msg)
{
	perror(msg);
	exit(1);
}

int main(int argc, char *argv[])
{
	/*
	if(argc < 2)
	{
		fprintf(stderr , "Port not provided. Program terminated\n");
		exit(1);
	}
	*/

	int sockfd, newsockfd, portno, n;
	char buffer[4];

	struct sockaddr_in serv_addr, cli_addr;
	socklen_t clilen;

	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if(sockfd < 0)
	{
		error("Error opening Socket");
	}
	
	fprintf(stderr, "Open socket\n");

	bzero((char *) &serv_addr, sizeof(serv_addr));
	portno = 9898;

	serv_addr.sin_family = 	AF_INET;
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	serv_addr.sin_port = htons(portno);

	if(bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
		error ("Binding Failed");
	
	fprintf(stderr, "Bind\n");
	listen(sockfd, 5);
	clilen = sizeof(cli_addr);

	newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);

	if(newsockfd < 0)
		error("Error on Accept");
	
	fprintf(stderr, "Accepted\n");
	
	FILE *fp;
	FILE *fp2;

	int ch = 0;
	fp = fopen("glad_received.txt", "w");
	int words;

	read(newsockfd, &words, sizeof(words));

	printf("%d\n", words);

	while(ch != words)
	{
		read(newsockfd, buffer, 4);
		fprintf(fp, "%s", buffer);
		printf("%s\n", buffer);
		ch++;
	}

	fclose(fp);

	printf("\n \n \n");

	int consonantes = readFile("glad_received.txt");
	printf("\n La cantidad de consonantes que habian eran: %d", consonantes);

	send(newsockfd, &consonantes, sizeof(consonantes), 0);

	printf("the file has been received. It has been saved");
	close(newsockfd);
	close(sockfd);
	return 0;
}