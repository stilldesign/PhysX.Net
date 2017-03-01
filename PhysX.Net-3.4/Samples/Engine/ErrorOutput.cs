using System;
using System.Collections.Generic;

namespace PhysX.Samples
{
	public class ErrorOutput : ErrorCallback
	{
		public override void ReportError(ErrorCode errorCode, string message, string file, int lineNumber)
		{
			Console.WriteLine("PhysX: " + message);
		}
	}
}