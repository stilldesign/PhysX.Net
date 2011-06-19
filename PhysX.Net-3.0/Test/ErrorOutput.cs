using System;
using System.Collections.Generic;
using System.Linq;

namespace PhysX.Test
{
	public class ErrorLog : PhysX.ErrorCallback
	{
		private List<string> _errors;

		public ErrorLog()
		{
			_errors = new List<string>();
		}

		public override void ReportError(ErrorCode errorCode, string message, string file, int lineNumber)
		{
			_errors.Add(string.Format("Code: {0}, Message: {1}", errorCode, message));
		}
	}
}