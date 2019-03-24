using System;
using System.Collections.Generic;
using System.Linq;
using System.Numerics;
using Buffer = SharpDX.Direct3D11.Buffer;

namespace PhysX.Samples.Engine
{
	public class Model
	{
		public Buffer VertexBuffer { get; set; }
		public Buffer IndexBuffer { get; set; }
		public int IndexCount { get; set; }

		public Vector3[] VertexPositions { get; set; }
		public int[] Indices { get; set; }
	}
}