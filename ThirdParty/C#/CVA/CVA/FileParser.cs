//	For list
using System.Collections.Generic;

namespace CVA
{
	public class FileParser
	{
		public System.Collections.Generic.List<string> FutureWebsiteToBeCalled;

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
	}
}

