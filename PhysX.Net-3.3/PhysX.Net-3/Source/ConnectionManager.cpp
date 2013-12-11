#include "StdAfx.h"
#include "ConnectionManager.h"
#include "Physics.h"
#include "Foundation.h"
//#include <PvdConnectionFlags.h>
//#include <PxDefaultAllocator.h> 

using namespace PhysX;
using namespace PhysX::VisualDebugger;
using namespace physx::debugger;

ConnectionManager::ConnectionManager(PvdConnectionManager* manager, PhysX::Physics^ owner)
{
	if (manager == NULL)
		throw gcnew ArgumentNullException("manager");
	ThrowIfNullOrDisposed(owner, "owner");

	_manager = manager;
	_physics = owner;

	ObjectTable::Add((intptr_t)_manager, this, owner);
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

bool ConnectionManager::IsConnected()
{
	return _manager->isConnected();
}
void ConnectionManager::Disconnect()
{
	_manager->disconnect();
}

void ConnectionManager::Connect(System::String^ host, Nullable<int> port, Nullable<TimeSpan> timeout, Nullable<VisualDebuggerConnectionFlag> connectionType, Nullable<bool> doubleBuffered)
{
	if (host == nullptr)
		throw gcnew ArgumentNullException("host");
	if (timeout.HasValue && timeout.Value < TimeSpan::Zero)
		throw gcnew ArgumentOutOfRangeException("Timeout cannot be less than zero", "timeout");

	PxAllocatorCallback* allocator = _physics->Foundation->GetAllocator();
	auto p = port.GetValueOrDefault(5425);
	auto to = (int)timeout.GetValueOrDefault(TimeSpan::FromSeconds(10)).TotalMilliseconds;
	auto f = (PvdConnectionType::Enum)(connectionType.HasValue ? (PxU32)connectionType.Value : (PxU32)PxVisualDebuggerExt::getAllConnectionFlags());
	auto h = Util::ToUnmanagedString(host);
	auto db = doubleBuffered.GetValueOrDefault(true);

	_manager->connect(*allocator, h, p, to, f, db);

	Marshal::FreeHGlobal(IntPtr(h));
}

PhysX::Physics^ ConnectionManager::Physics::get()
{
	return _physics;
}

PvdConnectionManager* ConnectionManager::UnmanagedPointer::get()
{
	return _manager;
}