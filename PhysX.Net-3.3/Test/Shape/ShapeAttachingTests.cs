using System;
using System.Collections.Generic;
using System.Linq;
using Microsoft.VisualStudio.TestTools.UnitTesting;

namespace PhysX.Test.Shape
{
	[TestClass]
	public class ShapeAttachingTests : Test
	{
		[TestMethod]
		public void AttachSharedShapeToActor()
		{
			using (var physics = CreatePhysicsAndScene())
			{
				var material = physics.Physics.CreateMaterial(0.1f, 0.1f, 0.1f);

				var boxShape = physics.Physics.CreateShape(new BoxGeometry(2, 2, 2), material);

				var actor = physics.Physics.CreateRigidDynamic();

				actor.AttachShape(boxShape);

				Assert.AreEqual(1, actor.Shapes.Count());
				Assert.AreEqual(actor, boxShape.AttachedTo.First());
			}
		}

		[TestMethod]
		public void MoveSharedShapeBetweenActors()
		{
			using (var physics = CreatePhysicsAndScene())
			{
				var material = physics.Physics.CreateMaterial(0.1f, 0.1f, 0.1f);

				// None exclusive shape
				var boxShape = physics.Physics.CreateShape(new BoxGeometry(2, 2, 2), material);

				var actorA = physics.Physics.CreateRigidDynamic();
				var actorB = physics.Physics.CreateRigidDynamic();

				// Attach to A
				actorA.AttachShape(boxShape);
				Assert.AreEqual(actorA, boxShape.AttachedTo.First());

				// Detach from A
				actorA.DetachShape(boxShape);
				Assert.AreEqual(0, boxShape.AttachedTo.Count());

				// Attach to B
				actorB.AttachShape(boxShape);
				Assert.AreEqual(actorB, boxShape.AttachedTo.First());
			}
		}

		[TestMethod]
		public void AttachAShapeToTwoActorsAtTheSameTime()
		{
			using (var physics = CreatePhysicsAndScene())
			{
				var material = physics.Physics.CreateMaterial(0.1f, 0.1f, 0.1f);

				// None exclusive shape
				var boxShape = physics.Physics.CreateShape(new BoxGeometry(2, 2, 2), material);

				var actorA = physics.Physics.CreateRigidDynamic();
				var actorB = physics.Physics.CreateRigidDynamic();

				// Attach to A
				actorA.AttachShape(boxShape);
				Assert.AreEqual(actorA, boxShape.AttachedTo.ToArray()[0]);

				// Attach to B
				actorB.AttachShape(boxShape);
				Assert.AreEqual(actorB, boxShape.AttachedTo.ToArray()[1]);

				AssertNoPhysXErrors(physics);
			}
		}

		[TestMethod]
		public void CreateExclusiveShape()
		{
			using (var physics = CreatePhysicsAndScene())
			{
				var material = physics.Physics.CreateMaterial(0.1f, 0.1f, 0.1f);

				var actor = physics.Physics.CreateRigidDynamic();

				var shape = actor.CreateShape(new BoxGeometry(2, 2, 2), material);

				Assert.IsTrue(shape.IsExclusive);
			}
		}

		[TestMethod]
		public void CreateNoneExclusiveShape()
		{
			using (var physics = CreatePhysicsAndScene())
			{
				var material = physics.Physics.CreateMaterial(0.1f, 0.1f, 0.1f);

				var shape = physics.Physics.CreateShape(new BoxGeometry(2, 2, 2), material);

				Assert.IsFalse(shape.IsExclusive);
			}
		}

		/// <summary>
		/// If a shape is exclusive (i.e. created solely for/on an actor) and is
		/// then detached, it will be release() by the SDK.
		/// </summary>
		[TestMethod]
		public void DetachExclusiveShapeCausesDispose()
		{
			using (var physics = CreatePhysicsAndScene())
			{
				var material = physics.Physics.CreateMaterial(0.1f, 0.1f, 0.1f);

				var actor = physics.Physics.CreateRigidDynamic();

				var shape = actor.CreateShape(new BoxGeometry(2, 2, 2), material);

				Assert.IsTrue(shape.IsExclusive);

				// Detach shape will cause it to be released
				actor.DetachShape(shape);

				Assert.IsTrue(shape.Disposed);
				Assert.AreEqual(0, actor.Shapes.Count());
			}
		}

		[TestMethod]
		public void DisposeSharedShapeRemovesItFromAttachedActors()
		{
			using (var physics = CreatePhysicsAndScene())
			{
				var material = physics.Physics.CreateMaterial(0.1f, 0.1f, 0.1f);

				var actorA = physics.Physics.CreateRigidDynamic();
				var actorB = physics.Physics.CreateRigidDynamic();

				var shape = physics.Physics.CreateShape(new BoxGeometry(2, 2, 2), material);

				actorA.AttachShape(shape);
				actorB.AttachShape(shape);

				Assert.IsFalse(shape.IsExclusive);
				Assert.AreEqual(shape, actorA.Shapes.ToArray()[0]);
				Assert.AreEqual(shape, actorB.Shapes.ToArray()[0]);

				shape.Dispose();

				Assert.AreEqual(0, actorA.Shapes.Count());
				Assert.AreEqual(0, actorB.Shapes.Count());
			}
		}

		[TestMethod]
		public void DisposeActorWithSharedShape()
		{
			using (var physics = CreatePhysicsAndScene())
			{
				var material = physics.Physics.CreateMaterial(0.1f, 0.1f, 0.1f);

				var actor = physics.Physics.CreateRigidDynamic();

				var shape = physics.Physics.CreateShape(new BoxGeometry(2, 2, 2), material);

				actor.AttachShape(shape);

				actor.Dispose();
			}
		}

		// A bit of a duplicated test, but it's the opposite of the above test and makes it easy to find
		[TestMethod]
		public void DisposeActorWithExclusiveShape()
		{
			using (var physics = CreatePhysicsAndScene())
			{
				var material = physics.Physics.CreateMaterial(0.1f, 0.1f, 0.1f);

				var actor = physics.Physics.CreateRigidDynamic();

				var shape = actor.CreateShape(new BoxGeometry(2, 2, 2), material);

				actor.Dispose();
			}
		}
	}
}
