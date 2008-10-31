#pragma once

using namespace System;
UsingFrameworkNamespace

namespace StillDesign
{
	namespace PhysX
	{
		ref class Shape;
		
		public ref class SweepQueryHit
		{
			private:
				NxSweepQueryHit* _hit;
				
				Shape^ _hitShape;
				Shape^ _sweepShape;
				
				Object^ _userData;
				
			public:
				SweepQueryHit();
				~SweepQueryHit();
			protected:
				!SweepQueryHit();
			internal:
				SweepQueryHit( NxSweepQueryHit* hit, Object^ userData );
				
			public:
				/// <summary>Gets the distance to hit expressed as a percentage of the source motion vector ([0,1] coeff)</summary>
				property float T
				{
					float get();
				}
				/// <summary>Hit shape</summary>
				property Shape^ HitShape
				{
					Shape^ get();
				}
				property Shape^ SweepShape
				{
					Shape^ get();
				}
				property Object^ UserData
				{
					Object^ get();
				}
				/// <summary>Gets the ID of touched triangle (internal)</summary>
				property int InternalFaceID
				{
					int get();
				}
				/// <summary>Gets the ID of touched triangle (external)</summary>
				property int FaceID
				{
					int get();
				}
				/// <summary>Gets the world-space impact point</summary>
				property Vector3 Point
				{
					Vector3 get();
				}
				/// <summary>Gets the world-space impact normal</summary>
				property Vector3 Normal
				{
					Vector3 get();
				}
		};
	};
};