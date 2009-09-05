using System;
using System.Text;
using System.Collections.Generic;
using System.Linq;
using Microsoft.VisualStudio.TestTools.UnitTesting;
#if GRAPHICS_XNA31
using Microsoft.Xna.Framework;
#elif GRAPHICS_SLIMDX
using SlimDX;
#else
#error No Graphics Framework Defined
#endif

namespace StillDesign.PhysX.UnitTests
{
	[TestClass]
	public class ShapeTests : TestBase
	{
		[TestMethod]
		public void ContactStream()
		{
			CreateCoreAndScene();

			// Create two boxes
			Actor a = CreateBoxActor( 0, 10, 0 );
			Actor b = CreateBoxActor( 0, 5, 0 );

			// Enable contact reporting
			this.Scene.SetActorPairFlags( a, b, ContactPairFlag.All );

			this.Scene.UserContactReport = new ContactReport( this );

			this.ContactNotifyCalled = false;

			//

			// Simulate the scene for a maximum of 4 seconds, or until the contact report happens
			float maxSimulationTime = 4;
			float t = 0;
			float step = 1.0f/60.0f;

			while( true )
			{
				t += step;

				if( t >= maxSimulationTime )
					break;

				if( this.ContactNotifyCalled )
					break;

				this.Scene.Simulate( step );
				this.Scene.FlushStream();
				this.Scene.FetchResults( SimulationStatus.RigidBodyFinished, true );
			}

			Assert.IsTrue( this.ContactNotifyCalled, "No contact report or contact pairs, patches or points occured" );
		}

		//

		public bool ContactNotifyCalled
		{
			get;
			set;
		}

		//

		private class ContactReport : UserContactReport
		{
			public ContactReport( ShapeTests test )
			{
				this.Test = test;
			}

			public override void OnContactNotify( ContactPair contactInformation, ContactPairFlag events )
			{
				ContactStreamIterator iter;
				using( iter = new ContactStreamIterator( contactInformation.ContactStream ) )
				{
					while( iter.GoToNextPair() )
					{
						while( iter.GoToNextPatch() )
						{
							while( iter.GoToNextPoint() )
							{
								// Test each of the available 'information' functions

								int numberOfPairs = iter.GetNumberOfPairs();
								Shape shapeA = iter.GetShapeA();
								Shape shapeB = iter.GetShapeB();
								bool isShapeADeleted = iter.IsDeletedShapeA();
								bool isShapeBDeleted = iter.IsDeletedShapeB();
								ShapeFlag shapeFlags = iter.GetShapeFlags();
								int numberOfPatches = iter.GetNumberOfPatches();
								int numberOfPatchesRemaining = iter.GetNumberOfPatchesRemaining();
								Vector3 patchNormal = iter.GetPatchNormal();
								int numberOfPoints = iter.GetNumberOfPoints();
								int numberOfPointsRemaining = iter.GetNumberOfPointsRemaining();
								Vector3 point = iter.GetPoint();
								float separation = iter.GetSeperation();
								int featureIndex0 = iter.GetFeatureIndex0();
								int featureIndex1 = iter.GetFeatureIndex1();
								float pointNormalForce = iter.GetPointNormalForce();

								this.Test.ContactNotifyCalled = true;
							}
						}
					}
				}

				Assert.IsTrue( iter.IsDisposed );
			}

			private ShapeTests Test
			{
				get;
				set;
			}
		}
	}
}