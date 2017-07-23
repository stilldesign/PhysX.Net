#include "StdAfx.h"
#include "Pvd.h"
#include "Physics.h"
#include "Foundation.h"

using namespace PhysX;
using namespace PhysX::VisualDebugger;

Pvd::Pvd(Foundation^ foundation)
{
	ThrowIfNullOrDisposed(foundation, "foundation");

	_pvd = PxCreatePvd(*foundation->UnmanagedPointer);

	ObjectTable::Instance->Add((intptr_t)_pvd, this, foundation);
}
Pvd::~Pvd()
{
	this->!Pvd();
}
Pvd::!Pvd()
{
	OnDisposing(this, nullptr);

	if (this->Disposed)
		return;

	_pvd->disconnect();
	// TODO: Calling PxPvd::release() causes a exception in shdfnd::BroadcastingAllocator for some reason
	//_pvd->release();
	_pvd = NULL;

	OnDisposed(this, nullptr);
}

bool Pvd::Disposed::get()
{
	return (_pvd == NULL);
}

bool Pvd::IsConnected(bool useCachedStatus)
{
	return _pvd->isConnected(useCachedStatus);
}
void Pvd::Disconnect()
{
	_pvd->disconnect();
}

void Pvd::Connect(System::String^ host, Nullable<int> port, Nullable<TimeSpan> timeout, Nullable<InstrumentationFlag> connectionType)
{
	if (host == nullptr)
		throw gcnew ArgumentNullException("host");
	if (timeout.HasValue && timeout.Value < TimeSpan::Zero)
		throw gcnew ArgumentOutOfRangeException("Timeout cannot be less than zero", "timeout");

	auto port_ = port.GetValueOrDefault(5425);
	auto timeout_ = (int)timeout.GetValueOrDefault(TimeSpan::FromSeconds(10)).TotalMilliseconds;
	auto host_ = Util::ToUnmanagedString(host);

	auto transport = PxDefaultPvdSocketTransportCreate(host_, port_, timeout_);

	_pvd->connect(*transport, PxPvdInstrumentationFlag::eALL);

	Marshal::FreeHGlobal(IntPtr(host_));
}

PxPvd* Pvd::UnmanagedPointer::get()
{
	return _pvd;
}