using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using Microsoft.Xna.Framework.Graphics;
using StillDesign.PhysX.MathPrimitives;

namespace StillDesign.PhysX.Samples
{
	public static class Convex
	{
		public static Actor LoadConvexMesh( Scene scene, Model model )
		{
			Core core = scene.Core;

			ModelMesh mesh = model.Meshes.First();

			var transforms = new Microsoft.Xna.Framework.Matrix[ model.Bones.Count ];
			model.CopyAbsoluteBoneTransformsTo( transforms );

			// Gets the vertices from the mesh
			VertexPositionNormalTexture[] vertices = new VertexPositionNormalTexture[ mesh.MeshParts[ 0 ].NumVertices ];
			mesh.VertexBuffer.GetData<VertexPositionNormalTexture>( vertices );

			//

			// Allocate memory for the points and triangles
			var convexMeshDesc = new ConvexMeshDescription()
			{
				PointCount = vertices.Length
			};
			convexMeshDesc.Flags |= ConvexFlag.ComputeConvex;
			convexMeshDesc.AllocatePoints<Vector3>( vertices.Length );

			// Write in the points and triangles
			// We only want the Position component of the vertex. Also scale down the mesh
			foreach( VertexPositionNormalTexture vertex in vertices )
			{
				var t = Microsoft.Xna.Framework.Matrix.CreateScale( 0.1f, 0.1f, 0.1f ) * transforms[ 0 ];
				var position = Microsoft.Xna.Framework.Vector3.Transform( vertex.Position, t );

				convexMeshDesc.PointsStream.Write( position );
			}

			//

			// Cook to memory or to a file
			ConvexMesh convexMesh;
			using( MemoryStream stream = new MemoryStream() )
			{
				//FileStream stream = new FileStream( @"Convex Mesh.cooked", FileMode.CreateNew );

				Cooking.InitializeCooking( new ConsoleOutputStream() );
				Cooking.CookConvexMesh( convexMeshDesc, stream );
				Cooking.CloseCooking();

				stream.Position = 0;

				convexMesh = core.CreateConvexMesh( stream );
			}
			ConvexShapeDescription convexShapeDesc = new ConvexShapeDescription( convexMesh );

			ActorDescription actorDesc = new ActorDescription()
			{
				BodyDescription = new BodyDescription( 10.0f ),
				GlobalPose = Matrix.Translation( 30, 30, 0 )
			};
			actorDesc.Shapes.Add( convexShapeDesc );

			return scene.CreateActor( actorDesc );
		}
	}
}