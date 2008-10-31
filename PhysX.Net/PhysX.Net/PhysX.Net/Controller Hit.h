#pragma once

using namespace System;

UsingFrameworkNamespace

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
				/// <summary></summary>
				property StillDesign::PhysX::Controller^ Controller
				{
					StillDesign::PhysX::Controller^ get();
				}
				/// <summary></summary>
				property StillDesign::PhysX::Shape^ Shape
				{
					StillDesign::PhysX::Shape^ get();
				}
				
				/// <summary></summary>
				property Vector3 WorldPosition
				{
					Vector3 get();
				}
				/// <summary></summary>
				property Vector3 WorldNormal
				{
					Vector3 get();
				}
				
				/// <summary></summary>
				property unsigned int TriangleIndex
				{
					unsigned int get();
				}
				
				/// <summary></summary>
				property Vector3 MotionDirection
				{
					Vector3 get();
				}
				/// <summary></summary>
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
		
		public ref class ControllersHit
		{
			private:
				NxControllersHit* _controllersHit;
			
			public:
				ControllersHit();
			internal:
				ControllersHit( const NxControllersHit controllersHit );
			public:
				~ControllersHit();
			protected:
				!ControllersHit();
		};
	};
};