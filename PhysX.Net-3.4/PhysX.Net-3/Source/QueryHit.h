#pragma once

#include "ActorShape.h"

namespace PhysX
{
	/// <summary>
	/// Scene query hit information.
	/// All members of the PxSceneQueryHit structure are not always available. For example when the query hits a
	/// sphere, the faceIndex member is not computed. 
	/// </summary>
	public ref class QueryHit : ActorShape
	{
	internal:
		void PopulateUnmanaged(PxQueryHit& hit);
		void PopulateManaged(PxQueryHit hit);

		static QueryHit^ ToManaged(PxQueryHit* hit);

	public:
		/// <summary>
		/// Face index of touched triangle, for triangle mesh and height field. Note: These are post cooking
		/// indices, use PxTriangleMesh::getTrianglesRemap() to get the indices of the original mesh.
		/// </summary>
		property int FaceIndex;
	};
};