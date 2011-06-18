using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Xml;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using PhysX.Math;

namespace PhysX.Test
{
	[TestClass]
	[DeploymentItem(@"Resources\Teapot.DAE", "Resources")]
	public class DeformableTest : Test
	{
		[TestMethod]
		public void CreateAndDisposeDeformable()
		{
			using (var core = CreatePhysicsAndScene())
			{
				var model = ReadVerticesAndTrianglesFromColladaDoc(@"Resources\Teapot.DAE");

				var meshDesc = new DeformableMeshDesc()
				{
					NumberOfPrimitives = model.Indices.Length / 3,
					NumberOfVertices = model.Vertices.Length,
					PrimitiveType = DeformablePrimitiveType.Triangle,
					Vertices = model.Vertices
				};
				meshDesc.SetPrimitives(model.Indices);

				var cook = core.Physics.CreateCooking();

				var cookedMeshStream = new MemoryStream();

				cook.CookDeformableMesh(meshDesc, cookedMeshStream);

				var mesh = core.Physics.CreateDeformableMesh(cookedMeshStream);

				var desc = new DeformableDesc()
				{
					DeformableMesh = mesh,
					Flags = ActorFlag.Visualization,
					Mass = 10
				};

				Deformable deformable;
				using (deformable = core.Physics.CreateDeformable(desc))
				{
					Assert.IsFalse(deformable.Disposed);
				}

				Assert.IsTrue(deformable.Disposed);
			}
		}

		private Model ReadVerticesAndTrianglesFromColladaDoc(string documentFile)
		{
			var doc = new XmlDocument();
			doc.Load(documentFile);

			var namespaces = new XmlNamespaceManager(doc.NameTable);
			namespaces.AddNamespace("c", "http://www.collada.org/2005/11/COLLADASchema");

			var verticesString = doc.SelectSingleNode("/c:COLLADA/c:library_geometries/c:geometry/c:mesh/c:source/c:float_array", namespaces).InnerText;
			var trianglesString = doc.SelectSingleNode("/c:COLLADA/c:library_geometries/c:geometry/c:mesh/c:triangles/c:p", namespaces).InnerText;

			var model = new Model()
			{
				Indices = trianglesString
					.Split(new[] { ' ', '\n' }, StringSplitOptions.RemoveEmptyEntries)
					.Select(s => int.Parse(s))
					.ToArray(),
				Vertices = StringToVector3Array(verticesString).ToArray()
			};

			return model;
		}
		private IEnumerable<Vector3> StringToVector3Array(string verticesString)
		{
			var vertexElements = verticesString
				.Split(new[] { ' ', '\n' }, StringSplitOptions.RemoveEmptyEntries)
				.Select(v => float.Parse(v))
				.ToArray();

			for (int i = 0; i < vertexElements.Length; i += 3)
			{
				yield return new Vector3
				(
					vertexElements[i + 0], 
					vertexElements[i + 1],
					vertexElements[i + 2]
				);
			}
		}
	}
}