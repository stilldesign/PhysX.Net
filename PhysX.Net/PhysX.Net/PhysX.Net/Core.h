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
		ref class PhysicsParametersWrapper;

		
		[System::ComponentModel::TypeConverter( System::ComponentModel::ExpandableObjectConverter::typeid )]
		public ref class Core : IDisposable
		{
			public:
				virtual event EventHandler^ onDisposing;
				virtual event EventHandler^ onDisposed;
				
			private:
				NxPhysicsSDK* _physicsSDK;
				
				ElementCollection< Scene^ >^ _sceneCollection;
				ElementCollection< TriangleMesh^ >^ _triangleMeshCollection;
				ElementCollection< ConvexMesh^ >^ _convexMeshCollection;
				ElementCollection< ClothMesh^ >^ _clothMeshCollection;
				ElementCollection< HeightField^ >^ _heightFieldCollection;
				ElementCollection< CCDSkeleton^ >^ _CCDSkeletonCollection;
				ElementCollection< SoftBodyMesh^ >^ _softBodyMeshCollection;
				
				StillDesign::PhysX::UserOutputStream^ _userOutputStream;
				
				Foundation^ _foundation;
				PhysicsParametersWrapper^ _physicsParametersWrapper;
				
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
				property ReadOnlyList< Scene^ >^ Scenes
				{
					ReadOnlyList< Scene^ >^ get();
				}
				/// <summary>Gets the Collection of Triangle Mesh</summary>
				property ReadOnlyList< TriangleMesh^ >^ TriangleMeshes
				{
					ReadOnlyList< TriangleMesh^ >^ get();
				}
				/// <summary>Gets the Collection of Convex Mesh</summary>
				property ReadOnlyList< ConvexMesh^ >^ ConvexMeshes
				{
					ReadOnlyList< ConvexMesh^ >^ get();
				}
				/// <summary>Gets the Collection of Cloth Mesh</summary>
				property ReadOnlyList< ClothMesh^ >^ ClothMeshes
				{
					ReadOnlyList< ClothMesh^ >^ get();
				}
				/// <summary>Gets the Collection of Heightfield</summary>
				property ReadOnlyList< HeightField^ >^ HeightFields
				{
					ReadOnlyList< HeightField^ >^ get();
				}
				/// <summary>Gets the Collection of CCD Skeletons</summary>
				property ReadOnlyList< CCDSkeleton^ >^ CCDSkeletons
				{
					ReadOnlyList< CCDSkeleton^ >^ get();
				}
				/// <summary>Gets the Collection of SoftBody Mesh</summary>
				property ReadOnlyList< SoftBodyMesh^ >^ SoftBodyMeshes
				{
					ReadOnlyList< SoftBodyMesh^ >^ get();
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
				/// <summary>Gets the internal API version number of the SDK</summary>
				property Version^ InternalVersion
				{
					Version^ get();
				}
				/// <summary>Gets the SDK version number</summary>
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

				property PhysicsParametersWrapper^ Parameters
				{
					PhysicsParametersWrapper^ get();
				}
			
			internal:
				property NxPhysicsSDK* UnmanagedPointer
				{
					NxPhysicsSDK* get();
				}
		};
	};
};