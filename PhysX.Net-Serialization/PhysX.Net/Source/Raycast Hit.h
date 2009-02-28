#pragma once

#include "Enums.h"

using namespace System;
UsingFrameworkNamespace

namespace StillDesign
{
	namespace PhysX
	{
		ref class Shape;
		ref class Scene;
		
		public ref class RaycastHit
		{
			private:
				Shape^ _shape;
				
				unsigned int _faceID;
				unsigned int _internalFaceID;
				float _distance;
				float _u, _v;
				short _materialID;
				RaycastBit _flags;
				Vector3 _worldImpact;
				Vector3 _worldNormal;
				
			internal:
				static explicit operator NxRaycastHit( RaycastHit^ rayCastHit );
				static explicit operator RaycastHit^( NxRaycastHit hit );
			
			public:
				/// <summary>Gets or Sets the touched shape</summary>
				property StillDesign::PhysX::Shape^ Shape
				{
					StillDesign::PhysX::Shape^ get();
					void set( StillDesign::PhysX::Shape^ value );
				}
				
				/// <summary>Gets or Sets the impact point in world space </summary>
				property Vector3 WorldImpact
				{
					Vector3 get();
					void set( Vector3 value );
				}
				/// <summary>Gets or Sets the impact normal in world space</summary>
				property Vector3 WorldNormal
				{
					Vector3 get();
					void set( Vector3 value );
				}
				
				/// <summary>Gets or Sets the index of touched face</summary>
				property int FaceID
				{
					int get();
					void set( int value );
				}
				property int InternalFaceID
				{
					int get();
					void set( int value );
				}
				
				/// <summary>Gets or Sets the distance from ray start to impact point</summary>
				property float Distance
				{
					float get();
					void set( float value );
				}
				/// <summary>Gets or Sets the impact barycentric coordinates</summary>
				property float U
				{
					float get();
					void set( float value );
				}
				/// <summary>Gets or Sets the impact barycentric coordinates</summary>
				property float V
				{
					float get();
					void set( float value );
				}
				/// <summary>Gets or Sets the index of touched material</summary>
				property short MaterialIndex
				{
					short get();
					void set( short value );
				}
				/// <summary>Gets or Sets a combination of RaycastBit, when a corresponding flag is set, then the member is valid</summary>
				property RaycastBit Flags
				{
					RaycastBit get();
					void set( RaycastBit value );
				}
		};
	};
};