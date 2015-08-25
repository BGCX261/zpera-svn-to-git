#include "../Socket.h"

void OnReceive(int isendID, char* buffer, int ireceivesize, int imaxsize)
{
	cout << "\tMsg from " << isendID << " : " << buffer << endl;
}

int main(int argc, char** argv)
{
	char inputbuff;

	int itype = -1;

	do 
	{
		printf("Input type (1=server, 2=client, q=quit): ");
		scanf("%c", &inputbuff);

		switch (inputbuff)
		{
		case '1':
			itype = 1;
			break;
		case '2':
			itype = 2;
			break;
		case 'q':
		case 'Q':
			return 0;
			break;
		default:
			break;
		}
	} while (-1 == itype);

	if (1 == itype)
	{
		CServer server(8888, OnReceive, SZBUFF);

		char buf[255];
		while (1)
		{
			cout << endl << "Input Command (list, info, send, port, quit/exit)" << endl;
			scanf("%s", buf);
			if (!strcmp(buf, "list"))
			{
				cout << "There are "<< server.client_number() << " clients connected.";
			}
			else if (!strcmp(buf, "info"))
			{
				cout << "input client UID (0 for all): ";
				int uid;
				scanf("%d", &uid);
				cout << server.client_info(uid) << endl;
			} 
			else if (!strcmp(buf, "port"))
			{
				cout << "Current listening port is " << server.localport() << endl ;
			} 
			else if (!strcmp(buf, "send"))
			{
				cout<< "input client UID (0 for all): " << endl ;
				int uid;
				scanf("%d", &uid);
				cout<< "input Message: ";
				scanf("%s", buf);
				server.send_message(uid, buf, sizeof(buf));
			} 
			else if (!strcmp(buf, "quit") || !strcmp(buf, "exit"))
			{
				break;
			} 
		}

	}
	else if (2 == itype)
	{
		srand((unsigned int)time(NULL));
		int iport = (1000 + rand()) % 12345;


		CClient clt(iport, "127.0.0.1", 8888, OnReceive, SZBUFF);

		char buf[SZBUFF];
		while (1)
		{
			cout << "Input message (use \"quit/exit\" to exit): " << endl;
			scanf("%s", buf);
			if (!strcmp(buf, "quit"))
			{
				break;
			}
			clt.send_message(buf, sizeof(buf));
		}
	}

	return 0;
}
