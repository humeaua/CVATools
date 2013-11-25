using System;
using System.Runtime.CompilerServices;

namespace Extensions
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

	class MoreDatesFunctions
	{
		public static bool IsLeapYear(long year)
		{
			/*if (year % 400 == 0)
				return true;
			else if (year % 4 == 0 && year % 100 != 0)
				return true;
			return false;*/

			return (year % 400 == 0) || (year % 4 == 0&& year % 100 != 0);
		}

		public static DateTime ChangeDateToBondBasisConvention(ref DateTime date)
		{
			return new DateTime (date.Year, date.Month, Math.Min (30, date.Day), date.Hour, date.Minute, date.Second, date.Millisecond);
		}

		public static DateTime ChangeDateToBondBasisUSConvention(ref DateTime date)
		{
			if (date.Month == 2 && date.Day == 29) {
				// Change day to 30
				return new DateTime (date.Year, date.Month, 30, date.Hour, date.Minute, date.Second, date.Millisecond);
			} else {
				return ChangeDateToBondBasisConvention (ref date);
			}
		}
	}
	/*public DateTime FirstDayOfCurrentWeek()
	{
		return ;
	}*/
}

