using System;
using System.Collections.Generic; // for Dictonary and Tuple

namespace CVA
{
	public class Tournament
	{
		private string cTournamentName;
		private DateTime sTournamentDate; 
		private Dictionary<Tuple<string,string>, double> sResults;
		public Tournament (ref string cTournamentName0, ref DateTime sTournamentDate0)
		{
			cTournamentName = cTournamentName0;
			sTournamentDate = sTournamentDate0;
		}

		public string GetName()
		{
			return cTournamentName;
		}

		public DateTime GetDate()
		{
			return sTournamentDate;
		}

		public Dictionary<Tuple<string,string>, double> GetResults()
		{
			return sResults;
		}
	}
}

