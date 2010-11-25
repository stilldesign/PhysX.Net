using System;
using System.Collections.Generic;
using System.Linq;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using StillDesign.PhysX.MathPrimitives;

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
			// a sits on the ground, b is 10 up and c is way up at 100
			// Simulating the scene will cause b to hit a and generate a contact report, then awhile later, c will hit b
			Actor a = CreateBoxActor( 0, 2.5f, 0, "A" );
			Actor b = CreateBoxActor( 0, 10, 0, "B" );
			Actor c = CreateBoxActor( 0, 100, 0, "C" );

			// Enable contact reporting
			this.Scene.SetActorPairFlags( a, b, ContactPairFlag.All );
			this.Scene.SetActorPairFlags( b, c, ContactPairFlag.All );

			this.Scene.UserContactReport = new ContactReport( RegisterABHit, RegisterBCHit, a.Shapes.First(), b.Shapes.First(), c.Shapes.First() );

			this.ABContactNotifyCalled =
			this.BCContactNotifyCalled = false;

			//

			// Simulate the scene for a maximum of 20 seconds, or until the contact reports happen
			const float maxSimulationTime = 20;
			float t = 0;
			const float step = 1.0f/60.0f;

			while( true )
			{
				t += step;

				if( t >= maxSimulationTime )
					break;

				if( this.ABContactNotifyCalled && this.BCContactNotifyCalled )
					break;

				this.Scene.Simulate( step );
				this.Scene.FlushStream();
				this.Scene.FetchResults( SimulationStatus.RigidBodyFinished, true );
			}

			Assert.IsTrue( this.ABContactNotifyCalled, "No contact report or contact pairs, patches or points occured" );
		}

		private void RegisterABHit()
		{
			this.ABContactNotifyCalled = true;
		}
		private void RegisterBCHit()
		{
			this.BCContactNotifyCalled = true;
		}

		//

		private bool ABContactNotifyCalled
		{
			get;
			set;
		}
		private bool BCContactNotifyCalled
		{
			get;
			set;
		}

		//

		private class ContactReport : UserContactReport
		{
			public ContactReport( Action abHitCallback, Action bcHitCallback, Shape a, Shape b, Shape c )
			{
				this.ABHitCallback = abHitCallback;
				this.BCHitCallback = bcHitCallback;

				this.A = a;
				this.B = b;
				this.C = c;
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
								// Test each of the available 'information' functions/properties

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

								// First collision should be AB
								if( IsPairContacting( shapeA, A, B ) && IsPairContacting( shapeB, A, B ) )
								{
									ABHitCallback();
								}

								// Second collision should be BC, but only if AB has happened
								if( IsPairContacting( shapeA, B, C ) && IsPairContacting( shapeB, B, C ) )
								{
									BCHitCallback();
								}
							}
						}
					}
				}

				Assert.IsTrue( iter.IsDisposed );
			}

			private bool IsPairContacting( Shape shape, params Shape[] compare )
			{
				// As PhysX can return contacting pairs in any order (i.e. AB is the same as BA)
				// You can't simply go if( shapeA == shapeB ), you'll need; if( shapeA == shapeB || shapeB == shapeA )
				return compare.Contains( shape );
			}

			private Action ABHitCallback
			{
				get;
				set;
			}
			private Action BCHitCallback
			{
				get;
				set;
			}

			private Shape A
			{
				get;
				set;
			}
			private Shape B
			{
				get;
				set;
			}
			private Shape C
			{
				get;
				set;
			}
		}
	}
}