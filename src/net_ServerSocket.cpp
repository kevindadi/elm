/*
 *	$Id$
 *	ServerSocket class implementation
 *
 *	This file is part of OTAWA
 *	Copyright (c) 2012, IRIT UPS.
 *
 *	ELM is free software; you can redistribute it and/or modify
 *	it under the terms of the GNU General Public License as published by
 *	the Free Software Foundation; either version 2 of the License, or
 *	(at your option) any later version.
 *
 *	ELM is distributed in the hope that it will be useful,
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *	GNU General Public License for more details.
 *
 *	You should have received a copy of the GNU General Public License
 *	along with ELM; if not, write to the Free Software
 *	Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 */

#ifdef __unix
#	include <sys/types.h>
#	include <sys/socket.h>
#	include <netinet/in.h>
#	include <arpa/inet.h>
#	include <unistd.h>
#	include <errno.h>
#	include <string.h>
#	include <elm/string.h>
#	include <elm/io/UnixInStream.h>
#	include <elm/io/UnixOutStream.h>
#else
#	error "unsupported platform"
#endif
#include <elm/net/ServerSocket.h>

namespace elm { namespace net {

// unix socket server implementation
#ifdef __unix

	class NativeServerSocket: public ServerSocket {
	public:
		NativeServerSocket(void): _port(-1), _fd(-1) { }
		NativeServerSocket(int port): _port(port), _fd(-1) { }
		virtual ~NativeServerSocket(void) { close(); }
		virtual int port(void) const { return _port; }

		virtual void open(void) throw(Exception) {

			// create the socket
			_fd = socket(AF_INET, SOCK_STREAM, 0);
			if(_fd == -1)
				throw Exception(_ << "cannot create socket: " << strerror(errno));

			// set the REUEADDR option
			int b = 1;
			int res = setsockopt(_fd, SOL_SOCKET, SO_REUSEADDR, &b, sizeof(b));
			if (res == -1)
				throw Exception(_ << "cannot set REUSEADDR option: " << strerror(errno));

			// bind the socket
			struct sockaddr_in addr;
			addr.sin_family = AF_INET;
			addr.sin_port = htons(_port < 0 ? 0 : _port);
			addr.sin_addr.s_addr = INADDR_ANY;
			memset(&addr.sin_zero, 0, 8);
			res = bind(_fd, (struct sockaddr *)&addr, sizeof(struct sockaddr));
			if(res == -1) {
				close();
				throw Exception(_ << "cannot bind the socket: " << strerror(errno));
			}

			// start listening
			if(::listen(_fd, 5) == -1) {
				close();
				throw Exception(_ << "cannot listening: " << strerror(errno));
			}

			// if required, get back the port name
			if(_port < 0) {
				struct sockaddr_in maddr;
				socklen_t mlen = sizeof(maddr);
				getsockname(_fd, (struct sockaddr *)&maddr, &mlen);
				_port = maddr.sin_port;
			}
		}

		virtual Connection *listen(void) throw(Exception) {

			// accept the connection
			struct sockaddr_in caddr;
			socklen_t size = sizeof(caddr);
			int con = accept(_fd, (struct sockaddr *)&caddr, &size);
			if(con == -1)
				throw net::Exception(_ << "cannot accept: " << strerror(errno));

			// make the connection
			return new Connection(con);
		}


		virtual void close(void) {
			if(_fd >= 0)
				::close(_fd);
			_fd = -1;
		}

	private:
		int _port;
		int _fd;
	};


// undefined implementation
#else
#	error "unsupported net"
#endif

/**
 * @class Exception
 * Exception thrown for network errors.
 */


/**
 * Build an exception with the given message.
 * @param message	Exception message.
 */
Exception::Exception(const string& message): elm::MessageException(message) {
}


/**
 * @class Connection
 * Represents a connection on a server socket. The connection is bidirectional
 * formed of an in and an out stream. The connection is either closed by the client,
 * or by a deletion of this object.
 */


/**
 * Build a connection with the given stream.
 * @param in	Input stream.
 * @param out	Output stream.
 */
Connection::Connection(int fd): _fd(fd), _in(fd), _out(fd) {
}


/**
 * Cause the deconnection.
 */
Connection::~Connection(void) {
	::close(_fd);
}


/**
 * @fn io::InStream& Connection::in(void) const;
 * Get the input stream of the connection.
 * @return	Input stream.
 */


/**
 * @fn io::InStream& Connection::out(void) const;
 * Get the output stream of the connection.
 * @return	Input stream.
 */


/**
 * @class ServerSocket
 * This class provides a way to listen on a port for connection.
 * For each connection, a dedicated object is created and returned.
 */


/**
 * Build a server without specifiying a precise port.
 * @return	Built server socket.
 */
ServerSocket *ServerSocket::make(void) {
	return new NativeServerSocket();
}


/**
 * Build a server working on the given port.
 * @param port	Port of the server.
 * @return	Built server socket.
 */
ServerSocket *ServerSocket::make(int port) {
	return new NativeServerSocket(port);
}


/**
 */
ServerSocket::~ServerSocket(void) {
}


/**
 * @fn int ServerSocket::port(void);
 * Get the current port. This information is only meaningful once
 * the server socket is opened.
 * @return	Current socket server port.
 */


/**
 * @fn void ServerSocket::open(void) throw(Exception);
 * Open the port.
 * @throw Exception		Thrown if there is an error during the open.
 */

/**
 * void ServerSocket::close(void);
 * Close the server socket.
 */

/**
 * @fn void ServerSocket::listen(void) throw(Exception);
 * Listen for a connection and return it.
 * @throw Exception		Thrown if there is an error during the open.
 */


/**
 * @class Server
 * This class provides a way to listen on a port for connection as server.
 * For each connection, a dedicated object is created and the method onConnection()
 * is called: this lets an inheriting class to specialize the processing of this connection.
 */


/**
 * Build a server on non-predefined port.
 */
Server::Server(void): _port(-1), sock(0) {
}


/**
 * Build a server on the given port.
 * @param port	Port to use.
 */
Server::Server(int port): _port(port), sock(0) {
}


/**
 */
Server::~Server(void) {
	close();
}


/**
 * Open the server.
 */
void Server::open(void) throw(Exception) {
	if(_port < 0)
		sock = ServerSocket::make();
	else
		sock = ServerSocket::make(_port);
	sock->open();
}


/**
 * Close the connection and stop the managing of the server
 * (end of function manage()).
 */
void Server::close(void) {
	on = false;
	if(sock)
		delete sock;
}

/**
 * Manage the server, that is, get the incoming connections
 * until it is requested to close.
 * @throw Exception		Thrown if there is an error during the open.
 */
void Server::manage(void) throw(Exception) {
	on = true;
	while(on) {
		Connection *con = sock->listen();
		onConnection(*con);
		delete(con);
	}
}


/**
 * @fn void Server::onConnection(Connection *connection);
 * Called each time a connection arises. The current connection (with input and output streams)
 * is passed to let the application to process it.
 * @param connection	Created connection.
 */


} }	// elm::net
