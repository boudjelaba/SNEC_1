/*
simple serveur UDP sur RPi
Date 07-02-2022
compilateur g++
g++ -Wall -o srvUDP srvUDP.cpp -lwiringP
*/
#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h> // conversion types reseau ASCII
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <netdb.h>
#include <unistd.h>

// c++
#include <iostream>
#include <string>
// wiringPi pour gérer les périphériques
#include <wiringPi.h>

using namespace std;

#define portEcoute 26000
#define led 0 // GPIO 17
#define btn 1 // GPIO 18

void error(const char *msg);
void infoServeur(void);

int main(void)
{
	cout<<"Serveur UDP..."<<endl;
	cout<<"Reception ASCII 0 -> extinction LED"<<endl;
	cout<<"Reception ASCII 1 -> allumage LED"<<endl;
	cout<<"Reception ASCII 2 -> retourne etat du bouton"<<endl;
	cout<<"--------------------------------------------"<<endl;
	int sock, n;
	socklen_t tailleClient;
	struct sockaddr_in server;
	struct sockaddr_in client;
	char buf[1024];
//	creation du socket
	sock = socket(AF_INET, SOCK_DGRAM, 0);
		if (sock < 0) error("ouverture socket");
		else cout<<"socket ouvert"<<endl;
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_port = htons(portEcoute);
//	activation ecoute
	if (bind(sock, (struct sockaddr *)&server, sizeof(server)) < 0) error("binding");
	tailleClient = sizeof(struct sockaddr_in);
//	Affichage infos serveur
	infoServeur();
	// configuration peripheriques
	wiringPiSetup();   //numeros broches
	pinMode(led,OUTPUT); // LED en sortie
	pinMode(btn,INPUT);  // bouton en entrée

	while (1)
	{
	string mess="";
		// attente requete du client
		n = recvfrom(sock, buf, 1024, 0, (struct sockaddr *)&client, &tailleClient);
		if (n < 0) error("reception depuis client");
		// message recu
		cout<<"Reception message de "<<inet_ntoa(client.sin_addr)<<":"<<client.sin_port<<" -> ";
		cout<<buf<<endl;
		// analyse du message
		// le premier caractère de buff definit la tâche
		switch(*buf)
		{
            		case '0': mess="LED eteinte";
				  digitalWrite(led,LOW);
                    		  break;
            		case '1': mess="LED allumee";
				  digitalWrite(led,HIGH);
                    		  break;
			case '2': if(digitalRead(btn)) mess="1 (bouton relache)";
				  else mess="0 (bouton appuye)";
			break;
            		default : mess="commande inconnue";
		}
		// emission de la réponse
		n = sendto(sock, mess.c_str(), 17,0, (struct sockaddr *)&client, tailleClient);
		if (n < 0) error("sendto");
		else cout<<"Reponse -> "<<mess<<endl;
	}
	return 0;
}

void infoServeur()
{
   	char hotebuff[256];
	char *IPbuff;
	struct hostent *hote;
  
	gethostname(hotebuff, sizeof(hotebuff));   
 	hote = gethostbyname(hotebuff); 

	IPbuff=inet_ntoa(*((struct in_addr*) hote->h_addr_list[0]));

	cout<<"Machine -> "<<hotebuff<<" ";
	cout<<IPbuff<<" ecoute sur port "<<portEcoute<<endl;
}

void error(const char *msg)
{
	perror(msg);
	exit(0);
}
