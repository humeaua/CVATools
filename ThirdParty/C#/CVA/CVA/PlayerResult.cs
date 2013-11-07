using System;

namespace CVA
{
	public class PlayerResult
	{
		#region Implementation
		private string cTournamentName;
		private DateTime sTournamentDate;
		private double dPoint;
		#endregion

		public PlayerResult()
		{}

		public PlayerResult (ref string cTournamentName0, ref DateTime sTournamentDate0, ref double dPoint0)
		{
			cTournamentName = cTournamentName0;
			sTournamentDate = sTournamentDate0;
			dPoint = dPoint0;
		}

		public static bool operator < (PlayerResult sLeft, PlayerResult sRight)
		{
			return sLeft.sTournamentDate < sRight.sTournamentDate;
		}

		public static bool operator > (PlayerResult sLeft, PlayerResult sRight)
		{
			return sLeft.sTournamentDate > sRight.sTournamentDate;
		}

		public double Point
		{
			get 
			{
				return dPoint;
			}
			set 
			{
				dPoint = value;
			}
		}

		public string Name
		{
			get 
			{
				return cTournamentName;
			}
			set 
			{
				cTournamentName = value;
			}
		}

		public DateTime Date
		{
			get 
			{
				return sTournamentDate;
			}
			set 
			{
				sTournamentDate = value;
			}
		}
	}
}

