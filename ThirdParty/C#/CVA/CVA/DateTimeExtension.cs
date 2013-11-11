using System;
using System.Runtime.CompilerServices;

namespace CVA
{
	public static class DateTimeExtensions
	{
		/*public static DateTime StartOfWeek(this DateTime dt, DayOfWeek startOfWeek)
		{
			int diff = dt.DayOfWeek - startOfWeek;
			if (diff < 0)
			{
				diff += 7;
			}

			return dt.AddDays(-diff).Date;
		}*/

		/*public static double LagInYear(this DateTime dt, DateTime dt0)
		{
			double dResult;
			//	Quick rule --> good for now 
			// need to figure out exactly the ACTACT convention
			dResult = dt.Year - dt0.Year;
			dResult += (dt.Month - dt0.Month) / 12.0;
			dResult += (dt.Day - dt0.Day) / 30.0;

			return dResult;
		}*/
	}

	/*public DateTime FirstDayOfCurrentWeek()
	{
		return ;
	}*/
}

