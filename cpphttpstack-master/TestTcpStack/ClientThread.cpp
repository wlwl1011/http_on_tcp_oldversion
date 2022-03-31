/* 
 * Copyright (C) 2012 Yee Young Han <websearch@naver.com> (http://blog.naver.com/websearch)
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA 
 */

#include "TestTcpStack.h"
#include "ServerUtility.h"
#include "Log.h"

THREAD_API ClientThread( LPVOID lpParameter )
{
	Socket hSocket = TcpConnect( "127.0.0.1", TCP_PORT );
	if( hSocket == INVALID_SOCKET )
	{
		CLog::Print( LOG_ERROR, "TcpConnect error" );
		return 0;
	}

	char szBuf[8192];

	memset( szBuf, 0, sizeof(szBuf) );

	while( 1 )
	{
		if( TcpRecv( hSocket, szBuf, sizeof(szBuf), 5 ) > 0 )
		{
			CLog::Print( LOG_NETWORK, "TcpRecv [%s] (client)", szBuf );
			memset( szBuf, 0, sizeof(szBuf) );
		}
		else
		{
			break;
		}
	}

	return 0;
}

bool StartClientThread( )
{
	for( int i = 0; i < 3; ++i )
	{
		if( StartThread( "ClientThread", ClientThread, NULL ) == false )
		{
			printf( "ClientThread start error\n" );
			return false;
		}
	}

	return true;
}
