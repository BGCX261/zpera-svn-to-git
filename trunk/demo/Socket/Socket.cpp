#include "Socket.h"

void CAsyncSock::_write_log(const std::string& strMsg)
{
	//try
	//{
	//	long tmsp = time( NULL );
	//	char szLineName[ SZBUFF ];
	//	
	//	sprintf( szLineName, "%8i\t\t", tmsp );
	//	ofstream of(LOG_FILE);
	//	
	//	of<<szLineName<<strMsg<<endl<<endl;
		
	time_t tmsp = time( NULL );
	string strTm( ctime( &tmsp ) );
	cout<<endl << strTm << "\t" << strMsg << endl;
		
	//	cout<<"A log is stored... ..."<<endl;
	//	
	//	of.close(); 
	//}
	//catch( exception& e )
	//{
	//	_error( const_cast<char*>( e.what() ) );
	//}
}
	
void CAsyncSock::_error(const std::string& strMsg)
{
	time_t tmsp = time( NULL );
	string strTm( ctime( &tmsp ) );
	cout << endl << strTm << "\t!error~! "<< strMsg << endl;
}

void CAsyncSock::close(SOCKET& sock)
{
	if (0 != sock && INVALID_SOCKET != sock)
	{
		closesocket(sock);
		sock = 0;
	}
}

CClient::CClient(int ilocalport, const char m_szIP[], int iremoteport, OnReceivePtr onreceive, int imaxbuf)
{	
	if( ( m_connectinfo.Socket = socket( AF_INET, SOCK_STREAM, 0 ) ) == INVALID_SOCKET )
	{
		_error( "Can't create a sock at this client!" );
		return;
	}
	_write_log("Client socket is setup.");

	m_ilocalport = ilocalport;
	sockaddr_in tempaddr;
	memset( &tempaddr, 0, sizeof( tempaddr ) );
	tempaddr.sin_family = AF_INET;
	tempaddr.sin_addr.s_addr = htons( INADDR_ANY );
	tempaddr.sin_port   = htons( ilocalport );
	int ret = bind( m_connectinfo.Socket, (SOCKADDR*)&tempaddr, sizeof( tempaddr ) );
	if( ret < 0 )
	{
		_error( "Can't bind to the computer(client)!" );
		close( m_connectinfo.Socket );
		return;
	}//
	_write_log("Client socket is binded.");

	m_irevsize = 0;
	m_connectinfo.bConnected = false;
	m_czrevbuff = NULL;

	connectserver(m_szIP, iremoteport, onreceive, imaxbuf);
}

CClient::~CClient()
{
	close(m_connectinfo.Socket);

	if (NULL != m_czrevbuff)
	{
		delete[] m_czrevbuff;
	}
}

void CClient::connectserver(const char m_szIP[], int iport, OnReceivePtr callfun, int imax)
{
	if (m_connectinfo.Socket == INVALID_SOCKET || m_connectinfo.Socket == 0)
	{
		_error("Network is not prepared!");
		return;
	}

	if (false != m_connectinfo.bConnected)
	{
		_error("Already connected!");
		return;
	}

	memset( &m_connectinfo.Sockaddr, 0, sizeof( m_connectinfo.Sockaddr ) );
	m_connectinfo.Sockaddr.sin_family = AF_INET;
	m_connectinfo.Sockaddr.sin_addr.s_addr = inet_addr(m_szIP);
	m_connectinfo.Sockaddr.sin_port = htons( iport );

	int iret = connect( m_connectinfo.Socket, (SOCKADDR*)&m_connectinfo.Sockaddr, sizeof( m_connectinfo.Sockaddr ) );
	if( iret < 0 )
	{
		_error( "The client can't connect to the server!" );
		return;
	}	

	m_connectinfo.bConnected = true;
	_write_log("Client is connected to server.");

	m_ponreceive = callfun;
	if (m_irevsize != imax)
	{
		if (NULL != m_czrevbuff)
		{
			delete[] m_czrevbuff;
		}
	}

	m_irevsize = imax;
	m_czrevbuff = new char[m_irevsize];

	m_hreceive = (HANDLE) _beginthread(receive_message, 0, this);
}

