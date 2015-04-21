using System;
using System.Numerics;
using Microsoft.VisualStudio.TestTools.UnitTesting;

namespace PhysX.Test.Constraint
{
	[TestClass]
	public class ConstraintTest : Test
	{
		[TestMethod]
		public void GetConstraintOfJoint()
		{
			using (var core = CreatePhysicsAndScene())
			{
				var boxA = CreateBoxActor(core.Scene, new Vector3(1, 1, 1), new Vector3(-10, 10, 0));
				var boxB = CreateBoxActor(core.Scene, new Vector3(1, 1, 1), new Vector3(10, 10, 0));

				var joint = core.Scene.CreateJoint<SphericalJoint>(boxA, Matrix4x4.Identity, boxB, Matrix4x4.Identity);

				// Make sure its been wrapped when the joint was created
				Assert.IsNotNull(joint.Constraint);

				// Sanity checks
				Assert.AreEqual(boxA, joint.Constraint.Actor0);
				Assert.AreEqual(boxB, joint.Constraint.Actor1);
				Assert.AreEqual(core.Scene, joint.Constraint.Scene);
			}
		}

		[TestMethod]
		public void DisposingOfAJointDisposesItsChildConstraint()
		{
			using (var core = CreatePhysicsAndScene())
			{
				var boxA = CreateBoxActor(core.Scene, new Vector3(1, 1, 1), new Vector3(-10, 10, 0));
				var boxB = CreateBoxActor(core.Scene, new Vector3(1, 1, 1), new Vector3(10, 10, 0));

				var joint = core.Scene.CreateJoint<SphericalJoint>(boxA, Matrix4x4.Identity, boxB, Matrix4x4.Identity);

				Assert.IsNotNull(joint.Constraint);
				Assert.IsFalse(joint.Constraint.Disposed);

				bool constraintOfJointDisposed = false;
				joint.Constraint.OnDisposed += (s, e) =>
				{
					constraintOfJointDisposed = true;
				};

				joint.Dispose();

				Assert.IsTrue(constraintOfJointDisposed);
			}
		}
	}
}