using System;
using System.Collections.Generic;
using System.Linq;

namespace PhysX.Test
{
	public class PhysicsAndSceneTestUnit : System.IDisposable
	{
		public Foundation Foundation { get; set; }
		public Physics Physics { get; set; }
		public Scene Scene { get; set; }
		public ErrorLog ErrorOutput { get; set; }

		#region IDisposable Members

		public void Dispose()
		{
			if (Foundation != null && !Foundation.Disposed)
				Foundation.Dispose();

			Foundation = null;
			Physics = null;
			Scene = null;
			ErrorOutput = null;
		}

		#endregion
	}
}