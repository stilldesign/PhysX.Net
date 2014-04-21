#pragma once

#include "IDisposable.h"

using namespace System;
class NxClothMesh;

namespace StillDesign
{
	namespace PhysX
	{
		ref class Core;
		interface class IStreamReader;
		ref class ClothMeshDescription;
		
		public ref class ClothMesh : StillDesign::PhysX::IDisposable
		{
			public:
				virtual event EventHandler^ OnDisposing;
				virtual event EventHandler^ OnDisposed;
				
			private:
				NxClothMesh* _clothMesh;
				
				Core^ _core;
				
				String^ _name;
				
			internal:
				ClothMesh( NxClothMesh* clothMesh, StillDesign::PhysX::Core^ core );
			public:
				~ClothMesh();
			protected:
				!ClothMesh();
			public:
				property bool IsDisposed
				{
					virtual bool get();
				}
			
			public:
				/// <summary>Saves the cloth descriptor</summary>
				/// <remarks>A cloth mesh is created via the cooker. The cooker potentially changes the order of the arrays references by the pointers points and triangles. Since saveToDesc returns the data of the cooked mesh, this data might differ from the originally provided data. Note that this is in contrast to the meshData member of NxClothDesc, which is guaranteed to provide data in the same order as that used to create the mesh</remarks>
				ClothMeshDescription^ SaveToDescription();
				
				/// <summary>Gets the Core the Cloth Mesh was Created on</summary>
				property StillDesign::PhysX::Core^ Core
				{
					StillDesign::PhysX::Core^ get();
				}
				
				/// <summary>Gets or Sets the Name of the Cloth Mesh</summary>
				property String^ Name
				{
					String^ get();
					void set( String^ value );
				}
				
				/// <summary>Gets the number of cloth instances referencing this cloth mesh</summary>
				property int ReferencedCount
				{
					int get();
				}
			
			internal:
				property NxClothMesh* UnmanagedPointer
				{
					NxClothMesh* get();
				}
		};
	};
};