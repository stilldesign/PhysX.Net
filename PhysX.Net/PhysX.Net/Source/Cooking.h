#pragma once

UsingFrameworkNamespace

class NxCookingInterface;

namespace StillDesign
{
	namespace PhysX	
	{
		value class CookingParameters;
		ref class TriangleMeshDescription;
		ref class ConvexMeshDescription;
		ref class ClothMeshDescription;
		ref class SoftBodyMeshDescription;
		ref class UserOutputStream;
		ref class CookingResult;
		ref class UserOutputStream;
		interface class IStreamWriter;
		interface class IStreamReader;
		
		public ref class Cooking
		{
			private:
				static NxCookingInterface* _cooking;
				
				static UserOutputStream^ _userOutputStream;
			
			protected:
				Cooking()
				{
					
				}
			private:
				static Cooking();
			public:
				~Cooking();
			protected:
				!Cooking();
				
			public:
				/// <summary>Checks endianness is the same between cooking &amp; target platforms</summary>
				static bool IsPlatformMismatch();
				/// <summary>Initializes cooking</summary>
				static void InitializeCooking();
				/// <summary>Initializes cooking</summary>
				/// <param name="outputStream">The output stream to use. If outputStream is null, no output stream is used</param>
				/// <exception cref="StillDesign.PhysX.PhysXException">Thrown when cooking fails to initalize</exception>
				static void InitializeCooking( UserOutputStream^ outputStream );
				/// <summary>Closes cooking</summary>
				static void CloseCooking();
				
				/// <summary>Cooks a triangle mesh. The results are written to the stream</summary>
				/// <param name="description">The triangle mesh descriptor to read the mesh from</param>
				/// <param name="stream">User stream to output the cooked data</param>
				/// <exception cref="ArgumentNullException">Thrown when the description argument is null</exception>
				/// <exception cref="ArgumentException">Thrown when the description argument is invalid</exception>
				/// <exception cref="ArgumentNullException">Thrown when the stream argument is null</exception>
				/// <exception cref="ArgumentException">Thrown when the stream argument is not writable</exception>
				static bool CookTriangleMesh( TriangleMeshDescription^ description, Stream^ stream );
				/// <summary>Cooks a convex mesh. The results are written to the stream</summary>
				/// <param name="description">The triangle mesh descriptor to read the mesh from</param>
				/// <param name="stream">User stream to output the cooked data</param>
				/// <exception cref="ArgumentNullException">Thrown when the description argument is null</exception>
				/// <exception cref="ArgumentException">Thrown when the description argument is invalid</exception>
				/// <exception cref="ArgumentNullException">Thrown when the stream argument is null</exception>
				/// <exception cref="ArgumentException">Thrown when the stream argument is not writable</exception>
				static bool CookConvexMesh( ConvexMeshDescription^ description, Stream^ stream );
				/// <summary>Cooks a cloth mesh. The results are written to the stream</summary>
				/// <param name="description">The triangle mesh descriptor to read the mesh from</param>
				/// <param name="stream">User stream to output the cooked data</param>
				/// <exception cref="ArgumentNullException">Thrown when the description argument is null</exception>
				/// <exception cref="ArgumentException">Thrown when the description argument is invalid</exception>
				/// <exception cref="ArgumentNullException">Thrown when the stream argument is null</exception>
				/// <exception cref="ArgumentException">Thrown when the stream argument is not writable</exception>
				static bool CookClothMesh( ClothMeshDescription^ description, Stream^ stream );
				/// <summary>Cooks a SoftBody mesh. The results are written to the stream</summary>
				/// <param name="description">The triangle mesh descriptor to read the mesh from</param>
				/// <param name="stream">User stream to output the cooked data</param>
				/// <exception cref="ArgumentNullException">Thrown when the description argument is null</exception>
				/// <exception cref="ArgumentException">Thrown when the description argument is invalid</exception>
				/// <exception cref="ArgumentNullException">Thrown when the stream argument is null</exception>
				/// <exception cref="ArgumentException">Thrown when the stream argument is not writable</exception>
				static bool CookSoftBodyMesh( SoftBodyMeshDescription^ description, Stream^ stream );
				
				/// <summary>Gets or Sets Cooking Parameters</summary>
				property CookingParameters Parameters
				{
					static CookingParameters get();
					static void set( CookingParameters value );
				}
				
			internal:
				property NxCookingInterface* UnmanagedPointer
				{
					static NxCookingInterface* get();
				}
		};
	};
};