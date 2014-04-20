#pragma once

#include "Enums.h"
#include "Groups Mask.h"
#include "IDisposable.h"

using namespace System;
class NxForceFieldShape;

namespace StillDesign
{
	namespace PhysX
	{
		value class GroupsMask;
		ref class ForceField;
		ref class ForceFieldShapeGroup;
		
		public ref class ForceFieldShape abstract : StillDesign::PhysX::IDisposable
		{
			public:
				virtual event EventHandler^ OnDisposing;
				virtual event EventHandler^ OnDisposed;
				
			private:
				NxForceFieldShape* _forceFieldShape;
				
				ForceFieldShapeGroup^ _group;
				
				Object^ _userData;
			
			protected:
				ForceFieldShape( NxForceFieldShape* forceFieldShape );
			public:
				~ForceFieldShape();
			protected:
				!ForceFieldShape();
			public:
				property bool IsDisposed
				{
					virtual bool get();
				}
				
				property ForceFieldShapeGroup^ ShapeGroup
				{
					ForceFieldShapeGroup^ get();
				}
				
				/// <summary>Retrieve the type of this force field shape</summary>
				property ShapeType Type 
				{
					ShapeType get();
				}
				
				property String^ Name
				{
					String^ get();
					void set( String^ value );
				}
				
				/// <summary>Gets or Sets the force field shape's transform</summary>
				property Matrix Pose
				{
					Matrix get();
					void set( Matrix value );
				}
				
				property Object^ UserData
				{
					Object^ get();
					void set( Object^ value );
				}
				
			internal:
				property NxForceFieldShape* UnmanagedPointer
				{
					NxForceFieldShape* get();
				}
		};
	};
};