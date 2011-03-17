using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading;
using System.Windows.Forms;
using SlimDX;

using ClothVertex = StillDesign.PhysX.Samples.VertexPositionColor;
using Buffer = SlimDX.Direct3D10.Buffer;

namespace StillDesign.PhysX.Samples
{
	public partial class Cloth : Sample
	{
		private StillDesign.PhysX.Cloth _flag;
		private MeshData _flagMeshData;
		private Buffer _vertexBuffer;

		public Cloth()
		{
			
		}

		protected override void LoadContent()
		{

		}

		protected override void Update(TimeSpan elapsed)
		{

		}

		protected override void Draw()
		{
			if(_flagMeshData.NumberOfVertices == null)
				return;

			int n = _flagMeshData.NumberOfVertices.Value;

			var positions = _flagMeshData.PositionsStream.GetData<Vector3>();
			var normals = _flagMeshData.NormalsStream.GetData<Vector3>();
			var indicies = _flagMeshData.IndicesStream.GetData<int>();

			var vertices = new ClothVertex[n];

			for (int i = 0; i < n; i++)
			{
				vertices[i].Position = new Vector4(positions[i], 1);
			}

			Engine.DrawSimple(v)
		}
	}
}