#include "StdAfx.h"
#include "HeightFieldGeometry.h"

HeightFieldGeometry::HeightFieldGeometry()
	: Geometry(GeometryType::Heightfield)
{
	
}
HeightFieldGeometry::HeightFieldGeometry(PhysX::HeightField^ heightField)
	: HeightFieldGeometry(heightField, (MeshGeometryFlag)0, 1, 1, 1)
{

}
HeightFieldGeometry::HeightFieldGeometry(PhysX::HeightField^ heightField, MeshGeometryFlag flags, float heightFieldScale, float rowScale, float columnScale)
	: Geometry(GeometryType::Heightfield)
{
	this->HeightField = heightField;
	this->HeightFieldFlags = flags;
	this->HeightScale = heightFieldScale;
	this->RowScale = rowScale;
	this->ColumnScale = columnScale;
}

PxHeightFieldGeometry HeightFieldGeometry::ToUnmanaged(HeightFieldGeometry^ geom)
{
	ThrowIfNull(geom, "geom");

	PxHeightFieldGeometry g;
		g.columnScale = geom->ColumnScale;
		g.heightField = (geom->HeightField == nullptr ? NULL : geom->HeightField->UnmanagedPointer);
		g.heightFieldFlags = ToUnmanagedEnum(PxMeshGeometryFlag, geom->HeightFieldFlags);
		g.heightScale = geom->HeightScale;
		g.rowScale = geom->RowScale;

	return g;
}
HeightFieldGeometry^ HeightFieldGeometry::ToManaged(PxHeightFieldGeometry geom)
{
	auto g = gcnew HeightFieldGeometry();
		g->ColumnScale = geom.columnScale;
		g->HeightField = ObjectTable::Instance->GetObject<PhysX::HeightField^>((intptr_t)geom.heightField);
		g->HeightFieldFlags = ToManagedEnum(MeshGeometryFlag, geom.heightFieldFlags);
		g->HeightScale = geom.heightScale;
		g->RowScale = geom.rowScale;

	return g;
}

PxGeometry* HeightFieldGeometry::ToUnmanaged()
{
	auto g = new PxHeightFieldGeometry();
	
	*g = ToUnmanaged(this);

	return g;
}

bool HeightFieldGeometry::IsValid()
{
	//if (mType != PxGeometryType::eHEIGHTFIELD)
	//	return false;
	if (!PxIsFinite(HeightScale) || !PxIsFinite(RowScale) || !PxIsFinite(ColumnScale))
		return false;
	if (RowScale <= 0.0f || ColumnScale <= 0.0f || HeightScale <= 0.0f)
		return false;
	if (this->HeightField == nullptr)
		return false;

	return true;
}