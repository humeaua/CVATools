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

		public Tournament(ref string cFileName)
		{
			LoadFromFile (ref cFileName);
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

		public void LoadFromFile(ref string cFileName)
		{
			// to be written
		}

		public void Add(ref Tuple<string,string> cPlayerName, double dResult)
		{
			sResults.Add (cPlayerName, dResult);
		}

		public void Add(ref Player sPlayer, double dResult)
		{
			sResults.Add (new Tuple<string, string> (sPlayer.GetFirstName(), sPlayer.GetLastName()), dResult);
		}
	}
}

