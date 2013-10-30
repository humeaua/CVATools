//	For list
using System.Collections.Generic;

namespace CVA
{
	public class FileParser
	{
		public List<string> FutureWebsiteToBeCalled;

		public FileParser ()
		{
			FutureWebsiteToBeCalled = new List<string> ();
		}

		public void ParseWorldRanking(ref string cFilePath)
		{
			string cSearchedString = "/players/bio.sps?";
			string cBegin = "href=";
			string cWebsiteName = "http://www.officialworldgolfranking.com/";
			foreach (var line in System.IO.File.ReadAllLines(cFilePath))
			{
				if (line.Contains (cSearchedString)) 
				{
					string cLine = line;
					int iFirst = cLine.IndexOf (cBegin) + cBegin.Length + 1;
					int iLast = cLine.Length - 1;

					string str = cLine.Substring (iFirst, iLast - iFirst);

					FutureWebsiteToBeCalled.Add (cWebsiteName + str);
				}
			}
			System.Console.WriteLine ("Parse World Ranking file done");
		}

		public void ParsePlayer(ref string cFilePath)
		{
			string cSearchedString = "/events/events_scorecard.sps?EventID";
			string cBegin = @"""newsdate"">";
			string cEnd = "</a>&nbsp;</td>";
			foreach (var line in System.IO.File.ReadAllLines(cFilePath)) 
			{
				if (line.Contains (cSearchedString)) 
				{
					int iFirst = line.IndexOf (cBegin) + cBegin.Length + 1;
					int iLast = line.IndexOf (cBegin);

					string cTournamentName = line.Substring (iFirst, iLast - iFirst);
				}
			}
		}
	}
}

