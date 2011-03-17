using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Windows.Forms;
using SlimDX;

namespace StillDesign.PhysX.Samples
{
	public partial class TearingCloth : Sample
	{
		private Cloth _cloth;

		private DateTime _keyboardDelay;

		public TearingCloth()
		{
			_keyboardDelay = DateTime.MinValue;

			Run();
		}

		protected override void LoadContent()
		{
			Engine.Camera.View = Matrix.LookAtLH(new Vector3(0, 30, -40), new Vector3(0, 20, 0), new Vector3(0, 1, 0));
		}

		protected override void Update(TimeSpan elapsed)
		{
			ProcessKeyboard();
		}

		protected override void Draw()
		{
			//int n = _cloth.MeshData.NumberOfVertices.Value;

			//var positions = _cloth.MeshData.PositionsStream.GetData<Vector3>();
			//var normals = _cloth.MeshData.NormalsStream.GetData<Vector3>();
			//var indicies = _cloth.MeshData.IndicesStream.GetData<int>();

			//ClothVertex[] vertices = new ClothVertex[ n ];

			//for( int x = 0; x < n; x++ )
			//{
			//    vertices[ x ].Position = positions[ x ];
			//    vertices[ x ].Normal = normals[ x ];
			//}

			//_lighting.TextureEnabled = false;
			//_lighting.World = Matrix.Identity;
			//_lighting.View = _engine.Camera.View;
			//_lighting.Projection = _engine.Camera.Projection;
			//_lighting.LightingEnabled = false;

			//_lighting.Begin();
			//foreach( var pass in _lighting.CurrentTechnique.Passes )
			//{
			//    pass.Begin();
			//    _engine.Device.DrawUserIndexedPrimitives<ClothVertex>( PrimitiveType.TriangleList, vertices, 0, n, indicies, 0, indicies.Length / 3 );
			//    pass.End();
			//}
			//_lighting.End();
		}

		private void ProcessKeyboard()
		{
			if (Engine.Keyboard.IsKeyDown(Keys.Space))
			{
				if (DateTime.Now - _keyboardDelay > TimeSpan.FromMilliseconds(100))
				{
					CreateBox();

					_keyboardDelay = DateTime.Now;
				}
			}
		}
	}
}