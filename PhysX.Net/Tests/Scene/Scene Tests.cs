using System;
using System.Collections.Generic;
using System.Linq;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using StillDesign.PhysX.MathPrimitives;

namespace StillDesign.PhysX.Tests
{
	[TestClass]
	public class SceneTests : TestBase
	{
		[TestMethod]
		public void CreateAndDisposeManyScenes()
		{
			using( CreateCore() )
			{
				for( int x = 0; x < 20; x++ )
				{
					Scene scene = this.Core.CreateScene();

					scene.Dispose();
				}
			}
		}

		#region Linear Sweep
		[TestMethod]
		public void LinearBoxSweep()
		{
			using( CreateCoreAndScene() )
			{
				CreateBoxActor( 0, 0, 20 );

				Box box = new Box( new Vector3( 0, 2.5f, 0 ), new Vector3( 5, 5, 5 ) );

				var sweepHits = this.Scene.LinearObbSweep( box, new Vector3( 0, 0, 1000 ), SweepFlags.Dynamics | SweepFlags.Statics, "Dummy Object" );

				Assert.IsTrue( sweepHits.Length == 1, "The linear box sweep should of returned 1 hit. Hits returned: {0}", sweepHits.Length );
			}
		}
		[TestMethod]
		public void LinearBoxSweepAllHits()
		{
			using( CreateCoreAndScene() )
			{
				CreateBoxActor( 0, 0, 200 );
				CreateBoxActor( 0, 0, 20 );

				Box box = new Box( new Vector3( 0, 2.5f, 0 ), new Vector3( 5, 5, 5 ) );

				var sweepHits = this.Scene.LinearObbSweep( box, new Vector3( 0, 0, 1000 ), SweepFlags.Dynamics | SweepFlags.Statics | SweepFlags.AllHits, "Dummy Object" );

				Assert.IsTrue( sweepHits.Length == 2, "The linear box sweep should of returned 2 hit. Hits returned: {0}", sweepHits.Length );
			}
		}
		[TestMethod]
		public void LinearBoxSweepCallback()
		{
			using( CreateCoreAndScene() )
			{
				CreateBoxActor( 0, 0, 20 );

				Box box = new Box( new Vector3( 0, 2.5f, 0 ), new Vector3( 5, 5, 5 ) );

				SweepCallback callback = new SweepCallback();

				this.Scene.LinearObbSweep( box, new Vector3( 0, 0, 1000 ), SweepFlags.Dynamics | SweepFlags.Statics, "Dummy Object", callback );

				Assert.IsTrue( callback.NumberOfHits == 1, "The linear box sweep should of returned 1 hit. Hits returned: {0}", callback.NumberOfHits );
			}
		}

		[TestMethod]
		public void LinearCapsuleSweep()
		{
			using( CreateCoreAndScene() )
			{
				CreateBoxActor( 0, 0, 20 );

				Capsule capsule = new Capsule( new Vector3( 0, -5, 0 ), new Vector3( 0, 5, 0 ), 10 );

				var sweepHits = this.Scene.LinearCapsuleSweep( capsule, new Vector3( 0, 0, 1000 ), SweepFlags.Dynamics | SweepFlags.Statics, "Dummy Object" );

				Assert.IsTrue( sweepHits.Length == 1, "The linear capsule sweep should of returned 1 hit. Hits returned: {0}", sweepHits.Length );
			}
		}
		[TestMethod]
		public void LinearCapsuleSweepAllHits()
		{
			using( CreateCoreAndScene() )
			{
				CreateBoxActor( 0, 0, 20 );
				CreateBoxActor( 0, 0, 50 );

				Capsule capsule = new Capsule( new Vector3( 0, -5, 0 ), new Vector3( 0, 5, 0 ), 10 );

				var sweepHits = this.Scene.LinearCapsuleSweep( capsule, new Vector3( 0, 0, 1000 ), SweepFlags.Dynamics | SweepFlags.Statics | SweepFlags.AllHits, "Dummy Object" );

				Assert.IsTrue( sweepHits.Length == 2, "The linear capsule sweep should of returned 2 hit. Hits returned: {0}", sweepHits.Length );
			}
		}
		[TestMethod]
		public void LinearCapsuleSweepCallback()
		{
			using( CreateCoreAndScene() )
			{
				CreateBoxActor( 0, 0, 20 );

				Capsule capsule = new Capsule( new Vector3( 0, -5, 0 ), new Vector3( 0, 5, 0 ), 10 );

				SweepCallback callback = new SweepCallback();

				this.Scene.LinearCapsuleSweep( capsule, new Vector3( 0, 0, 1000 ), SweepFlags.Dynamics | SweepFlags.Statics, "Dummy Object", callback );

				Assert.IsTrue( callback.NumberOfHits == 1, "The linear capsule sweep should of returned 1 hit. Hits returned: {0}", callback.NumberOfHits );
			}
		}
		#endregion

