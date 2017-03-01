#include "StdAfx.h"
#include "Connection.h"
#include "Physics.h"

using namespace PhysX::VisualDebugger;

Connection::Connection(physx::PxPvd* connection, PhysX::Physics^ owner)
{
	if (connection == NULL)
		throw gcnew ArgumentNullException("connection");
	ThrowIfNullOrDisposed(owner, "owner");

	_connection = connection;

	ObjectTable::Add((intptr_t)_connection, this, owner);
}
Connection::~Connection()
{
	this->!Connection();
}
Connection::!Connection()
{
	OnDisposing(this, nullptr);

	if (this->Disposed)
		return;

	//SAFE_DELETE(_connection);
	// TODO: Delete the connection object somehow
	_connection->disconnect();
	_connection = NULL;

	OnDisposed(this, nullptr);
}

bool Connection::Disposed::get()
{
	return (_connection == NULL);
}

void Connection::Connect()
{
	//_connection->connect()
}

physx::PxPvd* Connection::UnmanagedPointer::get()
{
	return _connection;
}