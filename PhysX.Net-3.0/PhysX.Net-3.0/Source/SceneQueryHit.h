#pragma once

#include "SceneEnum.h"
#include "Shape.h"

namespace PhysX
{
	/// <summary>
	/// Scene query hit information.
	/// All members of the PxSceneQueryHit structure are not always available. For example when the query hits a
	/// sphere, the faceIndex member is not computed. 
	/// </summary>
	public ref class SceneQueryHit
	{
		internal:
			void PopulateUnmanaged(PxSceneQueryHit& hit);
			void PopulateManaged(PxSceneQueryHit& hit);

			static SceneQueryHit^ ToManaged(PxSceneQueryHit* hit);

		public:
			/// <summary>
			/// Hit shape, only nonzero if Actor contains Shapes.
			/// </summary>
			property Shape^ Shape;
			/// <summary>
			/// Hit actor.
			/// </summary>
			property Actor^ Actor;
			/// <summary>
			/// Face index of touched triangle, for triangle mesh and height field. Note: These are post cooking
			/// indices, use PxTriangleMesh::getTrianglesRemap() to get the indices of the original mesh.
			/// </summary>
			property int FaceIndex;
			/// <summary>
			/// Hit flags specifying which optional members are valid.
			/// </summary>
			property SceneQueryFlags Flags;
	};
};