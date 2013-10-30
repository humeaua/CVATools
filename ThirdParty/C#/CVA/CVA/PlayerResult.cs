using System;

namespace CVA
{
	public class PlayerResult
	{
		private string cTournamentName;
		private DateTime sTournamentDate;
		private double dPoint;

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
	}
}