void CClient::send_message(char* buffer, int isize)
{
	if (m_connectinfo.Socket == INVALID_SOCKET || m_connectinfo.Socket == 0 || m_connectinfo.bConnected == false)
	{
		_error("Network is not prepared!");
		return;
	}

	int iret = send( m_connectinfo.Socket, buffer, isize, 0 );
	if( iret < 0 )
	{
		_error( "Can not send message to connected server!" );
	}
	_write_log("Message is sended.");

}

void CClient::receive_message(LPVOID pvoid)
{
	CClient *client = (CClient *)pvoid;


	int iret;
	while(0 < (iret = recv( client->m_connectinfo.Socket, client->m_czrevbuff, client->m_irevsize, 0  )))
	{
		(client->m_ponreceive)(0, client->m_czrevbuff, iret, client->m_irevsize);
	}

	_write_log("Server is quit.");

	return;
}

CServer::CServer(int ilocalport, OnReceivePtr onreceive, int imaxbuf)
{
	m_bListening = false;
	m_ponreceive = onreceive;
	m_iUID = 0;
	m_irevsize = imaxbuf;

	m_bConnectPool[111] = true;
	memset(m_bConnectPool, 0, sizeof(m_bConnectPool));

	if((m_serverinfo.Socket = socket( AF_INET, SOCK_STREAM, IPPROTO_TCP ) ) != INVALID_SOCKET)
	{
		_write_log("Server socket is setup.");

		memset( &m_serverinfo.Sockaddr, 0, sizeof( m_serverinfo.Sockaddr ) );
		m_serverinfo.Sockaddr.sin_family = AF_INET;
		m_serverinfo.Sockaddr.sin_port   = htons( ilocalport );
		m_serverinfo.Sockaddr.sin_addr.s_addr = htons( INADDR_ANY );
		
		int ret = bind( m_serverinfo.Socket, (SOCKADDR*) &m_serverinfo.Sockaddr, sizeof( m_serverinfo.Sockaddr ) );
		if(ret < 0 )
		{
			int err = WSAGetLastError();
			_error( "Can't bind to this computer(server)!" );
			close( m_serverinfo.Socket );
			return;
		}//
		_write_log("Server socket is binded.");
		
		ret = listen( m_serverinfo.Socket, SOMAXCONN );
		if(ret < 0 )
		{
			_error( "The server can't listen at the port!" );
			close( m_serverinfo.Socket );
			return;
		}
		m_bListening = true;
		_write_log("Server socket is listen....");

		HANDLE m_hlistenthread = (HANDLE) _beginthread(listenandwait, 0, this);		
		_write_log("Listen thread starts successful.");
	}
}//

CServer::~CServer()
{
	close( m_serverinfo.Socket ); 

	SocketVector::iterator iter;
	for (iter = m_connectinfo.begin(); iter != m_connectinfo.end(); ++iter)
	{
		ConnectInfo *temp = *iter;
		close(temp->Socket);
		if (NULL != temp->czrevbuff)
		{
			delete[] temp->czrevbuff;
		}
		delete temp;
	}
}//

