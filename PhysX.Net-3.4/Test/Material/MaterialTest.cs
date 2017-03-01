using System;
using System.Collections.Generic;
using System.Linq;
using Microsoft.VisualStudio.TestTools.UnitTesting;

namespace PhysX.Test
{
	[TestClass]
	public class MaterialTest : Test
	{
		[TestMethod]
		public void GetDynamicFriction()
		{
			using (var physics = CreatePhysicsAndScene())
			{
				var material = physics.Physics.CreateMaterial(5, 6, 7);

				Assert.AreEqual(6, material.DynamicFriction);
			}
		}

		[TestMethod]
		public void GetStaticFriction()
		{
			using (var physics = CreatePhysicsAndScene())
			{
				var material = physics.Physics.CreateMaterial(5, 6, 7);

				Assert.AreEqual(5, material.StaticFriction);
			}
		}

		[TestMethod]
		public void GetRestitution()
		{
			using (var physics = CreatePhysicsAndScene())
			{
				var material = physics.Physics.CreateMaterial(5, 6, 7);

				Assert.AreEqual(7, material.Restitution);
			}
		}

		[TestMethod]
		public void GetFlags()
		{
			using (var physics = CreatePhysicsAndScene())
			{
				var material = physics.Physics.CreateMaterial(5, 6, 7);

				material.Flags = MaterialFlag.DisableFriction | MaterialFlag.DisableStrongFriction;

				Assert.IsTrue(material.Flags.HasFlag(MaterialFlag.DisableFriction));
				Assert.IsTrue(material.Flags.HasFlag(MaterialFlag.DisableStrongFriction));
			}
		}

		[TestMethod]
		public void GetFrictionCombineMode()
		{
			using (var physics = CreatePhysicsAndScene())
			{
				var material = physics.Physics.CreateMaterial(5, 6, 7);

				material.FrictionCombineMode = CombineMode.Max;
				Assert.AreEqual(CombineMode.Max, material.FrictionCombineMode);

				material.FrictionCombineMode = CombineMode.Multiply;
				Assert.AreEqual(CombineMode.Multiply, material.FrictionCombineMode);
			}
		}

		[TestMethod]
		public void GetRestitutionCombineMode()
		{
			using (var physics = CreatePhysicsAndScene())
			{
				var material = physics.Physics.CreateMaterial(5, 6, 7);

				material.RestitutionCombineMode = CombineMode.Max;
				Assert.AreEqual(CombineMode.Max, material.RestitutionCombineMode);

				material.RestitutionCombineMode = CombineMode.Multiply;
				Assert.AreEqual(CombineMode.Multiply, material.RestitutionCombineMode);
			}
		}

		[TestMethod]
		public void GetConcreteTypeName()
		{
			using (var physics = CreatePhysicsAndScene())
			{
				var material = physics.Physics.CreateMaterial(5, 6, 7);

				Assert.AreEqual("PxMaterial", material.ConcreteTypeName);
			}
		}
	}
}