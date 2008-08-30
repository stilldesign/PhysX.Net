#pragma once

#include "Enums.h"
#include "Element Collection.h"
#include "Scene.h"
#include "Convex Mesh.h"
#include "Cloth Mesh.h"
#include "Triangle Mesh.h"
#include "Height Field.h"
#include "CCD Skeleton.h"
#include "Soft Body Mesh.h"
#include "Runtime File Checks.h"

#include <NxFoundationSDK.h> 
#include <NxPhysics.h>

using namespace System;
using namespace System::IO;

namespace StillDesign
{
	namespace PhysX
	{
		class InternalUserOutputStream;
		ref class CoreDescription;
		ref class UserOutputStream;
		ref class SceneDescription;
		ref class ConvexMeshDescription;
		interface class IStreamReader;
		ref class HeightFieldDescription;
		ref class SimpleTriangleMesh;
		ref class Foundation;
		
		public ref class Core : IDisposable
		{
			public:
				ref class SceneCollection : ReadOnlyElementCollection<Scene^>
				{
					
				};
				ref class TriangleMeshCollection : ReadOnlyElementCollection<TriangleMesh^>
				{
					
				};
				ref class ConvexMeshCollection : ReadOnlyElementCollection<ConvexMesh^>
				{
					
				};
				ref class ClothMeshCollection : ReadOnlyElementCollection<ClothMesh^>
				{
					
				};
				ref class HeightFieldCollection : ReadOnlyElementCollection<HeightField^>
				{
					
				};
				ref class CCDSkeletonCollection : ReadOnlyElementCollection<CCDSkeleton^>
				{
					
				};
				ref class SoftBodyMeshCollection : ReadOnlyElementCollection<SoftBodyMesh^>
				{
					
				};
			
			public:
				virtual event EventHandler^ onDisposing;
				virtual event EventHandler^ onDisposed;
				
			private:
				NxPhysicsSDK* _physicsSDK;
				
				ElementCollection< Scene^, SceneCollection^ >^ _sceneCollection;
				ElementCollection< TriangleMesh^, TriangleMeshCollection^ >^ _triangleMeshCollection;
				ElementCollection< ConvexMesh^, ConvexMeshCollection^ >^ _convexMeshCollection;
				ElementCollection< ClothMesh^, ClothMeshCollection^ >^ _clothMeshCollection;
				ElementCollection< HeightField^, HeightFieldCollection^ >^ _heightFieldCollection;
				ElementCollection< CCDSkeleton^, CCDSkeletonCollection^ >^ _CCDSkeletonCollection;
				ElementCollection< SoftBodyMesh^, SoftBodyMeshCollection^ >^ _softBodyMeshCollection;
				
				StillDesign::PhysX::UserOutputStream^ _userOutputStream;
				
				Foundation^ _foundation;
				
				bool _checkPhysXRuntimeFiles;
			
			public:
				Core();
				Core( CoreDescription^ description, StillDesign::PhysX::UserOutputStream^ userOutputStream );
			internal:
				Core( NxPhysicsSDK* core );
			public:
				~Core();
			protected:
				!Core();
			public:
				property bool IsDisposed
				{
					virtual bool get();
				}
			
			private:
				void CreateCore( CoreDescription^ desc, StillDesign::PhysX::UserOutputStream^ userOutputStream );
				void CreateAux();
				
			public:
				static bool CheckAllPhysXRuntimeFiles();
				static bool CheckAllPhysXRuntimeFiles( bool throwOnError );
				
			internal:
				Scene^ AddScene( NxScene* scene );
				TriangleMesh^ AddTriangleMesh( NxTriangleMesh* triangleMesh );
				ConvexMesh^ AddConvexMesh( NxConvexMesh* convexMesh );
				ClothMesh^ AddClothMesh( NxClothMesh* clothMesh );
				HeightField^ AddHeightField( NxHeightField* heightField );
				CCDSkeleton^ AddCCDSkeleton( NxCCDSkeleton* skeleton );
				SoftBodyMesh^ AddSoftBodyMesh( NxSoftBodyMesh* mesh );
				
			public:
				/// <summary>Creates a default scene</summary>
				Scene^ CreateScene();
				/// <summary>Creates a Scene</summary>
				/// <param name="sceneDescription">A Description of the Scene to Create</summary>
				Scene^ CreateScene( SceneDescription^ sceneDescription );
				/// <summary>Creates a Scene with from a Default Scene Description</summary>
				/// <param name="gravity">The Gravity Vector of the Scene</summary>
				/// <param name="groundPlane">To Create the Default Ground Plane</summary>
				Scene^ CreateScene( Vector3 gravity, bool groundPlane );
				
				/// <summary>Creates a Triangle Mesh</summary>
				/// <param name="streamReader">A Stream Reader Containing the Cooked Triangle Mesh Data</summary>
				/// <remarks>Make Sure the Data Pointer is Placed at the Beginning of the Stream</remarks>
				TriangleMesh^ CreateTriangleMesh( Stream^ stream );
				/// <summary>Creates a ConvexMesh</summary>
				/// <param name="streamReader">A Stream Reader Containing the Cooked Convex Mesh Data</summary>
				/// <remarks>Make Sure the Data Pointer is Placed at the Beginning of the Stream</remarks>
				ConvexMesh^ CreateConvexMesh( Stream^ stream );
				/// <summary>Creates a Cloth Mesh</summary>
				/// <param name="streamReader">A Stream Reader Containing the Cooked Cloth Mesh Data</summary>
				/// <remarks>Make Sure the Data Pointer is Placed at the Beginning of the Stream</remarks>
				ClothMesh^ CreateClothMesh( Stream^ stream );
				/// <summary>Creates a Heightfield</summary>
				/// <param name="description">A Description of the Heightfield to Create</param>
				HeightField^ CreateHeightField( HeightFieldDescription^ description );
				/// <summary>Creates a CCD Skeleton</summary>
				/// <param name="simpleTriangleMesh">A Description of the CCD Skeleton to Create</param>
				CCDSkeleton^ CreateCCDSkeleton( SimpleTriangleMesh^ simpleTriangleMesh );
				/// <summary>Creates a SoftBody Mesh</summary>
				/// <param name="streamReader">A Stream Reader Containing the Cooked SoftBody Mesh Data</summary>
				/// <remarks>Make Sure the Data Pointer is Placed at the Beginning of the Stream</remarks>
				SoftBodyMesh^ CreateSoftBodyMesh( Stream^ stream );
				
				/// <summary>Gets the State of a Physics Parameter</summary>
				/// <param name="parameter">The Physics Parameter to Reteieve</summary>
				float GetParameter( PhysicsParameter parameter );
				/// <summary>Sets the State of a Physics Parameter</summary>
				/// <param name="value">The Physics Parameter to Set</summary>
				void SetParameter( PhysicsParameter parameter, float value );
				/// <summary>Sets the State of a Physics Parameter</summary>
				/// <param name="enabled">The Physics Parameter to Set</summary>
				void SetParameter( PhysicsParameter parameter, bool enabled );
				
				/// <summary>Gets the Collection of Scenes</summary>
				property SceneCollection^ Scenes
				{
					SceneCollection^ get();
				}
				/// <summary>Gets the Collection of Triangle Mesh</summary>
				property TriangleMeshCollection^ TriangleMeshes
				{
					TriangleMeshCollection^ get();
				}
				/// <summary>Gets the Collection of Convex Mesh</summary>
				property ConvexMeshCollection^ ConvexMeshes
				{
					ConvexMeshCollection^ get();
				}
				/// <summary>Gets the Collection of Cloth Mesh</summary>
				property ClothMeshCollection^ ClothMeshes
				{
					ClothMeshCollection^ get();
				}
				/// <summary>Gets the Collection of Heightfield</summary>
				property HeightFieldCollection^ HeightFields
				{
					HeightFieldCollection^ get();
				}
				/// <summary>Gets the Collection of CCD Skeletons</summary>
				property CCDSkeletonCollection^ CCDSkeletons
				{
					CCDSkeletonCollection^ get();
				}
				/// <summary>Gets the Collection of SoftBody Mesh</summary>
				property SoftBodyMeshCollection^ SoftBodyMeshes
				{
					SoftBodyMeshCollection^ get();
				}
				
				/// <summary>Gets the Foundation Class Associated with this Core</summary>
				property StillDesign::PhysX::Foundation^ Foundation
				{
					StillDesign::PhysX::Foundation^ get();
				}
				
				/// <summary>Gets the number of physics processing units</summary>
				property int NumberOfPhysicsProcessingUnits
				{
					int get();
				}
				
				/// <summary>Gets the Hardware Version Being Used (If Available)</summary>
				property StillDesign::PhysX::HardwareVersion HardwareVersion
				{
					StillDesign::PhysX::HardwareVersion get();
				}
				property Version^ InternalVersion
				{
					Version^ get();
				}
				property Version^ SDKVersion
				{
					static Version^ get();
				}
				
				property bool CheckPhysXRuntimeFiles
				{
					bool get();
					void set( bool value );
				}
				
				/// <summary>Gets the User Output Stream</summary>
				property StillDesign::PhysX::UserOutputStream^ UserOutputStream
				{
					StillDesign::PhysX::UserOutputStream^ get();
				}
			
			internal:
				property NxPhysicsSDK* UnmanagedPointer
				{
					NxPhysicsSDK* get();
				}
		};
	};
};