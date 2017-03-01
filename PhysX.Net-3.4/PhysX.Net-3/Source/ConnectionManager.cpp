#include "StdAfx.h"
#include "ConnectionManager.h"
#include "Physics.h"
#include "Foundation.h"
//#include <PvdConnectionFlags.h>

using namespace PhysX;
using namespace PhysX::VisualDebugger;

ConnectionManager::ConnectionManager()
{

}
ConnectionManager::~ConnectionManager()
{
	this->!ConnectionManager();
}
ConnectionManager::!ConnectionManager()
{
	OnDisposing(this, nullptr);

	if (this->Disposed)
		return;

	_manager->disconnect();

	// PxPhysics owns the connection manager
	//_manager->release();

	_manager = NULL;

	OnDisposed(this, nullptr);
}

bool ConnectionManager::Disposed::get()
{
	return (_manager == NULL);
}

bool ConnectionManager::IsConnected::get()
{
	return _manager->isConnected();
}
void ConnectionManager::Disconnect()
{
	_manager->disconnect();
}

void ConnectionManager::Connect(System::String^ host, Nullable<int> port, Nullable<TimeSpan> timeout, Nullable<InstrumentationFlag> connectionType)
{
	if (host == nullptr)
		throw gcnew ArgumentNullException("host");
	if (timeout.HasValue && timeout.Value < TimeSpan::Zero)
		throw gcnew ArgumentOutOfRangeException("Timeout cannot be less than zero", "timeout");

	auto port_ = port.GetValueOrDefault(5425);
	auto timeout_ = (int)timeout.GetValueOrDefault(TimeSpan::FromSeconds(10)).TotalMilliseconds;
	auto host_ = Util::ToUnmanagedString(host);

	auto transport = PxDefaultPvdSocketTransportCreate(host_, port_, timeout_);

	_manager->connect(*transport, PxPvdInstrumentationFlag::eALL);

	Marshal::FreeHGlobal(IntPtr(host_));
}

ConnectionManager^ ConnectionManager::GetInstance(Foundation^ foundation)
{
	PxPvd* pvd = PxCreatePvd(*foundation->UnmanagedPointer);

	auto connectionManager = gcnew ConnectionManager();
	connectionManager->_manager = pvd;

	return connectionManager;
}

PxPvd* ConnectionManager::UnmanagedPointer::get()
{
	return _manager;
}