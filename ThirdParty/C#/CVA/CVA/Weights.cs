using System.Collections.Generic; // for list
using System; // for DateTime

namespace CVA
{
	public abstract class Weights
	{
		#region Implementation
		Interpolator sInterpolator;
		#endregion

		public Weights()
		{
		}

		public Weights (Interpolator sInterpolator0) // passing by reference does not work --> need to investigate why
		{
			sInterpolator = sInterpolator0;
		}

		public double Weight (double t)
		{
			return Interpolator.Interp (t);
		}

		public Interpolator Interpolator
		{
			get
			{ 
				if (sInterpolator == null)
					sInterpolator = new Interpolator ();
				return sInterpolator;
			}
			set { sInterpolator = value; }
		}

		private double LagInYear(DateTime sDate1, DateTime sDate2)
		{
			return new Coverage().YearFraction (ref sDate1, ref sDate2, EnumBasis.ACTACT);
		}

		private double LagInYearFromToday(DateTime sDate)
		{
			//	Get previous Monday -- date where the ranking has been published 
			int diff = DateTime.Now.DayOfWeek - DayOfWeek.Monday;
			if (diff < 0)
			{
				diff += 7;
			}

			DateTime PreviousMonday = DateTime.Now.AddDays(-diff).Date;
			return LagInYear (PreviousMonday, sDate);
		}

		public double Weight (DateTime sDate)
		{
			return Interpolator.Interp (LagInYearFromToday(sDate));
		}

		protected abstract Interpolator MakeInterpolator ();
	}
}

