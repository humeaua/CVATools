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
			double dResult;
			//	Quick rule --> good for now 
			// need to figure out exactly the ACTACT convention
			dResult = sDate1.Year - sDate2.Year;
			dResult += (sDate1.Month - sDate2.Month) / 12.0;
			dResult += (sDate1.Day - sDate2.Day) / 30.0;

			return dResult;
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

