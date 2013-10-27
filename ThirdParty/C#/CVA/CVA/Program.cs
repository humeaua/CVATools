namespace CVA
{
	class MainClass
	{
		public static void Main (string[] args)
		{
			System.Console.WriteLine ("Welcome !");
			CVA.InternetPageReader sInternetPageReader = new CVA.InternetPageReader ();
			string cWebsite = "http://www.officialworldgolfranking.com/rankings/default.sps";
			string cFileName = "/Users/alexhum49/Documents/Workspace/CVA/CVATools/Input/OfficialWorldGolfRankingHomePage.htm";
			sInternetPageReader.ToTextFile (ref cWebsite,
			                                ref cFileName);

			//	Parse file of WorldRanking
			CVA.FileParser sFileParser = new CVA.FileParser ();
			sFileParser.ParseWorldRanking (ref cFileName);
			foreach (string c in sFileParser.FutureWebsiteToBeCalled) 
			{
				System.Console.WriteLine (c);
			}

			System.Console.WriteLine ("Good bye !");
		}
	}
}
