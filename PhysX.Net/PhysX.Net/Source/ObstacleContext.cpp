#include "StdAfx.h"
#include "ObstacleContext.h"
#include "ControllerManager.h"

ObstacleContext::ObstacleContext(PxObstacleContext* context, ControllerManager^ owner)
{
	if (context == NULL)
		throw gcnew ArgumentNullException("context");
	ThrowIfNullOrDisposed(owner, "owner");

	_context = context;

	ObjectTable::Instance->Add((intptr_t)context, this, owner);
}
ObstacleContext::~ObstacleContext()
{
	this->!ObstacleContext();
}
ObstacleContext::!ObstacleContext()
{
	OnDisposing(this, nullptr);

	if (this->Disposed)
		return;

	_context->release();
	_context = NULL;

	OnDisposed(this, nullptr);
}

bool ObstacleContext::Disposed::get()
{
	return (_context == NULL);
}

int ObstacleContext::AddObstacle(Obstacle^ obstacle)
{
	if (obstacle == nullptr)
		throw gcnew ArgumentNullException("obstacle");

	ObstacleHandle handle = _context->addObstacle(*obstacle->UnmanagedPointer);

	return handle;

	//PxObstacle* o = obstacle->UnmanagedPointer;

	//switch (o->getType())
	//{
	//	case PxGeometryType::Box:
	//		_context->addObstacle(
	//	break;
	//	case PxGeometryType::Capsule:

	//	break;
	//}
}
 
bool ObstacleContext::RemoveObstacle(int handle)
{
	return _context->removeObstacle(handle);
}
		
bool ObstacleContext::UpdateObstacle(int handle, Obstacle^ obstacle)
{
	if (obstacle == nullptr)
		throw gcnew ArgumentNullException("obstacle");

	return _context->updateObstacle(handle, *obstacle->UnmanagedPointer);
}

Obstacle^ ObstacleContext::GetObstacle(int i)
{
	throw gcnew NotImplementedException();
}

int ObstacleContext::NumberOfObstacles::get()
{
	return _context->getNbObstacles();
}

PxObstacleContext* ObstacleContext::UnmanagedPointer::get()
{
	return _context;
}