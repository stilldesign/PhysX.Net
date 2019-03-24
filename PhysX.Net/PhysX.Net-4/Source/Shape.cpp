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
#include "Scene.h"
#include "Physics.h"

// TODO: Detached shapes (i.e. no parent actor)
Shape::Shape(PxShape* shape, PhysX::RigidActor^ parentActor)
{
	if (shape == NULL)
		throw gcnew ArgumentException("shape");
	ThrowIfNullOrDisposed(parentActor, "parentActor");

	_shape = shape;
	_actor = parentActor;

	ObjectTable::Instance->Add((intptr_t)_shape, this, parentActor);

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
		if (_shape->isExclusive())
			_shape->getActor()->detachShape(*_shape);
		else
			_shape->release();
	}

	_shape = NULL;

	OnDisposed(this, nullptr);
}

bool Shape::Disposed::get()
{
	return (_shape == NULL);
}

Shape^ Shape::Clone()
{
	if (_actor->Scene == nullptr)
		throw gcnew InvalidOperationException("The shape does not belong to a scene. Make sure Scene.AddActor() has been called prior, or specify the Physics argument in the other overload.");

	return Clone(_actor->Scene->Physics, _shape->isExclusive());
}
Shape^ Shape::Clone(Physics^ physics, bool isExclusive)
{
	ThrowIfNullOrDisposed(physics, "physics");

	PxShape* cloned = PxCloneShape(*physics->UnmanagedPointer, *_shape, isExclusive);

	return gcnew Shape(cloned, _actor);
}

Serializable^ Shape::AsSerializable()
{
	return gcnew Serializable(_shape);
}

Geometry^ Shape::GetGeometry()
{
	switch (_shape->getGeometryType())
	{
	case PxGeometryType::eBOX:
		return this->GetBoxGeometry();
	case PxGeometryType::eCAPSULE:
		return this->GetCapsuleGeometry();
	case PxGeometryType::eCONVEXMESH:
		return this->GetConvexMeshGeometry();
	case PxGeometryType::eHEIGHTFIELD:
		return this->GetHeightFieldGeometry();
	case PxGeometryType::ePLANE:
		return this->GetPlaneGeometry();
	case PxGeometryType::eSPHERE:
		return this->GetSphereGeometry();
	case PxGeometryType::eTRIANGLEMESH:
		return this->GetTriangleMeshGeometry();

	default: return nullptr;
	}
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

void Shape::SetGeometry(Geometry^ geometry)
{
	ThrowIfNull(geometry, "geometry");

	PxGeometry* g = geometry->ToUnmanaged();

	_shape->setGeometry(*g);

	SAFE_DELETE(g);
}

Material^ Shape::GetMaterialFromInternalFaceIndex(int faceIndex)
{
	PxMaterial* material = _shape->getMaterialFromInternalFaceIndex(faceIndex);

	if (material == NULL)
		return nullptr;

	return ObjectTable::Instance->GetObject<Material^>((intptr_t)material);
}

//

bool Shape::IsExclusive::get()
{
	return _shape->isExclusive();
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
	return _actor;
}

Matrix Shape::GlobalPose::get()
{
	PxRigidActor* actor = _shape->getActor();

	if (actor == NULL)
		throw gcnew InvalidOperationException("The shape is attached to more than one actor. Use Shape.GetGlobalPose(actor) instead.");

	return MathUtil::PxTransformToMatrix(&PxShapeExt::getGlobalPose(*_shape, *actor));
}

Vector3 Shape::GlobalPosePosition::get()
{
	PxRigidActor* actor = _shape->getActor();

	if (actor == NULL)
		throw gcnew InvalidOperationException("The shape is attached to more than one actor. Use Shape.GetGlobalPose(actor) instead.");

	return MV(PxShapeExt::getGlobalPose(*_shape, *actor).p);
}

Quaternion Shape::GlobalPoseQuat::get()
{
	PxRigidActor* actor = _shape->getActor();

	if (actor == NULL)
		throw gcnew InvalidOperationException("The shape is attached to more than one actor. Use Shape.GetGlobalPose(actor) instead.");

	return MathUtil::PxQuatToQuaternion(PxShapeExt::getGlobalPose(*_shape, *actor).q);
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
	PxBounds3 bounds = ShapeUtil::GetWorldBoundsUnmanaged(_shape, _actor->UnmanagedPointer);

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

Vector3 Shape::LocalPosePosition::get()
{
	return MV(_shape->getLocalPose().p);
}
void Shape::LocalPosePosition::set(Vector3 value)
{
	PxTransform t = _shape->getLocalPose();
	t.p = UV(value);

	_shape->setLocalPose(t);
}

Quaternion Shape::LocalPoseQuat::get()
{
	return MathUtil::PxQuatToQuaternion(_shape->getLocalPose().q);
}
void Shape::LocalPoseQuat::set(Quaternion value)
{
	PxTransform t = _shape->getLocalPose();
	t.q = MathUtil::QuaternionToPxQuat(value);

	_shape->setLocalPose(t);
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
		Material^ s = ObjectTable::Instance->TryGetObject<Material^>((intptr_t)mat);
		managedMaterials->Add(s);
	}

	delete[] materials;

	return managedMaterials->ToArray();
}
void Shape::Materials::set(array<PhysX::Material^>^ value)
{
	ThrowIfNull(value, "value");

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