		[TestMethod]
		public void CullShapes_TwoActorsSinglePlane()
		{
			CreateCoreAndScene();

			var actorA = CreateBoxActor( 0, 0, 10 );
			var actorB = CreateBoxActor( 0, 0, 100 );

			var frustum = new[] { new Plane( 0, 0, -1, 0 ) };
			var shapes = this.Scene.CullShapes( frustum, ShapesType.Dynamic );

			Assert.IsTrue( shapes.Contains( actorA.Shapes.Single() ), "Shape A is missing" );
			Assert.IsTrue( shapes.Contains( actorB.Shapes.Single() ), "Shape B is missing" );
		}
		[TestMethod]
		public void CullShapes_TwoActorsTwoPlanes()
		{
			CreateCoreAndScene();
			var actorA = CreateBoxActor( 0, 0, 10 );
			var actorB = CreateBoxActor( 0, 0, 100 );

			{
				var frustum = new[] { new Plane( 0, 0, -1, 0 ), new Plane( 0, 0, -1, -50 ) };
				var shapes = this.Scene.CullShapes( frustum, ShapesType.Dynamic );

				Assert.IsTrue( shapes.Contains( actorA.Shapes.Single() ), "Shape A should be culled" );
				Assert.IsTrue( shapes.Contains( actorB.Shapes.Single() ), "Shape B should be culled" );
			}
			{
				var shapes = this.Scene.CullShapes( new[] { new Plane( 0, 0, 1, 150 ) }, ShapesType.Dynamic );

				Assert.IsTrue( shapes.Count() == 0, "No shapes should be culled" );
			}
		}

		[TestMethod]
		public void RaycastAllShapes()
		{
			CreateCoreAndScene();

			Actor a = CreateBoxActor( 0, 0, 10 );
			Actor b = CreateBoxActor( 0, 0, 50 );
			Actor c = CreateBoxActor( 0, 10, 10 );

			Ray ray = new Ray( new Vector3( 0, 0, 0 ), new Vector3( 0, 0, 1 ) );

			var hits = this.Scene.RaycastAllShapes( ray, ShapesType.All );

			Assert.IsTrue( hits.Length == 2, "Ray should of hit 2 boxes" );
			Assert.IsTrue( hits.All( t => t.WorldNormal == new Vector3( 0, 0, -1 ) ), "The normals of hitting the boxes should point directly back" );
			Assert.IsTrue( hits.Any( t => t.Shape == a.Shapes.Single() ), "One of the shapes hit must be that of Actor a" );
			Assert.IsTrue( hits.Any( t => t.Shape == b.Shapes.Single() ), "One of the shapes hit must be that of Actor b" );
		}
		[TestMethod]
		public void RaycastClosestShape()
		{
			CreateCoreAndScene();

			// On the ground, 20 units ahead
			Actor box1 = CreateBoxActor( 0, 2.5f, 20 );
			Actor box2 = CreateBoxActor( 0, 2.5f, 40 );

			Ray ray = new Ray( new Vector3( 0, 2.5f, 0 ), new Vector3( 0, 0, 1 ) );
			var hit = this.Scene.RaycastClosestShape( ray, ShapesType.All, 0xFFFFFFFF, float.MaxValue, RaycastBit.All, null );

			// Calling RaycastClosestShape returns flags of Material | FaceNormal | Distance | Normal | Impact | Shape, so validate those variables
			Assert.AreEqual( this.Scene.Materials[ 0 ].Index, hit.MaterialIndex ); // The shape should have the default material (index 0)
			Assert.AreEqual( 17.5f, hit.Distance );
			Assert.AreEqual( new Vector3( 0, 0, -1 ), hit.WorldNormal );
			Assert.AreEqual( ray.Origin + ray.Direction * 17.5f, hit.WorldImpact );
			Assert.AreEqual( box1.Shapes.First(), hit.Shape );
		}
		[TestMethod]
		public void RaycastClosestBounds()
		{
			CreateCoreAndScene();

			// On the ground, 20 units ahead
			Actor box1 = CreateBoxActor( 0, 2.5f, 20 );
			Actor box2 = CreateBoxActor( 0, 2.5f, 40 );

			Ray ray = new Ray( new Vector3( 0, 2.5f, 0 ), new Vector3( 0, 0, 1 ) );
			var hit = this.Scene.RaycastClosestBounds( ray, ShapesType.All, 0xFFFFFFFF, float.MaxValue, RaycastBit.All, null );

			// Calling RaycastClosestBounds returns flags of Distance | Impact | Shape, so validate those variables
			Assert.AreEqual( box1.Shapes.First(), hit.Shape );
			Assert.AreEqual( 17.5f, hit.Distance );
			Assert.AreEqual( ray.Origin + ray.Direction * 17.5f, hit.WorldImpact );
		}

		[TestMethod]
		public void PrimitiveProperties()
		{
			CreateCoreAndScene();
			var primitiveProperties = from c in typeof( Scene ).GetProperties()
									  where c.PropertyType.IsPrimitive
									  select c;

			foreach( var property in primitiveProperties )
			{
				{
					var getMethod = property.GetGetMethod();

					try
					{
						var r = getMethod.Invoke( this.Scene, null );
					}
					catch
					{
						Assert.Fail( "Property from scene failed. Property: '{0}'", getMethod.Name );
					}
				}

				//

				{
					var setMethod = property.GetSetMethod();

					if( setMethod != null )
					{
						try
						{
							setMethod.Invoke( this.Scene, new[] { Activator.CreateInstance( property.PropertyType ) } );
						}
						catch
						{
							Assert.Fail( "Property from scene failed. Property: '{0}'", setMethod.Name );
						}
					}
				}
			}
		}

		[TestMethod]
		public void ForceFieldScale()
		{
			CreateCoreAndScene();

			this.Scene.SetForceFieldScale( 0, 0, 5.2f );
			Assert.AreEqual( 5.2f, this.Scene.GetForceFieldScale( 0, 0 ) );
		}
	}

	public class SweepCallback : UserEntitySweepQueryHitReport
	{
		public override bool OnEvent( SweepQueryHit[] entities )
		{
			this.NumberOfHits += entities.Length;

			return true;
		}

		public int NumberOfHits { get; private set; }
	}
}