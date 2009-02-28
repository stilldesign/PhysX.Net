#pragma once

UsingFrameworkNamespace

namespace StillDesign
{
	namespace PhysX
	{
		public value class SoftBodySplitPair
		{
			private:
				int _tetrahedronIndex0;
				int _tetrahedronIndex1;
				int _faceIndex0;
				int _faceIndex1;
			
			public:
				static explicit operator NxSoftBodySplitPair( SoftBodySplitPair pair );
				static explicit operator SoftBodySplitPair( NxSoftBodySplitPair pair );
				
				property int TetrahedronIndex0
				{
					int get();
					void set( int value );
				}
				property int TetrahedronIndex1
				{
					int get();
					void set( int value );
				}
				property int FaceIndex0
				{
					int get();
					void set( int value );
				}
				property int FaceIndex1
				{
					int get();
					void set( int value );
				}
		};
	};
};