void CServer::listenandwait(PVOID pvoid)
{
	CServer *pserver = (CServer *)pvoid;

	if (pserver->m_serverinfo.Socket == INVALID_SOCKET || pserver->m_serverinfo.Socket == 0 || pserver->m_bListening == false)
	{
		_error("Network is not prepared!");
		return;
	}


	ConnectInfo tempinfo;
	int iLen = sizeof(tempinfo.Sockaddr);
	while(true)
	{
		if( ( tempinfo.Socket = accept( pserver->m_serverinfo.Socket, (SOCKADDR*) &(tempinfo.Sockaddr), &iLen ) )  == INVALID_SOCKET )
		{
			pserver->_error( "The client can't be accepted by the server!" );
			return;
		}

		if (pserver->m_bConnectPool[pserver->m_iUID])
		{
			int itempcount = pserver->m_iUID;
			do 
			{
				itempcount = (itempcount + 1) % MAX_CONNECT;
			} while (pserver->m_bConnectPool[itempcount] && itempcount != pserver->m_iUID);

			if (itempcount == pserver->m_iUID)
			{
				pserver->_error( "A new commer, but Connect pool is full. Rejected!" );
				closesocket(tempinfo.Socket);

				continue;
			}
			pserver->m_iUID = itempcount;
		}

		pserver->m_bConnectPool[pserver->m_iUID] = true;
		tempinfo.iUID = pserver->m_iUID;
		tempinfo.ponreceive = pserver->m_ponreceive;
		tempinfo.irevsize = pserver->m_irevsize;
		tempinfo.czrevbuff = new char[tempinfo.irevsize];
		tempinfo.caller = pserver;

		char buff[SZBUFF];
		sprintf(buff, "ID: %d\tIP: %s, Port:%d is connected.", tempinfo.iUID + 1, inet_ntoa(tempinfo.Sockaddr.sin_addr), ntohs(tempinfo.Sockaddr.sin_port));
		pserver->_write_log(buff);
		pserver->m_connectinfo.push_back(new ConnectInfo(tempinfo));

		tempinfo.hrecvthread = (HANDLE) _beginthread(pserver->wait_for_receive_from_client, 0, pserver->m_connectinfo[pserver->m_connectinfo.size() - 1]);
	}//
}//

void CServer::wait_for_receive_from_client(PVOID pvoid)
{
	ConnectInfo *sockinfo = (ConnectInfo *)pvoid;

	int iret;	
	char szRet[SZBUFF];
	while( (iret = recv( sockinfo->Socket, sockinfo->czrevbuff, sockinfo->irevsize, 0  )) > 0 )
	{
		sprintf(szRet, "ID %d sends a message.", sockinfo->iUID + 1);
		_write_log(szRet);
		(*sockinfo->ponreceive)(sockinfo->iUID, sockinfo->czrevbuff, iret, sockinfo->irevsize);
	}

	sprintf(szRet, "Client ID %d is quit.", sockinfo->iUID + 1);
	_write_log(szRet);

	sockinfo->caller->RemoveClinet(sockinfo->iUID);

	return;
}//

void CServer::RemoveClinet(int iUID)
{
	SocketVector::iterator iter = m_connectinfo.begin();

	for(;m_connectinfo.end() != iter; ++iter)
	{
//		ConnectInfo* temp = ;

		if(iUID != (*iter)->iUID) continue;

		m_bConnectPool[iUID] = false;

		m_connectinfo.erase(iter);

		break;;
	}
}

bool CServer::send_message(unsigned iUID, char* buffer, int isize)
{
	unsigned i;
	if(m_connectinfo.size()<=iUID)
		return false;
	if (0 == iUID)
	{
		for (i = 0; i < m_connectinfo.size(); ++i)
		{
			if(false == send_message(i + 1, buffer, isize))
			{
				_error( "Can not send message to connected client!" );
				return false;
			}
		}
		return true;
	}
	
	if( send( m_connectinfo[iUID - 1]->Socket, buffer, isize, 0 ) < 0 )
	{
		return false;
	}//

	return true;
}//

string CServer::client_info(unsigned iUID)
{
	string strRet = "";

	if (iUID < 0 || iUID > m_connectinfo.size())
	{
		_error("Error input ID!");
		return strRet;
	}

	if (iUID == 0)
	{
		if (m_connectinfo.size() == 0)
		{
			_error("No client connected!");
		}
		else
		{
			for (unsigned i = 1; i <= m_connectinfo.size(); ++i)
			{
				strRet += client_info(i);
			}
		}
	}
	else
	{
		char buffer[SZBUFF];
		ConnectInfo *psockinfo = m_connectinfo[iUID - 1];
		sprintf(buffer, "%s", inet_ntoa(psockinfo->Sockaddr.sin_addr));
		sprintf(buffer, "ID: %d IP: %s Port: %d", psockinfo->iUID, inet_ntoa(psockinfo->Sockaddr.sin_addr), ntohs(psockinfo->Sockaddr.sin_port));
		strRet = string(buffer);
	}

	return strRet;
}
