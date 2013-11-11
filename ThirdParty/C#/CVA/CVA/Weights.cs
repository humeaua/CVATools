using System.Collections.Generic; // for list
using System;

namespace CVA
{
	public abstract class Weights
	{
		#region Implementation
		Interpolator sInterpolator;
		#endregion

		public Weights (Interpolator sInterpolator0)
		{
			sInterpolator = sInterpolator0;
		}

		public double Weight (double t)
		{
			return sInterpolator.Interp (t);
		}

		public double Weight (DateTime sDate)
		{
			//	needs to figure out why this is not working
			//DateTime PreviousMonday = DateTime.Now.StartOfWeek (DayOfWeek.Monday);
			return sInterpolator.Interp (/*PreviousMonday.LagInYear (sDate)*/0);
		}
		protected abstract Interpolator MakeInterpolator ();
	}
}

