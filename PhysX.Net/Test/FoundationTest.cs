using System;
using System.Collections.Generic;
using System.Linq;
using Microsoft.VisualStudio.TestTools.UnitTesting;

namespace PhysX.Test
{
	[TestClass]
	public class FoundationTest : Test
	{
		[TestMethod]
		public void CreateAndCleanlyDisposeOfFoundation()
		{
			var error = new ExceptionErrorCallback()
			{
				BadMessages = new[] { "" }
			};

			using (var foundation = new Foundation(error))
			{

			}
		}

		/// <summary>
		/// Releasing a PxFoundation can report an error and not close down successfully. Actions such as
		/// calling PxCloseVehicleSDK() when no corrisponding PxInitVehicleSDK call has been made can cause this.
		/// </summary>
		[TestMethod]
		public void CreateAndCleanlyDisposeOfFoundationWithPhysics()
		{
			var error = new ExceptionErrorCallback()
			{
				BadMessages = new[] { "" }
			};

			using (var foundation = new Foundation(error))
			{
				using (var physics = new Physics(foundation))
				{

				}
			}
		}

		[TestMethod]
		public void OnlyOneInstanceOfFoundationCanExist()
		{
			using (var foundation = new Foundation())
			{
				try
				{
					using (var foundation2 = new Foundation())
					{
						Assert.Fail("Only one instance of Foundation can exist at a time");
					}
				}
				catch (FoundationAlreadyInitalizedException)
				{

				}
				catch
				{
					Assert.Fail("Initalizing a second foundation should throw an error of type " + typeof(FoundationAlreadyInitalizedException).Name);
				}
			}
		}

		private class ExceptionErrorCallback : ErrorCallback
		{
			public string[] BadMessages { get; set; }

			public override void ReportError(ErrorCode errorCode, string message, string file, int lineNumber)
			{
				if (BadMessages.Any(m => message.Contains(m)))
					throw new Exception(message);
			}
		}
	}
}