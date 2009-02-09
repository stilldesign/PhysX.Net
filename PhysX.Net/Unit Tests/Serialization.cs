using System;
using System.Text;
using System.Collections.Generic;
using System.Linq;
using Microsoft.VisualStudio.TestTools.UnitTesting;

using Microsoft.Xna.Framework;

using StillDesign.PhysX.Utilities;

namespace StillDesign.PhysX.UnitTests
{
	[TestClass]
	public class Serialization : TestBase
	{
		public Serialization()
		{

		}

		private TestContext testContextInstance;

		public TestContext TestContext
		{
			get
			{
				return testContextInstance;
			}
			set
			{
				testContextInstance = value;
			}
		}

		#region Additional test attributes
		//
		// You can use the following additional attributes as you write your tests:
		//
		// Use ClassInitialize to run code before running the first test in the class
		// [ClassInitialize()]
		// public static void MyClassInitialize(TestContext testContext) { }
		//
		// Use ClassCleanup to run code after all tests in a class have run
		// [ClassCleanup()]
		// public static void MyClassCleanup() { }
		//
		// Use TestInitialize to run code before running each test 
		// [TestInitialize()]
		// public void MyTestInitialize() { }
		//
		// Use TestCleanup to run code after each test has run
		// [TestCleanup()]
		// public void MyTestCleanup() { }
		//
		#endregion

		[TestMethod]
		public void LoadSceneAndRaycast()
		{
			CreateCoreAndScene();

			PhysicsCollection collection = PhysX.Utilities.Utilities.LoadCollection( @"Scene 3.xml", UtilitiesFileType.Xml );

			LoadUserNotify notify = new LoadUserNotify();

			bool successfulLoad = collection.InstantiateCollection( this.Core, this.Scene, null, null );

			Assert.IsTrue( successfulLoad );
			Assert.IsTrue( this.Scene.Actors.Sum( t => t.Shapes.Count ) == 4 );
			{
				Ray ray = new Ray();
					ray.Origin = new Vector3( 0, 0, 0 );
					ray.Direction = Vector3.Normalize( this.Scene.Actors[ 2 ].Shapes[ 0 ].WorldSpaceBounds.Center - ray.Origin );

				Assert.IsTrue( this.Scene.RaycastAllShapes( ray, ShapesType.All ).Length == 1 );
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