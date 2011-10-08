using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using PhysX.Math;

namespace PhysX.Test
{
	[TestClass]
	public class DeformableMeshDescTest : Test
	{
		[TestMethod]
		public void SetPrimitivesOfDeformableMeshDesc_Valid_Int()
		{
			var deformableMeshDesc = new DeformableMeshDesc()
			{
				Primitives = new int[5]
			};
		}
		[TestMethod]
		public void SetPrimitivesOfDeformableMeshDesc_Valid_UInt()
		{
			var deformableMeshDesc = new DeformableMeshDesc()
			{
				Primitives = new uint[5]
			};
		}
		[TestMethod]
		public void SetPrimitivesOfDeformableMeshDesc_Valid_Short()
		{
			var deformableMeshDesc = new DeformableMeshDesc()
			{
				Primitives = new short[5]
			};
		}
		[TestMethod]
		public void SetPrimitivesOfDeformableMeshDesc_Valid_UShort()
		{
			var deformableMeshDesc = new DeformableMeshDesc()
			{
				Primitives = new ushort[5]
			};
		}

		[TestMethod]
		public void SetPrimitivesOfDeformableMeshDesc_WrongElementType()
		{
			try
			{
				var deformableMeshDesc = new DeformableMeshDesc()
				{
					Primitives = new double[5]
				};

				Assert.Fail("Should not be able to set primitives to an array of doubles, only int or short are allowed");
			}
			catch (ArgumentException)
			{

			}
		}

		[TestMethod]
		public void SetPrimitivesOfDeformableMeshDesc_ElementTypeNotAValueType() 
		{
			try
			{
				var deformableMeshDesc = new DeformableMeshDesc()
				{
					Primitives = new string[5]
				};

				Assert.Fail("Should not be able to set primitives to an array of string, only int or short are allowed");
			}
			catch (ArgumentException)
			{

			}
		}

		[TestMethod]
		public void SetPrimitivesOfDeformableMeshDesc_Null()
		{
			var deformableMeshDesc = new DeformableMeshDesc()
			{
				Primitives = null
			};
		}
	}
}