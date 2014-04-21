#pragma once

using namespace System;

namespace StillDesign
{
	namespace PhysX
	{
		ref class Scene;
		ref class Shape;
		ref class Controller;
	
		public ref class ControllerShapeHit
		{
			private:
				NxControllerShapeHit* _shapeHit;
				
				Controller^ _controller;
				Shape^ _shape;
				
			internal:
				ControllerShapeHit( NxControllerShapeHit shapeHit );
			public:
				~ControllerShapeHit();
			protected:
				!ControllerShapeHit();
				
			public:
				/// <summary>Gets the current controller</summary>
				property StillDesign::PhysX::Controller^ Controller
				{
					StillDesign::PhysX::Controller^ get();
				}
				/// <summary>Gets the touched shape</summary>
				property StillDesign::PhysX::Shape^ Shape
				{
					StillDesign::PhysX::Shape^ get();
				}
				
				/// <summary>Gets the contact position in world space</summary>
				property Vector3 WorldPosition
				{
					Vector3 get();
				}
				/// <summary>Gets the contact normal in world space</summary>
				property Vector3 WorldNormal
				{
					Vector3 get();
				}
				
				///// <summary>Gets the </summary>
				//property unsigned int TriangleIndex
				//{
				//	unsigned int get();
				//}
				
				/// <summary>Gets the motion direction</summary>
				property Vector3 MotionDirection
				{
					Vector3 get();
				}
				/// <summary>Gets the motion length</summary>
				property float MotionLength
				{
					float get();
				}
			
			internal:
				property NxControllerShapeHit* UnmanagedPointer
				{
					NxControllerShapeHit* get();
				}
		};
	};
};