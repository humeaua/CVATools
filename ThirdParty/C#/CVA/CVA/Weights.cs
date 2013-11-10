using System.Collections.Generic; // for list
using System;

namespace CVA
{
	public abstract class Weights
	{
		#region Implementation
		Interpolator sInterpolator;
		#endregion

		public Weights ()
		{}

		public abstract double Weight (double t);
		public abstract double Weight (DateTime sDate); 
	}
}

