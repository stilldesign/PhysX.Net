using System;
using System.Text;
using System.Collections.Generic;
using System.Linq;
using Microsoft.VisualStudio.TestTools.UnitTesting;

#if GRAPHICS_XNA2 || GRAPHICS_XNA3
using Microsoft.Xna.Framework;
#elif GRAPHICS_MDX
using Microsoft.DirectX;
#elif GRAPHICS_SLIMDX
using SlimDX;
#else
#error No Graphics Framework Defined
#endif

namespace StillDesign.PhysX.UnitTests
{
	[TestClass]
	public class HeightfieldTests : TestBase
	{
		public HeightfieldTests()
		{

		}

		public TestContext TestContext
		{
			get;
			set;
		}

		[ClassInitialize()]
		public static void MyClassInitialize( TestContext testContext )
		{

		}

		[ClassCleanup()]
		public static void MyClassCleanup()
		{

		}

		[TestInitialize()]
		public void MyTestInitialize()
		{
			CreateCoreAndScene();
		}

		[TestCleanup()]
		public void MyTestCleanup()
		{
			if( this.Core != null )
				this.Core.Dispose();
		}

		public void CreateHeightfieldTest()
		{
			int rows = 25;
			int columns = 25;

			HeightFieldSample[] samples = new HeightFieldSample[ rows * columns ];
			for( int r = 0; r < rows; r++ )
			{
				for( int c = 0; c < columns; c++ )
				{
					// Put a z and x curve together
					double h = Math.Sin( c ) * Math.Cos( r ) * short.MaxValue;

					HeightFieldSample sample = new HeightFieldSample();
					sample.Height = (short)h;
					sample.MaterialIndex0 = 0;
					sample.MaterialIndex1 = 1;
					sample.TessellationFlag = 0;

					samples[ r * columns + c ] = sample;
				}
			}

			HeightFieldDescription heightFieldDesc = new HeightFieldDescription()
			{
				NumberOfRows = rows,
				NumberOfColumns = columns,
				Samples = samples
			};

			HeightField heightField = this.Core.CreateHeightField( heightFieldDesc );

			//

			HeightFieldShapeDescription heightFieldShapeDesc = new HeightFieldShapeDescription()
			{
				HeightField = heightField,
				HoleMaterial = 2,
				// The max height of our samples is short.MaxValue and we want it to be 1
				HeightScale = 1.0f / (float)short.MaxValue,
				RowScale = 3,
				ColumnScale = 3
			};
			heightFieldShapeDesc.LocalPosition = new Vector3( -0.5f * rows * 1 * heightFieldShapeDesc.RowScale, 0, -0.5f * columns * 1 * heightFieldShapeDesc.ColumnScale );

			ActorDescription actorDesc = new ActorDescription()
			{
				GlobalPose = GraphicsLibraryWrapper.CreateTranslationMatrix( 100, 0, 0 ),
				Shapes = { heightFieldShapeDesc }
			};

			Actor actor = this.Scene.CreateActor( actorDesc );
		}

		public void ReadHeightfieldDataBack()
		{

		}
	}
}