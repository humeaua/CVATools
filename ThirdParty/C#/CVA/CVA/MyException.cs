using System;

namespace CVA
{
	// based on http://msdn.microsoft.com/en-us/library/ms173163.aspx
	[Serializable()]
	public class MyException : System.Exception
	{
		public MyException() : base() { }
		public MyException(string message) : base(message) { }
		public MyException(string message, System.Exception inner) : base(message, inner) { }

		// A constructor is needed for serialization when an 
		// exception propagates from a remoting server to the client.  
		protected MyException(System.Runtime.Serialization.SerializationInfo info,
		                                     System.Runtime.Serialization.StreamingContext context) { }
	}
}

