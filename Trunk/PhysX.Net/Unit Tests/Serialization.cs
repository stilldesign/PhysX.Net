using System;
using System.Text;
using System.Collections.Generic;
using System.Linq;
using Microsoft.VisualStudio.TestTools.UnitTesting;

#if GRAPHICS_MDX
using Microsoft.DirectX;
#elif GRAPHICS_XNA2 || GRAPHICS_XNA3
using Microsoft.Xna.Framework;
#elif GRAPHICS_SLIMDX
using SlimDX;
#endif

using StillDesign.PhysX.Utilities;

using Ray = StillDesign.PhysX.Ray;

namespace StillDesign.PhysX.UnitTests
{
	[TestClass]
	public class Serialization : TestBase
	{
		public Serialization()
		{

		}

		[TestMethod]
		public void LoadScene()
		{
			using( CreateCoreAndScene() )
			{
				PhysicsCollection collection = PhysX.Utilities.Utilities.LoadCollection( @"Scene 3.xml", UtilitiesFileType.Xml );

				LoadUserNotify userNotify = new LoadUserNotify();

				bool successfulLoad = collection.InstantiateCollection( this.Core, this.Scene, null, userNotify );

				Assert.IsTrue( successfulLoad, "Scene did not load successfully" );
			}
		}

		[TestMethod]
		public void LoadSceneAndRaycast()
		{
			using( CreateCoreAndScene() )
			{
				PhysicsCollection collection = PhysX.Utilities.Utilities.LoadCollection( @"Scene 3.xml", UtilitiesFileType.Xml );

				LoadUserNotify notify = new LoadUserNotify();

				bool successfulLoad = collection.InstantiateCollection( this.Core, this.Scene, null, null );

				Assert.IsTrue( successfulLoad );
				Assert.IsTrue( this.Scene.Actors.Sum( t => t.Shapes.Count ) == 4, "Loaded file does not contain 4 shapes" );
				{
					Ray ray = new Ray();
					ray.Origin = new Vector3( 0, 0, 0 );
					ray.Direction = Vector3.Normalize( this.Scene.Actors[ 2 ].Shapes[ 0 ].WorldSpaceBounds.Center - ray.Origin );

					Assert.IsTrue( this.Scene.RaycastAllShapes( ray, ShapesType.All ).Length == 1 );
				}
			}
		}
	}

	public class LoadUserNotify : StillDesign.PhysX.Utilities.UserNotify
	{
		public LoadUserNotify()
		{

		}

		public override void NotifyActor( Actor actor, string userProperties )
		{

		}
		public override bool PreNotifyJoint( JointDescription joint, string userProperties )
		{
			joint.IsValid();
			return true;
		}
		public override void NotifyJoint( Joint joint, string userProperties )
		{
			base.NotifyJoint( joint, userProperties );
		}
		public override void PreNotifyJointFailed( JointDescription joint, string userProperties )
		{
			base.PreNotifyJointFailed( joint, userProperties );
		}
	}
}