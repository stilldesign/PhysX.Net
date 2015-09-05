#include "StdAfx.h"
#include "Shape.h"
#include "Actor.h"
#include "RigidActor.h"
#include "Geometry.h"
#include "Serializable.h"
#include "BoxGeometry.h"
#include "SphereGeometry.h"
#include "CapsuleGeometry.h"
#include "PlaneGeometry.h"
#include "ConvexMeshGeometry.h"
#include "TriangleMeshGeometry.h"
#include "HeightFieldGeometry.h"
#include "ShapeUtil.h"
#include "RigidDynamic.h"

Shape::Shape(PxShape* shape, PhysX::IDisposable^ owner)
{
	ThrowIfNull(shape, "shape");
	ThrowIfNullOrDisposed(owner, "owner");

	_shape = shape;
	_owner = owner;

	// If the shape is not exclusive (i.e. created on a physics instance), then we'll need to know
	// what actors it's been attached to
	if (!shape->isExclusive())
		_attachedTo = gcnew List<RigidActor^>();

	ObjectTable::Add((intptr_t)_shape, this, owner);

	this->UnmanagedOwner = true;
}
Shape::~Shape()
{
	this->!Shape();
}
Shape::!Shape()
{
	OnDisposing(this, nullptr);

	if (this->Disposed)
		return;

	if (this->UnmanagedOwner)
	{
		// Shared shape - created on a Physics instance
		if (!_shape->isExclusive())
		{
			// Detach from all the actors
			for each (auto actor in _attachedTo->ToArray())
			{
				actor->DetachShape(this);
			}
			// TODO: Should this be needed? If we detach from all actors, this *should* be Count=0
			_attachedTo->Clear();
		}
		else
		{
			// Here, the shape was created for sole use on this actor. We call detach on our
			// parent actor, which will inturn delete/release this shape
			_shape->getActor()->detachShape(*_shape);
		}
	}

	_shape = NULL;

	OnDisposed(this, nullptr);
}

bool Shape::Disposed::get()
{
	return (_shape == NULL);
}

Serializable^ Shape::AsSerializable()
{
	return gcnew Serializable(_shape);
}

BoxGeometry^ Shape::GetBoxGeometry()
{
	PxBoxGeometry box;
	if (!_shape->getBoxGeometry(box))
		return nullptr;

	return BoxGeometry::ToManaged(box);
}
SphereGeometry^ Shape::GetSphereGeometry()
{
	PxSphereGeometry sphere;
	if (!_shape->getSphereGeometry(sphere))
		return nullptr;

	return SphereGeometry::ToManaged(sphere);
}
CapsuleGeometry^ Shape::GetCapsuleGeometry()
{
	PxCapsuleGeometry capsule;
	if (!_shape->getCapsuleGeometry(capsule))
		return nullptr;

	return CapsuleGeometry::ToManaged(capsule);
}
PlaneGeometry^ Shape::GetPlaneGeometry()
{
	PxPlaneGeometry plane;
	if (!_shape->getPlaneGeometry(plane))
		return nullptr;

	return PlaneGeometry::ToManaged(plane);
}
ConvexMeshGeometry^ Shape::GetConvexMeshGeometry()
{
	PxConvexMeshGeometry convexMesh;
	if (!_shape->getConvexMeshGeometry(convexMesh))
		return nullptr;

	return ConvexMeshGeometry::ToManaged(convexMesh);
}
TriangleMeshGeometry^ Shape::GetTriangleMeshGeometry()
{
	PxTriangleMeshGeometry triangleMesh;
	if (!_shape->getTriangleMeshGeometry(triangleMesh))
		return nullptr;

	return TriangleMeshGeometry::ToManaged(triangleMesh);
}
HeightFieldGeometry^ Shape::GetHeightFieldGeometry()
{
	PxHeightFieldGeometry heightField;
	if (!_shape->getHeightFieldGeometry(heightField))
		return nullptr;

	return HeightFieldGeometry::ToManaged(heightField);
}

Material^ Shape::GetMaterialFromInternalFaceIndex(int faceIndex)
{
	PxMaterial* material = _shape->getMaterialFromInternalFaceIndex(faceIndex);

	if (material == NULL)
		return nullptr;

	return ObjectTable::GetObject<Material^>((intptr_t)material);
}

IEnumerable<RigidActor^>^ Shape::AttachedTo::get()
{
	return _attachedTo;
}
void Shape::AddAttachedTo(RigidActor^ rigidActor)
{
	_attachedTo->Add(rigidActor);
}
void Shape::RemoveAttachedTo(RigidActor^ rigidActor)
{
	_attachedTo->Remove(rigidActor);
}

