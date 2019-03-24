#pragma once

#include "HeightField.h"
#include "GeometryEnum.h"
#include "Geometry.h"

namespace PhysX
{
	/// <summary>
	/// Height field geometry class.
	/// This class unifies a height field object with a scaling, and lets the combined object be used anywhere a PxGeometry is needed.
	/// </summary>
	public ref class HeightFieldGeometry : Geometry
	{
		public:
			HeightFieldGeometry();
			HeightFieldGeometry(PhysX::HeightField^ heightField);
			HeightFieldGeometry(PhysX::HeightField^ heightField, MeshGeometryFlag flags, float heightFieldScale, float rowScale, float columnScale);

		internal:
			static PxHeightFieldGeometry ToUnmanaged(HeightFieldGeometry^ geom);
			static HeightFieldGeometry^ ToManaged(PxHeightFieldGeometry geom);

		public:
			virtual PxGeometry* ToUnmanaged() override;

			/// <summary>
			/// Returns true if the geometry is valid.
			/// </summary>
			bool IsValid();

			//

			/// <summary>
			/// The height field data.
			/// </summary>
			property PhysX::HeightField^ HeightField;

			/// <summary>
			/// The scaling factor for the height field in vertical (sample) direction.
			/// </summary>
			property float HeightScale;
			
			/// <summary>
			/// The scaling factor for the height field in the row direction.
			/// </summary>
			property float RowScale;

			/// <summary>
			/// The scaling factor for the height field in the column direction.
			/// </summary>
			property float ColumnScale;

			/// <summary>
			/// Flags to specify some collision properties for the height field.
			/// </summary>
			property MeshGeometryFlag HeightFieldFlags;
	};
};