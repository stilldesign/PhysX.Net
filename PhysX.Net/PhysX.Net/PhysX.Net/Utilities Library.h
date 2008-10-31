#pragma once

UsingFrameworkNamespace

namespace StillDesign
{
	namespace PhysX
	{
		value class Bounds3;
		
		public ref class UtilitiesLibrary
		{
			public:
				ref class BoxPlanesResult;
				ref class BoxPointsResult;
				ref class BoxNormalsResult;
				ref class SphereGenerationResult;
			
			private:
				NxUtilLib* _library;
			
			public:
				UtilitiesLibrary();
				~UtilitiesLibrary();
			protected:
				!UtilitiesLibrary();
				
			public:
				bool BoxContainsPoint( Box box, Vector3 point );
				StillDesign::PhysX::Box CreateBox( Bounds3 AABB, Matrix transform );
				UtilitiesLibrary::BoxPlanesResult^ ComputeBoxPlanes( Box box );
				UtilitiesLibrary::BoxPointsResult^ ComputeBoxPoints( Box box );
				UtilitiesLibrary::BoxNormalsResult^ ComputeBoxVertexNormals( Box box );
				array<int>^ GetBoxEdges();
				//array<int>^ GetBoxEdgesAxes();
				//array<int>^ GetBoxTriangles();
				//array<Vector3>^ GetBoxLocalEdgeNormals();
				Vector3 ComputeBoxWorldEdgeNormal( Box box, unsigned int edgeIndex );
				Capsule ComputeCapsuleAroundBox( Box box );
				bool IsBoxAInsideBoxB( Box boxA, Box boxB );
				array<int>^ GetBoxQuads();
				array<int>^ BoxVertexToQuad( int vertexIndex );
				Box ComputeBoxAroundCapsule( Capsule capsule );
				
				void SetFPUPrecision24();
				void SetFPUPrecision53();
				void SetFPUPrecision64();
				void SetFPURoundingChop();
				void SetFPURoundingUp();
				void SetFPURoundingDown();
				void SetFPURoundingNear();
				void SetFPUExceptions( bool enable );
				int IntegerChop( float value );
				int IntegerFloor( float value );
				int IntegerCeiling( float value );
				
				SphereGenerationResult^ ComputeSphere( array<Vector3>^ vertices );
				
				Matrix FindRotationMatrix( Vector3 x, Vector3 b );
				Bounds3 ComputeBounds( array<Vector3>^ vertices );
				System::UInt32 CRC32( array< System::Byte >^ buffer );
				
				// Shape Densities and Mass
				float ComputeBoxDensity( Vector3 size, float mass );
				float ComputeBoxMass( Vector3 size, float density );
				Vector3 ComputeBoxInteriaTensor( Vector3 diagonalInertia, float mass, Vector3 size );
				
				float ComputeConeDensity( float radius, float length, float mass );
				float ComputeConeMass( float radius, float length, float density );
				
				float ComputeCylinderDensity( float radius, float length, float mass );
				float ComputeCylinderMass( float radius, float length, float density );
				
				float ComputeEllipsoidDensity( Vector3 radius, float mass );
				float ComputeEllipsoidMass( Vector3 radius, float density );
				
				float ComputeSphereDensity( float radius, float mass );
				float ComputeSphereMass( float radius, float density );
				Vector3 ComputeSphereInertiaTensor( float mass, float radius, bool hollow );
				Sphere MergeSpheres( Sphere sphere0, Sphere sphere1 );
				
				//
				
				ref class BoxPlanesResult
				{
					private:
						bool _successful;
						array<Plane>^ _planes;
					
					public:
						BoxPlanesResult( bool successful, array<Plane>^ planes );
						
						property bool Successful
						{
							bool get();
						}
						property array<Plane>^ Planes
						{
							array<Plane>^ get();
						}
				};
				ref class BoxPointsResult
				{
					private:
						bool _successful;
						array<Vector3>^ _points;
					
					public:
						BoxPointsResult( bool successful, array<Vector3>^ points );
						
						property bool Successful
						{
							bool get();
						}
						property array<Vector3>^ Points
						{
							array<Vector3>^ get();
						}
				};
				ref class BoxNormalsResult
				{
					private:
						bool _successful;
						array<Vector3>^ _normals;
					
					public:
						BoxNormalsResult( bool successful, array<Vector3>^ normals );
						
						property bool Successful
						{
							bool get();
						}
						property array<Vector3>^ Normals
						{
							array<Vector3>^ get();
						}
				};
				ref class SphereGenerationResult
				{
					private:
						SphereGenerationMethod _generationMethod;
						StillDesign::PhysX::Sphere _sphere;
					
					public:
						SphereGenerationResult( SphereGenerationMethod generationMethod, StillDesign::PhysX::Sphere sphere );
						
						property SphereGenerationMethod GenerationMethod
						{
							SphereGenerationMethod get();
						}
						property StillDesign::PhysX::Sphere Sphere
						{
							StillDesign::PhysX::Sphere get();
						}
				};
		};
	};
};