FilterData Shape::SimulationFilterData::get()
{
	return FilterData::ToManaged(_shape->getSimulationFilterData());
}
void Shape::SimulationFilterData::set(FilterData value)
{
	_shape->setSimulationFilterData(FilterData::ToUnmanaged(value));
}

FilterData Shape::QueryFilterData::get()
{
	return FilterData::ToManaged(_shape->getQueryFilterData());
}
void Shape::QueryFilterData::set(FilterData value)
{
	_shape->setQueryFilterData(FilterData::ToUnmanaged(value));
}

//

PhysX::GeometryType Shape::GeometryType::get()
{
	return ToManagedEnum(PhysX::GeometryType, _shape->getGeometryType());
}

PhysX::RigidActor^ Shape::Actor::get()
{
	// If the shape is 'exclusive', it's only used by one actor and that will be the owner/the object the shape was created on
	// See: PxShape::getActor()
	if (_shape->isExclusive())
		return (PhysX::RigidActor^)_owner;
	else
		return nullptr;
}
PhysX::Physics^ Shape::Physics::get()
{
	// If the shape is NOT 'exclusive', it was created on a Physics instance as opposed to on an actor.
	// See: PxShape::getActor()
	if (_shape->isExclusive())
		return nullptr;
	else
		return (PhysX::Physics^)_owner;
}
bool Shape::IsExclusive::get()
{
	return _shape->isExclusive();
}

Matrix Shape::GlobalPose::get()
{
	PxRigidActor* actor = _shape->getActor();

	if (actor == NULL)
		throw gcnew InvalidOperationException("The shape is attached to more than one actor. Use Shape.GetGlobalPose(actor) instead.");

	return MathUtil::PxTransformToMatrix(&PxShapeExt::getGlobalPose(*_shape, *actor));
}

String^ Shape::Name::get()
{
	return Util::ToManagedString(_shape->getName());
}
void Shape::Name::set(String^ value)
{
	if (_shape->getName() != NULL)
		Marshal::FreeHGlobal(IntPtr((char*)_shape->getName()));

	_shape->setName(Util::ToUnmanagedString(value));
}

Bounds3 Shape::WorldBounds::get()
{
	if (!this->IsExclusive)
		throw gcnew InvalidOperationException(String::Format("This method is only valid when the shape is exclusive, that is, when it was created on a RigidActor as opposed to having been created on a Physics instance."));

	PxBounds3 bounds = ShapeUtil::GetWorldBoundsUnmanaged(_shape, this->Actor->UnmanagedPointer);

	return Bounds3::ToManaged(bounds);
}

float Shape::ContactOffset::get()
{
	return _shape->getContactOffset();
}
void Shape::ContactOffset::set(float value)
{
	_shape->setContactOffset(value);
}

float Shape::RestOffset::get()
{
	return _shape->getRestOffset();
}
void Shape::RestOffset::set(float value)
{
	_shape->setRestOffset(value);
}

ShapeFlag Shape::Flags::get()
{
	return ToManagedEnum(ShapeFlag, _shape->getFlags());
}
void Shape::Flags::set(ShapeFlag value)
{
	_shape->setFlags((PxShapeFlags)(PxU32)value);
}

Matrix Shape::LocalPose::get()
{
	return MathUtil::PxTransformToMatrix(&_shape->getLocalPose());
}
void Shape::LocalPose::set(Matrix value)
{
	_shape->setLocalPose(MathUtil::MatrixToPxTransform(value));
}

array<PhysX::Material^>^ Shape::Materials::get()
{
	auto managedMaterials = gcnew List<Material^>();

	int n = _shape->getNbMaterials();

	PxMaterial** materials = new PxMaterial*[n];
	_shape->getMaterials(materials, n);

	for (int i = 0; i < n; i++)
	{
		PxMaterial* mat = materials[i];
		Material^ s = (Material^)ObjectTable::TryGetObject((intptr_t)mat);
		managedMaterials->Add(s);
	}

	delete[] materials;

	return managedMaterials->ToArray();
}
void Shape::Materials::set(array<PhysX::Material^>^ value)
{
	int n = value->Length;

	PxMaterial** materials = new PxMaterial*[n];
	for (int i = 0; i < n; i++)
		materials[i] = value[i]->UnmanagedPointer;

	_shape->setMaterials(materials, n);

	delete[] materials;
}

PxShape* Shape::UnmanagedPointer::get()
{
	return _shape;
}