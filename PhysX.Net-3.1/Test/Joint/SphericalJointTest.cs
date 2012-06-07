using System;
using System.Text;
using System.Collections.Generic;
using System.Linq;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using PhysX.Math;

namespace PhysX.Test.Joint
{
	[TestClass]
	public class SphericalJointTest : Test
	{
		/// <summary>
		/// Create a joint limit cone and assign it to the spherical joint, then make sure
		/// the values have been assigned.
		/// </summary>
		[TestMethod]
		public void SetLimitCone()
		{
			using (var core = CreatePhysicsAndScene())
			{
				var box1 = CreateBoxActor(core.Scene, new Vector3(5, 5, 5), new Vector3(0, 10, 0));
				var box2 = CreateBoxActor(core.Scene, new Vector3(5, 5, 5), new Vector3(0, 20, 0));

				SphericalJoint joint = core.Scene.CreateJoint<SphericalJoint>(box1, Matrix.Identity, box2, Matrix.Identity);

				// Set the limit cone
				var limit = new JointLimitCone()
				{
					YLimitAngle = 0.5f, // [0 - PI/2]
					ZLimitAngle = 0.6f, // [0 - PI/2]
					Spring = 3,
					Damping = 4,
					Restitution = 0.7f // [0 - 1]
				};

				joint.SetLimitCone(limit);

				// Get the limit cone back and compare the values to make sure they've been stored
				var retrievedLimitCone = joint.GetLimitCone();

				Assert.AreEqual(0.5f, retrievedLimitCone.YLimitAngle);
				Assert.AreEqual(0.6f, retrievedLimitCone.ZLimitAngle);
				Assert.AreEqual(3, retrievedLimitCone.Spring);
				Assert.AreEqual(4, retrievedLimitCone.Damping);
				Assert.AreEqual(0.7f, retrievedLimitCone.Restitution);
			}
		}

		///// <summary>
		///// Assign each limit cone individually, instead of creating a new limit cone class.
		///// </summary>
		//[TestMethod]
		//public void LimitConeByIndividualPropertyAssignment()
		//{
		//    using (var core = CreatePhysicsAndScene())
		//    {
		//        var box1 = CreateBoxActor(core.Scene, new Vector3(5, 5, 5), new Vector3(0, 10, 0));
		//        var box2 = CreateBoxActor(core.Scene, new Vector3(5, 5, 5), new Vector3(0, 20, 0));

		//        SphericalJoint joint = core.Scene.CreateJoint<SphericalJoint>(box1, Matrix.Identity, box2, Matrix.Identity);

		//        joint.Flags = SphericalJointFlag.LimitEnabled;

		//        joint.LimitCone.YLimitAngle = 0.5f; // [0 - PI/2]
		//        joint.LimitCone.ZLimitAngle = 0.6f; // [0 - PI/2]
		//        joint.LimitCone.Spring = 3;
		//        joint.LimitCone.Damping = 4;
		//        joint.LimitCone.Restitution = 0.7f; // [0 - 1]

		//        Assert.AreEqual(0.5f, joint.LimitCone.YLimitAngle);
		//        Assert.AreEqual(0.6f, joint.LimitCone.ZLimitAngle);
		//        Assert.AreEqual(3, joint.LimitCone.Spring);
		//        Assert.AreEqual(4, joint.LimitCone.Damping);
		//        Assert.AreEqual(0.7f, joint.LimitCone.Restitution);
		//    }
		//}
	}
}