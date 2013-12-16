//	For list
using System.Collections.Generic;

namespace CVA
{
	public class FileParser
	{
		#region Implementation
		private List<string> FutureWebsiteToBeCalled;
		#endregion

		public FileParser ()
		{
			FutureWebsiteToBeCalled = new List<string> ();
		}

		public List<string> FutureWebsites
		{
			get
			{ 
				return FutureWebsiteToBeCalled;
			}
			set
			{ 
				FutureWebsiteToBeCalled = value;
			}
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

		public void ParsePlayerNew(ref string cFilePath)
		{
			//	Open body

			// 	Open big table 780 * 1218

			//	Open table 780 * 1045

			//	Open central table 485 * 1085

			//	Open centrale table 465 * 1035

			// 	Open table 465 * 728

			//	Readlines one by one


		}

		public void ParsePlayer(ref string cFilePath)
		{
			string cSearchedString = "/events/events_scorecard.sps?EventID";
			string cBegin = @"""newsdate"">";
			//string cEnd = "</a>&nbsp;</td>";
			foreach (var line in System.IO.File.ReadAllLines(cFilePath)) 
			{
				if (line.Contains (cSearchedString)) 
				{
					int iFirst = line.IndexOf (cBegin) + cBegin.Length + 1;
					int iLast = line.IndexOf (cBegin);

					string cTournamentName = line.Substring (iFirst, iLast - iFirst);

				}
			}
			/*
 static void Main(string[] args) {
        String xml = @"
            <transactions>
                <transaction name=""Fred"" amount=""5,20"" />
                <transaction name=""John"" amount=""10,00"" />
                <transaction name=""Fred"" amount=""3,00"" />
            </transactions>";

        XDocument xmlDocument = XDocument.Parse(xml);

        var query = from x in xmlDocument.Descendants("transaction")
                    group x by x.Attribute("name").Value into g
                    select new { Name = g.Key, Amount = g.Sum(t => Decimal.Parse(t.Attribute("amount").Value)) };

        foreach (var item in query) {
            Console.WriteLine("Name: {0}; Amount: {1:C};", item.Name, item.Amount);
        }
    }
			 */
		}
	}
}

